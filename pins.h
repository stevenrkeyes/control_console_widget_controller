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

// Big Button
constexpr int BIG_BUTTON_PIN = 32;

// Jogwheel 1
constexpr int JOGWHEEL_LEFT_OPTO1_PIN = 34;  // First optocoupler output
constexpr int JOGWHEEL_LEFT_OPTO2_PIN = 35;  // Second optocoupler output

// Jogwheel 2
constexpr int JOGWHEEL_RIGHT_OPTO1_PIN = 36;  // First optocoupler output
constexpr int JOGWHEEL_RIGHT_OPTO2_PIN = 37;  // Second optocoupler output

// Missiles
constexpr int MISSILE_SWITCH_A_PIN = 38;
constexpr int MISSILE_SWITCH_B_PIN = 39;
constexpr int MISSILE_SWITCH_C_PIN = 40;

/*********** Controller C *******************/

// Triangle Buttons
constexpr int TRIANGLE_BUTTONS_BUTTON1_PIN = 1;
constexpr int TRIANGLE_BUTTONS_BUTTON2_PIN = 2;
constexpr int TRIANGLE_BUTTONS_BUTTON3_PIN = 3;
constexpr int TRIANGLE_BUTTONS_BUTTON4_PIN = 4;
constexpr int TRIANGLE_BUTTONS_BUTTON5_PIN = 5;
constexpr int TRIANGLE_BUTTONS_BUTTON6_PIN = 6;
constexpr int TRIANGLE_BUTTONS_LED1_PIN = 7;
constexpr int TRIANGLE_BUTTONS_LED2_PIN = 8;
constexpr int TRIANGLE_BUTTONS_LED3_PIN = 9;
constexpr int TRIANGLE_BUTTONS_LED4_PIN = 10;
constexpr int TRIANGLE_BUTTONS_LED5_PIN = 11;
constexpr int TRIANGLE_BUTTONS_LED6_PIN = 17;

// Knobs (on controller C because it has extra joystick axis outputs)
constexpr int KNOB1_PIN = 20;
constexpr int KNOB2_PIN = 21;
constexpr int KNOB3_PIN = 22;
constexpr int KNOB4_PIN = 23;

#endif
