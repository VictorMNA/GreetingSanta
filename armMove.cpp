//==============================================================================
//
//  Copyright (C) 2017 Víctor Navarro <victormna.developer@gmail.com>
//
//  This file is part of GreetingSanta.
//
//  GreetingSanta is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  GreetingSanta is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with ChristmasFrame.  If not, see <http://www.gnu.org/licenses/>.
//
//==============================================================================
#include <Arduino.h>

//==============================================================================
#include "armMove.h"


//==============================================================================
#define ANGLE_REST  120
#define ANGLE_UP    30
#define ANGLE_DOWN  90

// to reject noise reads
#define NUM_SAMPLES_EQUALS  3

//==============================================================================
armMove::armMove(int pinSensor, int pinServo):
pinSensor(pinSensor),
pinServo(pinServo)
{
  
}


//==============================================================================
void armMove::init(void)
{
  theServo.attach(pinServo);
  theServo.write(ANGLE_REST);
  pinMode(pinSensor, INPUT);
  samples = 0;
  counter = 0; 
  state = state_WAIT;
}



//==============================================================================
void armMove::step(void)
{
  switch(state)
  {
    case state_REST:
      if(digitalRead(pinSensor))
      {
        samples++;
        if(samples >= NUM_SAMPLES_EQUALS)
        {
          state = state_MOVE_DETECTED;
        }
      }
      else
      {
        samples = 0;
      }      
      break;
  
    case state_MOVE_DETECTED:
      theServo.attach(pinServo);
      counter = 0;
      times = 0;
      state = state_ARM_UP;
      break;
    
    case state_ARM_UP:
      theServo.write(ANGLE_UP);
      counter++;
      if(counter >= 6)
      {
        state = state_ARM_DOWN;
        counter = 0;          
      }    
      break;
      
    case state_ARM_DOWN:
      theServo.write(ANGLE_DOWN);
      counter++;
      if(counter >= 6)
      {
        times++;
        if(times >= 3)
        {
          state = state_WAIT;
          counter = 0;
        }
        else
        {
          state = state_ARM_UP;
          counter = 0;          
        }
      }
      break;
      
    case state_WAIT:
      theServo.write(ANGLE_REST);
      counter++;
      if(counter == 3)
      {
        // sometimes the servo began to vibrate at rest (cheap model),
        // so once in its position I deactivate it.
        theServo.detach();
        pinMode(pinServo, OUTPUT);
        digitalWrite(pinServo, LOW);         
      }

      // to have a deadband time and prevent it from constantly moving if there are people always in front
      if(counter >= 200)
      {
        state = state_REST;
        counter = 0;
      }
      break;
  } 
}


