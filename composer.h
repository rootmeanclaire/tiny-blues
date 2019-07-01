#ifndef COMPOSER_H
#define COMPOSER_H

#define MIDI_MIN 36
#define MIDI_MAX 96
#define RESOLUTION 8
#define LEN_SCALE 6
const char SCALE[] = {3, 2, 1, 1, 3, 2};
const char BASSLINE[] = {
  0, 0, 0 , 0,
  5, 5, 0 , 0,
  7, 5, 0 , 7
};

struct Note {
  char midi;
  char len;
  Note() : midi(0), len(0) {};
  Note(char midiPitch, char duration) : midi(midiPitch), len(duration) {};
};

class Part {
  public:
    virtual Note* getNoteAt(unsigned short tick) = 0;
};

class Melody : public Part {
  private:
    Note motive[RESOLUTION];
    Note continuous[RESOLUTION];
    Note conclusive[RESOLUTION];
  public:
    Melody(char key);
    Note* getNoteAt(unsigned short tick);
};

class Bassline : public Part {
  private:
    char key;
    Note rhythm[RESOLUTION];
  public:
    Bassline(char key);
    Note* getNoteAt(unsigned short tick);
};
#endif
