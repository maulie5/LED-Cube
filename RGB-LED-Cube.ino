#include <FastLED.h>
#define NUM_LEDS 27
#define LED_PIN D6
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2812,LED_PIN,GRB>(leds,NUM_LEDS);
}

void loop() {

}
