// include the library code:
#include <LiquidCrystal.h>
#include <Ultrasonic.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(27,25,6,9,10,11);

byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
 
// connect to the ST_CP of 74HC595 (pin 3,latch pin)
int latchPin = 24;
// connect to the SH_CP of 74HC595 (pin 4, clock pin)
int clockPin = 26;
// connect to the DS of 74HC595 (pin 2)
int dataPin = 22;


void setup() {
  Serial.begin(9600);
  delay(1000);
   
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("MEDIDOR DIST");

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
}

void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    
    Ultrasonic ultrasonic(5, 51);
    int hitTime = ultrasonic.distanceRead();
    int distanceInCm = hitTime;
    Serial.print(distanceInCm);
    Serial.println("cm");
    delay(1000);
    lcd.begin(16, 2);
    lcd.print("Distancia");
    lcd.setCursor(0, 1);
    lcd.print(distanceInCm);
    lcd.setCursor(3, 1);
    lcd.print("cm");

    for (byte digit = 10; digit > 0; --digit) {
    delay(1000);
    sevenSegWrite(digit - 1); 
  }
   

}   
