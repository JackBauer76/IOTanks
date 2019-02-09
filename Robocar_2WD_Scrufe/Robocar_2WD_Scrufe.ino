#include <L298N.h>
#include "Timer.h"
#include <Servo.h>
Timer t;

//pin definition
#define EN1 3
#define IN1 4
#define IN2 6

#define EN2 5
#define IN3 7
#define IN4 8

#define trigPin A0
#define echoPin A1
#define servopin 9

//create a motor instance
L298N motor1(EN1, IN2, IN1);
L298N motor2(EN2, IN4, IN3);
Servo myservo; 

volatile long duration, distance_fine;
int randNumber;
int randNumber2;
int randomdir;
int randomturning;
int motor_speed = 220;

void setup() {

  //Serial.begin(9600);
  motor1.setSpeed(motor_speed); 
  motor2.setSpeed(motor_speed);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servopin);
  distance_fine =t.every(50, readDistance);
}

void loop()
{
    t.update();
    //Serial.println(distance_fine);

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
    
} // end of loop



void turn_head_left()
{

  for (int pos = 0; pos <= 180; pos += 1) 
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(15);          
  }
}

void turn_head_right()
{

  for (int pos = 180; pos >= 0; pos -= 1) 
  { // goes from 180 degrees to 0 degrees
    myservo.write(pos); 
    delay(15);          
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


