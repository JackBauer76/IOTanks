
const int Led = 8;
const int IRdetector = 6;

void setup()
{
    pinMode(Led, OUTPUT);
    pinMode(IRdetector, INPUT);
}

void loop()
{
    if(digitalRead(IRdetector))
    {
        digitalWrite(Led, HIGH);
    }
    else
    {
        digitalWrite(Led, LOW);
    }
    
}