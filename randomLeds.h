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
#ifndef RANDOMLEDS_H
#define RANDOMLEDS_H

//==============================================================================
#include <Adafruit_NeoPixel.h>


//==============================================================================
#define MAX_LEDS  3
#define STEPS 12

typedef struct
{
  int LedNumber;
  uint8_t R, G, B;
} randomLedlsData;

//==============================================================================
class randomLeds
{
  public:
    randomLeds(int pin, int numberOfLeds, int brightness = 255, /* int maxOn = 4,*/ neoPixelType type = NEO_GRB + NEO_KHZ800);

    void init(void);

    void allWhite(void);

    void allOff(void);

    void allRandom(void);

    void step(void);

  protected:
    int numberOfLeds;
    Adafruit_NeoPixel ledsStrip;
    uint8_t brightness;
    neoPixelType type;
    uint8_t steps;
    randomLedlsData ledsList[MAX_LEDS];  
};

//==============================================================================
#endif

