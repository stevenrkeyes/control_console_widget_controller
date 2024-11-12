#ifndef KNOBS_H
#define KNOBS_H

#include "ConsoleWidget.h"
#include "pins.h"

constexpr int KNOBS_COUNT = 4;

class Knobs : public ConsoleWidget {
public:
  Knobs();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    int _knobPins[KNOBS_COUNT] = { 
        KNOB1_PIN,
        KNOB2_PIN,
        KNOB3_PIN,
        KNOB4_PIN,
    };

    void (usb_joystick_class::*knob_changed_callbacks[KNOBS_COUNT])(unsigned int) = {
        &usb_joystick_class::X,
        &usb_joystick_class::Y,
        &usb_joystick_class::Z,
        &usb_joystick_class::Zrotate,
    };

    int _knobValues[KNOBS_COUNT] = {0, 0, 0, 0};
};

#endif
