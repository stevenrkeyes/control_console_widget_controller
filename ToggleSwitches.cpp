#include <Arduino.h>
#include "ToggleSwitches.h"

ToggleSwitches::ToggleSwitches() {}

void ToggleSwitches::setup() {
    for (int i = 0; i < TOGGLE_SWITCHES_COUNT; ++i) {
        pinMode(_toggleSwitchPins[i], INPUT_PULLDOWN);
    }
    Serial.println("SETTING UP TOGGLE SWITCHES");    
}

void ToggleSwitches::CheckDataSendHID() {
    for (int i = 0; i < TOGGLE_SWITCHES_COUNT; ++i) {
        bool new_val = digitalRead(_toggleSwitchPins[i]) == HIGH;
        if (new_val != _toggleSwitchValues[i]) {
            Serial.printf("Toggle switch %d flipped; is now %d\n", i, new_val);
            _toggleSwitchValues[i] = new_val;
            Joystick.button(i + 1, new_val);
        }
    }
}

void ToggleSwitches::UpdateAnimationFrame() {
    // No animation for toggle switches.
}
