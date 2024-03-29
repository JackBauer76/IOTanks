/*******************************************************************
  SoftServo sketch for Adafruit Trinket.  Turn the potentiometer knob
  to set the corresponding position on the servo 
  (0 = zero degrees, full = 180 degrees)
 
  Required library is the Adafruit_SoftServo library
  available at https://github.com/adafruit/Adafruit_SoftServo
  The standard Arduino IDE servo library will not work with 8 bit
  AVR microcontrollers like Trinket and Gemma due to differences
  in available timer hardware and programming. We simply refresh
  by piggy-backing on the timer0 millis() counter
 
  Required hardware includes an Adafruit Trinket microcontroller
  a servo motor or two, and a potentiometer (nominally 1Kohm to 100Kohm
 
  As written, this is specifically for the Trinket although it should
  be Gemma or other boards (Arduino Uno, etc.) with proper pin mappings
 
  Trinket:        USB+   Gnd   Pin #0  Pin #1  Pin #2 A1
  Connection:     Servo+  -   Servo1 Servo2   Potentiometer wiper
 
 *******************************************************************/

#include <Adafruit_SoftServo.h>  // SoftwareServo (works on non PWM pins)

// We demonstrate two servos!
#define SERVO1PIN 0   // Trinket Pin #0

Adafruit_SoftServo myServo1;  //create TWO servo objects

int pos = 0;   

void setup() {
  // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  myServo1.attach(SERVO1PIN);   // Attach the servo to pin 0 on Trinket
  //myServo1.write(90);           // Tell servo to go to position per quirk
  delay(15);                    // Wait 15ms for the servo to reach the position
}

void loop()  
{
  for (pos = 0; pos <= 180; pos += 1) 
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    
    myServo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(80);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) 
  { // goes from 180 degrees to 0 degrees
    myServo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(80);       
  }
  
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    myServo1.refresh();
  }
}
