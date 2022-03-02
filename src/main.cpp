#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 2
#define LED_COUNT 9
#define BRIGHTNESS 70

CRGB leds[LED_COUNT];

#define LED_WIDTH 3
#define LED_HEIGHT 3
#define PATTERN_COUNT 16
bool patterns[PATTERN_COUNT][3][3] = {
    {{1, 0, 1},
     {0, 0, 0},
     {1, 0, 1}},

    {{0, 1, 0},
     {1, 1, 1},
     {0, 1, 0}},

    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},

    {{0, 0, 0},
     {0, 1, 0},
     {0, 0, 0}},

    {{1, 0, 1},
     {0, 1, 0},
     {1, 0, 1}},

    {{0, 1, 0},
     {1, 0, 1},
     {0, 1, 0}},

    {{1, 0, 0},
     {0, 1, 0},
     {0, 0, 1}},

    {{0, 0, 1},
     {0, 1, 0},
     {1, 0, 0}},

    {{1, 1, 0},
     {1, 0, 1},
     {0, 1, 1}},

    {{0, 1, 1},
     {1, 0, 1},
     {1, 1, 0}},

    {{1, 1, 1},
     {0, 0, 0},
     {1, 1, 1}},

    {{1, 0, 1},
     {1, 0, 1},
     {1, 0, 1}},

    {{0, 0, 0},
     {1, 1, 1},
     {0, 0, 0}},

    {{0, 1, 0},
     {0, 1, 0},
     {0, 1, 0}},

    {{1, 0, 1},
     {1, 1, 1},
     {1, 0, 1}},

    {{1, 1, 1},
     {0, 1, 0},
     {1, 1, 1}},
};

int LAST_PATTERN_INDEX = 0;

void setup() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    // pattern selection
    int patternIndex = 0;
    while (patternIndex == LAST_PATTERN_INDEX) {
        patternIndex = random(PATTERN_COUNT);
    }

    // color variation
    int red = random(70);
    int green = random(70);
    int blue = random(70);

    // set leds
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            int ledIndex = row * LED_WIDTH + column;
            bool activateLed = patterns[patternIndex][row][column];
            if (activateLed) {
                leds[ledIndex] = CRGB(red, green, blue);
            } else {
                leds[ledIndex] = CRGB(0, 0, 0);
            }
        }
    }
    FastLED.show();
    delay(100);
}