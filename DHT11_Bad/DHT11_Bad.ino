
#include <TM1637Display.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_Sensor.h>
#include "Timer.h"
//#include <SimpleDHT.h>
#include <dht.h>



#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#define Pushbutton 2
#define LED 11
#define CLK 4 // CLK is PB4 in ATtiny85
#define DIO 3 // DIO is PB3 in ATtiny85
#define DHT11_PIN 2

#define TEST_DELAY   1000

dht DHT;
 
int counter = 0;
float tempMax=0;
float tempMin=100;

Adafruit_SSD1306 display(OLED_RESET);
TM1637Display display4d(CLK, DIO);
Timer t;

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

byte temperature = 0;
byte humidity = 0;

void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  Serial.begin(9600);
  pinMode(Pushbutton, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(12,OUTPUT); // GND for LED
    
}


void loop()
{
  digitalWrite(12,LOW); // GND for LED
  int chk = DHT.read11(DHT11_PIN);

  display4d.setBrightness(15);
  display4d.showNumberDec((int)DHT.temperature, false); // Expect: ___0
  delay(TEST_DELAY);


  if(DHT.humidity >= 65)
  {
    
    digitalWrite(LED, HIGH);
  }
  else
  {
    
    digitalWrite(LED, LOW);
  }


  //t.update();
  //t.every(1000, readSensor);

  //readSensor();
  
  //int err = SimpleDHTErrSuccess;
  //if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
  //  Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
  //  return;
  
  //}

  
  //dht11.read(pinDHT11, &temperature, &humidity, NULL);
  if (DHT.humidity < tempMin)
  {
    tempMin = DHT.humidity;
  }
  if (DHT.humidity > tempMax)
  {
    tempMax = DHT.humidity;
  }
  
  //Serial.print("Sample OK: ");
  //Serial.print((int)temperature); Serial.print(" *C, "); 
  //Serial.print((int)humidity); Serial.println(" H");

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
 
    display4d.setBrightness(15);
    display4d.showNumberDec(DHT.temperature, false); // Expect: ___0
    delay(TEST_DELAY);
    display4d.showNumberDec(DHT.humidity, true);  // Expect: 04__
    delay(TEST_DELAY);
}

/*
void readSensor()
{

  byte temperature = 0;
  byte humidity = 0;
  dht11.read(pinDHT11, &temperature, &humidity, NULL);
  
  
  if ((int)humidity < tempMin)
  {
    tempMin = (int)humidity;
  }
  if ((int)humidity > tempMax)
  {
    tempMax = (int)humidity;
  }
} 
*/
