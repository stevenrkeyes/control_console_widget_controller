#include <Arduino.h>
#include "LEDGridPatterns.h"
#include "pins.h"
#include <FastLED.h>

constexpr int ROWS = 5;
constexpr int COLS = 10;
constexpr int FRAMES_PER_SECOND = 60;

int mapToLED(int row, int col) {    
    // Check if we're in a column that goes bottom-to-top
    bool isBottomToTop = (col % 2 == 0);
    
    if (isBottomToTop) {
        // For bottom-to-top columns, start from bottom
        return col * ROWS + (ROWS - 1 - row);
    } else {
        // For top-to-bottom columns, start from top
        return col * ROWS + row;
    }
}

// Get the current bar width for a given row based on time
int getBarWidth(int row, uint32_t currentMillis) {
    // Different ranges for each row
    const struct {
        int min;
        int max;
    } ranges[] = {
        {2, 8},  // Row 0
        {3, 7},  // Row 1
        {4, 6},  // Row 2
        {3, 7},  // Row 3
        {2, 8}   // Row 4
    };
    
    // Calculate sine wave animation
    float timeScale = currentMillis / 1000.0f; // Convert to seconds
    float offset = timeScale + (row * PI / 4); // Phase offset for each row
    float range = (ranges[row].max - ranges[row].min) / 2.0f;
    float center = (ranges[row].max + ranges[row].min) / 2.0f;
    
    return round(center + sin(offset) * range);
}

void showPulsatingBars(uint8_t hue, CRGB* leds) {
    uint32_t currentMillis = millis();
    
    // Clear all LEDs
    FastLED.clear();
    
    // Update each row
    for (int row = 0; row < ROWS; row++) {
        int barWidth = getBarWidth(row, currentMillis);
        float centerCol = (COLS - 1) / 2.0f;
        
        // Update each column in the row
        for (int col = 0; col < COLS; col++) {
            float distFromCenter = abs(col - centerCol);
            
            // Check if this LED should be lit
            if (distFromCenter <= barWidth / 2.0f) {
                int ledIndex = mapToLED(row, col);
                
                // Create color gradient based on position and time
                uint8_t rowHue = (hue + (row * 255 / ROWS)) % 256;
                uint8_t brightness = 255 * (1.0f - (distFromCenter / (barWidth / 2.0f)));
                
                leds[ledIndex] = CHSV(rowHue, 255, brightness);
            }
        }
    }
    
    // Show the updated LED values
    FastLED.show();
    
    // Add a small delay to maintain frame rate
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}