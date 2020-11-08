#include <FastLED.h>

#define Num_Strip1 50
#define Button 7

CRGB Strip1[Num_Strip1];

int Program = 0;
int maxProgram = 2;
int Num = 0;
int Run = 0;
int ButtonDelay = 500;
int Program0Delay = 100;
int Program1Delay = 100;
int Program2Delay = 10;

unsigned long ButtonTime = 0;
unsigned long DelayTime = 0;

void setup()
{
  pinMode(Button, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
  Serial.begin(9600);
}

void loop()
{
if(digitalRead(Button) == LOW && millis() - ButtonTime > ButtonDelay)
{
  ButtonTime = millis();
  Num = 0;
  Run = 0;
  if(Program < maxProgram)
  {
    Program++;
    for(int Num = 0; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
  else
  {
    Program = 0;
    for(int Num = 0; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
}

  if(Program == 0 && Run == 0 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    if(Num > Num_Strip1) {
      Run = 1;
      Num = 0;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 0 && Run == 1 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num++;
    if(Num > Num_Strip1) {
      Run = 2;
      Num = 0;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 0 && Run == 2 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num++;
    if(Num > Num_Strip1)  {
      Run = 3;
      Num = Num_Strip1 - 1;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 0 && Run == 3 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 4;
      Num = Num_Strip1 - 1;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 0 && Run == 4 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 5;
      Num = Num_Strip1 - 1;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 0 && Run == 5 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 0;
      Num = 0;
      Program = 0;
    }
    FastLED.show();
  }

  if(Program == 1 && Run == 0 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num >= Num_Strip1 - 1) {
      Run = 1;
      Program = 1;
    }
    FastLED.show();
  }
  
  if(Program == 1 && Run == 1 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num <= 0)  {
      Run = 0;
      Program = 1;
    }
    FastLED.show();
  }

  if(Program == 2 && millis() - DelayTime >= Program2Delay)  {
    DelayTime = millis();
    for(; Num <= Num_Strip1; Num++) {
      Strip1[Num] = CHSV(random(0, 255), 255, 255);
    }
    FastLED.show();
    Num = 0;
    Program = 2;
  }
}
