#ifndef FADERS_H
#define FADERS_H

#include "ConsoleWidget.h"
#include "GlobalState.h"
#include "pins.h"

constexpr int FADER_COUNT = 8;

class Faders : public ConsoleWidget {
  GlobalState& state;
public:
  Faders(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  // TODO: Refactor this to a struct?
  int fader_pins[FADER_COUNT] = { 
      FADER1_PIN,
      FADER2_PIN,
      FADER3_PIN,
      FADER4_PIN,
      FADER5_PIN,
      FADER6_PIN,
      FADER7_PIN,
      FADER8_PIN 
  };

  // TODO: Change last two function pointers to something else.
  void (usb_joystick_class::*fader_changed_callbacks[FADER_COUNT])(unsigned int) = {
      &usb_joystick_class::X,
      &usb_joystick_class::Y,
      &usb_joystick_class::Z,
      &usb_joystick_class::Zrotate,
      &usb_joystick_class::sliderLeft,
      &usb_joystick_class::sliderRight,
      nullptr, // Controls LED Grid Hue
      nullptr // Controls LED Grid Saturation
  };

  // TODO: Refactor this to a struct?
  bool fader_changed[FADER_COUNT] = { false, false, false, false, false, false, false, false };
  int fader_values[FADER_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  
  // TODO: Remove this? No longer being used as MIDI.
  // C Major scale.
  int fader_notes[FADER_COUNT] = { 48, 50, 52, 53, 55, 57, 59, 60 };
};

#endif
