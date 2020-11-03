#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #11
  mySwitch.enableTransmit(11);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set number of transmission repetitions.
  mySwitch.setRepeatTransmit(15);
  
}

void loop() {
  
  
  mySwitch.send(3214, 24);
  delay(5000);  
  
  mySwitch.send(8331, 24);
  delay(5000);  

  /* Same switch as above, but using binary code */
  mySwitch.send("100000000001010100010001");
  delay(1000);  
  mySwitch.send("111100000001010100010100");
  delay(1000);


  
}
