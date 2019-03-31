#include <RF24.h>
#include <SPI.h>
#include "nRF24L01.h"

int ledState = LOW;          
unsigned long previousMillis = 0;        
const long interval = 400;       
bool radioNumber = 0;
bool role = 0;
byte addresses[][6] = {"1Node","2Node"};
int LED1 = 5;
int msg[1];
unsigned long counter, rxTimer;
unsigned long startTime, stopTime; 

RF24 radio(7,8);

byte data[32];     

void setup()
{
    Serial.begin(115200);
    Serial.println(F("RF24/examples/GettingStarted"));
    Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
    radio.begin();
    radio.setPALevel(RF24_PA_MAX);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
    radio.setChannel(1);
    radio.startListening();
    pinMode(LED1, OUTPUT);
}

void loop()
{
     while(radio.available())
     {       
      radio.read(&data,32);
      counter++;
     }
   if(millis() - rxTimer > 1000)
   {
     rxTimer = millis();     
     unsigned long numBytes = counter*32;
     Serial.print(F("Rate: "));
     //Prevent dividing into 0, which will cause issues over a period of time
     Serial.println(numBytes > 0 ? numBytes/1000.0:0);
     Serial.print(F("Payload Count: "));
     Serial.println(counter);
     counter = 0;
   }
}