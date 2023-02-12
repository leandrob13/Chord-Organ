#include <SD.h>
#include "Settings.h"

Settings::Settings(const char* filename) {
	_filename = filename;
}

void Settings::init(boolean has_SD) {

	if(!has_SD) {
		// Configure defaults
		copy_defaults();
	} else {
	    File root = SD.open("/");
	    if (SD.exists(_filename)) {
	        read();
	    }
	    else { 
	      
	#ifdef DEBUG_MODE
	        Serial.println("Settings file not found, writing new settings");
	#endif
	        write();
	        read();
	    };
	}

}

void Settings::copy_defaults() {
	for(int i = 0; i < 16; i++) {
		for(int a = 0; a < 8; a++) {
			notes[i][a] = default_notes[i][a];
		}
	}
	num_chords = 16;
}

void Settings::read() {
    num_chords = 0;

    char character;
    int note = 0;
    String setting_value;

    int NONE = 0;
    int CHORD = 1;
    int SETTING = 2;
    int state = NONE;

    settings_file = SD.open(_filename);

    while (settings_file.available()) {
        
        character = settings_file.read();

        if (character == '[') {
            if(num_chords < 16) {
                state = CHORD;    
            }
        } else if(character == '!') {
            state = SETTING;
        }

        if(state == CHORD) {
            if (character == ',') {
                notes[num_chords][note] = setting_value.toInt();
                setting_value = "";   
                note++;
            } else if(character == ']') {
                notes[num_chords][note] = setting_value.toInt();
                setting_value = "";
                num_chords++;
                note = 0;
                state = NONE;
            } else {
                setting_value += character;     
            }

        } else if(state == SETTING) {
            if(character == '\n') {
                if(setting_value.startsWith("!GLIDE")) {
                    glide = true;
                    int spacePos = setting_value.indexOf(' ');
                    if(spacePos > 0) {
                        glide_time = setting_value.substring(spacePos).toInt();
                        if(glide_time < 5) glide_time = 5;
                        if(glide_time > 300) glide_time = 300;
                    }

                } else if(setting_value.startsWith("!RANGE")) {
                    int spacePos = setting_value.indexOf(' ');
                    if(spacePos > 0) {
                        note_range = setting_value.substring(spacePos).toInt();
                        if(note_range < 12) note_range = 12;
                        if(note_range > 72) note_range = 72;
                    }
                } else if(setting_value.startsWith("!STACK")) {
                	stacked = true;
                } else {
                    Serial.print("Unknown option:");
                    Serial.print(setting_value);
                    Serial.println(":");
                }
                setting_value = "";
                state = NONE;
            } else {
                setting_value += character;
            }
        }
    }   
    settings_file.close();
}

// converting string to Float
float Settings::to_float(String setting_value){
    char floatbuf[setting_value.length()];
    setting_value.toCharArray(floatbuf, sizeof(floatbuf));
    float f = atof(floatbuf);
    return f;
}

// Converting String to integer and then to boolean
// 1 = true
// 0 = false
boolean Settings::to_boolean(String setting_value) {
    if(setting_value.toInt() == 1){
        return true;
    } 
    else {
        return false;
    }
}


void Settings::write() {
    // Delete the old One
    SD.remove(_filename);
    // Create new one
    settings_file = SD.open(_filename, FILE_WRITE);
    //  // writing in the file works just like regular print()/println() function

    settings_file.println("o   o o   o  o-o  o-O-o   o-o   o-O-o o  o o-O-o o   o  o-o ");
    settings_file.println("|\\ /| |   | |       |    /        |   |  |   |   |\\  | o    ");
    settings_file.println("| O | |   |  o-o    |   O         |   O--O   |   | \\ | |  -o ");
    settings_file.println("|   | |   |     |   |    \\        |   |  |   |   |  \\| o   | ");
    settings_file.println("o   o  o-o  o--o  o-O-o   o-o     o   o  o o-O-o o   o  o-o ");
    settings_file.println("");
    settings_file.println("  o-o o  o  o-o  o--o  o-o        o-o  o--o   o-o    O  o   o ");
    settings_file.println(" /    |  | o   o |   | |  \\      o   o |   | o      / \\ |\\  | ");
    settings_file.println("O     O--O |   | O-Oo  |   O     |   | O-Oo  |  -o o---o| \\ | ");
    settings_file.println(" \\    |  | o   o |  \\  |  /      o   o |  \\  o   | |   ||  \\| ");
    settings_file.println("  o-o o  o  o-o  o   o o-o        o-o  o   o  o-o  o   oo   o");
    settings_file.println("");
    settings_file.println("Edit chord shapes into the spaces below.");
    settings_file.println("No more than 16 chords and up to 8 notes per chord.");
    settings_file.println("Anything outside the square brackets is ignored");
    settings_file.println("Reduce clicks on chord changes by giving all chords");
    settings_file.println("the same number of notes.");
    settings_file.println("");

    settings_file.println("1  [0,4,7,12,0] Major");
    settings_file.println("2  [0,3,7,12,0] Minor");
    settings_file.println("3  [0,4,7,11,0] Major 7th");
    settings_file.println("4  [0,3,7,10,0] Minor 7th");
    settings_file.println("5  [0,4,7,11,14] Major 9th");
    settings_file.println("6  [0,3,7,10,14] Minor 9th");
    settings_file.println("7  [0,5,7,12,0] Suspended 4th");
    settings_file.println("8  [0,7,12,0,7] Power 5th");
    settings_file.println("9  [0,5,12,0,5] Power 4th");
    settings_file.println("10 [0,4,7,8,0] Major 6th");
    settings_file.println("11 [0,3,7,8,0] Minor 6th");
    settings_file.println("12 [0,3,6,0,3] Diminished");
    settings_file.println("13 [0,4,8,0,4] Augmented");
    settings_file.println("14 [0,0,0,0,0] Root");
    settings_file.println("15 [-12,-12,0,0,0] Sub Octave");
    settings_file.println("16 [-12,0,0,12,24] 2 up 1 down octaves");

    //
    // close the file:
    settings_file.close();
    //Serial.println("Writing done.");	
}