#include <VirtualWire_Config.h>
#include <VirtualWire.h>

//simple Tx on pin D2

#define LEDPIN A3

void setup()    {
          vw_set_ptt_inverted(true); // Required for DR3100
          vw_set_rx_pin(2);       // Data Pin of RF Receiver on Pin 2
          vw_setup(1000); // Bits per sec
          Serial.begin(9600);
          pinMode(5, OUTPUT);    // Buzzer on Pin 5
          pinMode(LEDPIN, OUTPUT);    // LED on Pin 6
          pinMode(13, OUTPUT);    // LED on Pin 8
          vw_rx_start(); // Start the receiver PLL running
          tone(5, 5000,145);  // Buzzer on Pin 9
          analogWrite(LEDPIN,60); // LED on Pin 13
          delay(500);
          tone(5, 5000,45);  // Buzzer on Pin 9
          digitalWrite(13,0); // LED on Pin 13
          delay(500);
          tone(5, 5000,145);  // Buzzer on Pin 9
          digitalWrite(13,1); // LED on Pin 13
          delay(500);
          tone(5, 5000,45);  // Buzzer on Pin 9
          digitalWrite(13,0); // LED on Pin 13
          delay(500);
          
                }




                
void loop()     {
  
      uint8_t buf[VW_MAX_MESSAGE_LEN];
      uint8_t buflen = VW_MAX_MESSAGE_LEN;
      
      if (vw_get_message(buf, &buflen)) // Non-blocking
              {
              
              if(buf[0]=='6'){
              
                    tone(5, 5000,245);  // Buzzer on Pin 9
                    Serial.print("Message received ");
                    Serial.println(buf[VW_MAX_MESSAGE_LEN]);
                    analogWrite(LEDPIN,60); // LED on Pin 13
                    digitalWrite(13,1); // LED on Pin 13
                    

                    
                            }
                            
              if(buf[0]=='0') {
              
                    noTone(5);
                    Serial.print("just received ");
                    Serial.println(buf[0]);
                    digitalWrite(LEDPIN,0); // LED on Pin 13
                    digitalWrite(13,0); // LED on Pin 13
                            }
              
              }
}
