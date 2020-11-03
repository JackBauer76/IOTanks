#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            2
#define NUMPIXELS      4
#define COLORSTEP 10
// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//    

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#include "Timer.h"
Timer t;

int delayval = 1; // delay for half a second
int delaycol = 24;
const int PIR = 3;
const int Pushbutton = 3;
int state = HIGH;   
int reading;        
int previous = LOW; 
long time = 0; 
long debounce = 200;  

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(Pushbutton, INPUT_PULLUP);


}

void loop() 
{
    
  reading = digitalRead(Pushbutton);
  if ((reading == HIGH)&&(previous == LOW)&&(millis() - time > debounce))
  {
    if (state == HIGH)
    {
      state = LOW;
    }
    else
    {
      state = HIGH;

    }
    time = millis();
  }
  //digitalWrite(LED,state);
  previous = reading;
  
  //t.oscillate(LED,1000, LOW, 2000);
  t.update();
    /////////////////////
    if(state)
    {
        for(int i=0; i<NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(255,0,0));
          pixels.show();
          
        }
        //delay(500);
    }

    else
    {
     for(int i=0; i<NUMPIXELS; i++)
      {
        pixels.setPixelColor(i,0,0,0); 
        pixels.show(); 
        pixels.setPixelColor(i, pixels.Color(0,0,250));
        pixels.show();
        
      }
      //delay(500);
    }

}
