#include <RF24.h>
#include <SPI.h>
#include "nRF24L01.h"

unsigned long counter;
unsigned long startTime, stopTime; 
const int pinLed = A3;
int ledState = LOW;          
unsigned long previousMillis = 0;        
const long interval = 1000;       
bool radioNumber = 0;
bool role = 0;

byte data[32];     

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.

int msg[1];
RF24 radio(7,8);
int SW1 = 7;

void setup()
{
    pinMode(pinLed, OUTPUT);
  Serial.begin(115200);
  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
  Serial.println(F("\n\rRF24/examples/Transfer/"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  randomSeed(analogRead(0));              //Seed for random number generation
  
  for(int i=0; i<32; i++){
     data[i] = random(255);               //Load the buffer with random data
  }
  radio.powerUp(); 
}


void loop()
{
        delay(2000);
    
    Serial.println(F("Initiating Basic Data Transfer"));
    
    
    unsigned long cycles = 10000; //Change this to a higher or lower number. 
    
    startTime = millis();
    unsigned long pauseTime = millis();
            
    for(int i=0; i<cycles; i++){        //Loop through a number of cycles
      data[0] = i;                      //Change the first byte of the payload for identification
      if(!radio.write(&data,32)){   //Write to the FIFO buffers        
        counter++;                      //Keep count of failed payloads
      }
      
      //This is only required when NO ACK ( enableAutoAck(0) ) payloads are used
//      if(millis() - pauseTime > 3){
//        pauseTime = millis();
//        radio.txStandBy();          // Need to drop out of TX mode every 4ms if sending a steady stream of multicast data
//        //delayMicroseconds(130);     // This gives the PLL time to sync back up   
//      }
      
    }
    
   stopTime = millis();   
                                         //This should be called to wait for completion and put the radio in standby mode after transmission, returns 0 if data still in FIFO (timed out), 1 if success

   //radio.txStandBy(1000);              //Standby, using extended timeout period of 1 second
   
   float numBytes = cycles*32;
   float rate = numBytes / (stopTime - startTime);
    
   Serial.print("Transfer complete at "); Serial.print(rate); Serial.println(" KB/s");
   Serial.print(counter); Serial.print(" of "); Serial.print(cycles); Serial.println(" Packets Failed to Send");
   counter = 0;   
}


/*
void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;
        ledState == LOW ? ledState = HIGH: ledState = LOW;
        ledState == HIGH? analogWrite(pinLed, 255): analogWrite(pinLed, 0);
    }
   
        radio.stopListening();                                    // First, stop listening so we can talk.
    
    
    Serial.println(F("Now sending"));
    unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
     if (!radio.write( &start_time, sizeof(unsigned long) )){
       Serial.println(F("failed"));
     }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
        
    if ( timeout ){                                             // Describe the results
        Serial.println(F("Failed, response timed out."));
    }else{
        unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
        radio.read( &got_time, sizeof(unsigned long) );
        unsigned long end_time = micros();
        
        // Spew it
        Serial.print(F("Sent "));
        Serial.print(start_time);
        Serial.print(F(", Got response "));
        Serial.print(got_time);
        Serial.print(F(", Round-trip delay "));
        Serial.print(end_time-start_time);
        Serial.println(F(" microseconds"));
    }
    // Try again 1s later
    delay(1000);
}
*/