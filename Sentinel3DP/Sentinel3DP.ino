#include <TM1637Display.h>
#include <RCSwitch.h>

const int led_white = 9;
const int clk_pin = 5;
const int dio_pin = 6;
const int poti = A4;
const int pushbutton = 2;

volatile float last_timestamp = 0;
volatile int TimeTarget = 0;

TM1637Display display(clk_pin, dio_pin);
RCSwitch mySwitch = RCSwitch();

void setup()
{
    pinMode(led_white, OUTPUT);
    pinMode(poti, INPUT);
    display.setBrightness(15);
    Serial.begin(9600);
    mySwitch.enableTransmit(7);
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(190);
    mySwitch.setRepeatTransmit(6);
    attachInterrupt(digitalPinToInterrupt(pushbutton), check_timestamp, RISING);
}

void loop()
{
    
    long counter_time = millis()/60000 - last_timestamp;
    int time2off = TimeTarget - counter_time;
    

    display.showNumberDec(time2off, false); 
    if (time2off == 0 )
    {
        mySwitch.send(87500, 24);
    }
    (time2off > 0) ? digitalWrite(led_white, HIGH): digitalWrite(led_white, LOW);


}

void check_timestamp()
{
    last_timestamp = millis()/60000;
    TimeTarget = map(analogRead(poti),0,1023, 10, 600);
    mySwitch.send(87491, 24); // to be taken out later

}