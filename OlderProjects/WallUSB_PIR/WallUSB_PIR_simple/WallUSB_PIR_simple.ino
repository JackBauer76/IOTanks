#define LED1 1
#define LED2 2
#define PIR 0

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(PIR,INPUT);
  //attachInterrupt(PIR, motionDetector, CHANGE);
  
}

void loop() {

  if(digitalRead(PIR)){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
  }
  else
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
  }

   




}
