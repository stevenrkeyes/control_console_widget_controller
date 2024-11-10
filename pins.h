#ifndef PINS_H
#define PINS_H

// Pin to determine which controller this is (A, B, C)
constexpr int CONTROLLER_VARIANT_PIN = 0;

/*********** Controller A *******************/

// TODO: Change to 20-23.
constexpr int RED_JOYSTICK_TOP_LEFT_PIN = 5;
constexpr int RED_JOYSTICK_TOP_RIGHT_PIN = 6;
constexpr int RED_JOYSTICK_BOT_LEFT_PIN = 7;
constexpr int RED_JOYSTICK_BOT_RIGHT_PIN = 8;


/*********** Controller B *******************/

// PowerButtons
constexpr int POWER_BUTTONS_BUTTON1_PIN = 1;
constexpr int POWER_BUTTONS_BUTTON2_PIN = 2;
constexpr int POWER_BUTTONS_BUTTON3_PIN = 3;
constexpr int POWER_BUTTONS_BUTTON4_PIN = 4;
constexpr int POWER_BUTTONS_BUTTON5_PIN = 5;
constexpr int POWER_BUTTONS_LED1_PIN = 6;
constexpr int POWER_BUTTONS_LED2_PIN = 7;
constexpr int POWER_BUTTONS_LED3_PIN = 8;
constexpr int POWER_BUTTONS_LED4_PIN = 9;
constexpr int POWER_BUTTONS_LED5_PIN = 10;

// NeatButton
constexpr int NEAT_BUTTON_PIN = 12;
constexpr int NEAT_BUTTON_LED_PIN = 13;

// Faders
constexpr int FADER1_PIN = 14;
constexpr int FADER2_PIN = 15;
constexpr int FADER3_PIN = 16;
constexpr int FADER4_PIN = 17;
constexpr int FADER5_PIN = 18;
constexpr int FADER6_PIN = 19;
constexpr int FADER7_PIN = 20;
constexpr int FADER8_PIN = 21;

// LEDGrid
constexpr int LED_GRID_PIN = 22;

// Jogwheel
constexpr int JOGWHEEL_OPTO1_PIN = 34;  // First optocoupler output
constexpr int JOGWHEEL_OPTO2_PIN = 35;  // Second optocoupler output

#endif
