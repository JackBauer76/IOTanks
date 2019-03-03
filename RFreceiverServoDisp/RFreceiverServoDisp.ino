/*
Receiver 433 MHz with 4Digit Display and servo

*/
//#include <RCSwitch.h>

//RCSwitch mySwitch = RCSwitch();

#include <VirtualWire.h>

void setup()
{

    Serial.begin(9600);
    vw_set_rx_pin(2);
    //mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
    vw_set_ptt_inverted(false); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}


void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        

        digitalWrite(13, true); // Flash a light to show received good message
        // Message with a good checksum received, dump it.
        
        Serial.print("Got: ");
        
        //Serial.println(buf);
        
        for (int i = 0; i < buflen; i++)
        {
            Serial.print(buf[i], DEC);
            Serial.print(" ");
        }

        Serial.println("");
        digitalWrite(13, false);
    }



    /*
    if (mySwitch.available()) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );

    mySwitch.resetAvailable();
  }
  */
}