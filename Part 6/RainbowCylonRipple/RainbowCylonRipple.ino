#include <FastLED.h>                            
                                    
#define NUM_LEDS 30
#define NUM_LEDS_RAINBOW 10
#define NUM_LEDS_CYLON 20  
#define NUM_LEDS_RIPPLE 30
#define maxRipples 6

int CYLON_Delay = 50;
int CYLON_LEDS = 9;

bool CYLON_UP = true;

unsigned long Time_Delay = 0;
 
CRGB Strip1[NUM_LEDS];

CRGBPalette16 currentPalette = OceanColors_p;
CRGBPalette16 targetPalette = OceanColors_p;

static uint8_t hue = 0;
 
void setup() { 
  Serial.begin(9600); 
  LEDS.addLeds<NEOPIXEL,6>(Strip1, NUM_LEDS);
  delay(1000);
}
 
void FADE_CYLON()
{
  for(int CYLON_LEDs = 0; CYLON_LEDs < NUM_LEDS_CYLON; CYLON_LEDs++)
  {
    Strip1[CYLON_LEDs].nscale8(200);
  }
}

void FADE_RIPPLE()
{
  for(int RIPPLE_LEDs = 0; RIPPLE_LEDs < NUM_LEDS_RIPPLE; RIPPLE_LEDs++)
  {
    Strip1[RIPPLE_LEDs].nscale8(200);
  }
}

struct ripple {
  uint8_t brightness;
  int8_t color;
  int16_t pos;
  int8_t velocity;
  uint8_t life;
  uint8_t maxLife;
  uint8_t fade;
  bool exist;
 
  void Move() {
    
    pos += velocity;
    life++;
    
    if (pos > NUM_LEDS - 1) {
      velocity *= -1;
      pos = NUM_LEDS - 1;
    }
    
    if (pos < 0) {
      velocity *= -1;
      pos = 0;
    }
    
    brightness = scale8(brightness, fade);
    if (life > maxLife) exist = false;
    
  }

  void Init(uint8_t Fade, uint8_t MaxLife) {    
    pos = random8(NUM_LEDS/8, NUM_LEDS-NUM_LEDS/8);
    velocity = 1;
    life = 0;
    maxLife = MaxLife;
    exist = true;
    brightness = 255;
    color = millis();
    fade = Fade;    
  }  
};

typedef struct ripple Ripple;

Ripple ripples[maxRipples];

void rippless() {

  for (int i = 0; i < maxRipples; i += 2) {
    if (random8() > 224 && !ripples[i].exist) {
      ripples[i].Init(192, 10);
      ripples[i + 1] = ripples[i];
      ripples[i + 1].velocity *= -1;
    }
  }
  
  for (int i = 0; i < maxRipples; i++) {
    if (ripples[i].exist && 20 <= ripples[i].pos) {
      Strip1[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
      ripples[i].Move();
    }
    else if(ripples[i].exist)
    {
      ripples[i].Move();
    }
  }
  
  FADE_RIPPLE();
  
}

void SetupMySimilar4Palette() {

  uint8_t thishue = random8();

  targetPalette = CRGBPalette16(CHSV(thishue+random8(32), 255, random8(200,255)),
                                CHSV(thishue+random8(32), 255, random8(190,255)),
                                CHSV(thishue+random8(32), 192, random8(180,255)),
                                CHSV(thishue+random8(32), 255, random8(170,255)));

}
 
void loop () {
  //RAINBOW LEDS 0-9
  uint8_t thisSpeed = 20;
  uint8_t deltaHue= 5;
  uint8_t thisHue = beat8(thisSpeed,255);
  fill_rainbow(Strip1, NUM_LEDS_RAINBOW, thisHue, deltaHue);            
  FastLED.show();

  
  //CYLON LEDS 10-19
  if(CYLON_LEDS < NUM_LEDS_CYLON && millis() - CYLON_Delay > Time_Delay && CYLON_UP == true)
  {
    CYLON_LEDS++;
    Time_Delay = millis();
    Serial.println("UP");
    Strip1[CYLON_LEDS] = CHSV(hue++, 255, 255);
    FastLED.show();
    FADE_CYLON();    
    if(CYLON_LEDS == NUM_LEDS_CYLON - 1)
    {
      CYLON_UP = false;
    }
  }
  if(CYLON_LEDS > 10 && millis() - CYLON_Delay > Time_Delay && CYLON_UP == false)
  {
    CYLON_LEDS--;
    Time_Delay = millis();
    Serial.println("DOWN");
    Strip1[CYLON_LEDS] = CHSV(hue++, 255, 255);
    FastLED.show();
    FADE_CYLON();
    
    if(CYLON_LEDS == 10)
    {
      static uint8_t hue = 0;
      CYLON_UP = true;
    }
  }

  
  //RIPPLE LEDS 20-29
  EVERY_N_MILLISECONDS(50) {
    uint8_t maxChanges = 24; 
      nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  
  }

  EVERY_N_SECONDS(5) {
    SetupMySimilar4Palette();
  }

  EVERY_N_MILLIS(50) {
    rippless();
  }

  FastLED.show();   
}
