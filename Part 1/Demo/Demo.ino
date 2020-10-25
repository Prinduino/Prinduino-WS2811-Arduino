#include <FastLED.h>

#define Num_Strip1 1

CRGB Strip1[Num_Strip1];

int colour = 255;
int fading = 255;
int brightness = 255;

void setup()  {
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
}

void loop() {
  Serial.println("colour");

  for(; colour > 0; colour--)  {
    Strip1[0] = CHSV(colour, 255, 255);
    FastLED.show();
    Serial.println(colour);
    delay(200);
  }

  for(; colour < 255; colour++) {
    Strip1[0] = CHSV(colour, 255, 255);
    FastLED.show();
    Serial.println(colour);
    delay(200);
  }

  Serial.println("fading");

  for(; fading > 0; fading--)  {
    Strip1[0] = CHSV(255, fading, 255);
    FastLED.show();
    Serial.println(fading);
    delay(200);
  }

  for(; fading < 255; fading++) {
    Strip1[0] = CHSV(255, fading, 255);
    FastLED.show();
    Serial.println(fading);
    delay(200);
  }

  Serial.println("brightness");

  for(; brightness > 0; brightness--)  {
    Strip1[0] = CHSV(255, 255, brightness);
    FastLED.show();
    Serial.println(brightness);
    delay(200);
  }

  for(; brightness < 255; brightness++) {
    Strip1[0] = CHSV(255, 255, brightness);
    FastLED.show();
    Serial.println(brightness);
    delay(200);
  }
}
