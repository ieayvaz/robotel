// -*- C++ -*-

#include <AccelStepper.h> //accelstepper library

boolean connection = false;
enum class axis_type
  {
    axis_1,
    axis_2,
    axis_3,
    axis_4,
  };

int axis_1_cm = 0;
int axis_2_angle = 0;
int axis_3_angle = 0;
int axis_4_angle = 0;

const char* START_DELIM = "<";
const char* END_DELIM = ">";
const char* AXIS_1_DELIM = "1";
const char* AXIS_2_DELIM = "2";
const char* AXIS_3_DELIM = "3";
const char* AXIS_4_DELIM = "4";
const char* GRIPPER_DELIM = "G";

#define AXIS_AKT_VAL 5680/360
#define LINEER_AKT 

AccelStepper stepper(AccelStepper::DRIVER, 8, 9); // direction Digital 9 (CCW), pulses Digital 8 (CLK)
AccelStepper stepper2(AccelStepper::DRIVER, 10, 11); // direction Digital 11 (CCW), pulses Digital 10 (Clk)
AccelStepper stepper3(AccelStepper::DRIVER, 12, 13); // direction Dİgital 13, pulses Digtal 12
AccelStepper stepper4(AccelStepper::DRIVER, 14, 15) ; // direction Dİgital 15, pulses Digtal 14
  
void setup()
{
  String test = "G";
  #if !(tes == GRIPPER_DELIM)
  #error "String eslestirme hatali!"
  #endif
  //SERIAL
  Serial.begin(9600);
  //----------------------------------------------------------------------------    
  //Stepper parameters
  //setting up some default values for maximum speed and maximum acceleration
  stepper.setMaxSpeed(10000); //SPEED = Steps / second  
  stepper.setAcceleration(1000); //ACCELERATION = Steps /(second)^2    
  stepper.setSpeed(500);
  delay(500);
  //----------------------------------------------------------------------------
  stepper2.setMaxSpeed(10000); //SPEED = Steps / second  
  stepper2.setAcceleration(1000); //ACCELERATION = Steps /(second)^2    
  stepper2.setSpeed(500);
  delay(500);
  //----------------------------------------------------------------------------
  stepper3.setMaxSpeed(10000); //SPEED = Steps / second  
  stepper3.setAcceleration(1000); //ACCELERATION = Steps /(second)^2    
  stepper3.setSpeed(500);
  delay(500);
  //----------------------------------------------------------------------------
  stepper4.setMaxSpeed(10000); //SPEED = Steps / second  
  stepper4.setAcceleration(1000); //ACCELERATION = Steps /(second)^2    
  stepper4.setSpeed(500);
  delay(500);
}

void loop()
{
  while(!Serial.available())
    {
      String newline = Serial.readStringUntil('\n');
      if(connection)
	{
	  if(newline == END_DELIM)
	    connection = false;
	  else
	    process_input(newline);
	}
      else
	{
	  if(newline == START_DELIM)
	    connection = true;
	}
    }
}

void process_input(const String& str)
{
  String sub = str.substring(0,1);
  if(sub == AXIS_1_DELIM)
  set_axis(str.substring(2).toInt(), axis_type::axis_1);
  else if(sub == AXIS_2_DELIM)
  set_axis(str.substring(2).toInt(), axis_type::axis_2);
  else if(sub == AXIS_3_DELIM)
  set_axis(str.substring(2).toInt(), axis_type::axis_3);
  else if(sub == AXIS_4_DELIM)
  set_axis(str.substring(2).toInt(), axis_type::axis_4);
}

void set_axis(int angle, axis_type axis)
{
  String ax;
  switch(axis)
    {
    case(axis_type::axis_1):
      stepper.moveTo((angle - axis_1_cm) * LINEER_AKT);
      break;
    case(axis_type::axis_2):
      stepper2.moveTo((angle - axis_2_angle) * AXIS_AKT_VAL);
      stepper2.setSpeed(10000); 

      while (stepper2.currentPosition() != stepper2.targetPosition()) { 
	stepper2.runSpeedToPosition();
}
      break;
    case(axis_type::axis_3):
      stepper3.moveTo((angle - axis_3_angle) * AXIS_AKT_VAL);
      stepper3.setSpeed(10000); 
      
      while (stepper3.currentPosition() != stepper3.targetPosition()) { 
	stepper3.runSpeedToPosition();
      }
      break;
    case(axis_type::axis_4):
      stepper4.moveTo((angle - axis_4_angle) * AXIS_AKT_VAL);
      stepper4.setSpeed(10000);
      
      while (stepper4.currentPosition() != stepper4.targetPosition()) {
        stepper4.runSpeedToPosition();
      }   
      break;
    }
 
}
