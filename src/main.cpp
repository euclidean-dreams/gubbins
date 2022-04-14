#include <Arduino.h>
#include <FastLED.h>

#include <list>

#define DATA_PIN 13
#define LED_COUNT 300
#define BRIGHTNESS 20
#define COMET_SPAWN_RATE 50

int ticksSinceLastComet = 999777;

CRGB leds[LED_COUNT];

struct CometBody
{
    int size;
    int locus;
    CRGB color;
};

struct CometTail
{
    CRGB color;
    float fadeRate;
};

struct Comet
{
    CometBody body;
    CometTail tail;
};

std::list<Comet> comets{};

Comet createComet(

)
{
    CometBody cometBody{
        random(10),
        0,
        {random(100),
         random(100),
         random(100)}};

    CometTail cometTail{
        {random(100),
         random(100),
         random(100)},
        static_cast<float>(random(100)) / 100};
    comets.push_back({cometBody,
                      cometTail});
}

void setup()
{
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, LED_COUNT);
    FastLED.setBrightness(BRIGHTNESS);
}

// uint8_t driftColor(int color) {
//     int result = color + random(COLOR_DRIFT) - COLOR_DRIFT / 2;
//     while (result < 0) {
//         result += 100;
//     }
//     result %= 100;
//     return result;
// }

// void boundLED(int index, CRGB color)
// {
//     while (index < 0)
//     {
//         index += LED_COUNT;
//     }
//     index %= LED_COUNT;
//     leds[index] = color;
// }

void renderComet(Comet &comet)
{
    for (int index = 0; index < comet.body.locus - comet.body.size && index < LED_COUNT; index++)
    {
        leds[index] = comet.tail.color;
    }
    for (int index = comet.body.locus - comet.body.size; index < comet.body.locus + comet.body.size && index < LED_COUNT; index++)
    {
        leds[index] = comet.body.color;
    }
}

void loop()
{
    if (ticksSinceLastComet % 10 == 0)
    {
        createComet();
        ticksSinceLastComet = 0;
    }
    else
    {
        ticksSinceLastComet++;
    }
    for (auto &comet : comets)
    {
        renderComet(comet);
        comet.body.locus++;
    }
    // auto iterator = comets.begin();
    // while (iterator != comets.end()) {
    //     auto & comet = *iterator;
    //     renderComet(comet);
    //     comet.body.locus++;
    //     iterator++;

    // if (comet.body.locus + comet.body.size > LED_COUNT) {
    //     iterator = comets.erase(iterator);
    // } else {
    //     iterator++;
    // }
    // }
    FastLED.show();
    delay(random(50));
}
