
#include <RCSwitch.h>
#include <SPI.h>
#include <Wire.h>


const int LedPin = 13;

long value_received;
long counter = 0;
RCSwitch mySwitch = RCSwitch();

void setup()
{
    Serial.begin(9600);	  // Debugging only
    pinMode(LedPin, OUTPUT);
    mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
    Serial.println("Starting");
    
}

void loop() 
{
  if (mySwitch.available()) 
  {
    value_received = mySwitch.getReceivedValue();
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
    counter++;
    Serial.print("counter = ");
    Serial.println(counter);
    mySwitch.resetAvailable();
  }
  if (value_received > 1200)
  {
    digitalWrite(LedPin, HIGH);
  }
  else
  {
    digitalWrite(LedPin, LOW);
  }
}