#include <FastLED.h>

#define Num_Strip1 30

CRGB Strip1[Num_Strip1];

int Num = 0;
int Run = 0;
int ProgramDelay = 100;

unsigned long DelayTime = 0;

void setup()  {
  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
}

void loop() {
  if(Run == 0 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    if(Num >= Num_Strip1 - 1) {
      Run = 1;
      Num = 0;
    }
    FastLED.show();
  }

  if(Run == 1 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num++;
    if(Num >= Num_Strip1 - 1) {
      Run = 2;
      Num = 0;
    }
    FastLED.show();
  }

  if(Run == 2 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num++;
    if(Num >= Num_Strip1 - 1)  {
      Run = 3;
      Num = Num_Strip1;
    }
    FastLED.show();
  }

  if(Run == 3 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    if(Num <= 0)  {
      Run = 4;
      Num = Num_Strip1;
    }
    FastLED.show();
  }

  if(Run == 4 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num--;
    if(Num <= 0)  {
      Run = 5;
      Num = Num_Strip1;
    }
    FastLED.show();
  }

  if(Run == 5 && millis() - DelayTime >= ProgramDelay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num--;
    if(Num <= 0)  {
      Run = 0;
      Num = 0;
    }
    FastLED.show();
  }
}
