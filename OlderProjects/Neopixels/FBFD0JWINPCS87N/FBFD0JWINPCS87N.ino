#include <Adafruit_NeoPixel.h>

#define PIN 6 //pin number that you have connected your data pin to
#define PIXNUMBER 20 //number of neopixels you have connected

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXNUMBER, PIN, NEO_GRB + NEO_KHZ800); //1. nuber defines number of pixels you have connected, 2. is number of the pin your data is connected to, 3 and 4 are other arguments but use these as they are default for most neopixels but refet to datasheet for other options

uint32_t color = strip.Color(0, 0, 0);//in (0, 0, 0) type in intesities for each color

void setup() {
  
  strip.begin();
  strip.show();//sets all pixels to off state

}

void loop() {

 strip.setPixelColor(5, RED, GREEN, BLUE); //set pixel collor: 1. is the pixel number, 2., 3., 4. are values from 0-255 for brightness of each color of the pixel

 strip.setPixelColor(6, color); //you can use a variable such as color that is defined in another section of the code.//

 uint32_t color = strip.getPixelColor(pixel);//get a color of a pixel for previous cycle

 uint16_t n = strip.numPixels(); //get a number of pixels previously-declared strip

 strip.setBrightness(brightness);//Set brightness of the whole strip from 0 - 255

 strip.show();//show the pixels / colors of them after every cycle of loop -- like a refresh state

}
    
