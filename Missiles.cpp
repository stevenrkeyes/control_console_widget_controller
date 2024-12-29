#include <Arduino.h>
#include "Missiles.h"

Missiles::Missiles(GlobalState& state) : state(state) {}

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
    // TODO: Compute a value from 0-7 representing the current state of switches.
    uint8_t missile_switch_val = _missileValues[0] + (_missileValues[1] << 1) + (_missileValues[2] << 2);
    state.setMissileSwitchState(missile_switch_val);
}

void Missiles::UpdateAnimationFrame() {
    // No animation for missiles.
}
