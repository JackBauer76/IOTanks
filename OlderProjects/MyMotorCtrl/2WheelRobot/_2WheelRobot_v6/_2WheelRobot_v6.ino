#include <stdio.h>
#include <Ultrasonic.h>
#include <NewPing.h>
#include <AFMotor.h>


AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

#define trigPinFwd 27 // define the pins of your sensor
#define echoPinFwd 26
#define trigPinBwd 50 // define the pins of your sensor
#define echoPinBwd 49

#define BLUE 34 // Pin 34 connected to monitoring LED 
#define GREEN 32 // Pin 32 connected to monitoring LED 
#define RED 30 // Pin 30 connected to monitoring LED 


int hitTimeFwd;
int hitTimeBwd;
int distanceObstacleFwd;
int distanceObstacleBwd;
int factorSpeed = 5;
int currentSpeed;
int max_cm_distance = 255;

int redValue;
int greenValue;
int blueValue;

void setup() {
  // put your setup code here, to run once:
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

void halfSpeed()
{
  
  motor1.setSpeed(factorSpeed*254/200);
  motor2.setSpeed(factorSpeed*254/200);
  
}

void fullSpeed()
{
  motor1.setSpeed(factorSpeed*254/100);
  motor2.setSpeed(factorSpeed*254/100);
}

void stopvehicle()
{
  Serial.println("Vehicle Stopped");
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(400);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
   }


void turnback()
{
  
  halfSpeed();
  Serial.println("Driving Backwards");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);

  int counterBlue;
  for(int counterBlue = 0; counterBlue < 250; counterBlue++)
    {
          digitalWrite(BLUE, HIGH); // Blue LED on      
          delay(2);
    }
  digitalWrite(BLUE, LOW); // Blue LED off
 }

void turnleft()
{
  fullSpeed();
  Serial.println("Turn left");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
 int counterGreen;
  for(int counterGreen = 0; counterGreen < 250; counterGreen++)
    {
          digitalWrite(GREEN, HIGH); // Blue LED on      
          delay(2);
    }
  digitalWrite(GREEN, LOW); // Blue LED off
  

  

}

void turnright()
{
  fullSpeed();
  Serial.println("Turn right");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  int counterRed;
  for(int counterRed = 0; counterRed < 250; counterRed++)
    {
          digitalWrite(RED, HIGH); // Blue LED on      
          delay(2);
    }
  digitalWrite(RED, LOW); // Blue LED off
  

  
  }

int distance2driveFwd()
{
  Ultrasonic ultrasonicFwd(trigPinFwd, echoPinFwd);
 
  int distanceObstacleFwd = ultrasonicFwd.distanceRead();
     if (distanceObstacleFwd == 0)
    {
      distanceObstacleFwd = max_cm_distance;
    }

  return distanceObstacleFwd;
}

int distance2driveBwd()
{
  Ultrasonic ultrasonicBwd(trigPinBwd, echoPinBwd);

  int distanceObstacleBwd = ultrasonicBwd.distanceRead();
  if (distanceObstacleBwd == 0)
    {
      distanceObstacleBwd = max_cm_distance;
    }
  
   return distanceObstacleBwd;
}

void obstacleFwd() {
  int distanceObstacleFwd = distance2driveFwd();

    if (distanceObstacleFwd == 0)
    {
      delay(100);
    }
    else if (distanceObstacleFwd < 10)
      {
        Serial.println("Obstacle ahead");
        stopvehicle();
        turnback();
        turnleft();
       }
    else if (distanceObstacleFwd < 40)
    {
      Serial.println("Obstacle near ahead");  
      halfSpeed();
      delay(300);
      turnright();
      stopvehicle();
    }
}

void obstacleBwd() {
  int distanceObstacleBwd = distance2driveBwd();

    if (distanceObstacleBwd == 0)
    {
      delay(100);
    }
    else if (distanceObstacleBwd < 15)
      {
        Serial.println("Obstacle behind");
        stopvehicle();
        turnback();
        turnleft();
      }
    else if (distanceObstacleBwd < 30)
    {
      Serial.println("Obstacle near behind");  
      halfSpeed();
      delay(300);
      turnright();
      stopvehicle();
    }
}


void acceleration()
{
  Serial.println("Acceleration");
  halfSpeed();
  motor1.run(BACKWARD);
  motor2.run(FORWARD);

  int currentSpeed;
  if (distanceObstacleFwd> 150)
  {
    for(int currentSpeed= 50; currentSpeed < 255; currentSpeed++)
    {
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(currentSpeed);   
  Serial.println("Accelerating");
   }
  
}
}

void loop() {

  int distanceObstacleFwd = distance2driveFwd();
  int distanceObstacleBwd = distance2driveBwd();
  Serial.print(distanceObstacleFwd);
  Serial.println("cm to the Front");
  Serial.print(distanceObstacleBwd);
  Serial.println("cm to the Back");
  acceleration();
  obstacleFwd();
  obstacleBwd();
  delay(10);
}


