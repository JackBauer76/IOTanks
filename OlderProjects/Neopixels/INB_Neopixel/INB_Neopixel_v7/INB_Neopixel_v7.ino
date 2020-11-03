/* PIR and each color being flushed
 * Version with just 7 Neopixels and supplied by Nano 5v
 * 
 * 
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            12
#define NUMPIXELS      7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



int delayval = 100; // delay for half a second
const int PIR = 3;

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(PIR, INPUT);
}

void loop() 
{
 
  if(digitalRead(PIR))
  {
    for(int i=0;i<NUMPIXELS;i++)
    {
      pixels.setPixelColor(i, pixels.Color(random(0,255),random(0,255),0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor(i-1, pixels.Color(0,0,0)); 
      pixels.setPixelColor((i-2), pixels.Color(random(0,255),random(0,255),random(0,255))); 
      pixels.setPixelColor((i-3), pixels.Color(random(0,255),random(0,255),random(0,255))); 
      pixels.setPixelColor((i-2)-1, pixels.Color(0,0,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      pixels.setPixelColor((i-3)-1, pixels.Color(0,0,0)); 
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
    }
    for(int i=(NUMPIXELS-1);i>-1;i=i-1)
    {
        pixels.setPixelColor(i, pixels.Color(0,0,255)); 
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).
        pixels.setPixelColor(i-1, pixels.Color(255,255,0)); 
        pixels.setPixelColor(i+1, pixels.Color(0,0,0)); 
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).
    }
  }
  else
  {
        pixels.setPixelColor(NUMPIXELS,0,0,0); 
        pixels.show(); // This sends the updated pixel color to the hardware.
  }
}
