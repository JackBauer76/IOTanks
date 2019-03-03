/*
Sender 433 MHz with Poti, pushbutton and led

*/
//#include <RCSwitch.h>

//RCSwitch mySwitch = RCSwitch();
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

    //mySwitch.enableTransmit(sender_pin);
    //mySwitch.setProtocol(2);
    //mySwitch.setPulseLength(320);
    //mySwitch.setRepeatTransmit(9);
    pinMode(led, INPUT);
    pinMode(poti_y, INPUT);
    pinMode(poti_x, INPUT);
    pinMode(pushbutton, INPUT_PULLUP);
    Serial.begin(9600);
    //attachInterrupt(digitalPinToInterrupt(pushbutton), changeState, CHANGE);
}


void loop()
{
    const char *msg = "tenia yo una vez tres perritos";
    //const int *code = 123;
    digitalWrite(13, true); // Flash a light to show transmitting
    
    vw_send((uint8_t *)msg, strlen(msg));
    //vw_send((uint8_t *)code, strlen(code));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(200);
}



/*
void loop()
{
    
    VRx = analogRead(poti_x);
    VRy = analogRead(poti_y);

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis;



        int i=VRx;
        const char msg=i;
        Serial.print(i);
        Serial.println(msg);

        digitalWrite(13,HIGH);
        vw_send((uint8_t *)msg,1);
        vw_wait_tx();
        digitalWrite(13,LOW);



        (led_state == LOW)? led_state = HIGH: led_state = LOW;
        digitalWrite(led, led_state);
        if (led_state == LOW)
        {
            //mySwitch.send(VRx, 24);
            Serial.print("Poti x: ");
            Serial.print(VRx); 
        }
        if (led_state == HIGH)
        {
            //mySwitch.send(VRy, 24);
            Serial.print(", Poti y: ");
            Serial.println(VRy);
        }

    }
    //Serial.print("Poti x: ");
    //Serial.print(VRx); 
    //Serial.print(", Poti y: ");
    //Serial.println(VRy);
}

void changeState()
{
    led_state = !led_state;
}

*/