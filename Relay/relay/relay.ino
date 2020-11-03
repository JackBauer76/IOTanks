
// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
//      Ain0 (D 5) PB5  1|    |8  Vcc
// PIR  Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1     Neopixel
//      Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     Rotor
//                 GND  4|    |5  PB0 (D 0) pwm0     Pushbutton
//      


const int Pushbutton = 1;
const int Relay = 2;
const int Pir = 0;

void setup()
{
    pinMode(Pushbutton, INPUT_PULLUP);
    pinMode(Relay, OUTPUT);
    pinMode(Pir, INPUT);
}

void loop()
{
    
    if (digitalRead(Pir))
    {
        digitalWrite(Relay, HIGH);
    }
    else
    {
        digitalWrite(Relay, LOW);
    }
    
    //delay(1500);
    
    //delay(1200);
}
