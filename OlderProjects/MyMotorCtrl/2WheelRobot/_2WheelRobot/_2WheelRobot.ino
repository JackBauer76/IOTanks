#include <stdio.h>
#include <Ultrasonic.h>

#include <AFMotor.h> //import your motor shield library


AF_DCMotor motor1(2);
AF_DCMotor motor2(3);

#define trigPin 9 // define the pins of your sensor
#define echoPin 10
boolean motorOn;
const int potPin = A5;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);

}




void loop() {
  // put your main code here, to run repeatedly:

    Ultrasonic ultrasonic(trigPin, echoPin);
    int hitTime = ultrasonic.distanceRead();
    int distanceInCm = hitTime;
    // Serial.print(distanceInCm);
    // Serial.println("cm");
    
    float potiRead = analogRead(potPin)/1023.0;
   
    if (potiRead > 0.5)
    {
      motorOn == true;
      motor1.setSpeed(200);
      motor1.run(FORWARD);
      motor2.setSpeed(200);
      motor2.run(BACKWARD);
    }
    else
    {
      motorOn == false;
      motor1.setSpeed(20);
      motor1.run(FORWARD);
      motor2.setSpeed(20);
      motor2.run(BACKWARD);
    }
       

        
    Serial.println(potiRead);
    /* char buffer [50];
    i=sprintf (buffer, "%d cm %.2f", distanceInCm, potiRead);
      for(int l= 0; l<=i; l++) 
      Serial.print(buffer[l]); */
    delay(500); 

    
}
