/*
TaschenAlarm
using 2x tilt sensors, buzzer, 18650
V2. Using nano

*/

#include "TA31.h"

#define LedPin 5
#define SirenPin 12
#define TiltSensor 2
#define TiltSensor2 3// new version

#define TiltGnd 11
#define TDelayStart 5000

bool sensorValue;
bool lastTiltState = HIGH;
long lastDebounceTime = 0;
long debounceDelay = 50;
bool motionStatus;

#include <avr/interrupt.h>
volatile int MotionState = 0;
volatile byte counter = 0;

void setup()
{
    pinMode(LedPin, OUTPUT);
    pinMode(TiltSensor, INPUT_PULLUP);
    pinMode(TiltSensor2, INPUT_PULLUP);//new version
    pinMode(SirenPin, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(TiltSensor), motionDetector, CHANGE);
    attachInterrupt(digitalPinToInterrupt(TiltSensor2), motionDetector, CHANGE);
    Serial.begin(9600);
    
    for(int i=0; i< 50;i++)
    {
      digitalWrite(LedPin, HIGH);
      delay(20);
      digitalWrite(LedPin, LOW);
      delay(20);
      
    }
    
}

void loop()
{
//motionStatus = digitalRead(TiltSensor);

if(motionStatus)
{
      for(int i=0; i< 75;i++)
    {
      digitalWrite(LedPin, HIGH);
      delay(40);
      digitalWrite(LedPin, LOW);
      delay(40);
      
    }  
}
else
{
  digitalWrite(LedPin, LOW);
}

motionStatus? tone(SirenPin, 3700): noTone(SirenPin);    
}

void motionDetector()
{
      motionStatus = !motionStatus;      
}
