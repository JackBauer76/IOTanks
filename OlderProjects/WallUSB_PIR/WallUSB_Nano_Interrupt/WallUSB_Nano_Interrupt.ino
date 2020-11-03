#include <avr/interrupt.h>
#include <EnableInterrupt.h>

#define PIR 0
#define LED1 1
#define LED2 2

volatile int MotionState = 0;

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  //pinMode(PIR, INPUT);
  //attachInterrupt(digitalPinToInterrupt(PIR),pirfunction,CHANGE);
  PCMSK  |= bit (PCINT0);  // want pin D4 / pin 3
  GIFR   |= bit (PCIF);    // clear any outstanding interrupts
  GIMSK  |= bit (PCIE);    // enable pin change interrupts 
  
  
  //attachInterrupt(PIR,pirfunction,CHANGE);
}


ISR (PCINT2_vect) 
 {
  MotionState =!MotionState;
  
 }

void loop() {
  
  if(MotionState){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
  }
  else{
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
  }

}



