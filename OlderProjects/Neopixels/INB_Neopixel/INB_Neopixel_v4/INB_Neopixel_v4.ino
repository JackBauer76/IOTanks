/* PIR and each color being flushed
 * 
 * 
 * 
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      120

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second
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
    pixels.setPixelColor(i, pixels.Color(0,255,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i-1, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
   
  }
  for(int i=(NUMPIXELS-1);i>-1;i=i-1)
  {
    pixels.setPixelColor(i, pixels.Color(0,255,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i+1, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }

for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(255,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i-1, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
  }
  for(int i=(NUMPIXELS-1);i>-1;i=i-1)
  {
    pixels.setPixelColor(i, pixels.Color(255,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i+1, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }

for(int i=0;i<NUMPIXELS;i++)
  {
    pixels.setPixelColor(i, pixels.Color(0,0,255)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i-1, pixels.Color(0,0,0)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/10); // Delay for a period of time (in milliseconds).
  }
  for(int i=(NUMPIXELS-1);i>-1;i=i-1)
  {
    pixels.setPixelColor(i, pixels.Color(0,0,255)); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
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
