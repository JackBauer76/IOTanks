/*
Receiver 433 MHz with 4Digit Display and servo

*/
#include <VirtualWire.h>
#include <TM1637Display.h>

const int clk_pin = 5;
const int dio_pin = 4;

int Xvalue;
int Yvalue;
int display_x;

TM1637Display display(clk_pin, dio_pin);

void setup()
{

    Serial.begin(9600);
    display.setBrightness(15);
    vw_set_rx_pin(2);
    vw_set_ptt_inverted(false); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}


void loop()
{
    display.showNumberDec(display_x, false); 
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        

        digitalWrite(13, true); // Flash a light to show received good message
        Serial.print("Got: ");
        int Xvalue = buf[0];
        display_x = Xvalue;
        int Yvalue = buf[1];
        Serial.print(" Xvalue is : ");
        Serial.print(Xvalue);
        Serial.print("   Yvalue is : ");
        Serial.println(Yvalue);
        
        
        
       
        /*
        for (int i = 0; i < buflen; i++)
        {
            Serial.print(buf[i], DEC);
            Serial.print(" ");
        }
        */
        Serial.println("");
        digitalWrite(13, false);
    }
    
}