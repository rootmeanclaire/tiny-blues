#ifdef __linux__
  #include <ctime>
  #include <iostream>
  #include <chrono>
  #include <thread>
#else
  #include <Arduino.h>
#endif
#include "performer.h"

#ifdef __linux__
  unsigned long millis() {
    return clock() / (CLOCKS_PER_SEC / 1000);
  }
  unsigned long micros() {
    return clock() / (CLOCKS_PER_SEC / 1000000);
  }
#endif

Performer::Performer(Part& part, char pin) {
  this->part = &part;
  this->pin = pin;
  i = -1;
  startNote = 0;
  currNote = this->part->getNoteAt(i);
  period = periods[currNote->midi - MIDI_MIN];
  high = false;
  lastPeak = 0;
  currNoteLen = currNote->len * NOTE_LENGTH * ((i % 2) ? 0.333 : 0.666);
}

Performer::~Performer() {
  delete currNote;
}

void Performer::step() {
  int dNote = millis() - startNote;
  
  if (currNote->midi != 0 && dNote < currNoteLen * 0.9) {
    if (micros() - lastPeak > period) {
      #ifndef __linux__
        digitalWrite(pin, high ? LOW : HIGH);
      #endif
      high = !high;
      lastPeak = micros();
    }
  } else if (dNote > currNoteLen) {
    i++;
    startNote = millis();
    delete currNote;
    currNote = part->getNoteAt(i);
    if (currNote->midi < MIDI_MIN) {
      period = 0;
      #ifdef __linux__
        std::cout << "Midi value " << (int) currNote->midi << " (below min)" << std::endl;
      #endif
    } else if (currNote->midi > MIDI_MAX) {
      period = periods[MIDI_MAX - MIDI_MIN - 1];
      #ifdef __linux__
        std::cout << "Midi value " << (int) currNote->midi << " (above max)" << std::endl;
      #endif
    } else {
      period = periods[currNote->midi - MIDI_MIN];
      #ifdef __linux__
        std::cout << "Midi value " << (int) currNote->midi << std::endl;
      #endif
    }
    high = true;
    currNoteLen = currNote->len * NOTE_LENGTH * ((i % 2) ? 0.333 : 0.666);
    #ifdef __linux__
      if (period != 0) {
        std::cout << i << '\t' << period << '\t' << millis() << std::endl;
      }
    #endif
  } else {
    high = false;
  }
}

bool Performer::playing() {
  return currNote->midi != 0 && millis() - startNote < currNoteLen;
}
