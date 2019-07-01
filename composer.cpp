#include "composer.h"

Melody::Melody(char key) {
  char dn = 0;
  
  for (char i = 0; i < RESOLUTION; ++i) {
    if (i == RESOLUTION - 2) {
      motive[i] = Note(key + dn, 2);
      break;
    } else {
      motive[i] = Note(key + dn, 1);
    }
    dn += SCALE[i % LEN_SCALE];
  }
  
  dn = 12;
  for (char i = 0; i < RESOLUTION; ++i) {
    if (i == RESOLUTION - 2) {
      conclusive[i] = Note(key + dn, 2);
      break;
    } else {
      conclusive[i] = Note(key + dn, 1);
    }
    dn -= SCALE[i % LEN_SCALE];
  }

  dn = 12;
  for (char i = 0; i < RESOLUTION; ++i) {
    if (i == RESOLUTION - 2) {
      continuous[i] = Note(key + dn, 2);
      break;
    } else {
      continuous[i] = Note(key + dn, 1);
    }
    dn -= SCALE[i % LEN_SCALE];
  }

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
  char pitch;
  
  for (char i = 0; i < tickInMeasure;) {
    char dur = measure[noteInMeasure].len;
    noteInMeasure++;
    if (dur == 0) {
      break;
    } else {
      i += dur;
    }
  }
  
  return new Note(measure[noteInMeasure].midi, measure[noteInMeasure].len);
}

Bassline::Bassline(char key) {
  this->key = key;
  for (char i = 0; i < RESOLUTION / 4; ++i) {
    rhythm[i] = Note(1, 1);
  }
  for (char i = RESOLUTION / 4; i < RESOLUTION; ++i) {
    rhythm[i] = Note(0, 1);
  }
}

Note* Bassline::getNoteAt(unsigned short tick) {
  unsigned short measureNum = tick / RESOLUTION;

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
    return new Note(0, rhythm[noteInMeasure].len);
  } else {
    return new Note(BASSLINE[measureNum] + key, rhythm[noteInMeasure].len);
  }
}
