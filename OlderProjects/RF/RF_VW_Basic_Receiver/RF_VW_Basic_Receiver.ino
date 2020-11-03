#include <VirtualWire_Config.h>
#include <VirtualWire.h>

byte* buf;
uint8_t buflen = VW_MAX_MESSAGE_LEN;
uint8_t code_received;

void setup()    
        {
          vw_set_ptt_inverted(true); // Required for DR3100
          vw_set_rx_pin(2);       // Data Pin of RF Receiver on Pin 2
          vw_setup(2000); // Bits per sec
          pinMode(9, OUTPUT);    // Buzzer on Pin 9
          pinMode(6, OUTPUT);    // LED on Pin 6
          pinMode(13, OUTPUT);    // LED on Pin 8
          Serial.begin(9600);
          vw_rx_start(); // Start the receiver PLL running
          buf = malloc(VW_MAX_MESSAGE_LEN); // VW_MAX_MESSAGE_LEN + 1
        }

                
void loop()     
  {
      memset(buf, 0, VW_MAX_MESSAGE_LEN);
      vw_wait_rx(); // blocking
      if (vw_get_message(buf, &buflen)) // Non-blocking
      {
          Serial.print("Message received :");
          code_received= (int)*buf;    
          Serial.print("code :");
          Serial.println(code_received);
          tone(9,6200,18);  // Buzzer on Pin 9
          digitalWrite(6,1); // LED on Pin 13
          digitalWrite(13,1); // LED on Pin 13
          delay(250);
          noTone(9);
          digitalWrite(6,0); // LED on Pin 13
          digitalWrite(13,0); // LED on Pin 13
      }
  }


