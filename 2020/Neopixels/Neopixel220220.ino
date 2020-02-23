#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       5
#define NUMPIXELS 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 30
#define DELAYPAUSE 15

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();

  /*for(int i=0; i<NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(DELAYVAL);
  }*/

for(int k= 1; k<500;k++)
{
  for(int i=0;i<NUMPIXELS; i++)
  {
        int r,g,b;
        if(i==0)
        {   r= 100; g= 0; b= 0; }
        else if (i==1)
        {   r= 0; g= 100;  b= 0;  }
       else if (i==2)
        {   r= 0; g= 0;  b= 100;  }
        else if (i==3)
        {   r= 100; g= 100; b= 0; }
        else if (i==4)
        {   r= 100; g= 0;   b = 100;  }
        else if(i==5)
        {   r= 0;   g= 100; b= 100;   }
        pixels.setPixelColor(i, pixels.Color(r,g,b));
        pixels.show();
        delay(k*2);
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        delay(k*1);
  }
}
}