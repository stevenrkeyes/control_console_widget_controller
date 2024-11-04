#include <Arduino.h>
#include "Joystick.h"

Joystick::Joystick() {}

void Joystick::setup() {
  Serial.println("setting up joystick");
  pinMode(JOYSTICK_TOP_LEFT_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_TOP_RIGHT_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_BOT_LEFT_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_BOT_RIGHT_PIN, INPUT_PULLUP);
}

void Joystick::CheckDataSendMIDI() {
  const int velocity = 99;
}

void Joystick::UpdateAnimationFrame() {
  unsigned long currentTimeMs = millis();
  
  bool top_left = digitalRead(JOYSTICK_TOP_LEFT_PIN) == LOW; 
  bool top_right = digitalRead(JOYSTICK_TOP_RIGHT_PIN) == LOW;
  bool bot_left = digitalRead(JOYSTICK_BOT_LEFT_PIN) == LOW;
  bool bot_right = digitalRead(JOYSTICK_BOT_RIGHT_PIN) == LOW;

  if (top_left && top_right) {
    Serial.println("UP");
  } else if (top_left && bot_left) {
    Serial.println("LEFT");
  } else if (bot_left && bot_right) {
    Serial.println("DOWN");
  } else if (bot_right && top_right) {
    Serial.println("RIGHT");
  } else if (top_left) {
    Serial.println("UP-LEFT");
  } else if (top_right) {
    Serial.println("UP-RIGHT");
  } else if (bot_left) {
    Serial.println("BOT-LEFT");
  } else if (bot_right) {
    Serial.println("BOT-RIGHT");
  }
}
