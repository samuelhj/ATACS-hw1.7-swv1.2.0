/*
  Author: Samúel Þór Hjaltalín Guðjónsson
  samuel@ulfr.net 
  * English below
  Stutt lýsing:
    Forritið stýrir 6rása mosfet útgangsrás, snertiskjá og les einnig frá þrýstinema. 
    Gildin birtir það svo á skjánum.
    Frá skjánum tekur það valin gildi á hvaða þrýstingur á að vera í dekkjum og
    stillir þrýstingin í dekkjunum eftir því. Einnig fylgist það af og til með
    að réttur þrýstingur sé í dekkjum og ef það er ekki til staðar leiðréttir forritið
    þrýstingin í því dekki eða dekkjum sem um ræðir.

    Þetta forrit miðast við 2+4 kistu og með skynjarann á prentplötu
    Líklega er ekki mikið mál að breyta forritinu svo það lesi aðrar
    tegundir af skynjurum. Ef ekki er ætlunin að nota loftút eða auka úrtak frá
    loftkerfi má sleppa AIR_IN loka og tengja þann útgang frá MOSFET stýringu beint
    á segulrofa fyrir loftdælu og spara þannig bæði einn loftloka og aflestunarloka
    fyrir loftdælu.


    Inngangar eru eftirfarandi:
    * Þrýstinemi sem les þrýsting frá kistu.

      Nýtt 2020
      * Auka lykku sem dælir minna í einu
      * lengja tíma á standard dælingu/úrhleypingu
      * stoppa fyrr í þrýstingi í forvali
      * Sýna alltaf þrýsting kistu
      * minni nákvæmni á hærri þrýsting
      * Setja dekk sem lendir reglulega í "warningcheck" á sérstaka gjörgæslu (mæla oftar)

      * Libraries í notkun
      * TouchScreen.h: Lína 12 í TouchScreen.h, bæta við ||defined(__AVR_ATmega1284P__)
      * 

  Brief description of the project.
    The program controls 6 MOSFETs that connect to pneumatic valve base, TFT touchscreen and read 
    from MPX5700DP pressure sensor. The values are reported on the TFT and set values are selected on the TFT.
    The program will try to adjust and keep the tyres in a set range (~0.25psi)

    This program uses a valve base of 2+4 (2 in/out and then valve for each tyre). It can be modified to run some 
    other types of bases and read other types of sensors. If the intention is to use the compressor ONLY for this
    system the AIR_IN solenoid can be skipped, along with any controls for the air compressor and just use AIR_IN
    MOSFET to control a relay for the air compressor.

  INPUTS:
  * pressure sensor

  NEW 2020:
  * better handling of adjusting pressure when closer to set value
  * longer time for inflation/deflation when the value is far away from set value
  * Always show pressure in valve base
  * Less accuraccy on higher pressure (0.5psi does not really matter at higher pressure)
  * Tyre flagged in WarningCheck gets measured more often
  * 
  
  Libraries used and quirks:

  * TouchScreen.h: line 12 needs to be modified, add ||defined(__AVR_ATmega1284P__)

*/

#include <Arduino.h> 
#include <SPI.h> // For SPI to TFT
#include <EEPROM.h> // For nonvolatile memory
#include <Wire.h>
//  For Touchscreen
#include <TouchScreen.h> // For TFT Touchscreen
#include <Adafruit_GFX.h> // For drawing on screen
#include <Adafruit_ILI9341.h> // For ILI9341 on screen

// Project specific includes
#include "cfg/config.h"  // include  for variables, defines, etc
#include "cfg/tft.h" // include for TFT 
// Include for Menu
#include "menu.cpp"
#include "backlight.cpp"
#include "settings.cpp"

#include "Warningcheck.cpp" // 
#include "readPressure.cpp"
#include "adjustPressure.cpp"
#include "timerSelector.cpp"
#include "updateValues.cpp"
#include "draw.cpp"
#include "solenoids.cpp"
#include "tirePaint.cpp"
#include "toggleMenu.cpp"
#include "bootMessage.cpp"
#include "tireMonitor.cpp"
#include "boot.cpp"
#include "memory.cpp"
//#include <algorithm.h> // not used atm

void setup()
{ 
  boot();
}//Void Setup closes

void loop()
{
  backlightAdjust(backlight_selected); // Turn on backlight
  
  if(manual == false && adjust == true)
  {
    //timerSelector();
    //if(selectedPressure < 20)
      tireMonitor();
  }
  // fetch coordinates
  TSPoint p = ts.getPoint();

  // check whether input is within value
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height()); // min/max touch pressure x axis
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width()); // min/max touch pressure y axis
    int y = tft.height() - p.x; // Y coordinates depend on orientation
    int x = p.y;

    menu();
    settings();


    // Main menu.

    if(manual == true && x > 100 && x < 200) // if we're running manual
    {
      if(y>60 && y < 100)
      {
        air_base_close();
        tirePaint(GREEN,5);
      }
    }

    // Lower pressure arrow
    if(menuval == 0 && (x > 10) && (x<100)) // check where x is
    {
      if((y>50) && y< 150) // check where y is
      {
        delay(150);
        adjust = false; // if we don't want to adjust pressure
        if((selectedPressure < 6) && (selectedPressure > 0)) // If pressure is beneth 6 but above 0
        {
          selectedPressure = selectedPressure - 0.25; // decrement by 0.25 psi
          selectedPressure_LRT = selectedPressure_LRT - 0.25;
          selectedPressure_LFT = selectedPressure_LFT - 0.25;
          selectedPressure_RFT = selectedPressure_RFT - 0.25;
          selectedPressure_RRT = selectedPressure_RRT - 0.25;
        }
        if(selectedPressure >= 6) // IF pressure is above 6 psi 
        {
          selectedPressure = selectedPressure - 1.0; // decrement by 6psi
          selectedPressure_LRT = selectedPressure_LRT - 1.0;
          selectedPressure_LFT = selectedPressure_LFT - 1.0;
          selectedPressure_RFT = selectedPressure_RFT - 1.0;
          selectedPressure_RRT = selectedPressure_RRT - 1.0;
        }

        if(manual == true)
        {
          if(digitalRead(AIR_OUT) == OFF)
          {
            air_base_deflate();
          }
        }

      tiretoken = 0;
      toggleMenu();
      updateValues(); // Update values on screen
      }

    } // - pressure closes


    // increase pressure arrow
    if(menuval == 0 && (x > 250) && (x<320) && (selectedPressure < 35)) // Make sure we aren't over 35 psi
    {
      if((y>50) && y< 150)
      {
        adjust = false;
        delay(150); 
        if(selectedPressure >= 6 && manual == false) // if pressure is above 6 psi we increment by 1 psi 
        {
          selectedPressure = selectedPressure + 1.0; // increment by 1psi
          selectedPressure_LRT = selectedPressure_LRT + 1.0;
          selectedPressure_LFT = selectedPressure_LFT + 1.0;
          selectedPressure_RFT = selectedPressure_RFT + 1.0;
          selectedPressure_RRT = selectedPressure_RRT + 1.0;
        }


        if((selectedPressure < 35 && (selectedPressure < 6))) // If pressure is under 6 psi we increment by 0.25
        {
          if(selectedTire == 0)
          {
            selectedPressure = selectedPressure + 0.25; // Increment by 0.25psi 
            selectedPressure_LRT = selectedPressure_LRT + 0.25;
            selectedPressure_LFT = selectedPressure_LFT + 0.25;
            selectedPressure_RFT = selectedPressure_RFT + 0.25;
            selectedPressure_RRT = selectedPressure_RRT + 0.25;
          }

          if(selectedTire == 1)
          {
            selectedPressure_LRT = selectedPressure_LRT +0.25; // add 0.25 psi
            delay(500);
          }
          if(selectedTire == 2)
          {
            selectedPressure_LFT = selectedPressure_LFT + 0.25;
            delay(500);
          }
          if(selectedTire == 3)
          {
            selectedPressure_RFT = selectedPressure_RFT + 0.25;
            delay(500);
          }
          if(selectedTire == 4)
          {
            selectedPressure_RRT = selectedPressure_RRT + 0.25;
          }

        }
              
        if(manual == true)
        {
          if(digitalRead(AIR_IN) == OFF)
          {
            air_base_inflate();
          }
        }
        tiretoken = 0;
        toggleMenu();
        updateValues(); 
      }

    } // + pressure ends
  }


  if(manual == false && adjust == true && menuval == 0) 
  {
    
    float a = pressure_LRT;
    float b = pressure_LFT;
    float c = pressure_RFT;
    float d = pressure_RRT;

    float sum = max(max(a, b), max(c, d)) - min((a, b), min(c, d));

    if(tiretoken == 0)
    {
      if(sum > 0.5)
      {
       tiretoken = 1;
      }
    }
    if(sum < 0.5)
      {
        pressure_ALL = pressure_LRT;

        if(selectedPressure - pressure_ALL > 0.25 || pressure_ALL - selectedPressure > 0.25)
        {
          tiretoken = 5;
        }
        else
          tiretoken = 0;
    }

    if(debug == true)
    {
      tft.setTextSize(2);
      tft.setCursor(20,220); // Pick coordinates
      tft.println(sum); // Write out value 
    }



    // IF we're not in main menu and want to adjust left rear tire
    if( tiretoken == 1)
    {
      adjustLRT(); // adjust left rear tyre
    }//LRT closes

    if(tiretoken == 2)
    {
      adjustLFT(); // Left front tyre
    }
    // IF we're not in main menu and want to adjust right front tyre
    if(tiretoken == 3)
    {
      adjustRFT();
    }
    // IF we're not in main menu and want to adjust right rear tyre
    if(tiretoken == 4)
    {
      adjustRRT();
    }
    // If we're not in main menu and want to adjust all tyres
    if(tiretoken == 5)
    {
      adjustAllTires();
    }
  }


} // Lokum void loop lykkju
