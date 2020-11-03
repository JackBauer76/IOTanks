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
int max_cm_distance = 250;

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

/*   I still have to implement a internal mechanism to avoid having 0 in distance
void checkSonar(void)
{   
  int dist;

  dist = sonar.ping_in();                   // get distqnce in inches from the sensor
  if (dist == 0)                                // if too far to measure, return max distance;
    dist = MAX_DISTANCE_IN;  
  sonarDistance = sonarAverage.add(dist);      // add the new value into moving average, use resulting average
}
*/



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
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  delay(500);
   }


void turnback()
{
  
  halfSpeed();
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(1000);

 }

void turnleft()
{
  fullSpeed();
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(1000);
  

}

void turnright()
{
  fullSpeed();
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(1000);

  }

int distance2driveFwd()
{
  Ultrasonic ultrasonicFwd(trigPinFwd, echoPinFwd);
  // NewPing sonar(trigPinFwd, echoPinFwd, max_cm_distance); // NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
  int distanceObstacleFwd = ultrasonicFwd.distanceRead();
  // int distanceObstacleFwd = sonar.ping_cm();
  // int distanceObstacleFwd = sonar.ping_median(iterations);

    if (distanceObstacleFwd == 0)
    {
      distanceObstacleFwd = max_cm_distance;
    }
  // int distanceObstacleFwd = sonar.ping_cm();
  // int distanceObstacleFwd = sonar.ping_median(iterations);

  return distanceObstacleFwd;
}

int distance2driveBwd()
{
  Ultrasonic ultrasonicBwd(trigPinBwd, echoPinBwd);
    // NewPing sonar(trigPinBwd, echoPinBwd, max_cm_distance); // NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
  int distanceObstacleBwd = ultrasonicBwd.distanceRead();
  // int distanceObstacleBwd = sonar.ping_cm();
  // int distanceObstacleBwd = sonar.ping_median(iterations);
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
      //analogWrite(RED, 150);
      delay(100);
    }
  
    else if (distanceObstacleFwd < 10)
      {
        
    redValue = 0;
    for(int i = 0; i < 255; i += 2)
    {
    redValue += 2;
    analogWrite(RED, 255 - redValue);
    delay(5);
  }
        stopvehicle();
        turnback();
        turnleft();
        stopvehicle();
        
      }
    else if (distanceObstacleFwd < 40)
    {
        blueValue = 0;
  for(int i = 0; i < 255; i += 2)
  {
    blueValue += 2;
    analogWrite(BLUE, 255 - blueValue);
  delay(5);
  }
      halfSpeed();
      delay(300);
      turnright();
      stopvehicle();
    }
}


void acceleration()
{
  halfSpeed();
  motor1.run(BACKWARD);
  motor2.run(FORWARD);

  int currentSpeed;
  if (distanceObstacleFwd> 150)
  {
    for(int currentSpeed= 50; currentSpeed < 255; currentSpeed++)
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(currentSpeed);   
  greenValue = 0;
  for(int i = 0; i < 255; i += 2)
  {
    greenValue += 2;
    analogWrite(GREEN, 255 - greenValue);
  delay(5);
  }

  delay(2);
  }
  
}


void loop() {

  int distanceObstacleFwd = distance2driveFwd();
  int distanceObstacleBwd = distance2driveBwd();
  Serial.print(distanceObstacleFwd);
  Serial.println("cm");
  Serial.print(distanceObstacleBwd);
  Serial.println("cm Backward");
  
  acceleration();
  
  obstacleFwd();
  delay(100);

}


/* to implement later
 *  
 *  void loop() {
  for(int a=0;a<=180;a++) // rotates the servo motor from 0 to 180 degrees
  {  
  myServo.write(a); //Sending stes to servo which servo should move
  delay(20);
  distance = Distance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print(a); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.println(distance); // Sends the distance value into the Serial Port
  }
  for(int b=180;b>0;b--) //   Rversing rotation from 180 to 0 degrees
  {  
  myServo.write(b); 
  delay(20);
  distance = Distance();
  Serial.print(b);
  Serial.print(",");
  Serial.println(distance);
  }
}
 *  
 *  #include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}

sonar.ping(); - Send a ping, returns the echo time in microseconds or 0 (zero) if no ping echo within set distance limit

sonar.ping_cm(); - Send a ping, returns the distance in centimeters or 0 (zero) if no ping echo within set distance limit
sonar.convert_cm(echoTime); - Converts microseconds to distance in centimeters


 *  
 */






