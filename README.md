# Teensy MIDI CC and Potentiometer Mapping

A small library which allow for easy mapping of potentiometer values and MIDI CC values coming in.
Works with Teensy.

## Why and what?

To read incoming MIDI CC values and analog readings of potentiometers and map the values to an 
easy-to-use simple function call. So that we don't need to code this thing every single time
ourselves.

It will bind a potentiometer input and a MIDI CC input to the same index. The index will output
whichever value changed last. So if you're using MIDI that will be the value, but if you change to
your analog potentiometer that will be the value now.

It also handles input noise on the potentiometers so you don't have to worry about swinging and
jittering values.

## How?

Place both `midi_pot_mapping.cpp` and `midi_pot_mapping.h` in your Teensy projects' folder (next to
your `.ino` file).

The following in an excerpt of the example in (`example.ino`)[./example.ino]:

```
#include "midi_pot_mapping.h"

setup() {
  // start reading CC messages for 66, 67, 68, and 69
  int ccMapping[7] = { 66, 67, 68, 69 };
  setMidiCCMapping(ccMapping, 4);
  
  // read the first 3 analog pins
  byte potMapping[3] = { A0, A1, A2 };
  setPotPinMapping(potMapping, 3);
  
  // setup MIDI to handle incoming messages
  usbMIDI.setHandleControlChange(handleMidiControlChange);
}

loop() {
  // handle pot each loop
  handlePotInputs();
  
  // reading the value of the first input:
  int value0 = getInputValue(0);
}
```

### Setting a bigger jitter buffer

Are the potentiometers still picking up noise? You can increase the threshold, though it's not
recommended and you should probably check your wiring.

```
setup() {
  setJitterThreshold(6);
}
```

### I want more than 8 inputs to keep track of!

In `midi_pot_mapping` you can change the value of `MAPPING_SIZE` to what ever you like. High number
means lower performance, so only take what you need.
