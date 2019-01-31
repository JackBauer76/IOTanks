// New pins for Nano L293 Robot (Yoavs)
// Version 2 will be updated with new logic

#include <L298N.h>
#include "Timer.h"
Timer t;

//pin definition
#define EN1 10
#define IN1 9
#define IN2 3

#define EN2 5
#define IN3 11
#define IN4 6
#define trigPin A0
#define echoPin A1


//create a motor instance
L298N motor1(EN1, IN2, IN1);
L298N motor2(EN2, IN4, IN3);

volatile long duration, distance_fine;
int randNumber;
int randNumber2;
int randomdir;
int randomturning;
int rand_speed;

void setup() {

  //used for display information
  Serial.begin(9600);

  motor1.setSpeed(180); // an integer between 0 and 255
  motor2.setSpeed(180); // an integer between 0 and 255
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance_fine =t.every(20, readDistance);
}

void loop()
{
    t.update();
    Serial.println(distance_fine);
    if(distance_fine < 30)
    {
      if(distance_fine < 10)
      {
        
        backward(160);
      }
      else
      {
      turnright(190);
      }
    }
    else
    {
      forward(200);
    }

    
/*
    while(distance_fine  < 15)
    {
      forward(150);
    }
    
  */  
    
}



int readDistance() {
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

void forward(int DC_Speed){
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  motor1.forward();
  motor2.forward();
  }



void backward(int DC_Speed){
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  motor1.backward();
  motor2.backward();
}


void turnleft(int DC_Speed){
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  motor1.forward();
  motor2.backward();
}

void turnright(int DC_Speed){
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  motor1.backward();
  motor2.forward();
}

void stop_engine(){
  motor1.stop();
  motor2.stop();
}


