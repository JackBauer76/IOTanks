/* V3 based on v2 but with other loop control  
 * new ideas: adapting the lighting pattern functios and instead of using delay, use timer library
 */

#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h> 
#ifdef __AVR__
#include <avr/power.h>
#endif
//#define PIN            3 // Tiny
#define PIN             6 // Nano
#define NUMPIXELS      6
#define COLORSTEP       10
#define Pushbutton      3
//#define Pushbutton      0
//#define PCINT_PIN 0
#define PCINT_MODE CHANGE
#define PCINT_FUNCTION blinkLed
#define Poti1 A3
#include "Timer.h"
#include "PinChangeInterrupt.h"

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
//      Ain0 (D 5) PB5  1|    |8  Vcc
// PIR  Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1     Neopixel
//      Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     Rotor
//                 GND  4|    |5  PB0 (D 0) pwm0     Pushbutton
//    


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Timer t;

volatile int AuthState = 0;
int ValuePoti;

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(Pushbutton, INPUT_PULLUP);
  pinMode(Poti1, INPUT);
  //pinMode(PCINT_PIN, INPUT_PULLUP);
   // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif
  //Serial.begin(9600);
  //attachInterrupt(Pushbutton, Auth, RISING);
  //attachPinChangeInterrupt();
  attachPCINT(digitalPinToPCINT(Pushbutton), Auth, CHANGE);
}

void loop() 
{
  //Serial.print(AuthState);
  //ValuePoti = analogRead(Poti1);
  ValuePoti = map(analogRead(Poti1),0,1023,0,255 );
  
  switch(AuthState)
  {
    case 0:
        colorWipe(pixels.Color(255, 0, ValuePoti), 1); 
        break;
    case 1:
        colorWipe(pixels.Color(255, 0, 0), 1); 
    
        break;
    case 2:
        colorWipe(pixels.Color(20, 200, 200), 1); 
    
        break;
    case 3:
        colorWipe(pixels.Color(255, 255, 255), 1); 
    
        break;
    case 4:
        colorWipe(pixels.Color(100, 200, 25), 1); 
    
        break;
    
    case 5:
        rainbow(1);
    
        break;
    case 6:
        theaterChaseRainbow(1);
    
        break;
   
  }
 delay(1);

 
}


void Auth() 
{
  AuthState = AuthState + 1;
  if (AuthState > 6)
  {
    AuthState = 0;
  }
  
}

       

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<pixels.numPixels(); i++) 
  {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) 
{
  uint16_t i, j;
  for(j=0; j<256; j++) 
  {
    for(i=0; i<pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<10; j++) 
  {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) 
    {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) 
      {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();
      delay(wait);
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) 
      {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;
  for(j=0; j<256*5; j++) 
  { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}


//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) 
    {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) 
      {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();
      delay(wait);
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) 
      {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

/*
 *     colorWipe(pixels.Color(255, 0, 0), 50); // Red
       rainbow(10);
       theaterChase(pixels.Color(127, 127, 127), 20); // White
       theaterChase(pixels.Color(127, 0, 0), 20); // Red
       theaterChase(pixels.Color(127, 0, 127), 20); // Blue
       rainbowCycle(5);
       theaterChaseRainbow(20);
       colorWipe(pixels.Color(0, 0, 255), 50); // Blue
       rainbow(10);
       theaterChase(pixels.Color(127, 127, 127), 50); // White
       theaterChase(pixels.Color(127, 0, 0), 50); // Red
       theaterChase(pixels.Color(0, 0, 127), 50); // Blue
       rainbowCycle(20);
       theaterChaseRainbow(50);
       
 */
