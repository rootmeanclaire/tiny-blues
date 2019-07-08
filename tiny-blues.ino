#include "composer.h"
#include "performer.h"

#define MIDI_A4 69
#define PIN_MELODY 1
#define PIN_BASS 0

Melody melody(60);
Bassline bassline(60 - 12);
Performer playMelody(melody, PIN_MELODY);
Performer playBass(bassline, PIN_BASS);
int periods[MIDI_MAX - MIDI_MIN];

void setup() {
  pinMode(PIN_MELODY, OUTPUT);
  pinMode(PIN_BASS, OUTPUT);
  for (int i = 0; i < MIDI_MAX - MIDI_MIN; ++i) {
    periods[i] = round(500000.0 / getFreq(i + MIDI_MIN));
  }
  randomSeed(analogRead(3));
  melody.write();
}

void loop() {
  long startSong = millis();
  
  while (millis() - startSong < NOTE_LENGTH / 2 * RESOLUTION * 12 || (!playMelody.done() && !playBass.done())) {
    playBass.step();
//    if (!playBass.playing()) {
      playMelody.step();
//    }
  }
}

double getFreq(int midiNum) {
  return 440 * pow(2, (midiNum - MIDI_A4) / 12.0);
}
