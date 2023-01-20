#include "midi_pot_mapping.h"

void setup() {
  // start serial output
  Serial.begin(9600);

  // map MIDI CC types to input readings
  int ccMapping[7] = { 74, 71, 76, 77, 93, 18, 19 };
  setMidiCCMapping(ccMapping, 7);

  // set potentiometer's analog's pins for mapping
  byte potMapping[3] = { A0, A1, A2 };
  setPotPinMapping(potMapping, 3);

  // setup MIDI message handlers
  usbMIDI.setHandleControlChange(handleMidiControlChange);
}

void loop() {
  // handle pot reading
  handlePotInputs();

  // get a value (last updated from MIDI or potentiometer)
  int value0 = getInputValue(0);

  // get last MIDI CC value
  int value0 = getMidiCCValue(0);

  // get last mapped potentiometer value
  int value0 = getPotValue(0);

  // prevent MIDI crash
  while (usbMIDI.read()) {
  }
}
