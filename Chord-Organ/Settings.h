#ifndef Settings_h
#define Settings_h

#include <SD.h>

class Settings {
  public:
    Settings(const char* filename);
    void init(boolean has_SD);
    void read();
    void write();
	float to_float(String setting_value);
	boolean to_boolean(String setting_value);

	boolean custom_chords = false;
	boolean no_valid_value = false;
    boolean glide = false;
	int low_note = 0;
    int glide_time = 50;
    uint8_t note_range = 36;
    uint8_t num_chords = 12;
	// Initialise Array with 255s, to identify unfilled elements when reading from SD card 
	int16_t notes[16][4] = {
	    { 255,255,255,255 },    
	    { 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 },
		{ 255,255,255,255 } 
	};
	int16_t default_notes[16][4] = {
	    {0,4,7,12},    
	    {0,3,7,12},    
	    {0,4,7,11},    
	    {0,3,7,10},    
	    {0,4,7,11},    
	    {0,3,7,10},    
	    {0,5,7,12},    
	    {0,7,12,0},    
	    {0,5,12,0},    
	    {0,4,7,8},    
	    {0,3,7,8},    
	    {0,3,6,0},    
	    {0,4,8,0},    
	    {0,0,0,0},    
	    {-12,-12,0,0},    
	    {-12,0,0,12}    
	};	
  private:
    const char* _filename;
    File settings_file;
    void copy_defaults();
};

#endif
