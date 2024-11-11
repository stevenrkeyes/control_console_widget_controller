#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

class GlobalState {
    uint8_t LEDGridHue = 0;
    uint8_t LEDGridSaturation = 255;
public:
    uint8_t getLEDGridHue() { return LEDGridHue; }
    void setLEDGridHue(uint8_t val) { LEDGridHue = val; }

    uint8_t getLEDGridSaturation() { return LEDGridSaturation; }
    void setLEDGridSaturation(uint8_t val) { LEDGridSaturation = val; }
};

#endif