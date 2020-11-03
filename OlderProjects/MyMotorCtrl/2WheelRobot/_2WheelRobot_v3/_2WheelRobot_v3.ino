#include <stdio.h>
#include <Ultrasonic.h>
#include <AFMotor.h> 


AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

#define trigPin 9 // define the pins of your sensor
#define echoPin 10
int hitTime;
int distanceObstacle;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  distance2drive();
   pinMode(A5,OUTPUT);

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
      delay(700);
}

void turnleft()
{
      fullSpeed();     
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(600);
}

void turnright()
{
      fullSpeed();
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(800);
}



int distance2drive()
{
    Ultrasonic ultrasonic(trigPin, echoPin);
    int distanceObstacle = ultrasonic.distanceRead();
    return distanceObstacle;
}


void obstacle() {
  int distanceObstacle = distance2drive();
  if (distanceObstacle <30 && distanceObstacle >=10)
            {
              stopvehicle();
              analogWrite(A5, 20);
              turnback();
              turnleft();
              stopvehicle();
              }

  else if (distanceObstacle <10 && distanceObstacle >=1)
            {
              stopvehicle();
              analogWrite(A5, 100);
              turnright();
              stopvehicle();
              }

 else if (distanceObstacle ==0)
            {
             
 
              delay(200);
              if (distanceObstacle ==0){
              stopvehicle();
              }
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
      analogWrite(A5, 0);
      halfSpeed();
      motor1.run(BACKWARD);
      motor2.run(FORWARD);      
      obstacle();
      delay(100);
    
}
