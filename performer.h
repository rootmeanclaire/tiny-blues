#include "composer.h"
#ifdef __linux__
  #include <vector>
  #include <SFML/Audio.hpp>
#endif

#ifndef PERFORMER_H
#define PERFORMER_H
#define NOTE_LENGTH 500
//#define TEMPO 120
//#define NOTE_LENGTH ((60 * 1000) / TEMPO)
extern unsigned short periods[LEN_SCALE];

class Performer {
  private:
    Part* part;
    char pin;
    unsigned short iTick;
    unsigned long startNote;
    Note* currNote;
    unsigned short period;
    bool high;
    unsigned long lastPeak;
    unsigned short currNoteLen;
    #ifdef __linux__
      long lastSample;
      std::vector<sf::Int16> samples;
    #endif
  public:
    Performer(Part& part, char pin);
    ~Performer();
    void step();
    void reset();
    bool playing() const;
    bool done() const;
    #ifdef __linux__
      std::vector<sf::Int16> getSamples(unsigned int amp) const;
    #endif
};

#ifdef __linux__
  #define SAMPLE_RATE 8000
  unsigned long millis();
  unsigned long micros();
  void play(std::vector<sf::Int16> samples);
#endif

#endif
