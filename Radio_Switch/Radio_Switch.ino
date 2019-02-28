
#include <Arduino.h>
#include <SimpleDHT.h>

#define led_white 5
#define led_blue 9
#define dht_pin 7
// #define pir_pin A6 // Test1
#define pir_pin 3


SimpleDHT11 dht11(dht_pin);
long threshold = 1200;
unsigned long previousMillis = 0; 
bool led_blue_state = LOW;
int pirStatus;
int pirStatusOld;

void setup()
{
  Serial.begin(9600);
  pinMode(led_white, OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(dht_pin, INPUT);
  // pinMode(pir_pin, INPUT); // Test1
  pinMode(pir_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pir_pin), blink, RISING);
}

byte temperature = 0;
byte humidity = 0;
int pirCounter = 0;

void loop() 
{
  unsigned long currentTime = millis();
  
  if (millis() - previousMillis > threshold)
  {
      
      int err = SimpleDHTErrSuccess;
      if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
      {
        Serial.print("Read DHT11 failed, err="); Serial.println(err);
        return;
      }
      
      Serial.print("Sample OK: ");
      Serial.print((int)temperature); Serial.print(" *C, "); 
      Serial.print((int)humidity); Serial.println(" H");
      
      previousMillis = millis();
      if(led_blue_state == LOW)
      {
        led_blue_state = HIGH;
        
      }
      else
      {
        led_blue_state = LOW; 
      }
      
      digitalWrite(led_blue, led_blue_state);
      
      pirStatus = digitalRead(pir_pin);
      //Serial.print(pirStatus);


      Serial.print(" pir Counter : ");
      Serial.println(pirCounter);

  }
  // pirStatus = analogRead(pir_pin); // Test1
  //pirStatus = digitalRead(pir_pin);
  //Serial.print("Millis : ");
  //Serial.print(millis());
  //Serial.print("   Current time : ");
  //Serial.print((currentTime - previousMillis));
  //Serial.print(" Pir Status : ");
  //digitalWrite(led_white, pirStatus);
  digitalWrite(led_white, pirStatus);

}

void blink()
{
  pirCounter++;
}