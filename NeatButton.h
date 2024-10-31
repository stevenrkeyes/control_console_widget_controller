#ifndef NEATBUTTON_H
#define NEATBUTTON_H

#include "limits.h"
#include <Bounce2.h>
#include "ConsoleWidget.h"

constexpr int NEAT_BUTTON_PIN = 0;
constexpr int NEAT_BUTTON_MIDI_CHANNEL = 1;
constexpr int NEAT_BUTTON_LED_PIN = 13;

constexpr int NEAT_BUTTON_MAX_BRIGHTNESS = 255;
constexpr int NEAT_BUTTON_MID_BRIGHTNESS = 80;
constexpr int NEAT_BUTTON_MIN_BRIGHTNESS = 0;
constexpr unsigned long NEAT_BUTTON_PRESS_DURATION = 350;
constexpr unsigned long NEAT_BUTTON_RELEASE_DURATION = 200;

class NeatButton : public ConsoleWidget {
public:
  NeatButton();
  void setup() override;
  void CheckDataSendMIDI() override;
  void UpdateAnimationFrame() override;

private:
  Bounce button;
  unsigned long pressTimeMs = ULONG_MAX;    // Time when the button was pressed
  unsigned long releaseTimeMs = ULONG_MAX;  // Time when the button was released
};

#endif
