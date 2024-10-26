#include "ConsoleWidget.h"
#include "NeatButton.h"

// Add console widgets here
// NeatButton is just an example widget that uses the built-in LED and a single button on pin 5
NeatButton neatButton;
ConsoleWidget* widgets[] = { &neatButton };

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
    usbMIDI.read(); // Process incoming MIDI
}
