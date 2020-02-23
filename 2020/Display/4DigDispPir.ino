#include <TM1637Display.h>
#include <SPI.h>


#define CLK 4 // CLK is PB4 in ATtiny85
#define DIO 5 // DIO is PB3 in ATtiny85
#define TEST_DELAY   50

const int PIR = 2;
const int BLUE = 9;
const int BLUEGND = 8;
int counter = 0;
volatile long PIRstate=0;


TM1637Display display4d(CLK, DIO);

void setup() 
{
  pinMode(BLUE,OUTPUT);
  pinMode(BLUEGND,OUTPUT);
  pinMode(PIR,INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR),motionDetector,RISING);
}


void loop()
{
    digitalWrite(BLUEGND, LOW);
    display4d.setBrightness(15);
  //display4d.showNumberDec(13, false); // Expect: ___0
    display4d.showNumberDec(PIRstate, false); // Expect: ___0
//  delay(TEST_DELAY);
  //display4d.showNumberDec((int)temp, true,2,4);  // Expect: 04__
  //display4d.showNumberDec(88, false); // Expect: ___0
  //display4d.showNumberDec(27, false); // Expect: ___0
}


void motionDetector()
{
  PIRstate++;  
}

