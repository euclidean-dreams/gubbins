#include <Arduino.h>
#include <FastLED.h>

#include <list>

#define DATA_PIN 15
#define LED_COUNT 50
#define BRIGHTNESS 100
#define COLOR_DRIFT 2
#define MAX_RAYS 20
#define RAY_SPAWN_CHANCE 8

CRGB leds[LED_COUNT];

struct Ray {
    CRGB color;
    int origin;
    int size;
};

std::list<Ray> rays{};


CRGB baseColor{static_cast<uint8_t>(random(70)), static_cast<uint8_t>(random(70)), static_cast<uint8_t>(random(70))};

void setup() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(BRIGHTNESS);
}

uint8_t driftColor(int color) {
    int result = color + random(COLOR_DRIFT) - COLOR_DRIFT / 2;
    while (result < 0) {
        result += 100;
    }
    result %= 100;
    return result;
}

Ray createRay(CRGB baseColor) {
    return {
        {driftColor(baseColor.red),
         driftColor(baseColor.green),
         driftColor(baseColor.blue)},
        random(LED_COUNT),
        1};
}

void setLed(int index, CRGB color) {
    while (index < 0) {
        index += LED_COUNT;
    }
    index %= LED_COUNT;
    leds[index] = color;
}

void loop() {
    baseColor = CRGB{driftColor(baseColor.red),
         driftColor(baseColor.green),
         driftColor(baseColor.blue)};
    for (int index = 0; index < LED_COUNT; index++) {
        CRGB varianceColor = CRGB{driftColor(baseColor.red),
         driftColor(baseColor.green),
         driftColor(baseColor.blue)};
        setLed(index, varianceColor);
    }
    FastLED.show();
    delay(50);
}
