#ifndef RED_JOYSTICK_H
#define RED_JOYSTICK_H

#include "ConsoleWidget.h"

// TODO: Change to 20-23.
constexpr int RED_JOYSTICK_TOP_LEFT_PIN = 5;
constexpr int RED_JOYSTICK_TOP_RIGHT_PIN = 6;
constexpr int RED_JOYSTICK_BOT_LEFT_PIN = 7;
constexpr int RED_JOYSTICK_BOT_RIGHT_PIN = 8;

constexpr int RED_JOYSTICK_MIDI_CHANNEL = 1;

constexpr int LEFT_NOTE = 10; 
constexpr int TOP_LEFT_NOTE = 11; 
constexpr int TOP_NOTE = 12; 
constexpr int TOP_RIGHT_NOTE = 13; 
constexpr int RIGHT_NOTE = 14; 
constexpr int BOT_RIGHT_NOTE = 15; 
constexpr int BOT_NOTE = 16; 
constexpr int BOT_LEFT_NOTE = 17;

class RedJoystick : public ConsoleWidget {
public:
  RedJoystick();
  void setup() override;
  void CheckDataSendMIDI() override;
  void UpdateAnimationFrame() override;

private:
  // TODO remove.
  bool was_high = false;
};

#endif
