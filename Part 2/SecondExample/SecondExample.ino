#include <FastLED.h>

#define Num_Strip1 11

CRGB Strip1[Num_Strip1];

int a = 0;

void setup()  {
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
}

void loop() {
  for(int a = 0; a <= 10; a++) {
    Strip1[a] = CHSV(255, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }

  for(int a = 0; a <= 10; a++) {
    Strip1[a] = CHSV(155, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }

  for(int a = 0; a <= 10; a++) {
    Strip1[a] = CHSV(100, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }
  
  for(int a = 10; a >= 0; a--) {
    Strip1[a] = CHSV(255, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }

  for(int a = 10; a >= 0; a--) {
    Strip1[a] = CHSV(155, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }

  for(int a = 10; a >= 0; a--) {
    Strip1[a] = CHSV(100, 255, 255);
    FastLED.show();
    Serial.println(a);
    delay(100);
  }
}
