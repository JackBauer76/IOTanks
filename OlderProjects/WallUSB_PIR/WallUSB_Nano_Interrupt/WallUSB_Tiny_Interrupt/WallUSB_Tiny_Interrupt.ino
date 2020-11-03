#include "PinChangeInterrupt.h"

// Choose a valid PinChangeInterrupt pin of your Arduino board
#define PIR 0
#define LED1 1
#define LED2 2

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(PIR, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  attachPCINT(digitalPinToPCINT(PIR), blinkLed, CHANGE);
}

void blinkLed(void) {
  // Switch Led state
  digitalWrite(LED1, !digitalRead(LED1));
  digitalWrite(LED2, !digitalRead(LED2));
}

void loop() {
  // Nothing to do here
}
