#define BuzzerPin 4
#define Ledpin 9
#define GroundPin 7

void setup() {
  pinMode(Ledpin, OUTPUT);
  pinMode(GroundPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
}

void loop() {
    digitalWrite(GroundPin, LOW);
    digitalWrite(Ledpin, HIGH);
    delay(1000);
    digitalWrite(Ledpin, LOW);
    delay(100);
    tone(BuzzerPin, 3880);  
/*    
    for (int i=0;i<12000;i++)
    {
    tone(BuzzerPin, i);
    delay(1);
*/
    
}
