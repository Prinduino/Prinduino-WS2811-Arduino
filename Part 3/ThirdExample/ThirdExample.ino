#include <FastLED.h>

#define Num_Strip1 30

CRGB Strip1[Num_Strip1];

int Num = 0;
int ProgramDelay = 10;

unsigned long DelayTime = 0;

void setup()  {
  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
}

void loop() {
  if(millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    for(; Num <= Num_Strip1; Num++) {
      Strip1[Num] = CHSV(random(0, 255), 255, 255);
    }
    FastLED.show();
    Num = 0;
  }
}
