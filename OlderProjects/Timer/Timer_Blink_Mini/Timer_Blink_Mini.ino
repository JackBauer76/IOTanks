#include <Timer.h>

Timer t;

#define LED 3
#define BUZZER 8
#define PIR 5

struct rect_t{
  int left;
  int bottom;
  int right;
  int top;
  char apodo;
  };
typedef struct rect_t rectangle;

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);

}

void loop() 
{
  //t.every(1000, blinkin);
  //t.every(2000, blinkoff);
  t.update();
  while (digitalRead(PIR))
  {
      digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, LOW);

  struct rect_t myRect;
  myRect.left = 1;
  myRect.bottom = 0;
  myRect.right = 6;
  myRect.top = 6;

  rectangle myRect2;
  myRect2.left = 1;
  myRect2.bottom = 0;
  myRect2.right = 6;
  myRect2.top = 6;
  myRect2.apodo = "s";


}


void blinkin()
{
  digitalWrite(LED, HIGH);
  for(int i=0; i<30000; i++)
  {
      //tone(BUZZER, i, 1200);  
  }
  
  //t.after(200,blinkoff);
}


void blinkoff()
{
  digitalWrite(LED, LOW);
  noTone(BUZZER);
}


