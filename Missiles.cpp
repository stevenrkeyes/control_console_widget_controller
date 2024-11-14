#include <Arduino.h>
#include "Missiles.h"

Missiles::Missiles() {}

void Missiles::setup() {
    for (int i = 0; i < MISSILES_COUNT; ++i) {
        pinMode(_missilePins[i], INPUT);
    }
    Serial.println("SETTING UP MISSILES");    
}

void Missiles::CheckDataSendHID() {
    for (int i = 0; i < MISSILES_COUNT; ++i) {
        bool new_val = digitalRead(_missilePins[i]) == HIGH;
        if (new_val != _missileValues[i]) {
            Serial.printf("Missile %d flipped; is now %d\n", i, new_val);
            _missileValues[i] = new_val;
            Joystick.button(i + 1, new_val);
        }
    }
}

void Missiles::UpdateAnimationFrame() {
    // No animation for missiles.
}
