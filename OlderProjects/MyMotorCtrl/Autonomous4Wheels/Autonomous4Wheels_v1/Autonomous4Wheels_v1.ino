#include <stdio.h>
#include <Ultrasonic.h>
#include <AFMotor.h>

AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

#define trigPinFwd 27 // define the pins of your sensor
#define echoPinFwd 26
#define trigPinBwd 50 // define the pins of your sensor
#define echoPinBwd 48
#define BLUE 34 // Pin 34 connected to monitoring LED 
#define GREEN 32 // Pin 32 connected to monitoring LED 
#define RED 30 // Pin 30 connected to monitoring LED 

int hitTimeFwd;
int hitTimeBwd;
int distanceObstacleFwd;
int distanceObstacleBwd;
int factorSpeed = 100;
int currentSpeed;
int max_cm_distance = 255;

void setup() {
  Serial.begin(9600);
  delay(500);
  distance2driveFwd();
  distance2driveBwd();
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(trigPinFwd, OUTPUT); // Not sure it is necessary
  pinMode(echoPinFwd, INPUT); // Not sure it is necessary
  pinMode(trigPinBwd, OUTPUT); // Not sure it is necessary
  pinMode(echoPinBwd, INPUT); // Not sure it is necessary
  digitalWrite(BLUE, HIGH); // Monitoring of LED during startup
  digitalWrite(GREEN, HIGH); // Monitoring of LED during startup
  digitalWrite(RED, HIGH); // Monitoring of LED during startup
  delay(1000);
  digitalWrite(BLUE, LOW); // Monitoring of LED during startup
  digitalWrite(GREEN, LOW); // Monitoring of LED during startup
  digitalWrite(RED, LOW); // Monitoring of LED during startup
}

void halfSpeed()                   //Function
{
  motor1.setSpeed(factorSpeed*254/200);
  motor2.setSpeed(factorSpeed*254/200);
}

void fullSpeed()                  //Function
{
  motor1.setSpeed(factorSpeed*254/100);
  motor2.setSpeed(factorSpeed*254/100);
}

void stopvehicle()                 //Function
{
  Serial.println("Vehicle Stopped");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(500);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void turnback()                   //Function
{
  
  Serial.println("Driving Backwards");
  digitalWrite(BLUE, HIGH); // Blue LED on      
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  digitalWrite(BLUE, LOW); // Blue LED off
 }

void turnleft()               //Function
{
  digitalWrite(GREEN, HIGH); // Blue LED on      
  fullSpeed();
  Serial.println("Turn left");
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  digitalWrite(GREEN, LOW); // Blue LED on      
 }

void turnright()              //Function
{
  fullSpeed();
  Serial.println("Turn right");
  int counterRed;
  for(int counterRed = 0; counterRed < 400; counterRed++)
    {
          motor1.run(FORWARD);
          motor2.run(BACKWARD);
          digitalWrite(RED, HIGH); // Blue LED on      
          delay(2);
    }
  digitalWrite(RED, LOW); // Blue LED off
}

int distance2driveFwd()         //Function with Ultrasound sensor
{
  Ultrasonic ultrasonicFwd(trigPinFwd, echoPinFwd);
  int distanceObstacleFwd = ultrasonicFwd.distanceRead();
  if (distanceObstacleFwd == 0)
    {
      distanceObstacleFwd = max_cm_distance;
    }
  return distanceObstacleFwd;
}

int distance2driveBwd()       //Function with Ultrasound sensor
{
    Ultrasonic ultrasonicBwd(trigPinBwd, echoPinBwd);
    int distanceObstacleBwd = ultrasonicBwd.distanceRead();
    if (distanceObstacleBwd == 0)
    {
      distanceObstacleBwd = max_cm_distance;
    }
  return distanceObstacleBwd;
}

void obstacleFwd() {              //Function with driving logic
  int distanceObstacleFwd = distance2driveFwd();
  int distanceObstacleBwd = distance2driveBwd();
  if (distanceObstacleFwd == 0)
    {   delay(10);    }
  else if (distanceObstacleFwd < 20)      // close obstacle forward
    {
      Serial.println("Obstacle ahead");
      stopvehicle();
      int counterBack;
      for(int counterBack = 0; counterBack < 50; counterBack++)
        {  
        if (distanceObstacleBwd > 30)
        { turnback(); }
        else if (distanceObstacleBwd <30)
        { 
          int randomDirection = random(1,3);
          if (randomDirection == 1)
          {
            turnright();
          }
          else if (randomDirection == 2)
          {
            turnleft();
          }
      }
        } }
  else if (distanceObstacleFwd < 60)      // far obstacle forward
    {
      Serial.println("Obstacle near ahead");  
      int randomDirection = random(1,3);
      Serial.println(randomDirection);
      if (randomDirection == 1)
      {
        turnright();
      }
      else if (randomDirection == 2)
      {
        turnleft();
      }
     }                   
}
void acceleration()               //Function, not yet tested
{
  halfSpeed();
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  int currentSpeed;
  if (distanceObstacleFwd> 150)
  {
    for(int currentSpeed= 50; currentSpeed < 255; currentSpeed++)
    {
      Serial.println("Accelerating");
      motor1.setSpeed(currentSpeed);
      motor2.setSpeed(currentSpeed);   
     }
   }   }

void loop() {
  int distanceObstacleFwd = distance2driveFwd();
  int distanceObstacleBwd = distance2driveBwd();
  Serial.print(distanceObstacleFwd);
  Serial.print("cm to the Front  /    ");
  Serial.print(distanceObstacleBwd);
  Serial.println("cm to the Back");
  acceleration();
  obstacleFwd();
  delay(10);
}



