#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif



#define PIN            0
#define NUMPIXELS      4
#define COLORSTEP 10

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
//      Ain0 (D 5) PB5  1|    |8  Vcc
// PIR  Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1     Neopixel
//      Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     Rotor
//                 GND  4|    |5  PB0 (D 0) pwm0     Pushbutton
//    


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#include "Timer.h"
Timer t;
int delayval = 100; // delay for half a second
int delaycol = 24;
//const int PIR = 7;
const int Pushbutton = 3;
//const int Rotor = 1;
int state = HIGH;   
int reading;        
int previous = LOW; 
long time = 0; 
long debounce = 200;  
 

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(Pushbutton, INPUT_PULLUP);
   // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif
 
 // pinMode(Rotor, OUTPUT);
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




    if(state)
    {
    for(int i=0;i<NUMPIXELS;i++)
    {
      pixels.setPixelColor(i, pixels.Color(0,255,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(20); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor(i-1, pixels.Color(0,0,0)); 
      pixels.setPixelColor((i-2), pixels.Color(0,0,255)); 
      pixels.setPixelColor((i-3), pixels.Color(255,0,0)); 
      pixels.setPixelColor((i-3)-1, pixels.Color(0,0,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(20); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor((i-3)-1, pixels.Color(0,0,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
 //     digitalWrite(Rotor, HIGH);
      
      
    }
    for(int i=(NUMPIXELS-1);i>-1;i=i-1)
    {
      pixels.setPixelColor(i, pixels.Color(0,0,255)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(20); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor(i-1, pixels.Color(255,255,0)); 
      pixels.setPixelColor(i+1, pixels.Color(0,0,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
 //     digitalWrite(Rotor, LOW);
      
    }
    }
    
  else
  {
     for(int i=0;i<NUMPIXELS;i++)
     {
      pixels.setPixelColor(i,250,0,0); 
      pixels.show(); // This sends the updated pixel color to the hardware.
     }  
  }

  t.update();
    
    }


