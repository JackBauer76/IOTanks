#include "PinChangeInterrupt.h"

// Choose a valid PinChangeInterrupt pin of your Arduino board
#define pinBlink 0
#define LED1 1
#define LED2 2

void setup() {
  // set pin to input with a pullup, led to output
  pinMode(pinBlink, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Manually blink once to test if LED is functional
  blinkLed();
  delay(1000);
  blinkLed();

  // Attach the new PinChangeInterrupt and enable event function below
  attachPCINT(digitalPinToPCINT(pinBlink), blinkLed, RISING);
}

void blinkLed(void) {
  // Switch Led state
  digitalWrite(LED1, !digitalRead(LED1));
  digitalWrite(LED2, !digitalRead(LED2));
}

void loop() {
  // Nothing to do here
}
