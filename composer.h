#ifndef COMPOSER_H
#define COMPOSER_H

#define RESOLUTION 8
#define LEN_SCALE 6
#define REST 127
const char BASSLINE[] = {
  0, 0, 0, 0,
  2, 2, 0, 0,
  4, 2, 0, 0
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
    char octave;
    Note motive[RESOLUTION];
    Note continuous[RESOLUTION];
    Note conclusive[RESOLUTION];
  public:
    Melody(char octave);
    void write();
    Note* getNoteAt(unsigned short tick);
};

class Bassline : public Part {
  private:
    char octave;
    Note rhythm[RESOLUTION];
  public:
    Bassline(char octave);
    Note* getNoteAt(unsigned short tick);
};

#ifdef __linux__
  long random(long min, long max);
  long random(long max);
#endif

#endif
