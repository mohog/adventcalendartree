// Advent Calendar Christmas Tree project
// http://www.iliketomakestuff.com/make-arduino-powered-advent-calendar
// By: Bob Clagett for I Like To Make Stuff

//modified from example code from Adafruit.
//https://github.com/adafruit/Adafruit-WS2801-Library

/*
This code is messy, and unsupported :)
I was in a hurry. Feel free to improve it and send pull requests!
*/

#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif


uint8_t dataPin  = 4;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 5;    // Green wire on Adafruit Pixels
int BUTTON_PIN=3;
long randNumber;
int val=0;
int dayCounter=0;
int i=0;
bool causeDelay=false;
int baseBrightness = 10;
int maxBrightnessChange = 5;

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin);


void setup() {
  randomSeed(analogRead(0));
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

pinMode(BUTTON_PIN, INPUT);
  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
}


void loop() {
   // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        dayCounter++;
        ledState = !ledState;
      }
    }
  }

  // set the LED:
 // if (buttonState == HIGH) {         // check if the input is HIGH (button released)
 
 if (dayCounter>25){
      dayCounter=0;
  }
  setupColoredDays();
  
//  }
  
  lastButtonState = reading;
}

void setupColoredDays(){
  for (i=0; i < 25; i++) {
    if(i<dayCounter){
          int clr0 = baseBrightness - random(maxBrightnessChange);
          int clr1 = baseBrightness - random(maxBrightnessChange);
          int clr2 = baseBrightness - random(maxBrightnessChange);   
      strip.setPixelColor(i, clr0,clr1,clr2);
      if(i==24){
        strip.setPixelColor(i, 255,255,255);
      }
    }else{
      strip.setPixelColor(i, 0,0,0);
      }
    }  
    strip.show();   // write all the pixels out
    delay(150);
 }

