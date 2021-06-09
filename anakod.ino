// -*- C++ -*-

#include <AccelStepper.h> //accelstepper library

boolean connection = false;

#define START_DELIM "<"
#define END_DELIM ">"
#define AXIS_1_DELIM "1"
#define AXIS_2_DELIM "2"
#define AXIS_3_DELIM "3"
#define AXIS_4_DELIM "4"
#define GRIPPER_DELIM "G"

AccelStepper stepper(AccelStepper::DRIVER, 8, 9); // direction Digital 9 (CCW), pulses Digital 8 (CLK)
AccelStepper stepper2(AccelStepper::DRIVER, 10, 11); // direction Digital 11 (CCW), pulses Digital 10 (Clk)
AccelStepper stepper3(AccelStepper::DRIVER, 12, 13); // direction Dİgital 13, pulses Digtal 12
AccelStepper stepper4(AccelStepper::DRIVER, 14, 15) ; // direction Dİgital 15, pulses Digtal 14
  
void setup()
{
  String test = "G";
  if(!test == GRIPPER_DELIM)
    {
#error "String eslestirme testi hatali!"
    }
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
  switch(str.substring(0,1))
    {
    case(AXIS_1_DELIM)
      set_axis(str.substring(2).toInt(), axis_type::axis_1);
    break;
    case(AXIS_2_DELIM)
      set_axis(str.substring(2).toInt(), axis_type::axis_2);
    break;
    case(AXIS_3_DELIM)
      set_axis(str.substring(2).toInt(), axis_type::axis_3);
    break;
    case(AXIS_4_DELIM)
      set_axis(str.substring(2).toInt(), axis_type::axis_4);
    break;
    }
}

void set_axis(int angle, axis_type axis)
{
  String ax;
  switch(axis)
    {
    case(axis_type::axis_1)
      ax = "Eksen 1";
    break;
    case(axis_type::axis_2)
      ax = "Eksen 2";
    break;
    case(axis_type::axis_3)
      ax = "Eksen 3";
    break;
    case(axis_type::axis_4)
      ax = "Eksen 4";
    break;
    }
  String angles(angle);
  Serial.println("Eksen = " + ax);
  Serial.println("Aci = " + angles);
}

enum class axis_type
  {
    axis_1,
    axis_2,
    axis_3,
    axis_4
  }
