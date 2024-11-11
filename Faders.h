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

  int fader_values[FADER_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
};

#endif
