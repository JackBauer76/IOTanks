const int Buzzer = 4;

void setup() 
{
  pinMode(Buzzer,OUTPUT);  
  Serial.begin(9600);
}

void loop() 
{
  machine_gun_tone();
  delay(1000);
  bomb_tone();
  delay(1000);
  bomb_tone2();
  delay(1000);
  
  //bomb_tone3();
  delay(1000);
}



void machine_gun_tone()
{
  

 for (int i=1; i <100;i++)
  {
    tone(Buzzer, 100, 15);
    delay(1);
    noTone(Buzzer);
    delay(55);
  }
}


void bomb_tone()
{
 for (int i=1; i <25;i++)
  {
    tone(Buzzer, 6000, 15);
    delay(10);
    noTone(Buzzer);
    delay(55);
  }
}


void bomb_tone2()
{
 for (int i=1; i <20;i++)
  {
    tone(Buzzer, 8000, 15);
    delay(15);
    noTone(Buzzer);
    delay(55);
  }
}



void bomb_tone3()
{
    tone(Buzzer, 6000, 175);
    delay(10);
    noTone(Buzzer);
}

