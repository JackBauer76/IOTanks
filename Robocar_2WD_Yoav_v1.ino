#include <L298N.h>

//pin definition
#define EN1 10
#define IN1 9
#define IN2 3

#define EN2 5
#define IN3 6
#define IN4 116

//create a motor instance
L298N motor1(EN1, IN1, IN2);
L298N motor2(EN2, IN3, IN4);

void setup() {

  //used for display information
  Serial.begin(9600);

  motor1.setSpeed(255); // an integer between 0 and 255
  motor2.setSpeed(255); // an integer between 0 and 255

}

void loop() {

  //tell the motor to go forward (may depend by your wiring)
  motor1.forward();
  motor2.forward();

  delay(2000);
  motor1.stop();
  motor2.stop();

  motor1.backward();
  motor2.backward();

  delay(2000);

  motor1.forward();
  motor2.backward();

  delay(2000);
  
  motor2.forward();
  motor1.backward();

  /*print the motor satus in the serial monitor
  Serial.print("Is moving = ");
  Serial.println(motor1.isMoving());

  delay(5000);

  //stop running
  motor1.stop();
  motor2.stop();

  Serial.print("Is moving = ");
  Serial.println(motor1.isMoving());

  delay(300);

  //change the initial speed
  motor1.setSpeed(125);
  motor2.setSpeed(125);
  //tell the motor to go back (may depend by your wiring)
  motor1.backward();
  motor2.backward();
  
  Serial.print("Is moving = ");
  Serial.println(motor1.isMoving());

  delay(300);

  //stop running
  motor1.stop();
  motor2.stop();

  Serial.print("Is moving = ");
  Serial.println(motor1.isMoving());

  //change the initial speed
  motor1.setSpeed(255);
  motor1.setSpeed(255);

  Serial.print("Get new speed = ");
  Serial.println(motor1.getSpeed());

  delay(300);*/
}
