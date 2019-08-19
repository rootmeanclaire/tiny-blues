#ifdef __linux__
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "composer.h"
#include "performer.h"

#define MIDI_A4 69
#define MIDI_KEY (69 + 12)
#define PIN_MELODY 1
#define PIN_BASS 0

Melody melody(4);
Bassline bassline(3);
Performer playMelody(melody, PIN_MELODY);
Performer playBass(bassline, PIN_BASS);
unsigned char SCALE[] = {0, 3, 5, 6, 7, 10};
unsigned short periods[LEN_SCALE];

double getFreq(unsigned char midiNum) {
  return 440 * pow(2, (midiNum - MIDI_A4) / 12.0);
}

void setup() {  
  for (unsigned char i = 0; i < LEN_SCALE; ++i) {
    periods[i] = round(1000000.0 / getFreq(SCALE[i] + MIDI_KEY));
  }
  
  srand(time(NULL));
  melody.write();
}

void loop() {
  while (!(playMelody.done() && playBass.done())) {
    if (!playBass.done()) {
      playBass.step();
    }
    if (!playMelody.done()) {
      playMelody.step();
    }
  }
}

int main() {
  setup();
  loop();
  std::vector<sf::Int16> finalSamples;
  std::vector<sf::Int16> mSamp = playMelody.getSamples(7500);
  std::vector<sf::Int16> bSamp = playBass.getSamples(7500);

  for (unsigned int i = 0; i < std::max(mSamp.size(), bSamp.size()); ++i) {
    sf::Int16 s = 0;
    if (i < mSamp.size()) {
      s += mSamp[i];
    }
    if (i < bSamp.size()) {
      s += bSamp[i];
    }
    finalSamples.push_back(s);
  }
  play(finalSamples);

  return 0;
}
#endif
