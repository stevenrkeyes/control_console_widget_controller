a# MIDI Widget Controller

Teensy 4.1 and 3.2 firmware that controls the flight deck widgets and sends MIDI commands.

# Setup

Follow the below instructions to setup up the Arduino IDE and required libraries.

## Install Arduino and Teensy support

Download and install the Arduino IDE (tested on version 2.3.3). Open the program.

Click File > Preferences (on MacOS, click Arduino IDE > Settings). In "Additional boards manager URLs", copy this link and click "ok": https://www.pjrc.com/teensy/package_teensy_index.json

In the main Arduino window, open Boards Manager by clicking the left-side board icon, search for "teensy" to find the Teensy library by Paul Stroffregen, and click "Install".

(This is based on the [instructions from PJRC](https://www.pjrc.com/teensy/td_download.html), the team behind Teensy)

## Install libraries

In the Arduino main window, open Library Manager by clicking the left-side library icon, and search for and install the following libraries:

 - Bounce2 by Thomas O Fredericks
 - Adafruit seesaw Library

## Configure Arduino

Select Tools > Board > Teensy > Teensy 4.1 or 3.2 dependong on which you are using

Select Tools > USB Type > Keyboard + Mouse + Joystick
