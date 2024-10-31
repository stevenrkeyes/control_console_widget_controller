#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"

// Add console widgets here
// NeatButton is just an example widget that uses the built-in LED and a single button on pin 5
NeatButton neatButton;
PowerButtons powerButtons;
ConsoleWidget* widgets[] = { &neatButton, &powerButtons };

void setup() {
  for (auto widget : widgets) {
    widget->setup();
  }
}

void loop() {
  for (auto widget : widgets) {
    widget->CheckDataSendMIDI();
    widget->UpdateAnimationFrame();
  }
  usbMIDI.read();  // Process incoming MIDI
}
