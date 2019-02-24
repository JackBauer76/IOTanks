/*                  +-\/-+
//            Ain0 (D 5) PB5  1|    |8  Vcc
// TempSensor Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
//            Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     CLK
//                       GND  4|    |5  PB0 (D 0) pwm0     DIO
*/
#include <TM1637Display.h>

#define CLK 1 // CLK is PB4 in ATtiny85
#define DIO 0 // DIO is PB3 in ATtiny85
#define TempSensor 3
#define TEST_DELAY   100

TM1637Display display(CLK, DIO);

int reading;
float voltage;
float temperatureC;

void setup()
{
  pinMode(TempSensor, INPUT);
}

void loop()
{
  display.setBrightness(03);
  reading = analogRead(TempSensor);
  voltage = reading * 4.4;
  voltage /= 1024.0;
  temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset
  display.showNumberDec(temperatureC, false); // Expect: ___0
  delay(TEST_DELAY);
}
