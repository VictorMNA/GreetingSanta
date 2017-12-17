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
#ifndef ARMMOVE_H
#define ARMMOVE_H

//==============================================================================
#include <Servo.h>


//==============================================================================
typedef enum
{
  state_REST,
  state_MOVE_DETECTED,
  state_ARM_UP,
  state_ARM_DOWN,
  state_WAIT
} type_state;


//==============================================================================
class armMove
{
  public:
    armMove(int pinSensor, int pinServo);

    void init(void);

    void step(void);

  protected:
    int pinSensor;
    int pinServo;
    Servo theServo;
    int samples;
    type_state state;
    uint8_t counter, times;
};


//==============================================================================
#endif

