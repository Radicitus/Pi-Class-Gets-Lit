/* FSR testing sketch. 
 
Connect one end of FSR to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
Connect LED from pin 11 through a resistor to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */

#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    300
#define BRIGHTNESS  30

CRGB leds[NUM_LEDS];
 
int fsrAnalogPin = 0; // FSR is connected to analog 0
int LEDpin = 5;      // connect Red LED to pin 11 (PWM pin)
int fsrReading;      // the analog reading from the FSR resistor divider
int LEDbrightness;
int score = 0;
bool ballOn = false;
int ledState = LOW;
int delay_variable = 500;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  //pinMode(LEDpin, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
}
 
void loop(void) {
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);
  Serial.print("; Score = ");
  Serial.println(score);


  if (fsrReading > 100) {
    if (!ballOn) {
      score++;
      ballOn = true;
    }
    //score++;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) 
    {
    // save the last time you blinked the LED
      previousMillis = currentMillis;
    }



    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) 
    {
      int a = 0;
      for (int i = 0; i < 10; i++) 
      {
        leds[a + score] = CRGB ( 0, 255, 0);
        ledState = HIGH;
      }
      //delay(delay_variable); 
    } 
 
    else 
    {
      for (int i = 0; i < 10; i++) 
      {
        leds[i] = CRGB ( 0, 0, 0);
        ledState = LOW;
      }
//      if (delay_variable > 100) {
//        delay_variable = delay_variable - 100;
//      }
      //delay(delay_variable); 
    }
  } 
  
  else 
  {
    for (int i = 0; i < 10; i++) 
    {
      leds[i] = CRGB ( 0, 0, 0);
    }

    ballOn = false;
  }

  FastLED.show();

  
  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!
  LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
  // LED gets brighter the harder you press
  
  //analogWrite(LEDpin, LEDbrightness);
 
  //delay(100);
}
