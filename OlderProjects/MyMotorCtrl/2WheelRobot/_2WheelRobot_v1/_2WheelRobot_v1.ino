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


int distance2drive()
{
    Ultrasonic ultrasonic(trigPin, echoPin);
    int distanceObstacle = ultrasonic.distanceRead();
    return distanceObstacle;
}




void loop() {
  
    /*Ultrasonic ultrasonic(trigPin, echoPin);
    int hitTime = ultrasonic.distanceRead();
    Serial.print(hitTime);
    Serial.println("cm"); */
      int distanceObstacle = distance2drive();
      Serial.print(distanceObstacle);
      Serial.println("cm");
      
      if (distanceObstacle >40)
      {

      motor1.setSpeed(70);
      motor1.run(BACKWARD);
      motor2.setSpeed(70);
      motor2.run(FORWARD);      
      }

      if (distanceObstacle <40)
            {
      delay(200);
      //Serial.print(distanceObstacle);
      //Serial.println("cm");
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor1.setSpeed(80);
      motor1.run(FORWARD);
      motor2.setSpeed(80);
      motor2.run(BACKWARD);
      delay(600);
      motor1.setSpeed(50);
      motor2.setSpeed(50);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      delay(500);
      motor1.setSpeed(150);
      motor2.setSpeed(150);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      
          }
     
    
    
delay(100);
    
}
