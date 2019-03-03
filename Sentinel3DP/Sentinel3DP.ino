#include <TM1637Display.h>

const int led_white = 9;
const int clk_pin = 5;
const int dio_pin = 6;
const int poti = A4;
const int pushbutton = 2;

int potiValue = 0;
int ledState = LOW;    
unsigned long previousMillis = 0;     
const long interval = 1000;   
volatile float timestamp = 0;

TM1637Display display(clk_pin, dio_pin);

void setup()
{
    pinMode(led_white, OUTPUT);
    pinMode(poti, INPUT);
    display.setBrightness(15);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(pushbutton), check_timestamp, RISING);
}


void loop()
{

    potiValue = analogRead(poti);
    int minutes = map(potiValue,0,1023, 10, 600);
    unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) 
     {
        previousMillis = currentMillis;
        if (ledState == LOW) 
        {
            ledState = HIGH;
        }   
        else 
        {
            ledState = LOW;
        }
        digitalWrite(led_white, ledState);
     
     }

    
    //display.showNumberDec(minutes, false); // Expect: ___0
    float op_time_m = timestamp/60000;
    Serial.println(int(op_time_m));
    display.showNumberDec(op_time_m, false); // Expect: ___0

}

void check_timestamp()
{
    timestamp = millis();
}