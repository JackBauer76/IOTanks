/*                  +-\/-+
//            Ain0 (D 5) PB5  1|    |8  Vcc
// TempSensor Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
//            Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     CLK
//                       GND  4|    |5  PB0 (D 0) pwm0     DIO
*/
#define LedPin 2
#define LedPin2 3
#define SirenPin 1
#define TiltSensor 0
#define Sensor 4
#include <avr/interrupt.h>
bool motionStatus;
volatile int MotionState = 0;
volatile byte counter = 0;

void setup()
{
    pinMode(LedPin, OUTPUT);
    pinMode(LedPin2, OUTPUT);
    pinMode(TiltSensor, INPUT);
    pinMode(SirenPin, OUTPUT);
    pinMode(Sensor, INPUT);
    attachInterrupt(TiltSensor, motionDetector, CHANGE);
        
    for(int i=0; i< 10;i++)
    {
      digitalWrite(LedPin, HIGH);
      delay(20);
      digitalWrite(LedPin, LOW);
      delay(20);
      
    }
    
}

void loop()
{
//motionStatus = digitalRead(TiltSensor);
digitalRead(Sensor)? digitalWrite(LedPin, HIGH): digitalWrite(LedPin, LOW);
digitalRead(Sensor)? digitalWrite(LedPin2, HIGH): digitalWrite(LedPin2, LOW);

motionStatus? digitalWrite(LedPin, HIGH): digitalWrite(LedPin, LOW);

if(digitalRead(TiltSensor)==HIGH)
{
  digitalWrite(LedPin2, HIGH);
  digitalWrite(SirenPin, HIGH);
  //tone(SirenPin, 3700);
  delay(2000);
}

else
{
  digitalWrite(LedPin2, LOW);
  digitalWrite(SirenPin, LOW);
  //noTone(SirenPin);
}
//motionStatus? tone(SirenPin, 3700): noTone(SirenPin); 
   
}

void motionDetector()
{
      motionStatus = !motionStatus;      
}
