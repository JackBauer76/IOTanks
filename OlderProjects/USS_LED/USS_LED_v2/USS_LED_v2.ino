/* Version 2 has a Buzzer
 * 
 * 
 */

#include "Timer.h"
Timer t;  

#define trigPin A0
#define echoPin A1
const int BlauLED = 4;
const int Button = 2;
const int VibMotor = 11;
const int Buzzer = 8;
volatile long duration, distance_fine;

void setup() 
{
  Serial.begin(9600);
  pinMode(BlauLED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(VibMotor, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  distance_fine =t.every(25, readDistance);
}


void loop() 
{
    t.update();
    Serial.println(distance_fine);
    if (distance_fine  < 35)
    {
      t.oscillate(BlauLED,25, HIGH, 10);
      digitalWrite(VibMotor, HIGH);
      for(uint8_t i = 1; i<200; i++){
            tone(Buzzer, i*100);  
      }
      
      
      //t.oscillate(Buzzer,25, HIGH, 10);
    }
    else
    {
      analogWrite(BlauLED, 0);
      digitalWrite(VibMotor, LOW);
      noTone(Buzzer);
    }
}


int readDistance() 
{
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  if(duration ==0)
  {
    duration = 1000;
  }
  distance_fine = (duration/2) / 29.1;
  return distance_fine;
}



