#include "composer.h"

#ifndef PERFORMER_H
#define PERFORMER_H
#define NOTE_LENGTH 750
extern int periods[MIDI_MAX - MIDI_MIN];

class Performer {
  private:
    Part* part;
    char pin;
    short i;
    long startNote;
    Note* currNote;
    int period;
    bool high;
    long lastPeak;
    int currNoteLen;
  public:
    Performer(Part& part, char pin);
    ~Performer();
    void step();
    bool playing();
};

#ifdef __linux__
  unsigned long millis();
  unsigned long micros();
#endif

#endif
