// -*- C++ -*-

#include <AccelStepper.h> //accelstepper library

AccelStepper stepper(AccelStepper::DRIVER, 8, 9); // direction Digital 9 (CCW), pulses Digital 8 (CLK)
AccelStepper stepper2(AccelStepper::DRIVER, 10, 11); // direction Digital 11 (CCW), pulses Digital 10 (Clk)
AccelStepper stepper3(AccelStepper::DRIVER, 12, 13); // direction Dİgital 13, pulses Digtal 12
AccelStepper stepper4(AccelStepper::DRIVER, 14, 15) ; // direction Dİgital 15, pulses Digtal 14
  
//Pins
//x and y axis readings
const byte Analog1_X_pin = A0; 
const byte Analog1_Y_pin = A1; 
const byte Analog2_X_pin = A2; 
const byte Analog2_Y_pin = A3;

//Variables
int Analog1_X = 0;
int Analog1_Y = 0; 
int Analog2_X = 0;
int Analog2_Y = 0;

int Analog1_X_AVG = 0; 
int Analog1_Y_AVG = 0; 
int Analog2_X_AVG = 0;
int Analog2_Y_AVG = 0;

void setup()
{

  //SERIAL
  Serial.begin(9600);
  //----------------------------------------------------------------------------    
  //PINS
  pinMode(Analog1_X_pin, INPUT);
  pinMode(Analog1_Y_pin, INPUT);
  pinMode(Analog2_X_pin, INPUT);
  pinMode(Analog2_Y_pin, INPUT);
  //----------------------------------------------------------------------------  
  InitialValues(); //averaging the values of the 3 analog pins (values from potmeters)
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
  ReadAnalog();  
  stepper.runSpeed(); //step the motor (this will step the motor by 1 step at each loop indefinitely)
  stepper2.runSpeed();
  stepper3.runSpeed();
  stepper4.runSpeed();
}

void ReadAnalog()
{
  //Reading the 3 potentiometers in the joystick: x, y
  Analog1_X = analogRead(Analog1_X_pin);  
  Analog1_Y = analogRead(Analog1_Y_pin);
  Analog2_X = analogRead(Analog2_X_pin);
  Analog2_Y = analogRead(Analog2_Y_pin);  
  
  //if the value is 25 "value away" from the average (midpoint), we allow the update of the speed
  //This is a sort of a filter for the inaccuracy of the reading
  if(abs(Analog1_X-Analog1_X_AVG)>25) 
    {
    stepper.setSpeed(10*(Analog1_X-Analog1_X_AVG));    
    }
  else
    {
    stepper.setSpeed(0);
    }
  //----------------------------------------------------------------------------  
  if(abs(Analog1_Y-Analog1_Y_AVG)>25) 
    {
    stepper2.setSpeed(10*(Analog1_Y-Analog1_Y_AVG));  
    }
  else
     {
    stepper2.setSpeed(0);
     }
  //----------------------------------------------------------------------------
  if(abs(Analog2_X-Analog2_X_AVG)>25) 
    {
      stepper3.setSpeed(10*(Analog2_X-Analog2_X_AVG));    
    }
  else
    {
      stepper3.setSpeed(0);
    }
  //----------------------------------------------------------------------------
  if(abs(Analog2_Y-Analog2_Y_AVG)>25) 
    {
      stepper4.setSpeed(10*(Analog2_Y-Analog2_Y_AVG));    
    }
  else
    {
      stepper4.setSpeed(0);
    }
}

// 

void InitialValues()
{
  //Set the values to zero before averaging
  float temp1X = 0;
  float temp1Y = 0;
  float temp2X = 0;
  float temp2Y = 0;
  
  //----------------------------------------------------------------------------  
  //read the analog 50x, then calculate an average. 
  //they will be the reference values
  for(int i = 0; i<50; i++)
  {
     temp1X += analogRead(Analog1_X_pin);  
     delay(10); //allowing a little time between two readings
     temp1Y += analogRead(Analog1_Y_pin);        
     delay(10);
     temp2X += analogRead(Analog2_X_pin);
     delay(10);
     temp2Y += analogRead(Analog2_Y_pin);
  }
  //----------------------------------------------------------------------------  
  Analog1_X_AVG = temp1X/50; 
  Analog1_Y_AVG = temp1Y/50;
  Analog2_X_AVG = temp2X/50;
  Analog2_Y_AVG = temp2Y/50;
  //----------------------------------------------------------------------------  
  Serial.print("AVG1_X: ");
  Serial.println(Analog1_X_AVG);
  Serial.print("AVG1_Y: ");
  Serial.println(Analog1_Y_AVG);
  Serial.print("AVG2_X: ");
  Serial.println(Analog2_X_AVG);
  Serial.print("AVG2_Y: ");
  Serial.println(Analog2_Y_AVG);
  Serial.println("Calibration finished");  
}
