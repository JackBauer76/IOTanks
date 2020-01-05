/*


*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Timer.h"
#include <dht.h>
#include <Adafruit_NeoPixel.h>
#include <avr/interrupt.h> 

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            13 // Nano
#define NUMPIXELS     35
#define COLORSTEP 10
#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafrui
dht DHT;

float tempMax=0;
float tempMin=100;
const int LedPin = 9;
const int TempSensorPin = 7;
const int IRdetector = 6;


void setup()
{
    pixels.begin(); // This initializes the NeoPixel library.
    pinMode(TempSensorPin, INPUT);
    pinMode(LedPin, OUTPUT);
    pinMode(IRdetector, INPUT);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    display.clearDisplay();

}

void loop()
{
    int chk = DHT.read11(TempSensorPin);
    if (DHT.humidity < tempMin)
    {
        tempMin = DHT.humidity;
    }
    if (DHT.humidity > tempMax)
    {
        tempMax = DHT.humidity;
    }
    
    rainbowCycle(1);

    colorWipe(pixels.Color(0, 0, 100), 50); // Blue

    DHT.humidity > 70.0? digitalWrite(LedPin, HIGH):digitalWrite(LedPin, LOW);

    digitalRead(IRdetector)?  digitalWrite(LedPin, LOW):digitalWrite(LedPin, HIGH);
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Temp = ");
    display.print(DHT.temperature);
    display.println(" *C");
    display.print("Humedad = ");
    display.print(DHT.humidity);
    display.println(" %");
    display.print("Hum Max= ");
    display.print(tempMax);
    display.println(" *C");
    display.print("Hum Min= ");
    display.print(tempMin);
    display.println(" *C");
    display.display();
    display.clearDisplay();

}

////////////////////// NEOPIXEL FUNCTIONS /////////////////

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