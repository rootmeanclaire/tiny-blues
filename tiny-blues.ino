#include "composer.h"
#include "performer.h"

#define MIDI_A4 69
#define PIN_MELODY 0
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
}

void loop() {
//  playScale(64 - 24);
//  for (int i = 0; i < 12 * RESOLUTION;) {
//    long startNoteMelody = millis();
//    Note noteMelody = melody.getNoteAt(i);
//    int periodMelody = periods[noteMelody.midi - MIDI_MIN];
//    
//    while (millis() - startNoteMelody < NOTE_LENGTH * ((i % 2) ? 0.333 : 0.666)) {
//      digitalWrite(PIN_MELODY, HIGH);
//      delayMicroseconds(periodMelody);
//      digitalWrite(PIN_MELODY, LOW);
//      delayMicroseconds(periodMelody);
//    }
//    i += note.len;
//  }
//=======================================
//  long startSong = millis();
//
//  int iMelody = 0;
//  long startNoteMelody = millis();
//  Note noteMelody = melody.getNoteAt(iMelody);
//  int periodMelody = periods[noteMelody.midi - MIDI_MIN];
//  bool melodyHigh = false;
//  long lastPeakMelody = 0;
//  int noteLenMelody = noteMelody.len * NOTE_LENGTH * ((iMelody % 2) ? 0.333 : 0.666);
//
//  int iBass = 0;
//  long startNoteBass = millis();
//  Note* noteBass = bassline.getNoteAt(iBass);
//  int periodBass = periods[noteBass->midi - MIDI_MIN];
//  bool bassHigh = false;
//  long lastPeakBass = 0;
//  int noteLenBass = noteBass->len * NOTE_LENGTH * ((iBass % 2) ? 0.333 : 0.666);
//  
//  while (millis() - startSong < NOTE_LENGTH * RESOLUTION * 12 * 6) {
//    int dMelodyNote = millis() - startNoteMelody;
//    int dBassNote = millis() - startNoteBass;
//
//    if (noteBass->midi != 0 && dBassNote < noteLenBass * 0.9) {
//      if (noteBass->midi != 0 && micros() - lastPeakBass > periodBass) {
//        digitalWrite(PIN_BASS, bassHigh ? LOW : HIGH);
//        bassHigh = !bassHigh;
//        lastPeakBass = micros();
//      }
//    } else if (dBassNote > noteLenBass) {
//      iBass++;
//      startNoteBass = millis();
//      delete noteBass;
//      noteBass = bassline.getNoteAt(iBass);
//      periodBass = periods[noteBass->midi - MIDI_MIN];
//      noteLenBass = noteBass->len * NOTE_LENGTH * ((iBass % 2) ? 0.333 : 0.666);
//    }
//    
//    if (noteBass->midi == 0 && dMelodyNote < noteLenMelody * 0.9) {
//      if (noteMelody.midi != 0 && micros() - lastPeakMelody > periodMelody) {
//        digitalWrite(PIN_MELODY, melodyHigh ? LOW : HIGH);
//        melodyHigh = !melodyHigh;
//        lastPeakMelody = micros();
//      }
//    } else if (dMelodyNote > noteLenMelody) {
//      iMelody++;
//      startNoteMelody = millis();
//      noteMelody = melody.getNoteAt(iMelody);
//      periodMelody = periods[noteMelody.midi - MIDI_MIN];
//      noteLenMelody = noteMelody.len * NOTE_LENGTH * ((iMelody % 2) ? 0.333 : 0.666);
//    }
    
  long startSong = millis();
  long lastSwitch = millis();
  
  while (millis() - startSong < NOTE_LENGTH * RESOLUTION * 12 * 6) {
//    playBass.step();
//    if (!playBass.playing()) {
      playMelody.step();
//    }
  }
  
  delay(NOTE_LENGTH * 4);
}

//void playScale(int start) {
//  int dn = 0;
//  int sDeg = 0;
//  
//  for (int i = 0; i < LEN_SCALE; ++i) {
//    playNote(PIN_MELODY, start + dn,  NOTE_LENGTH * ((i % 2) ? 0.333 : 0.666));
//    delay(NOTE_LENGTH * .25);
//    if (random(0, 3)) {
//      dn += SCALE[sDeg];
//      sDeg++;
//      if (sDeg >= LEN_SCALE) {
//        sDeg -= LEN_SCALE;
//      }
//    } else {
//      dn -= SCALE[sDeg];
//      sDeg--;
//      if (sDeg < 0) {
//        sDeg += LEN_SCALE;
//      }
//    }
//  }
//  
//  if (dn > 6) {
//    playNote(PIN_MELODY, start + 12, NOTE_LENGTH);
//  } else if (dn < -6) {
//    playNote(PIN_MELODY, start - 12, NOTE_LENGTH);
//  } else {
//    playNote(PIN_MELODY, start, NOTE_LENGTH);
//  }
//}

//void playNote(int pin, int note, int len) {
//  long noteStart = millis();
//  
//  while (millis() - noteStart < len) {
////    analogWrite(pin, 255);
//    digitalWrite(pin, HIGH);
//    delayMicroseconds(periods[note - MIDI_MIN]);
////    analogWrite(pin, 0);
//    digitalWrite(pin, LOW);
//    delayMicroseconds(periods[note - MIDI_MIN]);
//  }
//}

double getFreq(int midiNum) {
  return 440 * pow(2, (midiNum - MIDI_A4) / 12.0);
}
