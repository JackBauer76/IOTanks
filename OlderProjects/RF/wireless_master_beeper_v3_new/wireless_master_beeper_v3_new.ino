#include <VirtualWire_Config.h>
#include <VirtualWire.h>

const char* alex= "ALEX\0";
const char* elias= "888888\0";

int variable;

byte *message;// declares array of byte

void setup()  {
        pinMode(13,OUTPUT);     // LED on Pin 13
        pinMode(6,OUTPUT);     // LED on Pin 6
        vw_set_ptt_inverted(true); //
        vw_set_tx_pin(11);  // DATA to PIN 11
        vw_setup(1000);// speed of data transfer Kbps
              }



void loop()   {
 
    for (int i=0; i<32; i++){
      variable = i;
       
    //int len_message = strlen(alex);
    int len_message = 1;
    message = (byte*)malloc(len_message);// reserve memory for 1 byte
    
    memset(message,0,len_message); // clears data in vector/array
    
    //strcpy(message,alex); 
    //sprintf(message, "%06d", variable);

    //sprintf(message, "%06d", variable);
    *message = (byte)variable; // este es un casting explicito (convertir int a byte);  *message es el contenido, message es el pointer
    //message1= alex ; // This is the message sent, in our case we send a 1
    vw_send(message, strlen(message));
        
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,1); // activate LED when message sent
    digitalWrite(6,1); // activate LED when message sent
    delay(750);
    free(message);
 
  
/*
    len_message = strlen(elias);
    message = (unsigned char*)malloc( len_message + 1 );
    memset(message,0,len_message);
    strcpy(message,elias); 

    vw_send(message, strlen(message));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13,1); // activate LED when message sent
    digitalWrite(6,1); // activate LED when message sent
    delay(500);
    free(message);
*/    
    
    }

              }



              
