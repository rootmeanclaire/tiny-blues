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
unsigned short periods[6];

void setup() {
  pinMode(PIN_MELODY, OUTPUT);
  pinMode(PIN_BASS, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  
  for (unsigned char i = 0; i < 6; ++i) {
    periods[i] = round(1000000.0 / getFreq(SCALE[i] + MIDI_KEY));
  }
  randomSeed(analogRead(3));
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
  
  delay(1000);
}

double getFreq(unsigned char midiNum) {
  return 440 * pow(2, (midiNum - MIDI_A4) / 12.0);
}
