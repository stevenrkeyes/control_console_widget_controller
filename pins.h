#ifndef PINS_H
#define PINS_H

// Pin to determine which controller this is (A, B, C)
constexpr int CONTROLLER_VARIANT_PIN = 0;

/*********** Controller A *******************/

// Toggle Switches
// Uses output buttons 1-4
constexpr int TOGGLE_SWITCH1_PIN = 1;
constexpr int TOGGLE_SWITCH2_PIN = 2;
constexpr int TOGGLE_SWITCH3_PIN = 3;
constexpr int TOGGLE_SWITCH4_PIN = 4;

// Red Joystick
// Uses hat switch
constexpr int RED_JOYSTICK_TOP_LEFT_PIN = 5;
constexpr int RED_JOYSTICK_TOP_RIGHT_PIN = 6;
constexpr int RED_JOYSTICK_BOT_LEFT_PIN = 7;
constexpr int RED_JOYSTICK_BOT_RIGHT_PIN = 8;

// Big Button
// Uses output button 5
constexpr int BIG_BUTTON_PIN = 16;


/*********** Controller B *******************/

// PowerButtons
// Uses output buttons 31 - 27
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
// Uses axes 1-6
constexpr int FADER1_PIN = 14;
constexpr int FADER2_PIN = 15;
constexpr int FADER3_PIN = 16;
constexpr int FADER4_PIN = 17;
constexpr int FADER5_PIN = 18;
constexpr int FADER6_PIN = 19;
constexpr int FADER7_PIN = 20;
constexpr int FADER8_PIN = 21;

// LEDGrid
// No outputs
constexpr int LED_GRID_PIN = 22;

// Orb Reader
constexpr int ORB_READER_ORB_INSERTED_PIN = 25;
constexpr int ORB_READER_ENERGY_LEVEL_PIN = 26;
constexpr int ORB_READER_TOXIC_TRAIT_PIN = 27;

// Jogwheel 1
// Uses mouse scroll 1
constexpr int JOGWHEEL_LEFT_OPTO1_PIN = 34;  // First optocoupler output
constexpr int JOGWHEEL_LEFT_OPTO2_PIN = 35;  // Second optocoupler output

// Jogwheel 2
// Uses mouse scroll 2
constexpr int JOGWHEEL_RIGHT_OPTO1_PIN = 36;  // First optocoupler output
constexpr int JOGWHEEL_RIGHT_OPTO2_PIN = 37;  // Second optocoupler output

// Missiles
// Uses output buttons 6-8
constexpr int MISSILE_SWITCH_A_PIN = 38;
constexpr int MISSILE_SWITCH_B_PIN = 39;
constexpr int MISSILE_SWITCH_C_PIN = 40;

/*********** Controller C *******************/

// Triangle Buttons
// Uses output buttons 26-31 (maybe need to change to just 29-31)
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

// Lever
// Uses output button 7
constexpr int LEVER_PIN = 16;

// Knobs (on controller C because it has extra joystick axis outputs)
// Uses axes 1-4
constexpr int KNOB1_PIN = 20;
constexpr int KNOB2_PIN = 21;
constexpr int KNOB3_PIN = 22;
constexpr int KNOB4_PIN = 23;

#endif
