/* PIR and each color being flushed
 * Version with just 7 Neopixels and supplied by Nano 5v
 * LEDs light one after the other in one direction and the back
 * different colos
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            12
#define NUMPIXELS      7
#define COLORSTEP 10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1; // delay for half a second
int delaycol = 24;
const int PIR = 3;
const int Pushbutton = 2;

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(PIR, INPUT);
  pinMode(Pushbutton, INPUT_PULLUP);
}

void loop() 
{
  
  //digitalRead(Pushbutton);
  if(digitalRead(PIR))
  {
      for(int i=0; i<NUMPIXELS; i++)
      {
          
          for(int k=0; k<6; k++)
              {
              pixels.setPixelColor(i, pixels.Color(20,10,50*k));
              pixels.show(); // This sends the updated pixel color to the hardware.
              delay(delaycol); // Delay for a period of time (in milliseconds).
              }
              delay(delayval);
      }
      for(int i=(NUMPIXELS-1);i>-1;i=i-1)
      {
          for(int w=0; w<6; w++)
              {
              pixels.setPixelColor(i, pixels.Color(50*w,20,10));
              pixels.show(); // This sends the updated pixel color to the hardware.
              delay(delaycol); // Delay for a period of time (in milliseconds).
              }
              delay(delayval);
      }
  }      
  else
  {
     for(int i=0; i<NUMPIXELS; i++)
     {
     pixels.setPixelColor(i,0,0,0); 
     pixels.show(); // This sends the updated pixel color to the hardware.
     }
  }

  
}     
      
