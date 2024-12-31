#include <Arduino.h>
#include "LEDGridPatterns.h"
#include "pins.h"
#include <FastLED.h>

constexpr int ROWS = 5;
constexpr int COLS = 10;
constexpr int FRAMES_PER_SECOND = 60;
constexpr int NUM_LEDS = 50;

/* 
    General functions
*/
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

/* Sine wave */
// Colors
const CRGB BACKGROUND_COLOR = CRGB(20, 0, 30);  // Dark purple
const CRGB WAVE_COLOR = CRGB(0, 150, 255);      // Light blue

// Calculate the wave height at a given position
float calculateWaveHeight(float x, float time, uint8_t amplitude, uint8_t wavelength) {
    // Convert wavelength from columns (3-10) to radians
    float frequency = TWO_PI / (wavelength * ROWS);
    
    // Calculate base sine wave
    float wave = sin(frequency * x + time);
    
    // Scale amplitude from 1-5 rows
    float scaledWave = wave * ((amplitude - 1) / 2);
    
    // Center the wave vertically
    return ROWS / 2.0 + scaledWave;
}

// Draw a single frame of the animation
void drawWaveFrame(float time, uint8_t amplitude, uint8_t wavelength, CRGB* leds) {
    // Clear the display
    fill_solid(leds, NUM_LEDS, BACKGROUND_COLOR);
    
    // Draw the wave for each column
    for (int col = 0; col < COLS; col++) {
        // Calculate wave height for this column
        float waveHeight = calculateWaveHeight(col, time, amplitude, wavelength);
        
        // Draw the wave pixel and add some vertical blur for smoothness
        for (int row = 0; row < ROWS; row++) {
            float distanceFromWave = abs(row - waveHeight);
            if (distanceFromWave < 1.0) {
                uint8_t brightness = 255 * (1.0 - distanceFromWave);
                int ledIndex = mapToLED(row, col);
                leds[ledIndex] = WAVE_COLOR;
                leds[ledIndex].nscale8(brightness);
            }
        }
    }
    
    FastLED.show();
}

// Main animation loop
void animateWave(uint8_t amplitude, uint8_t wavelength, CRGB* leds) {
    static float time = 0;
    
    // Calculate time increment based on frame rate
    float timeIncrement = TWO_PI / (2 * FRAMES_PER_SECOND);
    
    // Update animation
    drawWaveFrame(time, amplitude, wavelength, leds);
    time += timeIncrement;
    
    // Keep time bounded
    if (time >= TWO_PI) {
        time -= TWO_PI;
    }
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}


/* Pulsating bar */
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