#include <EEPROM.h>
#include <math.h>

#include "Settings.h"
#include "teensy.h"
#include "organ.h"
#include "synth.h"
#include "j6_chords.h"

// #define DEBUG_STARTUP
// #define DEBUG_MODE
// #define CHECK_CPU

#define SHORT_PRESS_DURATION 10
#define LONG_PRESS_DURATION 1000

Settings settings("CHORDORG.TXT");
Organ organ;
Control control;
Synth synth;

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

    // SD CARD SETTINGS FOR MODULE 
    SPI.setMOSI(7);
    SPI.setSCK(14);

    // OPEN SD CARD 
    boolean hasSD = openSDCard();

    // READ SETTINGS FROM SD CARD 
    settings.init(hasSD);

    //Setup Synth
    synth.init();

    // Read waveform settings from EEPROM 
    synth.waveform_index = EEPROM.read(1234);
    if (synth.waveform_index < 0) synth.waveform_index = 0;
    ledWrite(synth.waveform_index);
    synth.set_waveform(organ.freq);

    //Setup Organ
    organ.init(settings);
}

void loop(){

    checkInterface();
    int16_t* chord = (settings.custom_chords) ? settings.notes[organ.chord] : genre_chords[organ.genre][organ.chord];

    // CHECK BUTTON STATUS 
    control.reset_hold = control.reset_hold * control.resetButton;

    if (control.short_press){
        synth.waveform_index++;
        synth.waveform_index = synth.waveform_index % (synth.num_waves);
        ledWrite(synth.waveform_index);
        EEPROM.write(1234, synth.waveform_index);
        AudioNoInterrupts();
        synth.set_waveform(organ.freq);
        AudioInterrupts();    
        control.changed = true;
        control.short_press = false;
    }

    if (control.changed)  {
        // Serial.println("Trig Out");
        control.pulse_out_timer = 0;
        control.flashing = true;
        pinMode(RESET_CV, OUTPUT);
        digitalWrite (RESET_LED, HIGH);
        digitalWrite (RESET_CV, HIGH);

        if(organ.glide) {
            organ.glideTimer = 0;
            organ.gliding = true;
        }
        int voice_count = organ.update_frequencies(chord);
        synth.update_amps(voice_count, organ.stacked, chord);

        AudioNoInterrupts();
        float* current_frequency = organ.get_current_frequency();
        synth.set_frequencies(current_frequency);
        //updateFrequencies();
        synth.update_mixers();
        //updateAmps(organ.AMP, organ.WAVEFORM_AMP);
        AudioInterrupts();

        control.changed = false;
    }

    if(organ.gliding) {
        if(organ.glideTimer >= organ.glide_time) {
            organ.gliding = false;
        }
        AudioNoInterrupts();
        float* current_frequency = organ.get_current_frequency();
        synth.set_frequencies(current_frequency);
        AudioInterrupts();
    }

    if (control.flashing && (control.pulse_out_timer > control.flash_time)) {
        digitalWrite (RESET_LED, LOW);
        digitalWrite (RESET_CV, LOW);
        pinMode(RESET_CV, INPUT);
        control.flashing = false;  
    } 
}

void checkInterface(){
    // Read pots + CVs
    int chordPot = analogRead(CHORD_POT_PIN); 
    int chordCV = analogRead(CHORD_CV_PIN); 
    int rootPot = analogRead(ROOT_POT_PIN); 
    int rootCV = analogRead(ROOT_CV_PIN); 

    rootPot = constrain(rootPot, 0, ADC_MAX_VAL - 1);
    rootCV = constrain(rootCV, 0, ADC_MAX_VAL - 1);

    // Apply hysteresis and filtering to prevent jittery quantization 
    // Thanks to Matthias Puech for this code 

    if (settings.custom_chords) {
        // Copy pots and CVs to new value 
        int chord_total = chordPot + chordCV; 
        chord_total = constrain(chord_total, 0, ADC_MAX_VAL - 1);

        if ((chord_total > control.chordRawOld + CHANGE_TOLERANCE) || (chord_total < control.chordRawOld - CHANGE_TOLERANCE)){
            control.chordRawOld = chord_total;    
        }
        else {
            control.chordRawOld += (chord_total - control.chordRawOld) >>5; 
            chord_total = control.chordRawOld;  
        }

        organ.chord = map(chord_total, 0, ADC_MAX_VAL, 0, organ.chord_count);

    } else {
        chordPot = constrain(chordPot, 0, ADC_MAX_VAL - 1);
        chordCV = constrain(chordCV, 0, ADC_MAX_VAL - 1);

        if ((chordCV > control.chordCVOld + CHANGE_TOLERANCE) || (chordCV < control.chordCVOld - CHANGE_TOLERANCE)){
            control.chordCVOld = chordCV;
        }
        else {
            control.chordCVOld += (chordCV - control.chordCVOld) >>5;
            chordCV = control.chordCVOld;
        }
        
        if ((chordPot > control.chordPotOld + CHANGE_TOLERANCE) || (chordPot < control.chordPotOld - CHANGE_TOLERANCE)){
            control.chordPotOld = chordPot;
        }
        else {
            control.chordPotOld += (chordPot - control.chordPotOld) >>5;
            chordPot = control.chordPotOld;
        }

        // Map ADC reading to Note Numbers
        int chordCVQuant = ceil(chordCV * midi_note_factor);
        int scale = chordCVQuant / 12;
        organ.chord_transpose = scale * 12; //map(chordCVQuant, 0, 40, 0, 3) * 12;
        organ.chord = chordCVQuant % 12;
        
        // Use Pot as genre selector
        organ.genre = map(chordPot, 0, ADC_MAX_VAL, 0, genre_count - 1);
    }

    if (organ.chord != organ.chord_old || organ.genre != organ.genre_old){
        control.changed = true; 
        organ.chord_old = organ.chord; 
        organ.genre_old = organ.genre;   
    }

    // Do Pot and CV separately
    if ((rootPot > control.rootPotOld + CHANGE_TOLERANCE) || (rootPot < control.rootPotOld - CHANGE_TOLERANCE)){
        control.rootPotOld = rootPot;
    }
    else {
        control.rootPotOld += (rootPot - control.rootPotOld) >>5;
        rootPot = control.rootPotOld;
    }
    
    if ((rootCV > control.rootCVOld + CHANGE_TOLERANCE) || (rootCV < control.rootCVOld - CHANGE_TOLERANCE)){
        control.rootCVOld = rootCV;
    }
    else {
        control.rootCVOld += (rootCV - control.rootCVOld) >>5;
        rootCV = control.rootCVOld;
    }

    // Map ADC reading to Note Numbers
    int rootCVQuant = ceil(rootCV * midi_note_factor) + LOW_NOTE;
    
    // Use Pot as transpose for CV
    int rootPotQuant = map(rootPot, 0, ADC_MAX_VAL, 0, 48);
    organ.root = rootCVQuant + rootPotQuant;
    if (organ.root != organ.root_old){
       control.changed = true; 
       organ.root_old = organ.root;  
    }

    int buttonState = digitalRead(RESET_BUTTON);
    if (control.button_timer > SHORT_PRESS_DURATION && buttonState == 0 && control.lock_out > 999 ){
        control.short_press = true;    
    }

    control.button_timer = control.button_timer * buttonState; 
    if (control.button_timer > LONG_PRESS_DURATION){
        control.long_press = true;
        control.lock_out = 0;
        control.button_timer = 0;
    }

    if (!control.flashing){
        control.reset_cv.update();
        control.reset_cv_rose = control.reset_cv.rose();
        if (control.reset_cv_rose) control.reset_flash = 0; 

        digitalWrite(RESET_LED, (control.reset_flash<20));
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

// WRITE A 4 DIGIT BINARY NUMBER TO LED0-LED3 
void ledWrite(int n){
    digitalWrite(LED3, (n >> 3) & 1);
    digitalWrite(LED2, (n >> 2) & 1);
    digitalWrite(LED1, (n >> 1) & 1);
    digitalWrite(LED0, (n >> 0) & 1); 
}
