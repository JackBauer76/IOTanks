/*


*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Timer.h"
#include <dht.h>

#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16


Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif




float tempMax=0;
float tempMin=100;


const int LedPin = 9;
const int TempSensorPin = 7;
const int IRdetector = 6;

dht DHT;

void setup()
{
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