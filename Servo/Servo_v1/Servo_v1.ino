#include <Servo.h>

const int Poti_x = A1;
const int Poti_y = A2;

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

int Sensorvalue;
int  *target;

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  pinMode(Poti_x, INPUT);
  pinMode(Poti_y, INPUT);

}

void loop() {
  Sensorvalue = map(analogRead(Poti_x), 0, 1023, 0, 180);
  target = &Sensorvalue;
  
  pos = 0;
  myservo.write(*target);

  /*
  for (pos = 0; pos <= *target; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }*/
}
