    // ATMEL ATTINY 25/45/85 / ARDUINO
    //
    //                  +-\/-+
    //      Ain0 (D 5) PB5  1|    |8  Vcc
    // PIR  Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1     Neopixel
    //      Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1     Rotor
    //                 GND  4|    |5  PB0 (D 0) pwm0     Pushbutton
    //      


const int Pushbutton = 9;
const int Relay = 7;
const int Pir = 3;
const int SensorDig = 2;
const int SensorAnalog = A0;
const int LedPin = 5;

void setup()
{
    Serial.begin(9600);
    pinMode(Pushbutton, INPUT_PULLUP);
    pinMode(Relay, OUTPUT);
    pinMode(Pir, INPUT);
    pinMode(SensorDig,INPUT);
    pinMode(SensorAnalog,INPUT);
    pinMode(LedPin, OUTPUT);    
}

void loop()
{
    Serial.println(analogRead(SensorAnalog));

    if (digitalRead(Pir)||digitalRead(SensorDig))
    {
        digitalWrite(Relay, HIGH);
        digitalWrite(LedPin, HIGH);

        
    }
    else
    {
        digitalWrite(Relay, LOW);
        digitalWrite(LedPin, LOW);
    }
    
}
