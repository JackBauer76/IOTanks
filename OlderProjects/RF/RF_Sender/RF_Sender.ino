
#include <VirtualWire_Config.h>
#include <VirtualWire.h>

#define LEDPIN 4
#define PIRPIN 2
#define RFPIN 11

boolean pir;
char *controller;

void setup() {
    pinMode(LEDPIN, OUTPUT);
    pinMode(PIRPIN, INPUT);
    vw_set_ptt_inverted(true); //
    vw_set_tx_pin(RFPIN);  // DATA to PIN 10
    vw_setup(1000);// speed of data transfer Kbps
              }

void loop() {
    pir = digitalRead(PIRPIN);
    if(pir == HIGH){
        digitalWrite(LEDPIN, HIGH);
        controller="6" ; // This is the message sent, in our case we send a 1
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone 
        }
               
    else{    
        digitalWrite(LEDPIN, LOW);
        controller="0" ;
        vw_send((uint8_t *)controller, strlen(controller));
        vw_wait_tx(); // Wait until the whole message is gone  */
    }
    
        
        
   
        
    

    }



