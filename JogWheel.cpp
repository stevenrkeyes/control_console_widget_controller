#include <Arduino.h>
#include <Bounce2.h>
#include "JogWheel.h"


volatile int JogWheel::pulseCount1 = 0;
volatile int JogWheel::pulseCount2 = 0;
volatile int JogWheel::lastPulseCount1 = 0;
volatile int JogWheel::lastPulseCount2 = 0;

// Direction detection
volatile int JogWheel::direction = 0;  // 1 = clockwise, -1 = counterclockwise, 0 = no motion
volatile unsigned long JogWheel::sensor1Time = 0;
volatile unsigned long JogWheel::sensor2Time = 0;

// Variables for state machine
volatile uint8_t JogWheel::sensorStates = 0;  // Stores current state of both sensors
volatile int8_t JogWheel::prevState = 0;      // Previous combined state

JogWheel::JogWheel() {
}

void JogWheel::setup() {
  pinMode(JOGWHEEL_OPTO1_PIN, INPUT);
  pinMode(JOGWHEEL_OPTO2_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(JOGWHEEL_OPTO1_PIN), sensorChange1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(JOGWHEEL_OPTO2_PIN), sensorChange2, CHANGE);
}

void JogWheel::CheckDataSendMIDI() {
  // Check for no motion
  if (millis() - max(sensor1Time, sensor2Time) > MOTION_TIMEOUT) {
    direction = 0;  // No motion detected
  }

  // Send MIDI based on direction and speed
  int pulses = max(pulseCount1 - lastPulseCount1, pulseCount2 - lastPulseCount2);
  if (pulses > 0) {
    if (direction == 1) {
      usbMIDI.sendControlChange(1, pulses, JOGWHEEL_MIDI_CHANNEL);  // CW rotation
    } else if (direction == -1) {
      usbMIDI.sendControlChange(2, pulses, JOGWHEEL_MIDI_CHANNEL);  // CCW rotation
    }
  }

  lastPulseCount1 = pulseCount1;
  lastPulseCount2 = pulseCount2;
}

void JogWheel::UpdateAnimationFrame() {
  // No LED animation needed for jogwheel
}


void JogWheel::sensorChange1() {
  // Update state machine with current real state
  bitWrite(sensorStates, 0, digitalRead(JOGWHEEL_OPTO1_PIN));
  updateDirection();
  if (digitalRead(JOGWHEEL_OPTO1_PIN) == HIGH) pulseCount1++;
  sensor1Time = millis();
}

void JogWheel::sensorChange2() {
  // Update state machine with current real state
  bitWrite(sensorStates, 1, digitalRead(JOGWHEEL_OPTO2_PIN));
  updateDirection();
  if (digitalRead(JOGWHEEL_OPTO2_PIN) == HIGH) pulseCount2++;
  sensor2Time = millis();
}

// Handle direction updates
void JogWheel::updateDirection() {
  int8_t currentState = sensorStates;

  // Gray code sequence for quadrature encoder
  switch (prevState) {
    case 0b00:
      direction = (currentState == 0b01) ? -1 : ((currentState == 0b10) ? 1 : direction);
      break;
    case 0b01:
      direction = (currentState == 0b11) ? -1 : ((currentState == 0b00) ? 1 : direction);
      break;
    case 0b11:
      direction = (currentState == 0b10) ? -1 : ((currentState == 0b01) ? 1 : direction);
      break;
    case 0b10:
      direction = (currentState == 0b00) ? -1 : ((currentState == 0b11) ? 1 : direction);
      break;
  }

  prevState = currentState;
}
