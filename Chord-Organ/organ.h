#include <wiring.h>
#include <Bounce2.h>
#include <synth_waveform.h>

#include "midi.h"
#include "Settings.h"

typedef struct Control
{
    int chordRawOld;
    int rootPotOld;
    int rootCVOld;
    int chordPotOld;
    int chordCVOld;

    // Flag for either chord or root note change
    boolean changed = true;

    Bounce reset_cv = Bounce( RESET_CV, 40 ); 
    boolean resetButton = false;
    boolean reset_cv_rose;
    elapsedMillis reset_hold;
    elapsedMillis reset_flash; 
    elapsedMillis button_timer = 0;
    elapsedMillis lock_out = 0;
    boolean short_press = false;
    boolean long_press = false;
    elapsedMillis pulse_out_timer = 0;
    uint32_t flash_time = 10;
    boolean flashing = false;

} Control;

typedef struct Organ {
    static const int oscillator_count = 8;
    int genre = 0;
    int genre_old;
    int chord_count = 12;
    int chord;
    int chord_old;
    int root;
    int root_old;
    int chord_transpose = 0;
    int low_note = 0;

    // Target frequency of each oscillator
    float freq[oscillator_count] = {55,110, 220, 440, 880,1760,3520,7040};

    // Total distance between last note and new.
    // NOT distance per time step.
    float delta_frequency[oscillator_count] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // Keep track of current frequency of each oscillator
    float current_frequency[oscillator_count] = {55,110, 220, 440, 880,1760,3520,7040};

    // GLIDE
    // Main flag for glide on / off
    boolean glide = false;
    // msecs glide time. 
    uint32_t glide_time = 50;
    // keep reciprocal
    float one_over_glide_time = 0.02;
    // Time since glide started
    elapsedMillis glideTimer = 0;
    // Are we currently gliding notes
    boolean gliding = false;

    // Stack mode replicates first 4 voices into last 4 with tuning offset
    boolean stacked = false;
    float stack_freq_scale = 1.001;

    int note_range = 38;

    void init(Settings settings) {
        chord_count = settings.num_chords;
        glide = settings.glide;
        glide_time = settings.glide_time;
        one_over_glide_time = 1.0 / (float) glide_time;
        note_range = settings.note_range;
        stacked = settings.stacked;
        low_note = settings.low_note;
    }

    float* get_current_frequency() {
        float* result_frequency = freq;
        if(gliding) {
            float dt = 1.0 - (glideTimer * one_over_glide_time);
            if(dt < 0.0) {
                dt = 0.0;
                gliding = false;
            }

            for(int i=0;i<8;i++) {
                current_frequency[i] = freq[i] - (delta_frequency[i] * dt);
            }
            result_frequency = current_frequency;
        }
        return result_frequency;
    }

    int update_frequencies(int16_t* chord) {
        int note_number;
        int voice_count = 0;
        int half_oscillator_count = oscillator_count >> 1;

        if(stacked) {
            for(int i=0;i < half_oscillator_count;i++) {
                if (chord[i] != 255) {
                    note_number = root + chord[i] + chord_transpose;
                    if(note_number < 0) note_number = 0;
                    if(note_number > 127) note_number = 127;
                    float new_freq = midi_to_freq_lut[note_number];

                    freq[i] = new_freq;
                    freq[i+half_oscillator_count] = new_freq * stack_freq_scale;
                    delta_frequency[i] = new_freq - current_frequency[i];
                    delta_frequency[i+half_oscillator_count] = (new_freq * stack_freq_scale) - current_frequency[i];
                    voice_count += 2;
                }            
            }
        } else {
            for(int i = 0; i< 8; i++){
                if (chord[i] != 255) {
                    note_number = root + chord[i] + chord_transpose;
                    if(note_number < 0) note_number = 0;
                    if(note_number > 127) note_number = 127;
                    
                    float newFreq = midi_to_freq_lut[note_number];
                    delta_frequency[i] = newFreq - current_frequency[i];
                    freq[i] = newFreq;
                    voice_count++;
                }
            }

        }
        return voice_count;
    }

} Organ;
