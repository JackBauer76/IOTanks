/*
TaschenAlarm
using tilt sensor, buzzer, 18650
V1. Using nano

*/

#include "TA31.h"

int sensorValue;
int lastTiltState = HIGH;
long lastDebounceTime = 0;
long debounceDelay = 50;

void setup()
{
    pinMode(LedPin, OUTPUT);
    pinMode(TiltSensor, INPUT_PULLUP);
    pinMode(SirenPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    
    sensorValue = digitalRead(TiltSensor);
    digitalWrite(SirenPin, LOW);
    if(sensorValue==lastTiltState)
    {
        lastDebounceTime = millis();
    }
    if((millis() - lastDebounceTime) < debounceDelay)
    {
        lastTiltState = sensorValue;
        //digitalWrite(SirenPin, HIGH);
        //delay(250);
    }
    digitalWrite(LedPin, lastTiltState);
    
    
    Serial.println(sensorValue);
    

        
    

   

}
