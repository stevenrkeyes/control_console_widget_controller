#include <Arduino.h>
#include "LEDGridPatterns.h"
#include "pins.h"
#include <FastLED.h>
#include <cstdlib>

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

uint8_t remap(uint8_t value, uint8_t min, uint8_t max) {
    return min + (uint8_t) (value * (max - min) / 255.0f);
}

/* Sine wave */
// Colors
const CRGB BACKGROUND_COLOR = CRGB(20, 0, 30);  // Dark purple
const CRGB WAVE_COLOR = CRGB(0, 150, 255);      // Light blue

// Calculate the wave height at a given position
float _calculateWaveHeight(float x, float time, uint8_t amplitude, uint8_t wavelength) {
    // Convert wavelength from columns (3-10) to radians
    float frequency = TWO_PI / (wavelength * ROWS);
    
    // Calculate base sine wave
    float wave = sin(frequency * x + time);
    
    // Scale amplitude from 1-5 rows
    float scaledWave = wave * (amplitude - 1);
    
    // Center the wave vertically
    return 2 + scaledWave;
}

// Draw a single frame of the animation
void _drawWaveFrame(float time, uint8_t amplitude, uint8_t wavelength, CRGB* leds) {
    // Clear the display
    fill_solid(leds, NUM_LEDS, BACKGROUND_COLOR);
    
    // Draw the wave for each column
    for (int col = 0; col < COLS; col++) {
        // Calculate wave height for this column
        float waveHeight = _calculateWaveHeight(col, time, amplitude, wavelength);
        
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
void animateWave(uint8_t amplitude_unmapped, uint8_t wavelength_unmapped, CRGB* leds) {
    static float time = 0;

    uint8_t wavelength = remap(wavelength_unmapped, 3, 10);
    uint8_t amplitude = remap(amplitude_unmapped, 1, 5);
    
    // Calculate time increment based on frame rate
    float timeIncrement = TWO_PI / (2 * FRAMES_PER_SECOND);
    
    // Update animation
    _drawWaveFrame(time, amplitude, wavelength, leds);
    time += timeIncrement;
    
    // Keep time bounded
    if (time >= TWO_PI) {
        time -= TWO_PI;
    }
    
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}


/* Pulsating bar */
// Get the current bar width for a given row based on time
int _getBarWidth(int row, uint8_t width_param, uint32_t currentMillis) {
    // Different ranges for each row
    const struct {
        int min;
        int max;
    } ranges[] = {
        // TODO scale this with other parameter.
        {2 - remap(width_param, 0, 2), 8 + remap(width_param, 0, 2)},  // Row 0
        {3 - remap(width_param, 0, 3), 7 + remap(width_param, 0, 3)},  // Row 1
        {4 - remap(width_param, 0, 4), 6 + remap(width_param, 0, 4)},  // Row 2
        {3 - remap(width_param, 0, 3), 7 + remap(width_param, 0, 3)},  // Row 3
        {2 - remap(width_param, 0, 2), 8 + remap(width_param, 0, 2)}   // Row 4
    };
    
    // Calculate sine wave animation
    float timeScale = currentMillis / 1000.0f; // Convert to seconds
    float offset = timeScale + (row * PI / 4); // Phase offset for each row
    float range = (ranges[row].max - ranges[row].min) / 2.0f;
    float center = (ranges[row].max + ranges[row].min) / 2.0f;
    
    return round(center + sin(offset) * range);
}

void showPulsatingBars(uint8_t hue, uint8_t width_param, CRGB* leds) {
    uint32_t currentMillis = millis();
    
    // Clear all LEDs
    FastLED.clear();
    
    // Update each row
    for (int row = 0; row < ROWS; row++) {
        int barWidth = _getBarWidth(row, width_param, currentMillis);
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

/* Pacman */

// Pacman configuration
struct PacmanConfig {
    uint8_t colorHue;     // 0-255 for full color wheel
    uint8_t mouthAngle;   // 0 (closed) to 255 (90 degrees open)
};

bool _isInsidePacman(float x, float y, float mouthAngleRadians) {
    // Center Pacman in the 5x5 grid
    float centerX = 2.0f;
    float centerY = 2.0f;
    
    // Calculate distance from center
    float dx = x - centerX;
    float dy = y - centerY;
    float distance = sqrt(dx * dx + dy * dy);
    
    // Pacman radius (2 pixels to fit in 5x5 grid)
    float radius = 2.0f;
    
    // If point is outside radius, it's not in Pacman
    if (distance > radius) return false;
    
    // Calculate angle from center to point (in radians)
    float angle = atan2(dy, dx);
    if (angle < 0) angle += TWO_PI;  // Convert to 0-2π range
    
    // Check if point is in mouth wedge
    float halfMouthAngle = mouthAngleRadians / 2.0;
    
    // Offset angle to make Pacman face right
    angle = fmod(angle + PI/2, TWO_PI);
    
    return !(angle < halfMouthAngle || angle > TWO_PI - halfMouthAngle);
}

// Draw a single frame of Pacman
void _drawPacmanFrame(const PacmanConfig& config, CRGB* leds) {
    // Clear the display
    FastLED.clear();
    
    // Convert mouth angle from [0,255] to radians [0,π/2]
    float mouthAngleRadians = remap(config.mouthAngle, 0, PI/2);
    
    // Convert hue to RGB color
    CHSV pacmanColor = CHSV(config.colorHue, 255, 255);
    CRGB rgbColor;
    hsv2rgb_rainbow(pacmanColor, rgbColor);
    
    // Draw Pacman pixel by pixel
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            float x = row;
            float y = col % ROWS;
            
            if (_isInsidePacman(x, y, mouthAngleRadians)) {
                int ledIndex = mapToLED(row, col);
                leds[ledIndex] = rgbColor;
            }
        }
    }
    
    FastLED.show();
}

// Main Pacman animation loop
void animatePacman(uint8_t hue, uint8_t mouth_angle, CRGB* leds) {
    PacmanConfig config;
    config.colorHue = hue;
    config.mouthAngle = mouth_angle;
    _drawPacmanFrame(config, leds);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

struct TriangleConfig {
    uint8_t frequency;    // Controls flash speed (0-255)
};

// Define the bright green color
const CRGB TRIANGLE_GREEN = CRGB(255, 0, 0);
const CRGB TRIANGLE_BLACK = CRGB(0, 0, 0);

// Helper function to determine if a point is inside the triangle
bool _isInsideTriangle(int row, int col) {
    return abs(col - 5) < row + 1 ;
}

// Draw a single frame of the triangle pattern
void _drawTriangleFrame(bool inverted, CRGB* leds) {
    // Calculate whether we're in a flash state based on time and frequency
    CRGB foreground = inverted ? TRIANGLE_BLACK : TRIANGLE_GREEN;
    CRGB background = inverted ? TRIANGLE_GREEN : TRIANGLE_BLACK;
    
    // Draw the pattern
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            int ledIndex = mapToLED(row, col);
            if (_isInsideTriangle(row, col)) {
                leds[ledIndex] = foreground;
            } else {
                leds[ledIndex] = background;
            }
        }
    }
    
    FastLED.show();
}

// Main triangle animation loop
void animateTriangle(uint8_t frequency, CRGB* leds) {
    static unsigned long lastUpdate = 0;
    static bool inverted = false;
    
    // Calculate delay between flashes (0x.25s to 2s)
    float flashFreq = remap(frequency, 0.5, 4.0);  // Flashes per second
    unsigned long updateInterval = (unsigned long)(1000.0 / flashFreq);
    
    // Check if it's time to update
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate >= updateInterval) {
        inverted = !inverted;
        lastUpdate = currentTime;
    }
    
    _drawTriangleFrame(inverted, leds);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

// Space Invader configuration
struct InvaderConfig {
    uint8_t colorHue;     // 0-255 for full color wheel
    uint8_t saturation;   // Overall brightness
};

// Classic Space Invader shape (5x5 pixel art)
const bool INVADER_SHAPE[5][5] = {
    {0, 1, 1, 1, 0},  // Top row (tentacles)
    {1, 0, 1, 0, 1},  // Eyes
    {1, 1, 1, 1, 1},  // Full middle row
    {0, 1, 0, 1, 0},  // Legs
    {1, 0, 1, 0, 1}   // Feet
};

// Alternative shapes for animation
const bool INVADER_SHAPE_ALT[5][5] = {
    {0, 1, 1, 1, 0},  // Top row stays same
    {1, 0, 1, 0, 1},  // Eyes stay same
    {1, 1, 1, 1, 1},  // Middle stays same
    {1, 0, 1, 0, 1},  // Legs move out
    {0, 1, 0, 1, 0}   // Feet move in
};

// Draw a single frame of the Space Invader
void drawInvaderFrame(const InvaderConfig& config, bool useAltShape, CRGB* leds) {
    // Clear the display
    FastLED.clear();
    
    // Convert hue to RGB color
    CHSV invaderColor = CHSV(config.colorHue, config.saturation, 255);
    CRGB rgbColor;
    hsv2rgb_rainbow(invaderColor, rgbColor);
    
    // Choose which shape to use
    const bool (*currentShape)[5] = useAltShape ? INVADER_SHAPE_ALT : INVADER_SHAPE;
    
    // Draw the invader pattern
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            // Get position within 5x5 grid
            int gridRow = row;
            int gridCol = col % 5;
            
            // Set LED color based on the pattern
            int ledIndex = mapToLED(row, col);
            if (currentShape[gridRow][gridCol]) {
                leds[ledIndex] = rgbColor;
            } else {
                leds[ledIndex] = CRGB::Black;
            }
        }
    }
    
    FastLED.show();
}

// Main Space Invader animation loop
void animateInvader(uint8_t colorHue, uint8_t saturation, CRGB* leds) {
    InvaderConfig config;
    config.saturation = saturation;
    config.colorHue = colorHue;
    
    static uint8_t animationFrame = 0;
    static unsigned long lastUpdate = 0;
    const unsigned long ANIMATION_INTERVAL = 500; // 500ms between animation frames
    
    // Update animation frame every ANIMATION_INTERVAL milliseconds
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate >= ANIMATION_INTERVAL) {
        animationFrame = !animationFrame;  // Toggle between 0 and 1
        lastUpdate = currentTime;
    }
    
    drawInvaderFrame(config, animationFrame, leds);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

// [Previous animation code remains unchanged...]

// Raindrop configuration
struct RainConfig {
    uint8_t density;     // 0-255: controls how many drops appear
    uint8_t speed;       // 0-255: controls how fast drops fall
};

// Structure to track individual raindrops
struct Raindrop {
    float row;        // Current row position (floating point for smooth movement)
    uint8_t col;      // Column position
    bool active;      // Whether this drop is currently falling
    float velocity;   // How fast this drop is falling
};

#define MAX_DROPS 8

Raindrop raindrops[MAX_DROPS];

// Initialize raindrop system
void initRain() {
    for (int i = 0; i < MAX_DROPS; i++) {
        raindrops[i].active = false;
    }
}

// Create a new raindrop at the top of the display
void createRaindrop(float baseVelocity) {
    // Find an inactive drop slot
    for (int i = 0; i < MAX_DROPS; i++) {
        if (!raindrops[i].active) {
            raindrops[i].row = 0;
            raindrops[i].col = random8(COLS);
            raindrops[i].active = true;
            // Add some randomness to velocity
            raindrops[i].velocity = baseVelocity * (0.8 + (random8(40) / 100.0));
            break;
        }
    }
}

// Draw a single frame of rain
void drawRainFrame(const RainConfig& config, CRGB* leds) {
    // Clear the display
    FastLED.clear();
    fill_solid(leds, 50 , CRGB(25, 0, 60));
    
    // Calculate base velocity from speed parameter
    // bug: always 0 due to uint8_t cast
    float baseVelocity = remap(config.speed, 0.05, 0.3);  // Remap 0-255 to 0.05-0.3 rows per frame
    
    // Randomly create new drops based on density
    if (random8() < config.density) {
        createRaindrop(baseVelocity);
    }
    
    // Update and draw all active drops
    for (int i = 0; i < MAX_DROPS; i++) {
        if (raindrops[i].active) {
            // Update position
            raindrops[i].row += .05 * remap(config.speed, 1, 20);
            
            // Check if drop has fallen off bottom
            if (raindrops[i].row >= ROWS) {
                raindrops[i].active = false;
                continue;
            }
            
            // Draw the drop with a tail
            int currentRow = (int)raindrops[i].row;
            float fraction = raindrops[i].row - currentRow;
            
            // Draw main drop
            if (currentRow < ROWS) {
                int ledIndex = mapToLED(currentRow, raindrops[i].col);
                leds[ledIndex] = CRGB(150, 0, 255);  // Light blue
                leds[ledIndex].nscale8(255);
            }
            
            // Draw tail (fainter)
            if (currentRow > 0) {
                int tailIndex = mapToLED(currentRow - 1, raindrops[i].col);
                leds[tailIndex] = CRGB(100, 0, 200);  // Slightly darker blue
                leds[tailIndex].nscale8(255 * (1.0 - fraction));
            }
        }
    }
    
    FastLED.show();
}

// Main rain animation loop
void animateRain(uint8_t density, u_int8_t speed, CRGB* leds) {
    RainConfig config;
    config.density = density;
    config.speed = speed;

    static bool initialized = false;
    
    if (!initialized) {
        initRain();
        initialized = true;
    }
    
    drawRainFrame(config, leds);
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}
