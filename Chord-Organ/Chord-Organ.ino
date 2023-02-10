#include <Bounce2.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <EEPROM.h>
#include <math.h>

#include "Settings.h"
#include "Waves.h"
#include "teensy.h"
#include "midi.h"
#include "organ.h"

// #define DEBUG_STARTUP
// #define DEBUG_MODE
// #define CHECK_CPU

// For arbitrary waveform, required but unused apparently.
#define MAX_FREQ 600

#define SHORT_PRESS_DURATION 10
#define LONG_PRESS_DURATION 1000

Organ organ;
Control control;

// Current waveform index
int waveform = 0; 

// Waveform LED
boolean flashingWave = false;
elapsedMillis waveformIndicatorTimer = 0;

int waveformPage = 0;
int waveformPages = 1;

// Custom wavetables
int16_t const* waveTables[8] {
    wave1,
    wave7,
    wave3,
    wave4,    
    wave8,
    wave9,
    wave10,
    wave11
};


// GLIDE
// Main flag for glide on / off
boolean glide = false;
// msecs glide time. 
uint32_t glideTime = 50;
// keep reciprocal
float oneOverGlideTime = 0.02;
// Time since glide started
elapsedMillis glideTimer = 0;
// Are we currently gliding notes
boolean gliding = false;

// Stack mode replicates first 4 voices into last 4 with tuning offset
boolean stacked = false;
float stackFreqScale = 1.001;

int noteRange = 38;

// GUItool: begin automatically generated code

AudioSynthWaveform       waveform1;      //xy=215,232
AudioSynthWaveform       waveform2;      //xy=243,295
AudioSynthWaveform       waveform3;      //xy=273,354
AudioSynthWaveform       waveform4;      //xy=292,394
AudioSynthWaveform       waveform5;      //xy=215,232
AudioSynthWaveform       waveform6;      //xy=243,295
AudioSynthWaveform       waveform7;      //xy=273,354
AudioSynthWaveform       waveform8;      //xy=292,394
AudioMixer4              mixer1;         //xy=424,117
AudioMixer4              mixer2;         //xy=424,181
AudioMixer4              mixer3;         //xy=571,84
AudioEffectEnvelope      envelope1;      //xy=652,281
AudioOutputAnalog        dac1;           //xy=784,129
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord7(waveform3, 0, mixer1, 2);
AudioConnection          patchCord8(waveform4, 0, mixer1, 3);
AudioConnection          patchCord3(waveform5, 0, mixer2, 0);
AudioConnection          patchCord4(waveform6, 0, mixer2, 1);
AudioConnection          patchCord5(waveform7, 0, mixer2, 2);
AudioConnection          patchCord6(waveform8, 0, mixer2, 3);
AudioConnection          patchCord9(mixer1, 0, mixer3, 0);
AudioConnection          patchCord10(mixer2, 0, mixer3, 1);
AudioConnection          patchCord11(mixer3, envelope1);
AudioConnection          patchCord12(envelope1, dac1);
// GUItool: end automatically generated code
// Pointers to waveforms
AudioSynthWaveform* oscillator[8];

Settings settings("CHORDORG.TXT");

void setup(){
    pinMode(BANK_BUTTON,INPUT);
    pinMode(RESET_BUTTON, INPUT);
    pinMode(RESET_CV, INPUT); 
    pinMode(RESET_LED, OUTPUT);
    pinMode(LED0,OUTPUT);
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    AudioMemory(50);
    analogReadRes(ADC_BITS);
    
    oscillator[0] = &waveform1;
    oscillator[1] = &waveform2;
    oscillator[2] = &waveform3;
    oscillator[3] = &waveform4;
    oscillator[4] = &waveform5;
    oscillator[5] = &waveform6;
    oscillator[6] = &waveform7;
    oscillator[7] = &waveform8;

    // SD CARD SETTINGS FOR MODULE 
    SPI.setMOSI(7);
    SPI.setSCK(14);

    // Read waveform settings from EEPROM 
    waveform = EEPROM.read(1234);

    if (waveform < 0) waveform = 0;
    ledWrite(waveform % 4);

    // OPEN SD CARD 
    boolean hasSD = openSDCard();

    // READ SETTINGS FROM SD CARD 
    settings.init(hasSD);

    organ.chordCount = settings.numChords;
    waveformPages = settings.extraWaves ? 3 : 1;
    if(waveformPages > 1) {
        waveformPage = waveform >> 2;
    } else {
        // If we read a custom waveform index from EEPROM
        // but they are not enabled in the config then change back to sine
        waveform = 0;
    }
    
    glide = settings.glide;
    glideTime = settings.glideTime;
    oneOverGlideTime = 1.0 / (float) glideTime;
    noteRange = settings.noteRange;
    stacked = settings.stacked;

    // Setup audio
    for(int i=0;i<SINECOUNT;i++) {
        oscillator[i]->pulseWidth(0.5);
    }

    for(int m=0;m<4;m++) {
        mixer1.gain(m,0.25);
        mixer2.gain(m,0.25);
    }

    mixer3.gain(0,0.49);
    mixer3.gain(1,0.49);
    mixer3.gain(2,0);
    mixer3.gain(3,0);

    envelope1.attack(1);
    envelope1.decay(1);
    envelope1.sustain(1.0);
    envelope1.release(1);
    envelope1.noteOn();

    if(waveformPage == 0) {
        // First page is built in waveforms
        setWaveformType(organ.wave_type[waveform]);
    } else {
        // Second and third pages are arbitrary waves
        setupCustomWaveform(waveform);
        // Start the wave led flashing
        flashingWave = true;
        waveformIndicatorTimer = 0;
    }
}

boolean openSDCard() {
    int crashCountdown = 0; 
    if (!(SD.begin(10))) {
        while (!(SD.begin(10))) {
            ledWrite(15);
            delay(20);
            ledWrite(crashCountdown % 4);
            delay(20);
            crashCountdown++;
            if (crashCountdown > 4) {
                return false;
            }
        }
    }
    return true;
}

void loop(){

    checkInterface();

    if (control.changed) {
        updateAmpAndFreq();
        if(glide) {
            glideTimer = 0;
            gliding = true;
        }

        #ifdef CHECK_CPU
        int maxCPU = AudioProcessorUsageMax();
        Serial.print("MaxCPU=");
        Serial.println(maxCPU);
        #endif // CHECK_CPU
    }

    // CHECK BUTTON STATUS 
    control.resetHold = control.resetHold * control.resetButton;

    if (control.shortPress){
        waveform++;
        waveform = waveform % (4 * waveformPages);
        selectWaveform(waveform);
        control.changed = true;
        control.shortPress = false;
    }

    if (control.changed)  {
        // Serial.println("Trig Out");
        control.pulseOutTimer = 0;
        control.flashing = true;
        pinMode(RESET_CV, OUTPUT);
        digitalWrite (RESET_LED, HIGH);
        digitalWrite (RESET_CV, HIGH);

        AudioNoInterrupts();
        updateFrequencies();
        updateAmps(organ.AMP, organ.WAVEFORM_AMP);
        AudioInterrupts();

        control.changed = false;
    }

    if(gliding) {
        if(glideTimer >= glideTime) {
            gliding = false;
        }
        AudioNoInterrupts();
        updateFrequencies();
        AudioInterrupts();
    }

    updateWaveformLEDs();

    if (control.flashing && (control.pulseOutTimer > control.flashTime)) {
        digitalWrite (RESET_LED, LOW);
        digitalWrite (RESET_CV, LOW);
        pinMode(RESET_CV, INPUT);
        control.flashing = false;  
    } 
}

void updateAmpAndFreq() {
    int16_t* chord = settings.notes[control.chordQuant];

    int noteNumber;
    int voiceCount = 0;
    int halfSinecount = SINECOUNT>>1;

    if(stacked) {
        for(int i=0;i < halfSinecount;i++) {
            if (chord[i] != 255) {
                noteNumber = control.rootQuant + chord[i];
                if(noteNumber < 0) noteNumber = 0;
                if(noteNumber > 127) noteNumber = 127;
                float newFreq = midi_to_freq[noteNumber];

                organ.FREQ[i] = newFreq;
                organ.FREQ[i+halfSinecount] = newFreq * stackFreqScale;

                organ.deltaFrequency[i] = newFreq - organ.currentFrequency[i];
                organ.deltaFrequency[i+halfSinecount] = (newFreq * stackFreqScale) - organ.currentFrequency[i];

                voiceCount += 2;
            }            
        }
    } else {
        for(int i = 0; i< SINECOUNT; i++){
            if (chord[i] != 255) {
                noteNumber = control.rootQuant + chord[i];
                if(noteNumber < 0) noteNumber = 0;
                if(noteNumber > 127) noteNumber = 127;
                
                float newFreq = midi_to_freq[noteNumber];
                organ.deltaFrequency[i] = newFreq - organ.currentFrequency[i];
                organ.FREQ[i] = newFreq;
                voiceCount++;
            }
        }

    }

    float ampPerVoice = organ.AMP_PER_VOICE[voiceCount-1];
    float totalAmp = 0;

    if(stacked) {
        for (int i = 0; i < halfSinecount; i++){
            if (chord[i] != 255) {
                organ.AMP[i] = ampPerVoice;
                organ.AMP[i + halfSinecount] = ampPerVoice; 
                totalAmp += ampPerVoice;
            }
            else{
                organ.AMP[i] = 0.0;   
            }
        }        
    } else {
        for (int i = 0; i< SINECOUNT; i++){
            if (chord[i] != 255) {
                organ.AMP[i] = ampPerVoice;
                totalAmp += ampPerVoice;
            }
            else{
                organ.AMP[i] = 0.0;   
            }
        }        
    }
}

void selectWaveform(int waveform) {
    waveformPage = waveform >> 2;
    if(waveformPage > 0) {
        flashingWave = true;
        waveformIndicatorTimer = 0;
    }  
    ledWrite(waveform % 4);
    EEPROM.write(1234, waveform);

    #ifdef DEBUG_MODE
    Serial.print("Waveform ");
    Serial.println(waveform);
    Serial.print("Waveform page ");
    Serial.println(waveformPage);
    #endif // DEBUG_MODE

    AudioNoInterrupts();
    if(waveformPage == 0) {
        setWaveformType(organ.wave_type[waveform]);
    } else {
        setupCustomWaveform(waveform);    
    }
    AudioInterrupts();    
}

void setWaveformType(short waveformType) {
    for(int i=0;i<SINECOUNT;i++) {
        oscillator[i]->begin(1.0, organ.FREQ[i], waveformType);
    }   
}

void setupCustomWaveform(int waveselect) {
    waveselect = (waveselect - 4) % 8;

    const int16_t* wave = waveTables[waveselect];
    for(int i=0;i<SINECOUNT;i++) {
        oscillator[i]->arbitraryWaveform(wave, MAX_FREQ);
    }

    setWaveformType(WAVEFORM_ARBITRARY);
}

void updateWaveformLEDs() {
    // Flash waveform LEDs for custom waves
    if(waveformPage > 0) {
        uint32_t blinkTime = 100 + ((waveformPage - 1) * 300);
        if(waveformIndicatorTimer >= blinkTime) {
            waveformIndicatorTimer = 0;
            flashingWave = !flashingWave;
            if(flashingWave) {
                ledWrite(waveform % 4);
            } else {
                ledWrite(15);
            }
        }
    }    
}

void updateFrequencies() {

    if(gliding) {
        // TODO : Replace division with reciprocal multiply.
        float dt = 1.0 - (glideTimer * oneOverGlideTime);
        if(dt < 0.0) {
            dt = 0.0;
            gliding = false;
        }

        for(int i=0;i<SINECOUNT;i++) {
            organ.currentFrequency[i] = organ.FREQ[i] - (organ.deltaFrequency[i] * dt);
            oscillator[i]->frequency(organ.currentFrequency[i]);
        }
    } else {
        for(int i=0;i<SINECOUNT;i++) {
            oscillator[i]->frequency(organ.FREQ[i]);
        }
    }
}

void updateAmps(float* AMP, float* WAVEFORM_AMP){
    float waveAmp = WAVEFORM_AMP[waveform];
    mixer1.gain(0,AMP[0] * waveAmp);
    mixer1.gain(1,AMP[1] * waveAmp);
    mixer1.gain(2,AMP[2] * waveAmp);
    mixer1.gain(3,AMP[3] * waveAmp);
    mixer2.gain(0,AMP[4] * waveAmp);
    mixer2.gain(1,AMP[5] * waveAmp);
    mixer2.gain(2,AMP[6] * waveAmp);
    mixer2.gain(3,AMP[7] * waveAmp);
}

// WRITE A 4 DIGIT BINARY NUMBER TO LED0-LED3 
void ledWrite(int n){
    digitalWrite(LED3, HIGH && (n==0));
    digitalWrite(LED2, HIGH && (n==1));
    digitalWrite(LED1, HIGH && (n==2));
    digitalWrite(LED0, HIGH && (n==3)); 
}

void checkInterface(){

    // Read pots + CVs
    int chordPot = analogRead(CHORD_POT_PIN); 
    int chordCV = analogRead(CHORD_CV_PIN); 
    int rootPot = analogRead(ROOT_POT_PIN); 
    int rootCV = analogRead(ROOT_CV_PIN); 

    // Copy pots and CVs to new value 
    control.chordRaw = chordPot + chordCV; 
    control.chordRaw = constrain(control.chordRaw, 0, ADC_MAX_VAL - 1);

    rootPot = constrain(rootPot, 0, ADC_MAX_VAL - 1);
    rootCV = constrain(rootCV, 0, ADC_MAX_VAL - 1);

    control.rootChanged = false;
    // Apply hysteresis and filtering to prevent jittery quantization 
    // Thanks to Matthias Puech for this code 

    if ((control.chordRaw > control.chordRawOld + CHANGE_TOLERANCE) || (control.chordRaw < control.chordRawOld - CHANGE_TOLERANCE)){
        control.chordRawOld = control.chordRaw;    
    }
    else {
        control.chordRawOld += (control.chordRaw - control.chordRawOld) >>5; 
        control.chordRaw = control.chordRawOld;  
    }

    // Do Pot and CV separately
    if ((rootPot > control.rootPotOld + CHANGE_TOLERANCE) || (rootPot < control.rootPotOld - CHANGE_TOLERANCE)){
        control.rootPotOld = rootPot;
        control.rootChanged = true;
    }
    else {
        control.rootPotOld += (rootPot - control.rootPotOld) >>5;
        rootPot = control.rootPotOld;
    }
    
    if ((rootCV > control.rootCVOld + CHANGE_TOLERANCE) || (rootCV < control.rootCVOld - CHANGE_TOLERANCE)){
        control.rootCVOld = rootCV;
        control.rootChanged = true;
    }
    else {
        control.rootCVOld += (rootCV - control.rootCVOld) >>5;
        rootCV = control.rootCVOld;
    }

    control.chordQuant = map(control.chordRaw, 0, ADC_MAX_VAL, 0, organ.chordCount);
    if (control.chordQuant != control.chordQuantOld){
        control.changed = true; 
        control.chordQuantOld = control.chordQuant;    
    }

    // Map ADC reading to Note Numbers
    int rootCVQuant = ceil(rootCV * midi_note_factor) + LOW_NOTE;
    
    // Use Pot as transpose for CV
    int rootPotQuant = map(rootPot,0,ADC_MAX_VAL,0,48);
    control.rootQuant = rootCVQuant + rootPotQuant;
    if (control.rootQuant != control.rootQuantOld){
       control.changed = true; 
       control.rootQuantOld = control.rootQuant;  
    }

    int buttonState = digitalRead(RESET_BUTTON);
    if (control.buttonTimer > SHORT_PRESS_DURATION && buttonState == 0 && control.lockOut > 999 ){
        control.shortPress = true;    
    }

    control.buttonTimer = control.buttonTimer * buttonState; 
    if (control.buttonTimer > LONG_PRESS_DURATION){
        control.longPress = true;
        control.lockOut = 0;
        control.buttonTimer = 0;
    }

    if (!control.flashing){
        control.resetCV.update();
        control.resetCVRose = control.resetCV.rose();
        if (control.resetCVRose) control.resetFlash = 0; 

        digitalWrite(RESET_LED, (control.resetFlash<20));
    }

}

void reBoot(int delayTime){
    if (delayTime > 0)
        delay (delayTime);
    WRITE_RESTART(0x5FA0004);
}
