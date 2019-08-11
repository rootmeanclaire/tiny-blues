#ifdef __linux__
  #include <cstdlib>
  #include <iostream>
#else
  #include <Arduino.h>
#endif
#include "composer.h"

Melody::Melody(char octave) {
  this->octave = octave;
}

void Melody::write() {
  char ds = 0;

  for (char i = 0; i < 7; ++i) {
    if (i == 6) {
      motive[i] = Note(octave * 6 + ds, RESOLUTION / 4);
    } else {
      motive[i] = Note(octave * 6 + ds, RESOLUTION / 8);
    }
    if (random(4)) {
      ds++;
    } else {
      ds--;
    }
  }
  
  ds = 0;
  for (char i = 0; i < 7; ++i) {
    if (i == 6) {
      conclusive[i] = Note(octave * 6 - ds, RESOLUTION / 4);
    } else {
      conclusive[i] = Note(random(0, 6) ? (octave * 6 - ds) : REST, RESOLUTION / 8);
    }
  }

  ds = 0;
  for (char i = 0; i < 7; ++i) {
    if (i == 6) {
      continuous[i] = Note(octave * 6 + ds, RESOLUTION / 4);
    } else {
      continuous[i] = Note(octave * 6 + ds, RESOLUTION / 8);
    }
    if (random(4) == 0) {
      ds++;
    } else {
      ds--;
    }
  }
  // for (char i = 0; i < 7; ++i) {
  //   if (i == 6) {
  //     continuous[i] = Note(key + dn, RESOLUTION / 4);
  //   } else {
  //     continuous[i] = Note(random(0, 6) ? (key + dn) : 0, RESOLUTION / 8);
  //   }
  //   dn -= SCALE[i % LEN_SCALE];
  // }
}

Note* Melody::getNoteAt(unsigned short tick) {
  short measureNum = tick / RESOLUTION;
  Note* measure;
  
  if (measureNum % 2 == 0) {
    measure = motive;
  } else if (measureNum % 4 == 3) {
    measure = conclusive;
  } else {
    measure = continuous;
  }

  char tickInMeasure = tick % RESOLUTION;
  char noteInMeasure = 0;
  
  for (char i = 0; i < tickInMeasure;) {
    char dur = measure[noteInMeasure].len;
    noteInMeasure++;
    if (dur == 0) {
      break;
    } else {
      i += dur;
    }
  }

  #ifdef __linux__
    std::cout << "=========" << std::endl;
    std::cout << "Tick: " << tick << std::endl;
    std::cout << "Measure: " << measureNum << std::endl;
    std::cout << "Tick in Measure: " << (int) tickInMeasure << std::endl;
    std::cout << "Note in Measure: " << (int) noteInMeasure << std::endl;
    std::cout << "Pitch: " << (int) measure[noteInMeasure].midi << std::endl;
    std::cout << "Length: " << (int) measure[noteInMeasure].len << std::endl;
    std::cout << "=========" << std::endl;
  #endif
  return new Note(measure[noteInMeasure].midi, measure[noteInMeasure].len);
}

Bassline::Bassline(char octave) {
  this->octave = octave;
  rhythm[0] = Note(1, RESOLUTION / 8);
  rhythm[1] = Note(1, RESOLUTION / 8);
  rhythm[2] = Note(REST, 3 * RESOLUTION / 8);
  rhythm[3] = Note(1, RESOLUTION / 8);
  rhythm[4] = Note(1, RESOLUTION / 8);
  rhythm[5] = Note(1, RESOLUTION / 8);
}

Note* Bassline::getNoteAt(unsigned short tick) {
  unsigned char measureNum = tick / RESOLUTION;

  char tickInMeasure = tick % RESOLUTION;
  char noteInMeasure = 0;
  
  for (char i = 0; i < tickInMeasure;) {
    char dur = rhythm[noteInMeasure].len;
    noteInMeasure++;
    if (dur == 0) {
      break;
    } else {
      i += dur;
    }
  }

  if (rhythm[noteInMeasure].midi == 0) {
    return new Note(REST, rhythm[noteInMeasure].len);
  } else {
    return new Note(BASSLINE[measureNum] + octave * 6, rhythm[noteInMeasure].len);
  }
}

#ifdef __linux__
  long random(long min, long max) {
    return rand() % (max - min) + min;
  }
  long random(long max) {
    return rand() % max;
  }
#endif
