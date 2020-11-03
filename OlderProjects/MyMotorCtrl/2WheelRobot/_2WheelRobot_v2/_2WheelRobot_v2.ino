#include <stdio.h>
#include <Ultrasonic.h>
#include <AFMotor.h> 

AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

#define trigPin 9 // define the pins of your sensor
#define echoPin 10
int hitTime;
int distanceObstacle;
const int potPin = A5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  distance2drive();
}


void halfSpeed()
{
  motor1.setSpeed(70);
  motor2.setSpeed(70);
}

void fullSpeed()
{
  motor1.setSpeed(125);
  motor2.setSpeed(125);
}

void stopvehicle() 
{
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      delay(300);
}


void turnback()
{
      halfSpeed();
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      delay(300);
}

void turnleft()
{
      halfSpeed();     
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(300);
}

void turnright()
{
      halfSpeed();
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(300);
}



int distance2drive()
{
    Ultrasonic ultrasonic(trigPin, echoPin);
    int distanceObstacle = ultrasonic.distanceRead();
    return distanceObstacle;
}


void obstacle() {
  int distanceObstacle = distance2drive();
  if (distanceObstacle <30)
            {
              stopvehicle();
              turnback();
              turnleft();
              stopvehicle();
              }
}

void loop() {
  
    /*Ultrasonic ultrasonic(trigPin, echoPin);
    int hitTime = ultrasonic.distanceRead();
    Serial.print(hitTime);
    Serial.println("cm"); */
      int distanceObstacle = distance2drive();
      Serial.print(distanceObstacle);
      Serial.println("cm");
      
      fullSpeed();
      motor1.run(BACKWARD);
      motor2.run(FORWARD);      
      obstacle();
      delay(100);
    
}
