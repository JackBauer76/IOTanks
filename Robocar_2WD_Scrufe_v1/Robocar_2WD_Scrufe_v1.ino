/*
In this sketch I will try to call the distance 
function each time i need it (w/o timer)


*/

#include <L298N.h>
#include "Timer.h"

#include <Servo.h>

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
Timer t;
Servo myservo; 

volatile long duration, distance_fine;
int motor_speed = 180;
int motor_speedlow = 140;

volatile int loop_counter;
enum states { drive, stopvehicle, check_left, check_right};

////////////////////////Setup////////////////////
void setup() 
{
  ////Serial.begin(9600);
  myservo.attach(servoPin); 
  motor1.setSpeed(motor_speed); 
  motor2.setSpeed(motor_speed);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  distance_fine =t.every(50, readDistance);
  myservo.write(90);  
  loop_counter = 0;
} // End of Setup

///////////////////////Loop///////////////////
void loop()
{
    t.update();
     
    //Serial.println(distance_fine);
    myservo.write(90);
    

if(distance_fine > 40)
  {
      forward(motor_speed);
      loop_counter = 0;
  }
else
  {
      if (loop_counter<2)
      {

        if (distance_fine < 5)
        {
          backward(motor_speed);
          motor1.setSpeed(motor_speedlow); 
          motor2.setSpeed(motor_speedlow); 
          motor2.backward();
          motor1.forward();
          delay(300);
          loop_counter++;
        }
        else
        {
          decide_direction();
          loop_counter++;
        }
      }
      else
      {
          motor1.setSpeed(motor_speedlow); 
          motor2.setSpeed(motor_speedlow); 
          motor1.backward();
          motor2.forward();
          delay(300);
      }
      
      
      
      
  } 

    

} // end of loop

/////////////////// Functions ////////////////

void decide_direction()
{
          stop_engine();
          turn_head_left();
          int distance_left = readDistance(); 
          turn_head_right();  
          int distance_right = readDistance(); 
          if(distance_left > distance_right)
          {
              turnleft(motor_speed);             
          }    
          else // distance_right >= distance_left
          {
              turnright(motor_speed);
          }
}

void turn_head_left()
{
  
    for (int pos = 90; pos <= 120; pos = pos +2) 
    { 
        myservo.write(pos);
        delay(5);                     
    }
}

void turn_head_right()
{

  for (int pos = 120; pos >= 60; pos = pos -2) 
    { 
        myservo.write(pos);      
        distance_fine = readDistance();               
        delay(5);  
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
  //Serial.println("forward");
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  motor1.forward();
  motor2.forward();
  //delay(400);  
  }


void backward(int DC_Speed){
  //Serial.println("backward");
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  delay(400);  
  motor1.backward();
  motor2.backward();
}


void turnleft(int DC_Speed){
  //Serial.println("turnleft");
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  delay(600);
  motor1.forward();
  motor2.backward();
}

void turnright(int DC_Speed){
  //Serial.println("turnright");
  motor1.setSpeed(DC_Speed); // an integer between 0 and 255
  motor2.setSpeed(DC_Speed); // an integer between 0 and 255
  delay(600);
  motor1.backward();
  motor2.forward();
}

void stop_engine(){
  //Serial.println("stop_engine");
  motor1.stop();
  motor2.stop();
  //delay(200);
}
