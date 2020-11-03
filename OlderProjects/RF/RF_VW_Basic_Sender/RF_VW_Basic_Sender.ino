#include <VirtualWire_Config.h>
#include <VirtualWire.h>

uint8_t variable;
byte *message;// declares array of byte


void setup()  {
        pinMode(13,OUTPUT);     // LED on Pin 13
        pinMode(6,OUTPUT);     // LED on Pin 6
        vw_set_ptt_inverted(true); //
        vw_set_tx_pin(11);  // DATA to PIN 11
        vw_setup(2000);// speed of data transfer Kbps
              }


void loop()   
    {
 
    for (uint8_t i=0; i<500; i=i+1)
      {
      variable = i;
      int len_message = 1;
      message = (byte*)malloc(len_message);// reserve memory for 1 byte
      memset(message,0,len_message); // clears data in vector/array
      *message = (byte)variable; // este es un casting explicito (convertir int a byte);  *message es el contenido, message es el pointer
      vw_send(message, strlen(message));
      vw_wait_tx(); // Wait until the whole message is gone
      digitalWrite(13,1); // activate LED when message sent
      digitalWrite(6,1); // activate LED when message sent
      delay(50);
      free(message);
      }

    }



              
