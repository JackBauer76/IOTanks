// MPU6050 Simple program with Servo
#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>
#include "I2Cdev.h"

Servo ruder;
MPU6050 sensor;
const int Servo_pin = 3;
int16_t ax, ay, az;
int16_t gx, gy, gz;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer


void setup() {
   ruder.attach(Servo_pin);
   Wire.begin();
   Serial.begin(9600);
   sensor.initialize();
   Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 
   delay(1000);
}

void loop() {
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 

  
  gx = map(gx, -17000, 17000, -90, 90);
  Serial.println(gx);
  ruder.write(gx);
  delay(200);
}
