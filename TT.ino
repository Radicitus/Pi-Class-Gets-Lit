#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    300
#define BRIGHTNESS  30

CRGB leds[NUM_LEDS];
 
int fsrAnalogPin0 = 0, fsrAnalogPin1 = 1;
int LEDpin = 5;   
int fsrReading1, fsrReading2, LEDbrightness;
int score1 = 0, score2 = 0;
int ledState = LOW;
int delay_variable = 500;
bool startFlag = false;

unsigned long previousMillis = 0;        
const long interval = 1000;          

void rainbowStart();
void pressurePad1(int &score1);
void pressurePad2(int &score2);
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
void fadeToBlack(int ledNo, byte fadeValue);
void setPixel(int Pixel, byte red, byte green, byte blue);
void FadeInOut(byte red, byte green, byte blue);
void setAll(byte red, byte green, byte blue)
{
  for(int i = 0; i < NUM_LEDS; i++ ) 
  {
    setPixel(i, red, green, blue); 
  }
};
void colorWipe(byte red, byte green, byte blue, int SpeedDelay);

void setup(void) 
{
  Serial.begin(9600);   
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  rainbowStart();
}
 
void loop(void) 
{
  fsrReading1 = analogRead(fsrAnalogPin0);
  Serial.print("Analog reading = ");
  Serial.print(fsrReading1);
  fsrReading2 = analogRead(fsrAnalogPin1);
  Serial.print(" Analog Reading for second = ");
  Serial.print(fsrReading1);
  Serial.print("; Score = ");
  Serial.println(score1);

  //meteorRain(0xff,0xff,0xff,10, 64, true, 30);
  colorWipe(0x00,0xff,0x00, 50);
  colorWipe(0x00,0x00,0x00, 50);

  //pressurePad1(score1);
  //pressurePad2(score2);
  //FadeInOut(0xff, 0x77, 0x00);

  //LEDbrightness = map(fsrReading1, 0, 1023, 0, 255);
}

void rainbowStart()
{
  //Red
  for(int i = 0; i < 48; i++)
  {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
  }

  //Orange
  for(int i = 48; i < 90; i++)
  {
    leds[i] = CRGB(255, 127, 0);
    FastLED.show();    
  }

  //Yellow
  for(int i = 90; i < 132; i++)
  {
    leds[i] = CRGB(255, 255, 0);
    FastLED.show();    
  }

  //Green
  for(int i = 132; i < 174; i++)
  {
    leds[i] = CRGB(0, 255, 0);
    FastLED.show();    
  }

  //Blue
  for(int i = 174; i < 216; i++)
  {
    leds[i] = CRGB(0, 0, 255);
    FastLED.show();    
  }

  //Indigo
  for(int i = 216; i < 258; i++)
  {
    leds[i] = CRGB(75, 0, 130);
    FastLED.show();    
  }  

  //Violet
  for(int i = 258; i < 300; i++)
  {
    leds[i] = CRGB(148, 0, 211);
    FastLED.show();    
  }

  //Turn it off backwards
  for(int i = 299; i >= 0; i--)
  {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();    
  }

  startFlag = true;
}

void pressurePad1(int &score1)
{
  if (fsrReading1 > 100 && score1 < 10) 
  {     
    if (ledState == LOW) 
    {
      score1++;
      int base = 0;

      leds[base + score1] = CRGB( 0, 255, 0);
      ledState = HIGH;
    }

    else 
    {
      ledState = LOW;
    }
    
    FastLED.show();
    delay(500);
  }
}

void pressurePad2(int &score2)
{
  if (fsrReading2 > 100 && score2 < 10) 
  {     
    if (ledState == LOW) 
    {
      score2++;
      int base = 11;

      leds[base + score2] = CRGB( 255, 0, 0);
      ledState = HIGH;
    }

    else 
    {
      ledState = LOW;
    }
    
    FastLED.show();
    delay(500);
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {    
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    FastLED.show();   
    //delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
};

void FadeInOut(byte red, byte green, byte blue)
{
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    FastLED.show();
  }
     
  for(int k = 255; k >= 0; k=k-2) 
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    FastLED.show();
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) 
{
  for(uint16_t i=0; i<NUM_LEDS; i++)
  {
      setPixel(i, red, green, blue);
      FastLED.show();
      delay(SpeedDelay);
  }
}
