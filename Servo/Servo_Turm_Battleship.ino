
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo2;


int pos = 0;    // variable to store the servo position
int posPoti = 0;
const int Poti = A3;

void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);
  pinMode(Poti, INPUT);
  Serial.begin(9600);
}

void loop() 
{
/*
    posPoti = map(analogRead(Poti),0,1023,0,180);
    myservo2.write(posPoti); 
    Serial.println(posPoti);
    delay(500);
*/
    posPoti = map(analogRead(Poti),0,1023,0,180);
    while (myservo2.read() != posPoti)
    {
        myservo2.write(posPoti); 
    }






  //for (pos = 0; pos <= posPoti; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
  //  myservo.write(pos);   
    //myservo2.write(pos);            // tell servo to go to position in variable 'pos'
  //  delay(50);                       // waits 15ms for the servo to reach the position
  //}
 
  /*
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);   
        // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
*/

}
