# Chord Organ

The new firmware version of the popular module Music Thing Chord Organ includes the genre chords based on the [Roland J6 chord table](https://static.roland.com/manuals/J-6_manual_v102/eng/28645807.html). In addition to that, you can define custom chords from the SD card, just like in the previous firmware version.

## Contents

- [Installation](#installation)
- [Features](#features)
- [Configuration](#configuration)
- [Default Genres](#default-genres)
- [Caveats](#caveats)
- [Future Roadmap](#future-roadmap)

## Installation

- Download and install the [Teensy Loader](https://www.pjrc.com/teensy/loader.html) for your OS.
- Download the recent Chord Organ [hex file](https://github.com/leandrob13/Chord-Organ/releases).
- Remove the Chord Organ from your rack.
- Connect the Chord Organ to your computer via the micro USB socket on the back of the module.
- Open the Teensy Loader application and drag and drop the hex file to it.
- Select the `Auto`button in the Teensy Loader application.
- Press the button on the back of the module, in the Teensy board.
- Wait for the interface to show that it has completed the operation.

## Features

The new firmware includes new features and keeps others from the original v0.6. These are:

- Improved quantized 1V/Oct tracking for `Root`CV input and knob.
- The key of the chords are changed with the combination of `Root` knob and CV input.
- The `Chord` knob now selects the different default genres based on the Roland J6 chord tables.
- The `Chord` CV input tracks 1V/Oct so that you can follow the different chords of the genre just like you would in the Roland J6.
- 16 Waveforms are included by default and they are selected with the `Wave` button.
- Binary visualization of each waveform selected through the top leds.

## Configuration

As in the original firmware, it is possible to include additional functionalities based on the configuration file in the SD card. Include the configuration file in the SD card and name it `CHORDORG.txt`. The example file is included in this repo.

### Config Params

|Param           |min |Max |Description                                                     |
|----------------|----|----|----------------------------------------------------------------|
|`!CUSTOM`       |N/A |N/A |If set, custom chords will be used from the SD card.            |
|`!STACK`        |N/A |N/A |The first 4 voices will be doubled with a 0.1% frequency offset.|
|`!GLIDE {ms}`   |5   |300 |ms time in milliseconds. Leave blank for 50ms default time.     |
|`!RANGE {value}`|12  |72  |Knob note range. Defaults to 36.                                | 

## Default Genres

There are 20 default genres included in the firmware. Each genre includes 12 chords that can be properly tracked by octave with the `Chord` CV input and transposed with the `Root` knob and CV input. The genres correspond in order with the ones included in the [Roland J6 chord table](https://static.roland.com/manuals/J-6_manual_v102/eng/28645807.html). The included genres ordered as follow:

- Oct Stack1
- 5th Stack1
- Cinematic1
- Cinematic2
- EDM1
- EDM2
- EDM3
- EDM4
- House1
- House2
- House3
- House4
- Synthwave1
- Synthwave2
- Synthwave3
- Synthwave4
- Techno1
- Trad Maj1
- Trad Min1
- Trance1

## Caveats

- The 1V/Oct tracking in the CV inputs is restricted to 3 octaves given that the internal ADC reference voltage is 3.3V. There is no scaling circuit that can allow a broader range.
- I tested for the highest note range (72) from the original firmware and it gets a bit jittery after noon in the `Root` knob. I would recommend to leave it at the default value.
- I also tested the `STACK` option, it seems to not have much effect on the sound of the chords.

## Future Roadmap

I am considering adding these features in the future:
- Instead of custom chords, allow to add custom genres based on the J6 chord table.
- Reduce possible voices to 4 instead of 8.
- Add a chord arpeggiator.
- Add a lowpass gate triggered by the `Trig` CV input.
