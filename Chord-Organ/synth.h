#include <Audio.h>
#include <Wire.h>

#include "Waves.h"

// For arbitrary waveform, required but unused apparently.
#define MAX_FREQ 600

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

typedef struct synth {
    
    static const int oscillator_num = 8;
    // GUItool: end automatically generated code
    // Pointers to waveforms
    AudioSynthWaveform* oscillator[oscillator_num];

    int num_waves = 16;

    // Current waveform index
    int waveform_index = 0; 

    // Custom wavetables
    int16_t const* wave_tables[12] {
        wave0,
        wave1,
        wave2,
        wave3,
        wave4,
        wave5,
        wave6,
        wave7,
        wave8,    
        wave9,
        wave10,
        wave11
    };

    // Per-waveform amp level
    // First 4 are default waves, last 8 are custom wavetables
    float waveform_amp[16] = {
        0.8,0.6,0.8,0.6,
        0.8,0.8,0.8,0.8,
        0.8,0.8,0.8,0.8,
        0.8,0.8,0.8,0.8,
    };

    float amp[oscillator_num] = { 0.9, 0.9, 0.9, 0.9,0.9, 0.9, 0.9, 0.9};

    // Volume for a single voice for each chord size
    float amp_per_voice[oscillator_num] = {0.4,0.3,0.22,0.2,0.15,0.15,0.13,0.12};

    void init() {
        setup_oscillator();
        setup_mixer();
        setup_envelope();
    }

    void setup_oscillator() {
        oscillator[0] = &waveform1;
        oscillator[1] = &waveform2;
        oscillator[2] = &waveform3;
        oscillator[3] = &waveform4;
        oscillator[4] = &waveform5;
        oscillator[5] = &waveform6;
        oscillator[6] = &waveform7;
        oscillator[7] = &waveform8;

        // Setup audio
        for(int i = 0; i < oscillator_num; i++) {
            oscillator[i]->pulseWidth(0.5);
        }
    }

    void setup_mixer() {
        for(int m = 0; m < 4; m++) {
            mixer1.gain(m,0.25);
            mixer2.gain(m,0.25);
        }

        mixer3.gain(0,0.49);
        mixer3.gain(1,0.49);
        mixer3.gain(2,0);
        mixer3.gain(3,0);
    }

    void setup_envelope() {
        envelope1.attack(1);
        envelope1.decay(1);
        envelope1.sustain(1.0);
        envelope1.release(1);
        envelope1.noteOn();
    }

    void set_waveform(float* frequency) {
        if (waveform_index < 4) set_default_waveform(waveform_index, frequency);
        else set_custom_waveform(waveform_index, frequency);
    }

    void set_default_waveform(short wave_select, float* frequency) {
        for(int i = 0;i < oscillator_num; i++) {
            oscillator[i]->begin(1.0, frequency[i], wave_select);
        }   
    }

    void set_custom_waveform(short wave_select, float* frequency) {
        wave_select = (wave_select - 4) % 12;

        const int16_t* wave = wave_tables[wave_select];
        for(int i = 0; i < oscillator_num; i++) {
            oscillator[i]->arbitraryWaveform(wave, MAX_FREQ);
        }

        set_default_waveform(WAVEFORM_ARBITRARY, frequency);
    }

    void set_frequencies(float* frequency) {
        for(int i = 0; i < oscillator_num; i++) {
            oscillator[i]->frequency(frequency[i]);
        }
    }

    void update_amps(int voice_count, boolean is_stacked, int16_t* chord) {
        float voice_amp = amp_per_voice[voice_count-1];
        int half_oscillator_count = oscillator_num >> 1;
        float total_amp = 0;

        if(is_stacked) {
            for (int i = 0; i < half_oscillator_count; i++){
                if (chord[i] != 255) {
                    amp[i] = voice_amp;
                    amp[i + half_oscillator_count] = voice_amp; 
                    total_amp += voice_amp;
                }
                else{
                    amp[i] = 0.0;   
                }
            }        
        } else {
            for (int i = 0; i< 8; i++){
                if (chord[i] != 255) {
                    amp[i] = voice_amp;
                    total_amp += voice_amp;
                }
                else{
                    amp[i] = 0.0;   
                }
            }        
        }
    }

    void update_mixers(){
        float waveAmp = waveform_amp[waveform_index];
        mixer1.gain(0,amp[0] * waveAmp);
        mixer1.gain(1,amp[1] * waveAmp);
        mixer1.gain(2,amp[2] * waveAmp);
        mixer1.gain(3,amp[3] * waveAmp);
        mixer2.gain(0,amp[4] * waveAmp);
        mixer2.gain(1,amp[5] * waveAmp);
        mixer2.gain(2,amp[6] * waveAmp);
        mixer2.gain(3,amp[7] * waveAmp);
    }

} Synth;
