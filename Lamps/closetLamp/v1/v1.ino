

/* Closet lamp version 1.1
 *  23.12.19
 *  
 *  Objective: Test range & recognition hability of 
 *  mini PIR
 *  Radar
 *  USS
 * 
 */

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
//      Ain0 (D 5) PB5  1|    |8  Vcc
// PIR  Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1     Neopixel
//      Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     Rotor
//                 GND  4|    |5  PB0 (D 0) pwm0     Pushbutton
//    

    #include <avr/interrupt.h> 
    #ifdef __AVR__
    #include <avr/power.h>
    #endif
    #include "Timer.h"
    
    //#define USS
    #ifdef USS 
    const int trigPin = 10;
    const int echoPin = 11;
    volatile long duration, distance_fine;
    #endif

    const int mPir = 2;
    const int radarPin = 3;
    const int blueLed = 11;
    const int whiteLed = 9;
    bool pirCheck = false;
    bool radarCheck = false;
    bool tryDelay = true;
    const int tDelay = 20;
    volatile int AuthState = 0;
    volatile int radarState = 0;
    const int trigPin = 10;
    const int echoPin = 11;
    volatile long duration, distance_fine;

    Timer t;  

void setup() 
{
  pinMode(mPir, INPUT); 

  #ifdef USS
    pinMode(radarPin, INPUT); 
    pinMode(trigPin, OUTPUT);
    distance_fine =t.every(10, readDistance);
  #endif

  pinMode(echoPin, INPUT);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(mPir), motionDetection, CHANGE);
  attachInterrupt(digitalPinToInterrupt(radarPin), radarDetector, CHANGE);
  
}

 ///////// INTERRUPT ROUTINE //////////////////////////
void motionDetection() 
{ 
    AuthState = !AuthState;
}

void radarDetector() 
{ 
    radarState = !radarState;
}

#ifdef USS
int readDistance() {
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  if(duration ==0)
  {
    duration = 10000;
  }
  distance_fine = (duration/2) / 29.1;
  return distance_fine;
}
#endif

/////////////////////////// LOOP //////////////////////////////////
void loop() 
{
    if(AuthState)
    {
        digitalWrite(whiteLed, HIGH);
    }
    else if(radarState)
    {
        digitalWrite(blueLed, HIGH);
    }
    else
    {
        digitalWrite(whiteLed, LOW);
        digitalWrite(blueLed, LOW);
    }
    #ifdef USS
      if (distance_fine > 120)
    {
        /**/
    }
    #endif
}
