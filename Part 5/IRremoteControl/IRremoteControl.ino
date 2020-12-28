#include <FastLED.h>
#include <IRremote.h>

#define Num_Strip1 28
#define RECV_PIN 7

CRGB Strip1[Num_Strip1];

IRrecv irrecv(RECV_PIN);
decode_results results; 

int Program = 0;
int maxProgram = 2;
int Num = 0;
int Run = 0;
int Program0Delay = 100;
int Program1Delay = 100;
int Program2Delay = 10;

unsigned long DelayTime = 0;

bool Active = false;

void setup()
{
  FastLED.addLeds<NEOPIXEL,6>(Strip1, Num_Strip1);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void translateIR()
{
  switch(results.value)
  {
    case 0xFF629D: ProgramUP(); ClearStrip(); Active = true; Serial.println("VOL+");           break;
    case 0xFFA857: ProgramDown(); ClearStrip(); Active = true; Serial.println("VOL-");         break;
    case 0xFF6897: Num = 0; Program = 0; Run = 0; ClearStrip(); Active = true; Serial.println("0");     break;
    case 0xFF30CF: Num = 0; Program = 1; Run = 0; ClearStrip(); Active = true; Serial.println("1");     break;
    case 0xFF18E7: Num = 0; Program = 2; ClearStrip(); Active = true; Serial.println("2");     break;
    case 0xFF7A85: StaticColour(0); Program = 6 && Serial.println("3");     break;
    case 0xFF10EF: StaticColour(100); Program = 6 && Serial.println("4");     break;
    case 0xFF38C7: StaticColour(155); Program = 6 && Serial.println("5");     break;
    case 0xFF5AA5:  Serial.println("6");     break;
    case 0xFF42BD:  Serial.println("7");     break;
    case 0xFF4AB5:  Serial.println("8");     break;
    case 0xFF52AD:  Serial.println("9");     break;
    case 0xFFA25D: ClearStrip(); Serial.println("OFF");

    default:
      Serial.println("other Button");
  }
}

void ClearStrip()
{
  Num = 0;
  for(; Num < Num_Strip1; Num++)
  {
    Strip1[Num] = CHSV(255, 255, 0);
  }
  FastLED.show();
  Num = 0;
}

void ProgramUP()
{
  Num = 0;
  Run = 0;
  if(Program < maxProgram)
  {
    Program++;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
  else
  {
    Program = 0;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
}

void ProgramDown()
{
  Num = 0;
  Run = 0;
  if(Program > 0)  {
    Program--;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
  else
  {
    Program = maxProgram;
     for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
}

void StaticColour(int colour) {
  Num = 0;
  for(; Num < Num_Strip1; Num++)
  {
    Strip1[Num] = CHSV(colour, 255, 255);
  }
  FastLED.show();
}

void loop()
{
if(irrecv.decode(&results))
{
  Run = 0;
  Active = false;
  translateIR();
  Serial.println(results.value, HEX);
  irrecv.resume();
}

  if(Active == true && Program == 0 && Run == 0 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    if(Num > Num_Strip1) {
      Run = 1;
      Num = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 1 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num++;
    if(Num > Num_Strip1) {
      Run = 2;
      Num = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 2 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num++;
    if(Num > Num_Strip1)  {
      Run = 3;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 3 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 4;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 4 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 5;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 5 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 0;
      Num = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 1 && Run == 0 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num >= Num_Strip1 - 1) {
      Run = 1;
    }
    FastLED.show();
  }
  
  if(Active == true && Program == 1 && Run == 1 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num <= 0)  {
      Run = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 2 && millis() - DelayTime >= Program2Delay)  {
    DelayTime = millis();
    for(; Num <= Num_Strip1; Num++) {
      Strip1[Num] = CHSV(random(0, 255), 255, 255);
    }
    FastLED.show();
    Num = 0;
  }
}
