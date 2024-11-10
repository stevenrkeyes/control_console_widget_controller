#ifndef FADERS_H
#define FADERS_H

#include "ConsoleWidget.h"
#include "pins.h"

// TODO: Decide if we're going to use:
//    - 1 channel per module
//    - 1 channel per microcontroller
//    - 1 channel globally (defaulting to this for simplicity)
constexpr int FADER_COUNT = 8;

// Uses pings 14 - 21.
constexpr int FADER_PIN_OFFSET = 14;

// These may be used elsewhere; define in a more general location?
constexpr int MAX_MIDI_VELOCITY = 127;
constexpr int MIN_MIDI_VELOCITY = 1;

constexpr int MAX_FADER_VALUE = 1023;
constexpr int MIN_FADER_VALUE = 0;

class Faders : public ConsoleWidget {
public:
  Faders();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  // TODO: Refactor this to a struct?
  int fader_pins[FADER_COUNT] = { FADER1_PIN,
                                  FADER2_PIN,
                                  FADER3_PIN,
                                  FADER4_PIN,
                                  FADER5_PIN,
                                  FADER6_PIN,
                                  FADER7_PIN,
                                  FADER8_PIN };
  bool fader_changed[FADER_COUNT] = { false, false, false, false, false, false, false, false };
  int fader_values[FADER_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  // C Major scale.
  int fader_notes[FADER_COUNT] = { 48, 50, 52, 53, 55, 57, 59, 60 };
};

#endif
