#include <TM1637Display.h>

#define PushButtonPin 2
#define Buzzerpin 4
#define PotiPin A1
#define CLKPin 10
#define DIOPin 11
#define WhiteLedPin 5
#define BlueLedPin 6

int freq;
int PotiValue;
bool PushButtonStatus;

TM1637Display display4d(CLKPin, DIOPin);

void setup()
{
    pinMode(WhiteLedPin,OUTPUT);
    pinMode(BlueLedPin,OUTPUT);
    pinMode(PotiPin,INPUT);
    pinMode(PushButtonPin,INPUT_PULLUP);
    pinMode(Buzzerpin, OUTPUT);
        
}

void loop()
{
    display4d.setBrightness(15);
    
    PotiValue = analogRead(PotiPin);
    freq = map(PotiValue, 0, 1024, 500, 8000); //map(value, fromLow, fromHigh, toLow, toHigh)
    display4d.showNumberDec(freq, false);
    
    PushButtonStatus = digitalRead(PushButtonPin);
    digitalWrite(BlueLedPin,PushButtonStatus);

    if (PushButtonStatus == LOW)
    {
        tone(Buzzerpin, freq);
    }
    else
    {
        noTone(Buzzerpin);
    }
    



}
