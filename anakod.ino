// -*- C++ -*-

#include <AccelStepper.h> //accelstepper library

AccelStepper stepper(1, 8, 9); // direction Digital 9 (CCW), pulses Digital 8 (CLK)
AccelStepper stepper2(1, 10, 11); // direction Digital 11 (CCW), pulses Digital 10 (Clk)

//Pins
const byte Analog_X_pin = A0; //x-axis readings
const byte Analog_Y_pin = A1; //y-axis readings

//Variables
int Analog_X = 0; //x-axis value
int Analog_Y = 0; //y-axis value

int Analog_X_AVG = 0; //x-axis value averagen
int Analog_Y_AVG = 0; //y-axis value average

void setup()
{

  //SERIAL
  Serial.begin(9600);
  //----------------------------------------------------------------------------    
  //PINS
  pinMode(Analog_X_pin, INPUT);
  pinMode(Analog_Y_pin, INPUT);  
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

}

void loop()
{
  ReadAnalog();  
  stepper.runSpeed(); //step the motor (this will step the motor by 1 step at each loop indefinitely)
  stepper2.runSpeed();  
}

void ReadAnalog()
{
  //Reading the 3 potentiometers in the joystick: x, y and r.
  Analog_X = analogRead(Analog_X_pin);  
  Analog_Y = analogRead(Analog_Y_pin);
  
  //if the value is 25 "value away" from the average (midpoint), we allow the update of the speed
  //This is a sort of a filter for the inaccuracy of the reading
  if(abs(Analog_X-Analog_X_AVG)>25) 
  {
  stepper.setSpeed(10*(Analog_X-Analog_X_AVG));    
  }
  else
  {
    stepper.setSpeed(0);
  }
  //----------------------------------------------------------------------------  
  if(abs(Analog_Y-Analog_Y_AVG)>25) 
  {
  stepper2.setSpeed(10*(Analog_Y-Analog_Y_AVG));  
  }
   else
  {
    stepper2.setSpeed(0);
  }
  //----------------------------------------------------------------------------
}

// 

void InitialValues()
{
  //Set the values to zero before averaging
  float tempX = 0;
  float tempY = 0;
  //----------------------------------------------------------------------------  
  //read the analog 50x, then calculate an average. 
  //they will be the reference values
  for(int i = 0; i<50; i++)
  {
     tempX += analogRead(Analog_X_pin);  
     delay(10); //allowing a little time between two readings
     tempY += analogRead(Analog_Y_pin);        
     delay(10);
  }
  //----------------------------------------------------------------------------  
  Analog_X_AVG = tempX/50; 
  Analog_Y_AVG = tempY/50;  
  //----------------------------------------------------------------------------  
  Serial.print("AVG_X: ");
  Serial.println(Analog_X_AVG);
  Serial.print("AVG_Y: ");
  Serial.println(Analog_Y_AVG);
  Serial.println("Calibration finished");  
}
