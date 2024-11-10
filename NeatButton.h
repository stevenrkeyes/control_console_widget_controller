#ifndef NEATBUTTON_H
#define NEATBUTTON_H

#include "limits.h"
#include <Bounce2.h>
#include "ConsoleWidget.h"
#include "pins.h"

constexpr int NEAT_BUTTON_MIDI_CHANNEL = 1;

constexpr int NEAT_BUTTON_MAX_BRIGHTNESS = 255;
constexpr int NEAT_BUTTON_MID_BRIGHTNESS = 90;
constexpr int NEAT_BUTTON_MIN_BRIGHTNESS = 40;
constexpr unsigned long NEAT_BUTTON_PRESS_DURATION = 350;
constexpr unsigned long NEAT_BUTTON_RELEASE_DURATION = 200;

class NeatButton : public ConsoleWidget {
public:
  NeatButton();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  Bounce button;
  unsigned long pressTimeMs = ULONG_MAX;    // Time when the button was pressed
  unsigned long releaseTimeMs = ULONG_MAX;  // Time when the button was released
};

#endif
