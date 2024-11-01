#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Faders.h"

// Add console widgets here
// NeatButton is just an example widget that uses the built-in LED and a single button on pin 5
NeatButton neatButton;
PowerButtons powerButtons;
Faders faders;
ConsoleWidget* widgets[] = { &neatButton, &powerButtons, &faders };

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
