#ifdef __linux__
  #include <ctime>
  #include <iostream>
  #include <chrono>
  #include <thread>
  #include <SFML/Audio.hpp>
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
  reset();
}

Performer::~Performer() {
  delete currNote;
}

void Performer::step() {
  unsigned short dNote = millis() - startNote;
  
  #ifdef __linux__
    if (micros() - lastSample > 1000000 / SAMPLE_RATE) {
      samples.push_back(high);
      lastSample = micros();
    }
  #endif
  if (currNote->midi != REST && dNote < currNoteLen * 0.9) {
    if (micros() - lastPeak > (unsigned long) period) {
      #ifndef __linux__
        digitalWrite(pin, high ? LOW : HIGH);
      #endif
      high = !high;
      lastPeak = micros();
    }
  } else if (dNote > currNoteLen) {
    if (!done()) {
      startNote = millis();
      delete currNote;
      currNote = part->getNoteAt(iTick);
      if (currNote->midi == REST) {
        period = 0;
      } else {
        period = periods[currNote->midi % 6] << (5 - currNote->midi / 6);
      }
      high = true;
      currNoteLen = 0;
      for (char tick = 0; tick < currNote->len; ++tick) {
        bool swingLong = ((iTick + tick) / (RESOLUTION / 8)) % 2;
        currNoteLen += (8.0 / RESOLUTION) * NOTE_LENGTH * (swingLong ? 0.333 : 0.666);
      }
      iTick += currNote->len;
      #ifdef __linux__
        std::cout << iTick << '\t' << (int) currNote->len << '\t' << currNoteLen << '\t' << millis() << std::endl;
      #endif
    }
  } else {
    high = false;
  }
}

void Performer::reset() {
  iTick = 0;
  startNote = 0;
  currNote = new Note();
  period = periods[currNote->midi % 6] << (5 - currNote->midi / 6);
  high = false;
  lastPeak = 0;
  currNoteLen = 0;
  #ifdef __linux__
    lastSample = 0;
  #endif
}

bool Performer::playing() const {
  return currNote->midi != REST && millis() - startNote < currNoteLen;
}

bool Performer::done() const {
  return iTick > RESOLUTION * 12;
}

#ifdef __linux__
  std::vector<sf::Int16> Performer::getSamples(unsigned int amp) const {
    std::vector<sf::Int16> samples;
    for (bool s : this->samples) {
      samples.push_back(s ? amp : -amp);
    }

    return samples;
  }

  void play(std::vector<sf::Int16> samples) {
    sf::SoundBuffer Buffer;
    
    if (!Buffer.loadFromSamples(&samples[0], samples.size(), 1, SAMPLE_RATE)) {
      std::cerr << "Loading failed!" << std::endl;
      exit(1);
    }

    // sf::Sound Sound;
    // Sound.setBuffer(Buffer);
    // Sound.play();
    // sf::sleep(sf::milliseconds(samples.size() * 1000 / SAMPLE_RATE));
    Buffer.saveToFile("out.wav");
  }
#endif
