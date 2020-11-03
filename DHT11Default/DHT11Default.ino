#include <dht.h>
#include <TM1637Display.h>

const int led_white = 10;
const int led_blue = 7;
const int clk_pin = 8;
const int dio_pin = 9;
const int pinDHT11 = 4;
byte temperature = 0;
byte humidity = 0;

dht DHT;
TM1637Display display4d(clk_pin, dio_pin);

void setup() 
{
  Serial.begin(9600);
  display4d.setBrightness(15);
}

void loop() {

  int chk = DHT.read11(pinDHT11);
  display4d.showNumberDec((int)DHT.temperature, true, 2, 4); // Expect: ___0
  delay(1000);
  display4d.showNumberDec((int)DHT.humidity, false); 


  if(DHT.humidity >= 65)
  {
    
    digitalWrite(led_white, HIGH);
  }
  else
  {
    
    digitalWrite(led_white, LOW);
  }

  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  Serial.println(DHT.temperature);
  Serial.println(DHT.humidity);
  
  
  //delay(1500);
}
