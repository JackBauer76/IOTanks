#include <RF24.h>
#include <SPI.h>

const int pinLed = A3;
int ledState = LOW;          
unsigned long previousMillis = 0;        
const long interval = 1000;       
bool radioNumber = 0;
bool role = 0;
byte addresses[][6] = {"1Node","2Node"};

RF24 radio(7,8);


void setup()
{
    Serial.begin(115200);
    Serial.println(F("RF24/examples/GettingStarted"));
    Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
    radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    radio.startListening();
}


void loop()
{
    unsigned long got_time;
    
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &got_time, sizeof(unsigned long) );             // Get the payload
      }
     
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &got_time, sizeof(unsigned long) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      Serial.print(F("Sent response "));
      Serial.println(got_time);  
   }
}