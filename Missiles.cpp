// #include <Arduino.h>
// #include "SwitchButtons.h"

// SwitchButtons::SwitchButtons() {}

// void SwitchButtons::setup() {
//     pinMode(SWITCH_PIN_A, INPUT);
//     pinMode(SWITCH_PIN_B, INPUT);
//     pinMode(SWITCH_PIN_C, INPUT);
//     pinMode(SWITCH_BUTTONS_BUTTON_LED_PIN, OUTPUT);
//     Serial.begin(38400);
//     Serial.println("SETTING UP SWITCHBUTTON");    
// }

// void SwitchButtons::CheckDataSendMIDI() {
//     // Probably need to think about note allocaion at some point.
//     const int note_a_on = 70;
//     const int note_a_off = 71;
//     const int note_b_on = 72;
//     const int note_b_off = 73;
//     const int note_c_on = 74;
//     const int note_c_off = 75;
//     const int velocity = 99;

//     // Currently this constantly sends notes as long as the switch is on / off.
//     // Instead, we should check if the value has changed and send the corresponding value.
//     if (switch_a_on) {
//         usbMIDI.sendNoteOn(note_a_on, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     } else {
//         usbMIDI.sendNoteOn(note_a_off, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     }

//     if (switch_b_on) {
//         usbMIDI.sendNoteOn(note_b_on, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     } else {
//         usbMIDI.sendNoteOn(note_b_off, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     }

//     if (switch_c_on) {
//         usbMIDI.sendNoteOn(note_c_on, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     } else {
//         usbMIDI.sendNoteOn(note_c_off, velocity, SWITCH_BUTTONS_MIDI_CHANNEL);
//     }
// }

// void SwitchButtons::UpdateAnimationFrame() {

//   bool new_a_val = digitalRead(SWITCH_PIN_A) == HIGH;
//   bool new_b_val = digitalRead(SWITCH_PIN_B) == HIGH;
//   bool new_c_val = digitalRead(SWITCH_PIN_C) == HIGH;

//   bool anything_changed = false;

//   // Duplicating the same code 3 times is not optimal; this is to make debugging hardware easier.
//   if (new_a_val != switch_a_on) {
//     Serial.println("SWITCH A FLIPPED");
//     Serial.printf("Was: %d | is: %d\n", switch_a_on, new_a_val);
//     anything_changed = true;
//   }
//   if (new_b_val != switch_b_on) {
//     Serial.println("SWITCH B FLIPPED");
//     Serial.printf("Was: %d | is: %d\n", switch_b_on, new_b_val);
//     anything_changed = true;
//   }
//   if (new_c_val != switch_c_on) {
//     Serial.println("SWITCH C FLIPPED");
//     Serial.printf("Was: %d | is: %d\n", switch_c_on, new_c_val);
//     anything_changed = true;
//   }

//   unsigned long current_time_ms = millis();
//   if (anything_changed) {
//     // Only do updates if FLIP_TIME_THRESHOLD has passed.
//     if (current_time_ms - last_switch_time > FLIP_TIME_THRESHOLD) {
//       switch_a_on = new_a_val;
//       switch_b_on = new_b_val;
//       switch_c_on = new_c_val;
//     }

//     // Reset the last switch time to note that we registered a change.
//     // Do this even if we didn't decide to update the real values, since otherwise 
//     // we'd just keep registering "changes" every FLIP_TIME_THRESHOLD when given constant noise.
//     last_switch_time = current_time_ms;
//   }
// }
