#include "midi_pot_mapping.h"

const int MAPPING_SIZE = 8;
const int MIDI_CC_UNKNOWN = 9999;
const byte POT_UNKNOWN = 255;
const int POT_MIN = 0;
const int POT_MAX = 1024;

int POT_JITTER_THRESHOLD = 4;
int midiCCMapping[MAPPING_SIZE];
int potPinMapping[MAPPING_SIZE];

int midiCCValues[MAPPING_SIZE];
int potPrevValues[MAPPING_SIZE];
int potCurrentValues[MAPPING_SIZE];
int potMappedValues[MAPPING_SIZE];

int inputValues[MAPPING_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void setJitterThreshold(int jitterThreshold) {
  POT_JITTER_THRESHOLD = jitterThreshold;
}

void setMidiCCMapping(int controls[], int amount) {
  for (int i = 0; i < MAPPING_SIZE; i++) {
    midiCCMapping[i] = MIDI_CC_UNKNOWN;
  }

  for (int i = 0; i < amount; i++) {
    midiCCMapping[i] = controls[i];
    midiCCValues[i] = 0;
  }

  Serial.println("Configured MIDI controls");
}

void setPotPinMapping(byte pins[], int amount) {
  for (int i = 0; i < MAPPING_SIZE; i++) {
    potPinMapping[i] = POT_UNKNOWN;
  }

  for (int i = 0; i < amount; i++) {
    pinMode(pins[i], INPUT);

    potPinMapping[i] = pins[i];
    potPrevValues[i] = 0;
    potCurrentValues[i] = 0;
    potMappedValues[i] = 0;
  }

  Serial.println("Configured potentiometers");
}

void setInputValue(int index, int value) {
  inputValues[index] = value;
}

int getMidiCCValue(int index) {
  return midiCCValues[index];
}

int getPotValue(int index) {
  return potMappedValues[index];
}

int getInputValue(int index) {
  return inputValues[index];
}

void handleMidiControlChange(byte channel, byte control, byte value) {
  for (int i = 0; i < MAPPING_SIZE; i++) {
    if (control == midiCCMapping[i]) {
      midiCCValues[i] = (int) value;

      setInputValue(i, (int) value);
    }
  }
}

void handlePotInputs() {
  for (int i = 0; i < MAPPING_SIZE; i++) {
    if (potPinMapping[i] == POT_UNKNOWN) {
      continue;
    }

    int potCurVal = analogRead(potPinMapping[i]);
    int potPrevVal = potPrevValues[i];
    int margin = potPrevVal * 0.02;

    if (
      potCurVal > potPrevVal + (POT_JITTER_THRESHOLD + margin)
      || potCurVal < potPrevVal - (POT_JITTER_THRESHOLD + margin)
    ) {
      potPrevValues[i] = potCurVal;

      int mapped = map(potCurVal, POT_MIN, POT_MAX, 0, 127);

      if (potMappedValues[i] != mapped) {
        potMappedValues[i] = mapped;
        setInputValue(i, mapped);
      }
    }
  }
}
