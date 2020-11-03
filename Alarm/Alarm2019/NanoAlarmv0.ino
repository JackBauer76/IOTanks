

#define BAUDRATE 9600
#define PIR 3
const int PinLed = 5;
const int BuzzerPin = 6;
const int Relay = 9;
const int Poti = A4;
bool status;
bool motionStatus;
int freq;

#ifdef PIR 
#include <avr/interrupt.h>
volatile int MotionState = 0;
volatile byte counter = 0;
#endif

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
    pinMode(PinLed, OUTPUT);
    pinMode(BuzzerPin, OUTPUT);
    pinMode(PIR, INPUT);
    pinMode(Poti, INPUT);
    pinMode(Relay, OUTPUT);
    #ifdef PIR
    attachInterrupt(digitalPinToInterrupt(PIR), motionDetector, CHANGE);
    #endif

    #ifdef BAUDRATE
    Serial.begin(BAUDRATE);
    #endif


}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================


void loop() {

freq = map(analogRead(Poti),0,1024,3000,5000);
motionStatus = digitalRead(PIR);

motionStatus? digitalWrite(PinLed, HIGH): digitalWrite(PinLed, LOW);

motionStatus? tone(BuzzerPin, 3700): noTone(BuzzerPin); 
motionStatus? digitalWrite(Relay, HIGH): digitalWrite(Relay, LOW);

Serial.println(freq);

}

// ================================================================
// ===                    FUNCTIONS                             ===
// ================================================================


#ifdef PIR
void motionDetector()
{
      motionStatus = !motionStatus;      
}
#endif