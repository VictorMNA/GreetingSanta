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
#ifdef __AVR__
  #include <avr/power.h>
#endif


//==============================================================================
#include "randomLeds.h"
#define RANDOM_LEDS_PIN 2
#define RANDOM_LEDS_QTY 8
randomLeds leds = randomLeds(RANDOM_LEDS_PIN, RANDOM_LEDS_QTY);

//==============================================================================
#include "armMove.h"
#define SERVO 9
#define SENSOR  5
armMove armSystem = armMove(SENSOR, SERVO);


//==============================================================================
void setup()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  // to get a "truly" random data, use the seed with a "strange changing value"
  // i.e. an unused (not conected) analog input (will read "noise")
  randomSeed(analogRead(0));

  leds.init();
  armSystem.init();

  // to have visual reference of whem the system is reset
  delay(1000);
  leds.allWhite();
  delay (5000);
  leds.allOff();
  delay(1000);
}

//==============================================================================
void loop()
{
  leds.step();
  armSystem.step();

  // this pause sets the rhythm of the leds
  // and the response of the arm, but for this will be less important
  delay(50);

}

