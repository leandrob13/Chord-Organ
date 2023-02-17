const int genre_count = 29;

int16_t genre_chords[genre_count][12][8] = {
    {   //Oct Stack1
        { 48, 36, 36, 24, 255, 255, 255, 255 }, //Oct Stack C
        { 49, 37, 37, 25, 255, 255, 255, 255 }, //Oct Stack C#
        { 50, 38, 38, 26, 255, 255, 255, 255 }, //Oct Stack D
        { 51, 39, 39, 27, 255, 255, 255, 255 }, //Oct Stack D#
        { 52, 40, 40, 28, 255, 255, 255, 255 }, //Oct Stack E
        { 53, 41, 41, 29, 255, 255, 255, 255 }, //Oct Stack F
        { 54, 42, 42, 30, 255, 255, 255, 255 }, //Oct Stack F#
        { 55, 43, 43, 31, 255, 255, 255, 255 }, //Oct Stack G
        { 56, 44, 44, 32, 255, 255, 255, 255 }, //Oct Stack G#
        { 57, 45, 45, 33, 255, 255, 255, 255 }, //Oct Stack A
        { 58, 46, 46, 34, 255, 255, 255, 255 }, //Oct Stack A#
        { 59, 47, 47, 35, 255, 255, 255, 255 } //Oct Stack B
    },
    {   //5th Stack1
        { 43, 36, 31, 24, 255, 255, 255, 255 }, //5th Stack C
        { 44, 37, 32, 25, 255, 255, 255, 255 }, //5th Stack C#
        { 45, 38, 33, 26, 255, 255, 255, 255 }, //5th Stack D
        { 46, 39, 34, 27, 255, 255, 255, 255 }, //5th Stack D#
        { 47, 40, 35, 28, 255, 255, 255, 255 }, //5th Stack E
        { 48, 41, 36, 29, 255, 255, 255, 255 }, //5th Stack F
        { 49, 42, 37, 30, 255, 255, 255, 255 }, //5th Stack F#
        { 50, 43, 38, 31, 255, 255, 255, 255 }, //5th Stack G
        { 51, 44, 39, 32, 255, 255, 255, 255 }, //5th Stack G#
        { 52, 45, 40, 33, 255, 255, 255, 255 }, //5th Stack A
        { 53, 46, 41, 34, 255, 255, 255, 255 }, //5th Stack A#
        { 54, 47, 42, 35, 255, 255, 255, 255 } //5th Stack B
    },
    {   //Cinematic1
        { 35, 31, 28, 24, 255, 255, 255, 255 }, //CM7
        { 36, 33, 29, 28, 255, 255, 255, 255 }, //F/E
        { 38, 33, 29, 22, 255, 255, 255, 255 }, //A#M7
        { 38, 35, 31, 19, 255, 255, 255, 255 }, //G
        { 41, 36, 29, 26, 255, 255, 255, 255 }, //Dm7
        { 40, 36, 31, 24, 255, 255, 255, 255 }, //C
        { 41, 38, 33, 22, 255, 255, 255, 255 }, //A#M7
        { 43, 38, 35, 19, 255, 255, 255, 255 }, //G
        { 40, 36, 31, 24, 255, 255, 255, 255 }, //C
        { 40, 37, 33, 25, 255, 255, 255, 255 }, //A/C#
        { 41, 38, 33, 26, 255, 255, 255, 255 }, //Dm
        { 43, 38, 35, 29, 255, 255, 255, 255 } //G/F
    },
    {   //Cinematic2
        { 39, 34, 29, 24, 255, 255, 255, 255 }, //Ebsus2/C
        { 41, 36, 31, 26, 255, 255, 255, 255 }, //Fsus2/D
        { 43, 38, 33, 28, 255, 255, 255, 255 }, //Gsus2/E
        { 44, 39, 34, 29, 255, 255, 255, 255 }, //Absus2/F
        { 46, 41, 36, 31, 255, 255, 255, 255 }, //Bbsus2/G
        { 48, 43, 38, 33, 255, 255, 255, 255 }, //Csus2/A
        { 50, 45, 40, 35, 255, 255, 255, 255 }, //Dsus2/B
        { 51, 46, 41, 36, 255, 255, 255, 255 }, //Ebsus2/C
        { 53, 48, 43, 38, 255, 255, 255, 255 }, //Fsus2/D
        { 55, 50, 45, 40, 255, 255, 255, 255 }, //Gsus2/E
        { 56, 51, 46, 41, 255, 255, 255, 255 }, //Absus2/F
        { 58, 53, 48, 43, 255, 255, 255, 255 } //Bbsus2/G
    },
    {   //Cinematic3
        { 45, 38, 31, 24, 255, 255, 255, 255 }, //C6sus2
        { 45, 40, 33, 26, 255, 255, 255, 255 }, //Dsus2
        { 45, 43, 35, 28, 255, 255, 255, 255 }, //Emadd11
        { 45, 40, 38, 30, 255, 255, 255, 255 }, //Dadd9/F#
        { 47, 45, 38, 31, 255, 255, 255, 255 }, //Gadd9
        { 50, 43, 36, 33, 255, 255, 255, 255 }, //Am7/11
        { 50, 45, 42, 35, 255, 255, 255, 255 }, //Bm7
        { 52, 45, 43, 36, 255, 255, 255, 255 }, //C6
        { 54, 47, 45, 38, 255, 255, 255, 255 }, //D6
        { 54, 47, 43, 40, 255, 255, 255, 255 }, //Emadd9
        { 57, 50, 47, 40, 255, 255, 255, 255 }, //E7sus4
        { 55, 52, 50, 41, 255, 255, 255, 255 } //Em7b5/F
    },
    {   //EDM1
        { 35, 33, 26, 24, 255, 255, 255, 255 }, //CM9
        { 30, 35, 28, 27, 255, 255, 255, 255 }, //C6
        { 37, 35, 28, 26, 255, 255, 255, 255 }, //Dm9
        { 44, 37, 30, 29, 255, 255, 255, 255 }, //Dm6
        { 39, 37, 30, 28, 255, 255, 255, 255 }, //EM9
        { 40, 38, 31, 29, 255, 255, 255, 255 }, //FM9
        { 47, 40, 33, 32, 255, 255, 255, 255 }, //F6
        { 42, 40, 33, 31, 255, 255, 255, 255 }, //GM9
        { 37, 42, 35, 34, 255, 255, 255, 255 }, //G6
        { 56, 42, 35, 33, 255, 255, 255, 255 }, //Am9
        { 51, 44, 37, 36, 255, 255, 255, 255 }, //Am6
        { 58, 44, 37, 35, 255, 255, 255, 255 } //Bm9
    },
    {   //EDM2
        { 35, 33, 26, 24, 255, 255, 255, 255 }, //CM13(no 3)
        { 42, 35, 28, 27, 255, 255, 255, 255 }, //EM9(no 3)
        { 37, 35, 28, 26, 255, 255, 255, 255 }, //DM13(no 3)
        { 44, 37, 30, 29, 255, 255, 255, 255 }, //F#M9(no 3)
        { 39, 37, 30, 28, 255, 255, 255, 255 }, //EM13(no 3)
        { 40, 38, 31, 29, 255, 255, 255, 255 }, //FM13(no3)
        { 47, 40, 33, 32, 255, 255, 255, 255 }, //AM9(no3)
        { 42, 40, 33, 31, 255, 255, 255, 255 }, //GM13(no3)
        { 49, 42, 35, 34, 255, 255, 255, 255 }, //BM9(no3)
        { 44, 42, 35, 33, 255, 255, 255, 255 }, //AM13(no3)
        { 51, 44, 37, 36, 255, 255, 255, 255 }, //C#M9(no 3)
        { 46, 44, 37, 35, 255, 255, 255, 255 } //BM13(no3)
    },
    {   //EDM3
        { 45, 38, 31, 24, 255, 255, 255, 255 }, //Csus9/13
        { 52, 45, 31, 24, 255, 255, 255, 255 }, //C6
        { 47, 40, 33, 26, 255, 255, 255, 255 }, //Dsus9/13
        { 54, 47, 33, 26, 255, 255, 255, 255 }, //D6
        { 49, 42, 35, 28, 255, 255, 255, 255 }, //Esus9/13
        { 50, 43, 36, 29, 255, 255, 255, 255 }, //Fsus9/13
        { 45, 50, 36, 29, 255, 255, 255, 255 }, //F6
        { 52, 45, 38, 31, 255, 255, 255, 255 }, //Gsus9/13
        { 47, 40, 38, 31, 255, 255, 255, 255 }, //G6
        { 54, 47, 40, 33, 255, 255, 255, 255 }, //Asus9/13
        { 49, 42, 40, 33, 255, 255, 255, 255 }, //A6
        { 56, 49, 42, 35, 255, 255, 255, 255 } //Bsus9/13
    },
    {   //EDM4
        { 40, 35, 33, 24, 255, 255, 255, 255 }, //CM13
        { 39, 34, 30, 25, 255, 255, 255, 255 }, //C#sus9
        { 42, 37, 35, 26, 255, 255, 255, 255 }, //DM13
        { 41, 34, 32, 27, 255, 255, 255, 255 }, //D#sus9
        { 44, 39, 37, 28, 255, 255, 255, 255 }, //EM13
        { 45, 40, 38, 29, 255, 255, 255, 255 }, //FM13
        { 44, 37, 35, 30, 255, 255, 255, 255 }, //F#sus9
        { 47, 42, 40, 31, 255, 255, 255, 255 }, //GMaj13
        { 46, 39, 37, 32, 255, 255, 255, 255 }, //Absus9
        { 49, 44, 42, 33, 255, 255, 255, 255 }, //AM13
        { 48, 41, 39, 34, 255, 255, 255, 255 }, //Bbsus9
        { 51, 46, 44, 35, 255, 255, 255, 255 } //BM13
    },
    {   //EDM5
        { 40, 35, 24, 19, 255, 255, 255, 255 }, //CM7
        { 40, 35, 25, 20, 255, 255, 255, 255 }, //Dbm7
        { 41, 36, 26, 21, 255, 255, 255, 255 }, //Dm7
        { 43, 36, 27, 22, 255, 255, 255, 255 }, //Eb6
        { 43, 38, 28, 23, 255, 255, 255, 255 }, //Em7
        { 45, 40, 29, 24, 255, 255, 255, 255 }, //FM7
        { 45, 40, 30, 25, 255, 255, 255, 255 }, //Gbm7
        { 47, 42, 31, 26, 255, 255, 255, 255 }, //GM7
        { 47, 42, 32, 27, 255, 255, 255, 255 }, //Abm7
        { 48, 43, 33, 28, 255, 255, 255, 255 }, //Am7
        { 50, 43, 35, 29, 255, 255, 255, 255 }, //Bb6
        { 50, 45, 35, 30, 255, 255, 255, 255 } //Bm7
    },
    {   //EDM6
        { 40, 33, 31, 24, 255, 255, 255, 255 }, //C6
        { 40, 33, 32, 25, 255, 255, 255, 255 }, //AM7
        { 42, 35, 33, 26, 255, 255, 255, 255 }, //D6
        { 42, 35, 34, 27, 255, 255, 255, 255 }, //BM7
        { 44, 37, 35, 28, 255, 255, 255, 255 }, //E6
        { 45, 38, 36, 29, 255, 255, 255, 255 }, //F6
        { 45, 38, 37, 30, 255, 255, 255, 255 }, //DM7
        { 47, 40, 38, 31, 255, 255, 255, 255 }, //G6
        { 47, 40, 39, 32, 255, 255, 255, 255 }, //EM7
        { 49, 42, 40, 33, 255, 255, 255, 255 }, //A6
        { 49, 42, 41, 34, 255, 255, 255, 255 }, //GbM7
        { 51, 44, 42, 35, 255, 255, 255, 255 } //B6
    },
    {   //House1
        { 39, 34, 31, 24, 255, 255, 255, 255 }, //Cm7
        { 40, 35, 32, 25, 255, 255, 255, 255 }, //C#m7
        { 41, 36, 33, 26, 255, 255, 255, 255 }, //Dm7
        { 43, 38, 34, 27, 255, 255, 255, 255 }, //EbM7
        { 43, 38, 34, 28, 255, 255, 255, 255 }, //Gm/E
        { 43, 39, 34, 29, 255, 255, 255, 255 }, //Eb/F
        { 36, 33, 26, 18, 255, 255, 255, 255 }, //D7/F#
        { 34, 29, 26, 19, 255, 255, 255, 255 }, //Gm7
        { 36, 31, 27, 20, 255, 255, 255, 255 }, //AbM7
        { 39, 36, 32, 22, 255, 255, 255, 255 }, //Ab/Bb
        { 38, 33, 29, 22, 255, 255, 255, 255 }, //BbM7
        { 38, 33, 29, 23, 255, 255, 255, 255 } //Bm7b5
    },
    {   //House2
        { 40, 35, 31, 24, 255, 255, 255, 255 }, //Cmaj7
        { 42, 37, 33, 26, 255, 255, 255, 255 }, //Dmaj7
        { 43, 38, 35, 28, 255, 255, 255, 255 }, //Em7
        { 43, 40, 36, 29, 255, 255, 255, 255 }, //Fmaj9
        { 45, 42, 38, 31, 255, 255, 255, 255 }, //Gmaj9
        { 47, 42, 40, 32, 255, 255, 255, 255 }, //Eadd9/G#
        { 48, 43, 40, 33, 255, 255, 255, 255 }, //Am7
        { 50, 45, 42, 35, 255, 255, 255, 255 }, //Bm7
        { 50, 47, 43, 36, 255, 255, 255, 255 }, //Cmaj9
        { 52, 48, 41, 38, 255, 255, 255, 255 }, //Dm7/9
        { 55, 50, 47, 40, 255, 255, 255, 255 }, //Em7
        { 57, 52, 48, 41, 255, 255, 255, 255 } //Fmaj7
    },
    {   //House3
        { 34, 31, 27, 24, 255, 255, 255, 255 }, //Cm7
        { 36, 32, 27, 25, 255, 255, 255, 255 }, //G#/C#
        { 36, 33, 29, 26, 255, 255, 255, 255 }, //Dm7
        { 38, 34, 29, 27, 255, 255, 255, 255 }, //A#/D#
        { 38, 35, 31, 28, 255, 255, 255, 255 }, //Em7
        { 40, 36, 31, 29, 255, 255, 255, 255 }, //C/F
        { 40, 37, 33, 30, 255, 255, 255, 255 }, //F#m7
        { 42, 38, 33, 31, 255, 255, 255, 255 }, //D/G
        { 42, 39, 35, 32, 255, 255, 255, 255 }, //G#m7
        { 44, 40, 35, 33, 255, 255, 255, 255 }, //E/A
        { 44, 41, 37, 34, 255, 255, 255, 255 }, //A#m7
        { 46, 42, 37, 35, 255, 255, 255, 255 } //F#/B
    },
    {   //House4
        { 46, 39, 31, 24, 255, 255, 255, 255 }, //Cm7
        { 43, 36, 27, 20, 255, 255, 255, 255 }, //G#M7
        { 48, 41, 33, 26, 255, 255, 255, 255 }, //Dm7
        { 45, 38, 29, 22, 255, 255, 255, 255 }, //A#M7
        { 50, 43, 35, 28, 255, 255, 255, 255 }, //Em7
        { 47, 40, 31, 24, 255, 255, 255, 255 }, //CM7
        { 52, 45, 37, 30, 255, 255, 255, 255 }, //F#m7
        { 49, 42, 33, 26, 255, 255, 255, 255 }, //DM7
        { 54, 47, 39, 32, 255, 255, 255, 255 }, //G#m7
        { 51, 44, 35, 28, 255, 255, 255, 255 }, //EM7
        { 56, 49, 41, 34, 255, 255, 255, 255 }, //A#m7
        { 53, 46, 37, 30, 255, 255, 255, 255 } //F#M7
    },
    {   //House5
        { 41, 34, 27, 24, 255, 255, 255, 255 }, //Cm7/11
        { 42, 33, 27, 24, 255, 255, 255, 255 }, //Cdim7
        { 43, 36, 29, 25, 255, 255, 255, 255 }, //C#M7/b5
        { 44, 35, 29, 26, 255, 255, 255, 255 }, //Ddim7
        { 43, 36, 31, 27, 255, 255, 255, 255 }, //Cm
        { 41, 36, 29, 25, 255, 255, 255, 255 }, //C#M7
        { 40, 35, 31, 24, 255, 255, 255, 255 }, //CM7
        { 43, 38, 35, 28, 255, 255, 255, 255 }, //Em7
        { 45, 40, 36, 29, 255, 255, 255, 255 }, //FM7
        { 44, 38, 36, 29, 255, 255, 255, 255 }, //Fm6
        { 43, 38, 36, 28, 255, 255, 255, 255 }, //Csus2/E
        { 41, 36, 32, 29, 255, 255, 255, 255 } //Fm
    },
    {   //House6
        { 35, 31, 28, 24, 255, 255, 255, 255 }, //CM7
        { 38, 35, 31, 28, 255, 255, 255, 255 }, //Em7
        { 36, 33, 29, 26, 255, 255, 255, 255 }, //Dm7
        { 40, 36, 33, 29, 255, 255, 255, 255 }, //FM7
        { 38, 34, 31, 27, 255, 255, 255, 255 }, //D#M7
        { 41, 38, 34, 31, 255, 255, 255, 255 }, //Gm7
        { 40, 36, 33, 29, 255, 255, 255, 255 }, //FM7
        { 43, 40, 36, 33, 255, 255, 255, 255 }, //Am7
        { 41, 38, 34, 31, 255, 255, 255, 255 }, //Gm7
        { 45, 41, 38, 34, 255, 255, 255, 255 }, //A#M7
        { 43, 40, 36, 33, 255, 255, 255, 255 }, //Am7
        { 45, 42, 38, 35, 255, 255, 255, 255 } //Bm7
    },
    {   //Synthwave1
        { 33, 31, 29, 24, 255, 255, 255, 255 }, //C6sus4
        { 34, 33, 31, 26, 255, 255, 255, 255 }, //Gmadd9/D
        { 34, 33, 31, 28, 255, 255, 255, 255 }, //Edim11
        { 36, 31, 29, 26, 255, 255, 255, 255 }, //Fsus2/D
        { 38, 34, 33, 29, 255, 255, 255, 255 }, //BbM7
        { 38, 34, 33, 31, 255, 255, 255, 255 }, //Gmadd9
        { 40, 36, 33, 31, 255, 255, 255, 255 }, //Am/G
        { 40, 36, 34, 31, 255, 255, 255, 255 }, //C7/G
        { 41, 38, 34, 33, 255, 255, 255, 255 }, //A#M7
        { 43, 38, 34, 33, 255, 255, 255, 255 }, //Gm/A
        { 43, 40, 36, 34, 255, 255, 255, 255 }, //C7/A#
        { 43, 41, 37, 34, 255, 255, 255, 255 } //A#m6
    },
    {   //Synthwave2
        { 31, 28, 26, 24, 255, 255, 255, 255 }, //Cadd9
        { 33, 30, 28, 26, 255, 255, 255, 255 }, //Dadd9
        { 34, 31, 29, 27, 255, 255, 255, 255 }, //D#add9
        { 36, 33, 31, 29, 255, 255, 255, 255 }, //Fadd9
        { 38, 35, 33, 31, 255, 255, 255, 255 }, //Gadd9
        { 39, 36, 34, 32, 255, 255, 255, 255 }, //G#add9
        { 41, 38, 36, 34, 255, 255, 255, 255 }, //A#add9
        { 43, 40, 38, 36, 255, 255, 255, 255 }, //Cadd9
        { 45, 42, 40, 38, 255, 255, 255, 255 }, //Dadd9
        { 46, 43, 41, 39, 255, 255, 255, 255 }, //D#add9
        { 48, 45, 43, 41, 255, 255, 255, 255 }, //Fadd9
        { 50, 47, 45, 43, 255, 255, 255, 255 } //Gadd9
    },
    {   //Synthwave3
        { 36, 31, 28, 12, 255, 255, 255, 255 }, //C
        { 34, 31, 28, 13, 255, 255, 255, 255 }, //C#dim7
        { 36, 31, 29, 14, 255, 255, 255, 255 }, //Fsus2/D
        { 34, 31, 29, 15, 255, 255, 255, 255 }, //D#add9
        { 36, 31, 26, 16, 255, 255, 255, 255 }, //Csus2/E
        { 36, 33, 28, 17, 255, 255, 255, 255 }, //FM7
        { 36, 33, 30, 18, 255, 255, 255, 255 }, //F#dim
        { 36, 31, 26, 19, 255, 255, 255, 255 }, //Gsus4
        { 36, 32, 29, 20, 255, 255, 255, 255 }, //G#6
        { 36, 31, 26, 21, 255, 255, 255, 255 }, //Csus2/A
        { 36, 31, 26, 22, 255, 255, 255, 255 }, //Csus2/A#
        { 35, 31, 29, 23, 255, 255, 255, 255 } //G7/B
    },
    {   //Synthwave4
        { 48, 40, 31, 24, 255, 255, 255, 255 }, //C
        { 48, 41, 34, 27, 255, 255, 255, 255 }, //A#sus2/D#
        { 46, 41, 32, 20, 255, 255, 255, 255 }, //A#7/G#
        { 47, 38, 31, 23, 255, 255, 255, 255 }, //G/B
        { 48, 40, 31, 24, 255, 255, 255, 255 }, //C
        { 48, 41, 32, 17, 255, 255, 255, 255 }, //Fm
        { 48, 39, 33, 18, 255, 255, 255, 255 }, //F#dim7
        { 48, 40, 31, 19, 255, 255, 255, 255 }, //C
        { 48, 39, 34, 20, 255, 255, 255, 255 }, //G#add9
        { 48, 41, 33, 21, 255, 255, 255, 255 }, //F/A
        { 50, 41, 34, 22, 255, 255, 255, 255 }, //A#
        { 50, 41, 31, 23, 255, 255, 255, 255 } //G7/B
    },
    {   //Synthwave5
        { 43, 39, 34, 24, 255, 255, 255, 255 }, //Cm7
        { 41, 38, 34, 24, 255, 255, 255, 255 }, //A#/C
        { 43, 39, 34, 20, 255, 255, 255, 255 }, //D#/G#
        { 41, 38, 34, 20, 255, 255, 255, 255 }, //A#/G#
        { 43, 39, 34, 29, 255, 255, 255, 255 }, //D#/F
        { 29, 38, 34, 29, 255, 255, 255, 255 }, //A#/F
        { 39, 36, 34, 20, 255, 255, 255, 255 }, //G#add9
        { 41, 38, 34, 22, 255, 255, 255, 255 }, //A#
        { 39, 36, 31, 20, 255, 255, 255, 255 }, //G#M7
        { 41, 36, 31, 21, 255, 255, 255, 255 }, //Fsus2/A
        { 41, 38, 31, 22, 255, 255, 255, 255 }, //A#6
        { 41, 39, 32, 23, 255, 255, 255, 255 } //Fm7/B
    },
    {   //Synthwave6
        { 46, 43, 39, 24, 255, 255, 255, 255 }, //Cm7
        { 44, 39, 37, 29, 255, 255, 255, 255 }, //C#sus2/F
        { 46, 41, 38, 31, 255, 255, 255, 255 }, //Gm7
        { 46, 39, 31, 27, 255, 255, 255, 255 }, //D#
        { 43, 38, 36, 28, 255, 255, 255, 255 }, //Csus2/E
        { 44, 41, 36, 29, 255, 255, 255, 255 }, //Fm
        { 45, 39, 36, 30, 255, 255, 255, 255 }, //D#dim7
        { 46, 39, 32, 31, 255, 255, 255, 255 }, //G#sus2/G
        { 46, 39, 36, 24, 255, 255, 255, 255 }, //Cm7
        { 45, 39, 36, 29, 255, 255, 255, 255 }, //F7
        { 44, 39, 36, 29, 255, 255, 255, 255 }, //Fm7
        { 43, 38, 26, 31, 255, 255, 255, 255 } //G5
    },
    {   //Synthwave7
        { 32, 27, 24, 255, 255, 255, 255, 255 }, //Ab
        { 32, 29, 24, 255, 255, 255, 255, 255 }, //Fm
        { 34, 31, 26, 255, 255, 255, 255, 255 }, //Gm
        { 36, 32, 27, 255, 255, 255, 255, 255 }, //Ab
        { 36, 32, 29, 255, 255, 255, 255, 255 }, //Fm
        { 26, 34, 29, 255, 255, 255, 255, 255 }, //Bb
        { 38, 34, 31, 255, 255, 255, 255, 255 }, //Gm
        { 39, 36, 31, 255, 255, 255, 255, 255 }, //Cm
        { 39, 36, 32, 255, 255, 255, 255, 255 }, //Ab
        { 41, 36, 32, 255, 255, 255, 255, 255 }, //Fm
        { 41, 38, 34, 255, 255, 255, 255, 255 }, //Bb
        { 43, 39, 36, 255, 255, 255, 255, 255 } //Cm
    },
    {   //Synthwave8
        { 28, 19, 12, 255, 255, 255, 255, 255 }, //C
        { 30, 21, 14, 255, 255, 255, 255, 255 }, //D
        { 31, 23, 16, 255, 255, 255, 255, 255 }, //Em
        { 33, 26, 18, 255, 255, 255, 255, 255 }, //D
        { 35, 26, 19, 255, 255, 255, 255, 255 }, //G
        { 36, 28, 21, 255, 255, 255, 255, 255 }, //Am
        { 38, 30, 23, 255, 255, 255, 255, 255 }, //Bm
        { 40, 31, 24, 255, 255, 255, 255, 255 }, //C
        { 42, 33, 26, 255, 255, 255, 255, 255 }, //D
        { 43, 35, 28, 255, 255, 255, 255, 255 }, //Em
        { 45, 38, 30, 255, 255, 255, 255, 255 }, //D
        { 47, 38, 31, 255, 255, 255, 255, 255 } //G
    },
    {   //Techno1
        { 43, 39, 34, 24, 255, 255, 255, 255 }, //Cm7
        { 41, 37, 34, 25, 255, 255, 255, 255 }, //A#m/C#
        { 41, 38, 34, 26, 255, 255, 255, 255 }, //A#/D
        { 43, 39, 34, 27, 255, 255, 255, 255 }, //D#
        { 43, 40, 36, 16, 255, 255, 255, 255 }, //C/E
        { 43, 39, 36, 17, 255, 255, 255, 255 }, //Cm/F
        { 45, 42, 38, 18, 255, 255, 255, 255 }, //D/F#
        { 43, 38, 35, 19, 255, 255, 255, 255 }, //G
        { 43, 39, 36, 20, 255, 255, 255, 255 }, //G#M7
        { 43, 41, 36, 21, 255, 255, 255, 255 }, //Csus4/A
        { 43, 39, 34, 22, 255, 255, 255, 255 }, //D#/A#
        { 43, 38, 35, 23, 255, 255, 255, 255 } //G/B
    },
    {   //Trad Maj1
        { 48, 43, 40, 24, 255, 255, 255, 255 }, //C
        { 46, 43, 40, 25, 255, 255, 255, 255 }, //C#dim7
        { 45, 41, 38, 26, 255, 255, 255, 255 }, //Dm
        { 48, 45, 42, 27, 255, 255, 255, 255 }, //D#dim7
        { 47, 43, 40, 28, 255, 255, 255, 255 }, //Em
        { 48, 45, 41, 29, 255, 255, 255, 255 }, //F
        { 48, 45, 40, 30, 255, 255, 255, 255 }, //F#m7b5
        { 47, 43, 38, 31, 255, 255, 255, 255 }, //G
        { 47, 41, 38, 32, 255, 255, 255, 255 }, //G#dim7
        { 48, 45, 40, 21, 255, 255, 255, 255 }, //Am
        { 46, 41, 38, 22, 255, 255, 255, 255 }, //A#
        { 47, 41, 38, 23, 255, 255, 255, 255 } //Bdim
    },
    {   //Trad Min1
        { 48, 43, 39, 24, 255, 255, 255, 255 }, //Cm
        { 44, 41, 37, 25, 255, 255, 255, 255 }, //C#
        { 44, 41, 38, 26, 255, 255, 255, 255 }, //Ddim
        { 46, 43, 39, 27, 255, 255, 255, 255 }, //Eb
        { 46, 43, 37, 28, 255, 255, 255, 255 }, //Edim7
        { 44, 41, 36, 17, 255, 255, 255, 255 }, //Fm
        { 45, 39, 36, 18, 255, 255, 255, 255 }, //F#dim7
        { 43, 38, 34, 19, 255, 255, 255, 255 }, //Gm
        { 44, 39, 36, 20, 255, 255, 255, 255 }, //G#
        { 43, 39, 36, 21, 255, 255, 255, 255 }, //Am7b5
        { 46, 41, 38, 22, 255, 255, 255, 255 }, //A#
        { 44, 41, 38, 23, 255, 255, 255, 255 } //Bdim7
    },
    {   //Trance1
        { 39, 31, 24, 12, 255, 255, 255, 255 }, //Cm
        { 39, 32, 24, 12, 255, 255, 255, 255 }, //Ab/C
        { 41, 34, 29, 14, 255, 255, 255, 255 }, //Bb/D
        { 43, 34, 22, 15, 255, 255, 255, 255 }, //Eb
        { 43, 36, 31, 16, 255, 255, 255, 255 }, //C/E
        { 44, 36, 29, 17, 255, 255, 255, 255 }, //Fm
        { 45, 36, 29, 17, 255, 255, 255, 255 }, //F
        { 46, 38, 31, 19, 255, 255, 255, 255 }, //Gm
        { 36, 27, 20, 8, 255, 255, 255, 255 }, //Ab
        { 36, 29, 27, 9, 255, 255, 255, 255 }, //F7/A
        { 38, 29, 22, 10, 255, 255, 255, 255 }, //Bb
        { 38, 31, 29, 11, 255, 255, 255, 255 } //G7/B
    }
};