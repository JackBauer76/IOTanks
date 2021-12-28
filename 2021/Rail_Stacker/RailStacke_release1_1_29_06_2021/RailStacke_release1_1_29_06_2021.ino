#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <EEPROM.h>


const int Button_X_Pos = 2;
const int Button_X_Neg = 3;
const int Button_Y_Pos = 12;
const int Button_Y_Neg = 10;
const int Button_Z_Pos = 11;
const int Button_Z_Neg = 14;

const int EndStop_X= A6;

int EndStop_Value;

boolean EndStop_X_Reached;
boolean EndStop_Y_Reached;
boolean EndStop_Z_Reached;

int EndStop_Tolerance=15;



//Global variables for menu Routine//

int Menu_position=1; //1: steps; 2: step size; 3: Time between steps
int Number_steps;
int Time_step=180;

//Global variables for active Routine

int actual_step_routine;
int actual_time_routine;

int operational_mode = 0; //0=Manual; 1:menu configuration routine; 2:routine execution

const int Enable_X_pin =15;
const int Enable_Y_pin =16;
const int Enable_Z_pin =17;


const int stepPin_X = 7;  
const int stepPin_Y = 5; //RESUME
const int stepPin_Z = 4; //RESUME

const int dirPin = 6;//3; 


const int Speed_up = 9;//8;  
const int Speed_down = 8;   

const int led = 10; 

float Xp_offset= 0;
float Yp_offset= 0;
float Zp_offset= 0;

float x_Limit=50000;//Default limit for x
float y_Limit=30000;//Default limit for y
float z_Limit=25000;//Default limit for z


float mapX_absolute;
float mapY_absolute;
float mapZ_absolute;

float mapX_relative_center;
float mapY_relative_center;
float mapZ_relative_center;

int steps0= 10;
float DistanceToMove_nano=500; // max 32000 
volatile int update_lcd =1;


int y_speed=0;
int z_speed=0;


//general variables
int menuposition; //posicion del menu donde esta posicionado el cursor 
volatile long stepCounter=0;

//Controller Variables

boolean spd_up=LOW;   //spd_up=LOW;
boolean spd_down=LOW; //spd_down=LOW;
boolean x_up=LOW;
boolean x_down=LOW;
boolean z_up=LOW;  //time_up=LOW;
boolean z_down=LOW;  //time_down=LOW;
boolean back_menu=LOW;
boolean start_routine=LOW;



LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////////////// Setup //////////////////////////

void setup() 
{

  
  
  pinMode(stepPin_X,OUTPUT); 
  pinMode(stepPin_Y,OUTPUT); 
  pinMode(stepPin_Z,OUTPUT); 
  
  pinMode(dirPin, OUTPUT);


  pinMode(Enable_X_pin, OUTPUT);
  pinMode(Enable_Y_pin, OUTPUT);
  pinMode(Enable_Z_pin, OUTPUT);
  
  pinMode(EndStop_X, INPUT);
  
  //pinMode(Enable_pin, OUTPUT);
//  pinMode(led, OUTPUT);
  
//  pinMode(SW, INPUT_PULLUP);
  
 
  pinMode(Speed_up, INPUT_PULLUP); //RESUME
  pinMode(Speed_down, INPUT_PULLUP);//RESUME

  pinMode(Button_X_Pos, INPUT_PULLUP);
  pinMode(Button_X_Neg, INPUT_PULLUP);
  pinMode(Button_Y_Pos, INPUT_PULLUP);
  pinMode(Button_Y_Neg, INPUT_PULLUP);
  pinMode(Button_Z_Pos, INPUT_PULLUP);
  pinMode(Button_Z_Neg, INPUT_PULLUP);


  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,1);
  lcd.print("  Camera Stacker");
  delay(1000);

  lcd.clear();
  
  

  digitalWrite(Enable_X_pin,HIGH);
  digitalWrite(Enable_Y_pin,HIGH);
  digitalWrite(Enable_Z_pin,HIGH);

  center_all_axis();
  
  }


//////////////////////////////////// loop ////////////////////////////


void loop() 
{

read_controller();

  if (operational_mode==0)
  {
  
  EndStop_Value = analogRead(EndStop_X);
  Serial.print("Endstop Main : ");
  Serial.print(EndStop_Value);
  Serial.print("\n");

  Set_Axis_Control_Parameters();
  Move_Axis_With_Buttons(Button_X_Pos,Button_X_Neg,DistanceToMove_nano, stepPin_X,dirPin,Enable_X_pin);
  Move_Axis_With_Buttons(Button_Y_Pos,Button_Y_Neg,DistanceToMove_nano, stepPin_Y,dirPin,Enable_Y_pin);
  Move_Axis_With_Buttons(Button_Z_Pos,Button_Z_Neg,DistanceToMove_nano, stepPin_Z,dirPin,Enable_Z_pin);
  }

  else if (operational_mode==1)
  {
   Set_Axis_Control_Parameters();
  }

  else if (operational_mode==2)
  {
   automatic_routine_start();
  }

  else if (operational_mode==3)
  { 
   
  }

}
///////////////////////////////END OF MAIN PROGRAM//////////////////////////////////

/////////////////////////////// Functions ////////////////////////////////

void CheckEndStopLimits()
{

  EndStop_Value = analogRead(EndStop_X);
 // Serial.print("Endstop: ");
 // Serial.print(EndStop_Value);
 // Serial.print("\n");
  EndStop_X_Reached= LOW;
  EndStop_Y_Reached= LOW;
  EndStop_Z_Reached= LOW;

  if ((EndStop_Value + EndStop_Tolerance)>508 && (EndStop_Value - EndStop_Tolerance)<508)
  {
    EndStop_X_Reached= HIGH; //X Limit reached
  }
 else if((EndStop_Value + EndStop_Tolerance)>184 && (EndStop_Value - EndStop_Tolerance)<184)
  {
    EndStop_Y_Reached=HIGH; //Y Limit reached
  }
  else if((EndStop_Value + EndStop_Tolerance)>326 && (EndStop_Value - EndStop_Tolerance)<326)
  {
    EndStop_Z_Reached=HIGH; //Z Limit reached
  }
  else if((EndStop_Value + EndStop_Tolerance)>156 && (EndStop_Value - EndStop_Tolerance)<156)
  {
    EndStop_X_Reached=HIGH; //X Limit reached
    EndStop_Y_Reached=HIGH; //Y Limit reached
  } 
  else if((EndStop_Value + EndStop_Tolerance)>156 && (EndStop_Value - EndStop_Tolerance)<156)
  {
    EndStop_X_Reached=HIGH; //X Limit reached
    EndStop_Z_Reached=HIGH; //Z Limit reached
  }   

  else if((EndStop_Value + EndStop_Tolerance)>133 && (EndStop_Value - EndStop_Tolerance)<133)
  {
    EndStop_Y_Reached=HIGH; //X Limit reached
    EndStop_Z_Reached=HIGH; //Z Limit reached
  }   
}

int CheckAxleEnabled(const int axis_name)
{
 CheckEndStopLimits();
 if (axis_name==7){return  !EndStop_X_Reached;}
 else if(axis_name==5){return !EndStop_Y_Reached;}
 else if(axis_name==4){return !EndStop_Z_Reached;}
 else {return -1;}

}



float check_top_limit_axis(const int axix_name)
{

 if (axix_name==7){return x_Limit;}
 else if(axix_name==5){return y_Limit;}
 else if(axix_name==4){return z_Limit;}
 else {return -1;}
 
  
}





void center_all_axis()
{

  float x_center,y_center,z_center;

  x_center=x_Limit/2;
  y_center=y_Limit/2;
  z_center=z_Limit/2;

mapX_absolute=x_Limit;
mapY_absolute=y_Limit;
mapZ_absolute=z_Limit;

StepB(x_Limit, stepPin_X, dirPin);
StepB(y_Limit, stepPin_Y, dirPin);
StepB(z_Limit, stepPin_Z, dirPin);

lcd.clear(); 

StepF(x_center, stepPin_X, dirPin, LOW);
StepF(y_center, stepPin_Y, dirPin, LOW);
StepF(z_center, stepPin_Z, dirPin, LOW);


mapX_absolute=x_center;
mapY_absolute=y_center;
mapZ_absolute=z_center;

 

print_menu(DistanceToMove_nano, mapX_absolute, mapY_absolute, mapZ_absolute);
delay(2000);

mapX_relative_center=0;
mapY_relative_center=0;
mapZ_relative_center=0;
 
}



void automatic_routine_start()
{
  
int cancel_routine=LOW;
int triple_point=1;
int temp_steps;
int time_runtime_delay=99;
int time_accumulated_delay_motor1=0;
int time_accumulated_delay_motor2=0;
int constant_runtime_delay_motor=31;


lcd.clear();

actual_step_routine=0;
actual_time_routine=0;

print_active_routine(HIGH,HIGH,HIGH);
triple_point=1;

for(actual_step_routine=0;actual_step_routine<=Number_steps;actual_step_routine=actual_step_routine+1)
{

 for(actual_time_routine=0;actual_time_routine<Time_step;actual_time_routine++)
  {
    print_active_routine(HIGH,LOW,HIGH);
   
    cancel_routine=  not digitalRead(Button_Y_Neg); 
    
   
    //Prints blinking three points
    lcd.setCursor(0,0);
    if (triple_point==1) {lcd.print("Running.  "); triple_point=2;}
    else if (triple_point==2) {lcd.print("Running..  "); triple_point=3;}
    else {lcd.print("Running..."); triple_point=1;}
    delay(200-time_runtime_delay);//the delay of the runtime execution will be discounted
   
    cancel_routine=  cancel_routine || not digitalRead(Button_Y_Neg); 
    if (cancel_routine== HIGH) {break; }
    delay(200-time_accumulated_delay_motor1);//the delay of the motor control will be discounted
    time_accumulated_delay_motor1=0; 
    
    cancel_routine= cancel_routine|| not digitalRead(Button_Y_Neg);
    if (cancel_routine== HIGH) {break; }
    delay(200-time_accumulated_delay_motor2);
    time_accumulated_delay_motor2=0;
     
    cancel_routine= cancel_routine||  not digitalRead(Button_Y_Neg);
    if (cancel_routine== HIGH) {break; } 
    delay(200);
    cancel_routine= cancel_routine||  not digitalRead(Button_Y_Neg);
    if (cancel_routine== HIGH) {break; } 
    delay(200);
    cancel_routine= cancel_routine||  not digitalRead(Button_Y_Neg);
    if (cancel_routine== HIGH) {break; } 

  }
  
  if (cancel_routine== HIGH) 
    { operational_mode=1 ;
      lcd.clear();
      Print_Menu_Routine_Configuration(HIGH,HIGH,HIGH); 
      break;
    }


  
  //Moves the x-Axis
  if (cancel_routine==LOW){
  digitalWrite(Enable_X_pin,LOW); //Low in this case means enabled
  print_active_routine(HIGH,LOW,LOW);
  StepF(DistanceToMove_nano, stepPin_X, dirPin,LOW);
  time_accumulated_delay_motor1=(DistanceToMove_nano/625);
  time_accumulated_delay_motor2=constant_runtime_delay_motor;
  digitalWrite(Enable_X_pin,HIGH); //Low in this case means enabled
  }
 
}

operational_mode=1 ; //Finishes and goes back to configuration menu
lcd.clear();
Print_Menu_Routine_Configuration(HIGH,HIGH,HIGH);
delay(1500);

}


void print_active_routine(boolean update_steps,boolean update_distance, boolean update_time)
{

  lcd.setCursor(0,1);
  lcd.print("Steps: ");

  if (update_steps==HIGH){
  lcd.setCursor(11,1);
  lcd.print("        ");
  lcd.setCursor(11,1);
  lcd.print(actual_step_routine);
  lcd.print("/");
  lcd.print(Number_steps);}

  if (update_distance==HIGH){
  lcd.setCursor(0,2);
  lcd.print("Dist/s: ");
  lcd.setCursor(11,2);
  lcd.print("        ");
  lcd.setCursor(11,2);
  lcd.print(DistanceToMove_nano);
  lcd.print("um");}

  if (update_time==HIGH){
  
  lcd.setCursor(0,3);
  lcd.print("t/step: ");
  lcd.setCursor(11,3);
  lcd.print("        ");
  lcd.setCursor(11,3);
  lcd.print(actual_time_routine);
  lcd.print("s/");
  lcd.print(Time_step);
  lcd.print("s");}
  
}

void Print_Menu_Routine_Configuration(boolean update_steps,boolean update_distance, boolean update_time)
{


  lcd.setCursor(0,0);
  lcd.print("Configure Routine:");
  lcd.setCursor(0,1);
  lcd.print("No. Steps: ");
  
  if (update_steps==HIGH)
  {
  lcd.setCursor(11,1);
  lcd.print("        ");
  lcd.setCursor(11,1);
  lcd.print(Number_steps);
  }

  if(update_distance==HIGH)
  {
  lcd.setCursor(0,2);
  lcd.print("Dist/Step: ");
  lcd.setCursor(11,2);
  lcd.print("        ");
  lcd.setCursor(11,2);
  lcd.print(DistanceToMove_nano);
  lcd.print("um");
  }

  if(update_time==HIGH)
  {
  lcd.setCursor(0,3);
  lcd.print("Time/Step: ");
  lcd.setCursor(11,3);
  lcd.print("        ");
  lcd.setCursor(11,3);
  lcd.print(Time_step);
  lcd.print("s");
  }

}
//Reads the input from the control to activate different modes and set step/and time values
void Set_Axis_Control_Parameters() 
{

   boolean activation_flag_switch_mode=LOW; //avoids switching between one mode to the other constantly when the buttons are pressed
   
   int speed_selector_divider=1;
   int speed_selector=1;
   int old_step_value;
   float distance_increment=0.625;

  
  speed_selector=1;
  while (((spd_up==HIGH || spd_down==HIGH) && (operational_mode==0||operational_mode==1)) || ((x_up==HIGH ||x_down==HIGH || z_up==HIGH || z_down==HIGH || back_menu==HIGH || start_routine==HIGH) && operational_mode==1)) //RESUME
   {

     //increases the steps//
     if  (spd_up==HIGH && spd_down==LOW && (DistanceToMove_nano+distance_increment)<5000) 
        { 
                 
     //   digitalWrite(led,HIGH);  
        old_step_value=DistanceToMove_nano;
        DistanceToMove_nano = DistanceToMove_nano + distance_increment;
        if (operational_mode==0) {print_menu(DistanceToMove_nano, mapX_relative_center, mapY_relative_center, mapZ_relative_center);}
        else if (operational_mode==1) {Print_Menu_Routine_Configuration(LOW,HIGH,LOW);  }
        delay(300/speed_selector);

        }
        
      //Decreases steps  
      else if  (spd_up==LOW && spd_down==HIGH && (DistanceToMove_nano-distance_increment)>=(0.625)) 
        {
          old_step_value=DistanceToMove_nano;
          DistanceToMove_nano = DistanceToMove_nano - distance_increment;
          if (operational_mode==0) {print_menu(DistanceToMove_nano, mapX_relative_center, mapY_relative_center, mapZ_relative_center);}
          else if (operational_mode==1)  {Print_Menu_Routine_Configuration(LOW,HIGH,LOW);  }
          delay(300/speed_selector);
        }
         
      //Resets from highest steps to smallest step /////////////DEACTIVATED///////////
        else if  (spd_up==HIGH && spd_down==LOW && (DistanceToMove_nano+distance_increment)>59000) 
        {
          old_step_value=DistanceToMove_nano;
         // DistanceToMove_nano = 0.625;
          if (operational_mode==0) {print_menu(DistanceToMove_nano, mapX_relative_center, mapY_relative_center, mapZ_relative_center);}
          else if (operational_mode==1)  {Print_Menu_Routine_Configuration(LOW,HIGH,LOW);  }
          delay(300/speed_selector);
        }
        //Sets the number of steps for automatic routine
        else if (x_up==HIGH && x_down==LOW && operational_mode==1 && Number_steps<300)
        {
         Number_steps+=1;
         Print_Menu_Routine_Configuration(HIGH,LOW,LOW);  
         delay(300/speed_selector);
          
        }
        //sets the number of steps for automatic routine
         else if ( x_up==LOW && x_down==HIGH && operational_mode==1 && Number_steps>0)
          {
         Number_steps-=1;
         Print_Menu_Routine_Configuration(HIGH,LOW,LOW);  
         delay(300/speed_selector);
          }
         //Set the time between steps for the automatic routine 
         else if ( z_up==HIGH && z_down==LOW && operational_mode==1 && Time_step<1000)
          {
         Time_step+=1;
         Print_Menu_Routine_Configuration(LOW,LOW,HIGH);  
         delay(300/speed_selector);
          }
        //Set the time between steps for the automatic routine 
         else if ( z_up==LOW && z_down==HIGH && operational_mode==1 && Time_step>0)
          {
         Time_step-=1;
         Print_Menu_Routine_Configuration(LOW,LOW,HIGH);   
         delay(300/speed_selector);
          }
          
         if (((DistanceToMove_nano-distance_increment)<0.625) || (DistanceToMove_nano+distance_increment>5000)) //Resets speed divider
          {
            speed_selector=1;
            speed_selector_divider=1;
            distance_increment=0.625;
          }

    //Increases the speed of the steps//
    speed_selector_divider+=1;
    
    if (speed_selector_divider>2) // defines number of the steps that change at the same speed
        {
          if (speed_selector<=100) //defines maximum speed of step counter. The higher the number, the higher the speed is
          {
            speed_selector+=1;
          }

          if (speed_selector%3==0 && distance_increment<500)
          {
            distance_increment*=2;
          }
          speed_selector_divider=1;
        }
  
    read_controller(); //reads the controller in order to remain in the loop or exit
   
    //Enter configuration routine or manual, or reset mode


   
     if  (spd_up==HIGH && spd_down==HIGH && operational_mode==0) //Changes to routine configuration mode
     {
     
      lcd.clear();
      DistanceToMove_nano=old_step_value;
      Number_steps=1;
      Time_step=1;
      Print_Menu_Routine_Configuration(HIGH,HIGH,HIGH);   
      operational_mode=1;
      delay(1000);
     }

    
      //Goes back from configuration menu to manual mode
      if(operational_mode==1 && back_menu==HIGH)
      {
    
      lcd.clear(); 
      print_menu(DistanceToMove_nano, mapX_relative_center, mapY_relative_center, mapZ_relative_center);
      operational_mode=0;
      delay(1000);
      }

      //Starts a routine mode 
      if(operational_mode==1 && start_routine==HIGH)
      {
      lcd.clear();
      operational_mode=2;

      }

     
    }//end while

     //Resets the speed when no button is pressed//
     speed_selector=1;
     speed_selector_divider=0;
     old_step_value=DistanceToMove_nano;
     //digitalWrite(led,LOW);
     //**Resets the speed when no button is pressed**//
}


//Controls an axis by user input
void Move_Axis_With_Buttons(const int button_up_ID,const int button_down_ID, float distance_to_move_axis, const int Motor_ID, const int pin_direction_axis, const int Enable_Pin_Axis) //speed is given in Nanometers
{

   boolean button_up=LOW;
   boolean button_down=LOW;

   int speed_selector_divider=1;
   int speed_selector=1;
   int axis_position=0;
   boolean delay_activated=HIGH;
   
   button_up=  not digitalRead(button_up_ID);//RESUME
   button_down= not digitalRead(button_down_ID); //RESUME

 
   speed_selector=1;
   delay_activated=HIGH;
   
   while (button_up==HIGH || button_down==HIGH) //RESUME
   {
  //   digitalWrite(Enable_Pin_Axis,LOW); //Low in this case means enabled
     //increases the steps//
     if  (button_up==HIGH && button_down==LOW) 
        {           

         StepF(distance_to_move_axis, Motor_ID, pin_direction_axis,HIGH);
         if (delay_activated) {delay(500/speed_selector);}
        }
        
      //Decreases steps  
      else if  (button_up==LOW && button_down==HIGH) 
        {  
         StepB(distance_to_move_axis, Motor_ID, pin_direction_axis);

         if (delay_activated) {delay(500/speed_selector);}
        }
      
     //Increases the speed of the steps//
    speed_selector_divider+=1;
    
    if (speed_selector_divider>2) // defines number of the steps that change at the same speed
        {
          if (speed_selector<=10) //defines maximum speed of step counter. The higher the number, the higher the speed is
          {
            speed_selector+=1;
          }
          else
          {
            speed_selector+=1;
            delay_activated=LOW;
          }
          speed_selector_divider=1;
        }
        
    //Reads inputs again to exit the while if buttons are not pressed
    button_up= not digitalRead(button_up_ID);
    button_down= not digitalRead(button_down_ID); 
    
    //digitalWrite(Enable_Pin_Axis,HIGH); //High means in this case disabled
    }//end while
   
     //Resets the speed when no button is pressed//
     speed_selector=1;
     speed_selector_divider=0;
     //digitalWrite(led,LOW);
     //**Resets the speed when no button is pressed**//
}

//retrieves the PIN_ID given an axix name
int detect_enable_pin_ID(const int axis_name)
{


 if (axis_name==7){return Enable_X_pin;}
 else if(axis_name==5){return Enable_Y_pin;}
 else if(axis_name==4){return Enable_Z_pin;}

}

//step forwards for a selected axis
void StepF(float distanceToMove,const int Axs_Name, const int pin_direction_ID_axis, boolean Menu_update)
{
  
   float stepper_pos;
   float absolute_pos;
   float top_limit;
   boolean limit_not_reached;

   top_limit=check_top_limit_axis(Axs_Name);


   digitalWrite(detect_enable_pin_ID(Axs_Name),LOW); //High means in this case disabled
   
   digitalWrite(pin_direction_ID_axis,HIGH);
  

   for(stepper_pos = 0; stepper_pos < distanceToMove; stepper_pos = stepper_pos+ 0.625) 
   {
    absolute_pos=set_check_relative_position(Axs_Name,0,LOW); 

      if (absolute_pos<top_limit)
      {
        set_check_relative_position(Axs_Name,0.625,HIGH); 
        digitalWrite(Axs_Name,HIGH);
        delayMicroseconds(300);
        digitalWrite(Axs_Name,LOW);
        delayMicroseconds(100);
      }
      else
      {
        break;
      }
 
   }

   digitalWrite(detect_enable_pin_ID(Axs_Name),HIGH); //High means in this case disabled
   
   if (Menu_update==HIGH){
   print_menu(distanceToMove, mapX_relative_center, mapY_relative_center, mapZ_relative_center);
   }
}

//Step backwards for a selected axis
void StepB(float distanceToMove,int Axs_Name,const int pin_direction_ID_axis)
{

   float stepper_pos;
   float absolute_pos;
 

   digitalWrite(pin_direction_ID_axis,LOW);
   digitalWrite(detect_enable_pin_ID(Axs_Name),LOW); //High means in this case disabled

   for(stepper_pos = 0; stepper_pos < distanceToMove; stepper_pos = stepper_pos+ 0.625) 
   {
    absolute_pos=set_check_relative_position(Axs_Name,0, LOW); //checks values
    if(absolute_pos>0 && CheckAxleEnabled(Axs_Name)==HIGH)
    {
    set_check_relative_position(Axs_Name,-0.625, HIGH); 
    digitalWrite(Axs_Name,HIGH);
    delayMicroseconds(300);
    digitalWrite(Axs_Name,LOW);
    delayMicroseconds(300);
    }
    else {break;}
    
   }
   digitalWrite(detect_enable_pin_ID(Axs_Name),HIGH); //High means in this case disabled
   
   print_menu(distanceToMove, mapX_relative_center, mapY_relative_center, mapZ_relative_center);
}

void print_menu(float distpas, float x_Position, float y_Position, float z_Position)
{
 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Dx: ");
  lcd.print(x_Position);
  lcd.print("     ");
  
  lcd.setCursor(0,1);
  lcd.print("Dy: ");
  lcd.print(y_Position);
  lcd.print("     ");
  
  lcd.setCursor(0,2);
  lcd.print("Dz: ");
  lcd.print(z_Position);
  lcd.print("     ");

  lcd.setCursor(0,3);
  lcd.print("Steps:");
  lcd.print(distpas);
  lcd.print("um    ");

}

//sets/checks the global values of the position of the three axis
//when set_check=HIGH the absolute position will be set and the value of the set value will be returned
//when the set_check=LOW the function will return the absolute position of the selected axis without updating the value
float set_check_relative_position(const int Actual_axis, float step_delta, boolean set_check) 
{

if(Actual_axis==stepPin_X)
{
  if (set_check==HIGH){
  mapX_absolute+=step_delta;
  mapX_relative_center+=step_delta;
  
  }
   return mapX_absolute;
}

 if(Actual_axis==stepPin_Y)
{
  
  if (set_check==HIGH){
  mapY_absolute+=step_delta;
  mapY_relative_center+=step_delta;
  }
  return mapY_absolute;
}

if(Actual_axis==stepPin_Z)
{
  
  if (set_check==HIGH){
  mapZ_absolute=mapZ_absolute+step_delta;
  mapZ_relative_center+=step_delta;
  }
  return mapZ_absolute;
}

}


//Read Inputs from the Controller
void read_controller()
{
     
    spd_up=  not digitalRead(Speed_up);//RESUME
    spd_down= not digitalRead(Speed_down); //RESUME
    x_up=  not digitalRead(Button_X_Pos);
    x_down=  not digitalRead(Button_X_Neg);
    z_up=  not digitalRead(Button_Z_Pos);
    z_down=  not digitalRead(Button_Z_Neg);
    back_menu=  not digitalRead(Button_Y_Neg);
    start_routine = not digitalRead(Button_Y_Pos);

}

//Moves the machine without delays 
void Move_Axis_With_Buttons_Free_Run(const int button_up_ID,const int button_down_ID, const int Motor_ID, const int pin_direction_axis, const int Enable_Pin_Axis) //speed is given in Nanometers
{

   boolean button_up=LOW;
   boolean button_down=LOW;

   int speed_selector_divider=1;
   int speed_selector=1;

   button_up=  not digitalRead(button_up_ID);//RESUME
   button_down= not digitalRead(button_down_ID); //RESUME

   speed_selector=1;
     
   while (button_up==HIGH || button_down==HIGH) //STEP FORWARD
   {
     digitalWrite(Enable_Pin_Axis,LOW); //Low in this case means enabled
     //increases the steps//
     if  (button_up==HIGH && button_down==LOW) 
        {           
            set_check_relative_position(Motor_ID,0.625,HIGH); 
            digitalWrite(pin_direction_axis,HIGH);
            digitalWrite(Motor_ID,HIGH);
            delayMicroseconds(30);
            digitalWrite(Motor_ID,LOW);
            delayMicroseconds(30);
 
        }
        
      //Decreases steps  
      else if  (button_up==LOW && button_down==HIGH) 
        {  
            set_check_relative_position(Motor_ID,-0.625,HIGH);          
            digitalWrite(pin_direction_axis,LOW);
            digitalWrite(Motor_ID,HIGH);
            delayMicroseconds(30);
            digitalWrite(Motor_ID,LOW);
            delayMicroseconds(30);
        }
  
  
    button_up= not digitalRead(button_up_ID);
    button_down= not digitalRead(button_down_ID); 
    
    digitalWrite(Enable_Pin_Axis,HIGH); //High means in this case disabled
    }//end while
   
  
}
