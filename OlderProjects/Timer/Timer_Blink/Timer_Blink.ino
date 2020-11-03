#include "Timer.h"

Timer t;

/*
int every(long period, callback, int repeatCount) 
int after(long duration, callback) 
int oscillate(int pin, long period, int startingValue) 
int oscillate(int pin, long period, int startingValue, int repeatCount) 
int pulse(int pin, long period, int startingValue) 
int stop(int id) 


*/
const int LED = 6;
const int Pushbutton = 3;
const int Sensor1 = A0;
const int Sensor2 = A1;
int Sensorvalue1;
int Sensorvalue2;


void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Pushbutton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  t.update();
  t.oscillate(LED, 500, HIGH, 5);
  //t.every(1000,blink);
  //t.every(1500, blinkoff);
  //t.every(1000, takeReading);
  //Serial.print("Sensor 1 = ");
  //Serial.println(Sensorvalue1);
  //Serial.print("Sensor 2 = ");
  //Serial.println(Sensorvalue2);
}

void blink()
{
  digitalWrite(LED, HIGH);
  //t.after(2000, blinkoff);
}


void blinkoff()
{
  digitalWrite(LED, LOW);
}

void takeReading()
{
    Sensorvalue1 = map(analogRead(Sensor1),0,1023,0,10);
    Sensorvalue2 = map(analogRead(Sensor2),0,1023,0,10);
}
