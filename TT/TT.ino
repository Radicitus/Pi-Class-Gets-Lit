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
bool isDefault = true;
bool firstSetup = true;


unsigned long previousMillis = 0;        
const long interval = 1000;          

void rainbowStart();
void pressurePad1(int &score1);
void pressurePad2(int &score2);
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
void meteorRainLong(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
void fadeToBlack(int ledNo, byte fadeValue);
void setPixel(int Pixel, byte red, byte green, byte blue);
void fadeInOut(byte red, byte green, byte blue);
void fadeInOutlong1(byte red, byte green, byte blue);
void fadeInOutlong2(byte red, byte green, byte blue);
void Blink(byte red, byte green, byte blue);
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
  Serial.print("\nAnalog1 reading = ");
  Serial.print(fsrReading1);
  Serial.print("; score1 = ");
  Serial.println(score1);
  fsrReading2 = analogRead(fsrAnalogPin1);
  Serial.print("Analog2 Reading = ");
  Serial.print(fsrReading2);
  Serial.print("; score2 = ");
  Serial.println(score2);
  pressurePad1(score1); // green
  pressurePad2(score2); // reg
 
  if (score1 < 27 && score2 < 27 )
  { 
      if (isDefault == false || firstSetup == true)
      {
      isDefault = true;
      firstSetup = false;
      for(int i=0;i<63;i+=2)
      {
         setPixel(i,0xEF, 0x1A, 0x4D);
         setPixel(i+1,0x77, 0x77, 0x77);
      }
      FastLED.show();
      for(int i=98;i<151;i+=2){
         setPixel(i,0xEF, 0x1A, 0x4D);
         setPixel(i+1,0x77, 0x77, 0x77);

      }
      FastLED.show();
      }
//      uint8_t starthue = beatsin8(0xEF, 0x1A, 0x4D);
//      uint8_t endhue = beatsin8(119, 119, 119);
//      fill_gradient(leds, 0, CHSV(starthue,89,93), 62, CHSV(endhue,0,46), SHORTEST_HUES);
      
      //pressurePad1(score1); // green
      //pressurePad2(score2); // red
      //meteorRainlong1(0xff,0xff,0xff,10, 64, true, 30); //trailing lights
      //meteorRainlong2(0xff,0xff,0xff,10, 64, true, 30); //trailing lights
      //fadeInOutlong1(0x00, 0xff, 0x77);
      //fadeInOutlong2(0x00, 0xff, 0x77);

    }
    //tiebreaker
    if (score1==27 && score2==27)
    {
      pressurePad1(score1); // green
      pressurePad2(score2); // red
      fadeInOut(0xff, 0x77, 0x00); // tie break effect
      
      isDefault = false;
    }

    //game end
    if (score1 ==30 || score2 ==30)
    {
      if (score1 == 30)
      {
        Blink(0x00, 0x77, 0x00);
        colorWipe(0x00,0xff,0x00, 50); //wave of green lights
        colorWipe(0x00,0x00,0x00, 50); //turns off the green lights
        score1 = 0, score2 = 0;
      }
      else
      {
        Blink(0xff, 0x00, 0x00);
        colorWipe(0xff,0x00,0x00, 50); //wave of red lights
        colorWipe(0x00,0x00,0x00, 50); //turns off the green lights
        score1 = 0, score2=0;
      }
      isDefault = false;
    {
      //meteorRain(0xff,0xff,0xff,10, 64, true, 30); //trailing lights
      //colorWipe(0x00,0x00,0x00, 50); //turns off the lights
    }
    
  }
}
  //meteorRain(0xff,0xff,0xff,10, 64, true, 30); //trailing lights
  //colorWipe(0x00,0xff,0x00, 50); //wave of green lights
  //colorWipe(0x00,0x00,0x00, 50); //turns off the green lights

 //pressurePad1(score1);
  //pressurePad2(score2);
  

  //LEDbrightness = map(fsrReading1, 0, 1023, 0, 255);



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
  if (fsrReading1 > 100 && score1 < 30) 
  {     
    if (ledState == LOW) 
    {
      score1 += 3;
      Blink(0x77, 0x77, 0x77);
      showScores();
      
      ledState = HIGH;
      isDefault = false;
    }

    else 
    {
      ledState = LOW;
    }
    
    FastLED.show();
    //delay(100);
  }
}

void pressurePad2(int &score2)
{
  if (fsrReading2 > 100 && score2 < 30) 
  {     
    if (ledState == LOW) 
    {
      score2 +=3;
      Blink(0x77, 0x77, 0x77);
      showScores();
      
      ledState = HIGH;
      isDefault = false;
    }

    else 
    {
      ledState = LOW;
    }
    
    FastLED.show();
    //delay(100);
  }
}

void showScores() {
  int base1 = 150;
  int base2 = 63;

  for(int i=3; i<=score1; i += 3) {
    leds[base1 + i] = CRGB(0, 255, 0);
  }
  
  for(int i=3; i<=score2; i += 3) {
    leds[base2 + i] = CRGB(255, 0, 0);
  }
  
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {    
  for(int i = 0; i < NUM_LEDS; i++) {
    
    
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
void meteorRainlong1(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {    
  for(int i = 0; i < 63; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<63; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize-9; j++) {
      if( ( i-j <63) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    FastLED.show();   
    //delay(SpeedDelay);
  }
}
void meteorRainlong2(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {    
  for(int i = 98; i < 151; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=98; j<151; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize-9; j++) {
      if( ( i-j <151) && (i-j>=0) ) {
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
//
//void fadeInOut(byte red, byte green, byte blue)
//{
//  float r, g, b;
//      
//  for(int k = 0; k < 256; k=k+1) { 
//    r = (k/256.0)*red;
//    g = (k/256.0)*green;
//    b = (k/256.0)*blue;
//    FastLED.show();
//  }
//     
//  for(int k = 255; k >= 0; k=k-2) 
//  {
//    r = (k/256.0)*red;
//    g = (k/256.0)*green;
//    b = (k/256.0)*blue;
//    FastLED.show();
//  }
//}

void fadeInOut(byte red, byte green, byte blue)
{
  float r, g, b;

  static int k = 255;
  static bool increasing = false;

  Serial.print("fadeInOut: ");
  Serial.println(k);
  
  r = (k/256.0)*red;
  g = (k/256.0)*green;
  b = (k/256.0)*blue;
  fill_solid(leds, NUM_LEDS, CRGB(r,g,b));
  FastLED.show();

  if (k >= 255) 
  {
    increasing = false;
    k -= 5;
  } 
  
  else if (k <= 0) 
  {
    increasing = true;
    k += 5;
  } 
  
  else if (increasing) 
  {
    k += 5;
  } 
  
  else 
  {
    k -= 5;
  }
}

void fadeInOutlong1(byte red, byte green, byte blue)
{
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for(int i =0;i<63;i++){
      setPixel(i,r,g,b);
    }
    FastLED.show();
  }
     
  for(int k = 255; k >= 0; k=k-2) 
  {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for(int i =0;i<63;i++){
      setPixel(i,r,g,b);
    }
    FastLED.show();
  }
}

void fadeInOutlong2(byte red, byte green, byte blue)
{
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for(int i =98;i<151;i++){
      setPixel(i,r,g,b);
    }
    FastLED.show();
  }
     
  for(int z = 255; z >= 0; z=z-2){
  
    r = (z/256.0)*red;
    g = (z/256.0)*green;
    b = (z/256.0)*blue;
    for(int i =98;i<151;i++){
      setPixel(i,r,g,b);
    }
    FastLED.show();
  }
}

void Blink(byte red, byte green, byte blue)
{
  float r, g, b;
  for (int i=0; i<2; i++){
    
    for(int k = 0; k < 50; k=k+1) { 
      r = red;
      g  = green;
      b = blue;
      fill_solid(leds, NUM_LEDS, CRGB(r,g,b));
      FastLED.show();
    }
  
    //delay(249);
       
    for(int k = 0; k < 50; k=k+1) { 
      r = 0.0;
      g  = 0.0;
      b = 0.0;
      fill_solid(leds, NUM_LEDS, CRGB(r,g,b));
      FastLED.show();
    }
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