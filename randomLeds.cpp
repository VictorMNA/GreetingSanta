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
#include "randomLeds.h"


//==============================================================================
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel ledsStrip;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define FADE_STEP 8

//==============================================================================
randomLeds::randomLeds(int pin, int numberOfLeds, int brightness,/* int maxOn,*/ neoPixelType type):
numberOfLeds(numberOfLeds), brightness(brightness), type(type)
{
  ledsStrip = Adafruit_NeoPixel(numberOfLeds, pin, type);
}

//==============================================================================
void randomLeds::init()
{
  ledsStrip.begin();
  ledsStrip.setBrightness(brightness);
  ledsStrip.show(); // Initialize all pixels to 'off'  
  
  steps = 0;  
  for(int i = 0; i < MAX_LEDS; i++)
  {
    ledsList[i].LedNumber = -1;
  }   
}


//==============================================================================
void randomLeds::allWhite()
{
  for(int i = 0; i < ledsStrip.numPixels(); i++)
  {
    ledsStrip.setPixelColor(i, ledsStrip.Color(255, 255, 255));
  }
  ledsStrip.show();
}

//==============================================================================
void randomLeds::allOff()
{
  for(int i = 0; i < ledsStrip.numPixels(); i++)
  {
    ledsStrip.setPixelColor(i, ledsStrip.Color(0, 0, 0));
  }
  ledsStrip.show();
}

//==============================================================================
void randomLeds::allRandom(void)
{
  uint32_t Color = ledsStrip.Color(random(2)?255:0,random(2)?255:0, random(2)?255:0);
  for(int i = 0; i < ledsStrip.numPixels(); i++)
  {
    ledsStrip.setPixelColor(i, Color);
  }
  ledsStrip.show();
}

//==============================================================================
void randomLeds::step(void)
{
  bool LedUsed;
  int LedCalculated;

  for(int i = 0; i < MAX_LEDS; i++)
  {
    // the light of the leds will be fading to black slowly
    if(ledsList[i].LedNumber != -1)
    {
      if(ledsList[i].R >= FADE_STEP)
      {
        ledsList[i].R -= FADE_STEP;
      }
      else
      {
        ledsList[i].R = 0;
      }
  
      if(ledsList[i].G >= FADE_STEP)
      {
        ledsList[i].G -= FADE_STEP;
      }
      else
      {
        ledsList[i].G = 0;
      }
  
      if(ledsList[i].B >= FADE_STEP)
      {
        ledsList[i].B -= FADE_STEP;
      }
      else
      {
        ledsList[i].B = 0;
      } 
          
      ledsStrip.setPixelColor(ledsList[i].LedNumber, ledsStrip.Color(ledsList[i].R,ledsList[i].G, ledsList[i].B));

      // the led is completly black, so we mark it as unused
      if((ledsList[i].R == 0) && (ledsList[i].G == 0) && (ledsList[i].B == 0))
      {
        ledsList[i].LedNumber = -1;
      }
    }    
  }  
  ledsStrip.show();  

  // to get new lighted leds in lower rhythm
  steps++;
  if (steps >= STEPS)
  {
    steps = 0;
    
    for(int i = 0; i < MAX_LEDS; i++)
    {
      if(ledsList[i].LedNumber == -1)
      {
        do
        {
          LedCalculated = random(numberOfLeds);

          LedUsed = false;
          for(int j = 0; j < MAX_LEDS; j++)
          {
            if(ledsList[j].LedNumber == LedCalculated)
            {
              // to not light an already lighted led
              LedUsed = true;
              break;
            }
          }
                  
        } while (LedUsed);

        ledsList[i].LedNumber = LedCalculated;
        ledsList[i].R = random(2)?250:0;
        ledsList[i].G = random(2)?250:0;
        ledsList[i].B = random(2)?250:0; 
        break;         
      }
    }  
  } 
}

