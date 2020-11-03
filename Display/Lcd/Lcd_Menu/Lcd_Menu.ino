
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int key_a = 6 , key_b = 7, key_c = 8, key_d =9;
int menu_1stLevel;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{

    lcd.begin(0, 0);

    pinMode(key_a, INPUT_PULLUP);
    pinMode(key_b, INPUT_PULLUP);
    pinMode(key_c, INPUT_PULLUP);
    pinMode(key_d, INPUT_PULLUP);

}

void loop() {

    
    if (digitalRead(key_a)== LOW)
    {
        menu_1stLevel = 1;
    }
    else if (digitalRead(key_b)== LOW)
    {
        menu_1stLevel = 2;
    }
    else if (digitalRead(key_c)== LOW)
    {
        menu_1stLevel = 3;
    }
    else if (digitalRead(key_d)== LOW)
    {
        menu_1stLevel = 4;
    }
    else
    {
        menu_1stLevel = 0;
    }
    


    switch (menu_1stLevel)
    {
        case 0:
            lcd.clear();
            lcd.setCursor(1,1); 
            lcd.print("escoge algo");
            //lcd.scrollDisplayLeft();
            break;
        case 1:
            lcd.clear();
            lcd.setCursor(1,1); 
            lcd.print("quieres coger");
            //lcd.scrollDisplayLeft();
            break;
        case 2:
            lcd.clear();
            lcd.setCursor(1,1); 
            lcd.print("quieres fumar");
            //lcd.scrollDisplayLeft();
            break;
        case 3:
            lcd.clear();
            lcd.setCursor(1,1); 
            lcd.print("quieres coger");
            //lcd.scrollDisplayLeft();
            break;
        case 4:
        lcd.clear();
            lcd.setCursor(1,1);
            lcd.print("quieres mamar");
            //lcd.scrollDisplayLeft();
            break;
    }


    delay(100);
}
