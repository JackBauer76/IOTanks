#include <RCSwitch.h>
#include "Timer.h"


RCSwitch mySwitch = RCSwitch();
Timer t;

const int led = 6;
bool state=0;
void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  // Transmitter is connected to Arduino Pin #11
  mySwitch.enableTransmit(11);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
  
}

void loop() 
{
  t.update();
  t.every(1000, transmit_rf);
  
}

void transmit_rf()
{
  if(state==0)
  {
    mySwitch.send(random(1,19999), 24);
    digitalWrite(led, HIGH);
  }
  else
  {
    mySwitch.send(86514, 24);
    digitalWrite(led, LOW);
  }
  state = !state;
}


    
  /* Same switch as above, but using binary code  
  mySwitch.send(8331, 24);
  delay(5000);  

 
  mySwitch.send("100000000001010100010001");
  delay(1000);  
  mySwitch.send("111100000001010100010100");
  delay(1000);
*/

