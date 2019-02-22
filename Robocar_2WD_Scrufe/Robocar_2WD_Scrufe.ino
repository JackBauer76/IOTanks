#include <L298N.h>
#include "Timer.h"
#include <Servo.h>


Timer t;
Servo myservo; 

//pin definition
#define EN1 3
#define IN1 4
#define IN2 6

#define EN2 5
#define IN3 7
#define IN4 8

#define trigPin 11
#define echoPin 10
#define servoPin 9

//create a motor instance
L298N motor1(EN1, IN2, IN1);
L298N motor2(EN2, IN4, IN3);


volatile long duration, distance_fine;
int randNumber;
int randNumber2;
int randomdir;
int randomturning;
int motor_speed = 255;

void setup() 
{
  myservo.attach(servoPin); 
  motor1.setSpeed(motor_speed); 
  motor2.setSpeed(motor_speed);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance_fine =t.every(50, readDistance);
  myservo.write(90);  
}

void loop()
{
    t.update();
    //Serial.println(distance_fine);
    forward(motor_speed);
    turn_head_left();
    turn_head_right();
/*
    if(distance_fine < 30)
    {
      turn_head_left();
      if(distance_fine < 10)
      {
          turnright(motor_speed);
      }
      else
      {
        turn_head_right();
        if(distance_fine < 10)
        {
            turnleft(motor_speed);
        }
        else
        {
          backward(motor_speed);
          delay(500);
          turnright(motor_speed);
        }
      
      }
    }
    else
    {
      turn_head_right();
      forward(motor_speed);
    }

*/    
} // end of loop



void turn_head_left()
{

    for (int pos = 90; pos <= 120; pos += 1) 
    { 
        myservo.write(pos);             
        delay(25);                      
    }
}

void turn_head_right()
{

  for (int pos = 120; pos >= 60; pos -= 1) 
    { 
        myservo.write(pos);             
        delay(25);                      
    }
}

int readDistance() 
{
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
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
