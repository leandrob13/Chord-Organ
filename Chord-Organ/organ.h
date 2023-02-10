#include <wiring.h>
#include <Bounce2.h>
#include <synth_waveform.h>

#include "teensy.h"

#define SINECOUNT 8

typedef struct Control
{
    int chordRaw;
    int chordRawOld;
    int chordQuant;
    int chordQuantOld;

    int rootPotOld;
    int rootCVOld;

    int rootQuant;
    int rootQuantOld;

    // Flag for either chord or root note change
    boolean changed = true;
    boolean rootChanged = false;

    Bounce resetCV = Bounce( RESET_CV, 40 ); 
    boolean resetButton = false;
    boolean resetCVRose;

    elapsedMillis resetHold;
    elapsedMillis resetFlash; 
    int updateCount = 0;

    elapsedMillis buttonTimer = 0;
    elapsedMillis lockOut = 0;
    boolean shortPress = false;
    boolean longPress = false;
    elapsedMillis pulseOutTimer = 0;
    uint32_t flashTime = 10;
    boolean flashing = false;

} Control;

typedef struct Organ {
    int chordCount = 16;

    // Target frequency of each oscillator
    float FREQ[SINECOUNT] = {
        55,110, 220, 440, 880,1760,3520,7040};

    // Total distance between last note and new.
    // NOT distance per time step.
    float deltaFrequency[SINECOUNT] = {
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

    // Keep track of current frequency of each oscillator
    float currentFrequency[SINECOUNT]  = {
        55,110, 220, 440, 880,1760,3520,7040};

    float AMP[SINECOUNT] = { 
        0.9, 0.9, 0.9, 0.9,0.9, 0.9, 0.9, 0.9};

    // Volume for a single voice for each chord size
    float AMP_PER_VOICE[SINECOUNT] = {
    0.4,0.3,0.22,0.2,0.15,0.15,0.13,0.12};

    // Default wave types
    short wave_type[4] = {
        WAVEFORM_SINE,
        WAVEFORM_SQUARE,
        WAVEFORM_SAWTOOTH,
        WAVEFORM_PULSE,
    };

    // Per-waveform amp level
    // First 4 are default waves, last 8 are custom wavetables
    float WAVEFORM_AMP[12] = {
        0.8,0.6,0.8,0.6,
        0.8,0.8,0.8,0.8,
        0.8,0.8,0.8,0.8,
    };

} Organ;
