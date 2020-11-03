

//#define MY_SERVO 3
//#define LED 2

#define BAUDRATE 9600
#define PIR 0
#define LED 7

#ifdef MY_SERVO
#include <Servo.h>
Servo myservo; 
int pos = 0;    
#endif


#ifdef LED 
#include "Timer.h"
Timer t;
#endif

#ifdef PIR 
#include <avr/interrupt.h>
volatile int MotionState = 0;
volatile byte counter = 0;
const int BlueLED = 4;
const int WhiteLED = 5;
#endif

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

  #ifdef MY_SERVO
  myservo.attach(MY_SERVO);  // attaches the servo on pin 9 to the servo object
  #endif

  #ifdef LED
  pinMode(LED, OUTPUT);
  #endif

  #ifdef PIR
  pinMode(BlueLED, OUTPUT);
  pinMode(WhiteLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIR), motionDetector, RISING);
  #endif

  #ifdef BAUDRATE
  Serial.begin(BAUDRATE);
  #endif

}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() 
{
  #ifdef MY_SERVO
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  #endif 

  #ifdef LED
    t.update();
    t.oscillate(LED, 2000, LOW, 50);
  #endif


  #ifdef PIR
    void motionDetector()
    {
      MotionState = !MotionState;
      (digitalRead(BlueLED))? digitalWrite(BlueLED,LOW): digitalWrite(BlueLED,HIGH);
      (digitalRead(BlueLED))? digitalWrite(WhiteLED,HIGH): digitalWrite(WhiteLED,LOW);
    }
  #endif


  
} // End of Loop

