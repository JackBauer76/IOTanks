/*
Sender 433 MHz with Poti, pushbutton and led

*/
#include <VirtualWire.h>

const int led = 8;
const int pushbutton = 2;
const int sender_pin = 7;
const int poti_y = A4;
const int poti_x = A5;
int VRx = 0;
int VRy = 0;
const long interval = 1000;   
volatile bool led_state = LOW;
unsigned long previousMillis = 0;  

void setup()
{
    vw_set_tx_pin(sender_pin); 
    vw_set_ptt_inverted(false); // Required for DR3100
    
    vw_setup(2000);	 // Bits per sec

    pinMode(led, INPUT);
    pinMode(poti_y, INPUT);
    pinMode(poti_x, INPUT);
    pinMode(pushbutton, INPUT_PULLUP);
    Serial.begin(9600);

}


void loop()
{
    VRx = analogRead(poti_x);
    VRy = analogRead(poti_y);
    Istr[0] = map(VRx,0,1023,0,125);
    Istr[1] = map(VRy,0,1023,0,125);
    //const char *msg = "tenia yo una vez tres perritos";
    digitalWrite(13, true); // Flash a light to show transmitting
    
    vw_send((uint8_t *)Istr, strlen(Istr));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(200);
}
