#include <Stepper.h>

const int Poti = A0;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

int Potivalue;
int *Target;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(160);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(Poti,INPUT);
}

void loop() {
    Potivalue = map(analogRead(Poti), 0, 1023,30, 150);
    Target = &Potivalue;
    myStepper.setSpeed(*Target);
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution*10);
  delay(200);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution*10);
  delay(200);
}
