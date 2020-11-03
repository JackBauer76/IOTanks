

/* Closet lamp version 0.1
 *  23.12.19
 *  
 *  Objective: Test range & recognition hability of 
 *  mini PIR
 *  Radar
 * 
 * 
 */


  const int mPir = 2;
  const int radarPin = 3;
  const int blueLed = 11;
  const int whiteLed = 9;
  bool pirCheck = false;
  bool radarCheck = false;
  bool tryDelay = false;
  const int tDelay = 10;
  
     
void setup() 
{
  pinMode(mPir, INPUT); // check INPUT_PULLUP
  pinMode(radarPin, INPUT); // check INPUT_PULLUP
}

void loop() 
{
  
  for(int i=1; i < 5; i++)
  {
  
  pirCheck = digitalRead(mPir);
  radarCheck = digitalRead(radarPin);


  if(pirCheck)
{
  digitalWrite(whiteLed, HIGH);
  digitalWrite(blueLed, LOW);
  if(tryDelay==HIGH)
  {
    delay(i*tDelay);
  }
}
  else if(radarCheck)
{
  digitalWrite(blueLed, HIGH);
  digitalWrite(whiteLed, LOW);
  if(tryDelay==HIGH)
  {
    delay(i*tDelay);
  }
}
else
{
  digitalWrite(blueLed, LOW);
  digitalWrite(blueLed, LOW);
  if(tryDelay==HIGH)
  {
    delay(i*tDelay);
  }
}
  }// for
}// loop