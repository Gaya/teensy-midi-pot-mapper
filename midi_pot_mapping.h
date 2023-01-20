#ifndef MIDI_POT_MAPPING_H
#define MIDI_POT_MAPPING_H
#include <Arduino.h>

// setters
void setJitterThreshold(int jitterThreshold);
void setMidiCCMapping(int controls[], int amount);
void setPotPinMapping(byte pins[], int amount);

// getters
int getMidiCCValue(int index);
int getPotValue(int index);
int getInputValue(int index);

// handlers
void handleMidiControlChange(byte channel, byte control, byte value);
void handlePotInputs();

#endif
