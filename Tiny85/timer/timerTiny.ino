/* Testing the timer library to use it in Tiny
 * 
 * 
 */
// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//    

#include "Timer.h"
Timer t;
const int LED = 4; // Pin Nano2, Pin Tiny4
const int Pushbutton = 0; // Pin Nano3, pin tiny 0

int Beam;
int limitR = 500;
int state = HIGH;   
int reading;        
int previous = LOW; 
long time = 0; 
long debounce = 200;  


void setup() 
{
  pinMode(LED, OUTPUT);
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
  digitalWrite(LED,state);
  previous = reading;
  
  //t.oscillate(LED,1000, LOW, 2000);
  t.update();
}