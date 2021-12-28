#include <RCSwitch.h>

const int LedPin = 13;
char message = 0;

RCSwitch mySwitch = RCSwitch();
void setup() 
{
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
  mySwitch.enableTransmit(11);  // Der Sender wird an Pin 10 angeschlossen
}

void loop() 
{
  message++;
  mySwitch.send(message, 24); // Der 433mhz Sender versendet die Dezimalzahl „1234“
  Serial.println("alles ok");
  digitalWrite(LedPin, HIGH);
  delay(1000);  // Eine Sekunde Pause, danach startet der Sketch von vorne
  digitalWrite(LedPin, LOW);  
}  
