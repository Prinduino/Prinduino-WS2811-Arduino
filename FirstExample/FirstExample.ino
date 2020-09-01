#include <FastLED.h>

#define Num_Strip1 11

CRGB Strip1[Num_Strip1];

void setup() {
  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
}

void loop() {
  for(int a = 0; a < 10; )  {
    Strip1[a] = CHSV(255, 255, 255);
    a++;
    Strip1[a] = CHSV(155, 255, 255);
    FastLED.show();
    delay(100);
  }

  for(int a = 10; a > 0; )  {
    Strip1[a] = CHSV(255, 255, 255);
    a--;
    Strip1[a] = CHSV(155, 255, 255);
    FastLED.show();
    delay(100);
  }
}
