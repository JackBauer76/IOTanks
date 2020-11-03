#define Buzzerpin 3
#define BlueLedPin 6
#define WhiteLedPin 11
#define PotiPin A1
#define PushButtonPin 2
#define CLKPin 9
#define DIOPin 10

const int Freq = 4000;
const int tOn = 1000;

void setup() {
  pinMode(Buzzerpin,OUTPUT);
  pinMode(BlueLedPin, OUTPUT);
  pinMode(WhiteLedPin, OUTPUT);
  pinMode(PushButtonPin, INPUT_PULLUP);
  pinMode(PotiPin, INPUT);
  
}

void loop() {
  tone(Buzzerpin, Freq);
  delay(tOn);
  noTone(Buzzerpin);
  delay(tOn);
}
