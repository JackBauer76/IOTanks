

#define BAUDRATE 9600
#define PIR 3

const int PinLed = 8;
const int Ledgnd = 10;
const int Led2gnd = 7;
const int PinLed2 = 5;
const int TiltSensorPin = 2;
const int BuzzerPin1 = 6;
const int BuzzerPin2 = 4;
bool status;
bool motionStatus;

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
    pinMode(Ledgnd, OUTPUT);
    pinMode(PinLed2, OUTPUT);
    pinMode(Led2gnd, OUTPUT);
    pinMode(BuzzerPin1, OUTPUT);
    pinMode(BuzzerPin2, OUTPUT);
    
    pinMode(PIR, INPUT);
    pinMode(TiltSensorPin, INPUT_PULLUP);

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
digitalWrite(Ledgnd, LOW);    
digitalWrite(Led2gnd, LOW);
status = digitalRead(TiltSensorPin);
Serial.println(status);

motionStatus = digitalRead(PIR);

status? digitalWrite(PinLed, HIGH): digitalWrite(PinLed, LOW);
//digitalRead(PIR)? digitalWrite(PinLed2, HIGH): digitalWrite(PinLed2, LOW);

//status? tone(BuzzerPin1, 4000): noTone(BuzzerPin1);

//motionStatus? tone(BuzzerPin1, 4000): noTone(BuzzerPin1); 
MotionState? tone(BuzzerPin2, 4500): noTone(BuzzerPin2); 


}

// ================================================================
// ===                    FUNCTIONS                             ===
// ================================================================


#ifdef PIR
void motionDetector()
{
      MotionState = !MotionState;
      (digitalRead(PinLed2))? digitalWrite(PinLed2,LOW): digitalWrite(PinLed2,HIGH);    
      

}
#endif