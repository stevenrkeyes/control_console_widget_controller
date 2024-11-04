#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Trellis.h"
#include "Joystick.h"

// Add console widgets here
// NeatButton is just an example widget that uses the built-in LED and a single button on pin 5
// NeatButton neatButton;
// PowerButtons powerButtons;
Joystick joystick;
Trellis trellis;
// ConsoleWidget* widgets[] = { &neatButton, &powerButtons, &joystick };
ConsoleWidget* widgets[] = { &joystick, &trellis };

void setup() {
  // TODO remove.
  Serial.begin(9600);
  Serial.print("starting");
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
