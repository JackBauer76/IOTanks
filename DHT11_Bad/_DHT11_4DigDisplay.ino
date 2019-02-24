#include <TM1637Display.h>
#include <SPI.h>
#include <Wire.h>
#include "Timer.h"
#include <dht.h>

#define CLK 4 // CLK is PB4 in ATtiny85
#define DIO 3 // DIO is PB3 in ATtiny85
#define TEST_DELAY   50
#define DHT11_PIN 2

dht DHT;

int counter = 0;
float tempMax=0;
float tempMin=100;
int temp =10;
int humid =90;

TM1637Display display4d(CLK, DIO);
Timer t;

void setup()   {
  
}


void loop()
{
  
  t.update();
  t.every(250,readSensor);

    
  display4d.setBrightness(15);
  //display4d.showNumberDec(13, false); // Expect: ___0
  display4d.showNumberDec(temp, false); // Expect: ___0
  //delay(TEST_DELAY);
  //display4d.showNumberDec((int)temp, true,2,4);  // Expect: 04__
  //display4d.showNumberDec(88, false); // Expect: ___0
  display4d.showNumberDec(humid, false); // Expect: ___0
  //delay(TEST_DELAY);
  
  
  

  /*
  dht11.read(pinDHT11, &temperature, &humidity, NULL);
  if ((int)humidity < tempMin)
  {
    tempMin = (int)humidity;
  }
  if ((int)humidity > tempMax)
  {
    tempMax = (int)humidity;
  }
*/

}


void readSensor()
{

  int chk = DHT.read11(DHT11_PIN);
  humid = DHT.humidity;
  temp = DHT.temperature;

return humid,temp;
}

/*  
    int8_t hum = dht.readHumidity();
    int8_t temp = dht.readTemperature(1);
  //dht11.read(pinDHT11, &temperature, &humidity, NULL);
  
  
  if ((int)hum < tempMin)
  {
    tempMin = (int)hum;
  }
  if ((int)hum > tempMax)
  {
    tempMax = (int)hum;
  }
  return tempMax, tempMin, hum, temp;
} 
*/
