/*
  Höfundur: Samúel Þór Hjaltalín Guðjónsson
  samuel@ulfr.net
  * 
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


*/

#include <Arduino.h> //Við köllum á grunn library fyrir Arduino hlutann
#include <SPI.h> // Við þurfum SPI library fyrir samskipti við snertiskjá.
#include <EEPROM.h> // Við þurfum library til að skrifa og lesa EEPROM.
#include <Wire.h>
//  For Touchscreen // Fyrir snertiskjá
#include <TouchScreen.h> // Við þurfum library til að lesa snertingu af skjá.
#include <Adafruit_GFX.h> // Við þurfum library til að teikna á skjá.
#include <Adafruit_ILI9341.h> // Við þurfum library til að tala við ILI9341 stýringu á skjá.

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
//#include <algorithm.h>

void setup()
{ 
  boot();
}//Void Setup lokar

void loop()
{
  backlightAdjust(backlight_selected); // Við kveikjum á skjá.
  
  if(manual == false && adjust == true)
  {
    //timerSelector();
    //if(selectedPressure < 20)
      tireMonitor();
  }
  // sækjum hnit sem ýtt er á
  TSPoint p = ts.getPoint();

  // Ef þrýst er á skjáinn og er innan min/max marka
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height()); // möppum lesið gildi á X ás með min/max þrýstingi á skjá
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width()); //möppum lesið gildi á y ás með min/max þrýstingi á skjá
    int y = tft.height() - p.x; // Y hnit eftir því hvernig skjár snýr
    int x = p.y;

    menu();
    settings();


    // Hér erum við í aðalvalmynd.

    if(manual == true && x > 100 && x < 200)
    {
      if(y>60 && y < 100)
      {
        air_base_close();
        tirePaint(GREEN,5);
      }
    }

    // Ef ýtt er á lækka þrýsting örina.
    if(menuval == 0 && (x > 10) && (x<100)) // Athugum staðsetningu á x ásnum
    {
      if((y>50) && y< 150) // Athugum staðsetningu á y ásnum.
      {
        delay(150);
        adjust = false; // Við hættum að stilla
        if((selectedPressure < 6) && (selectedPressure > 0)) // Ef þrýstingur er undir 6 psi en yfir 0psi
        {
          selectedPressure = selectedPressure - 0.25; // Þá lækkum við um 0.25 psi
          selectedPressure_LRT = selectedPressure_LRT - 0.25;
          selectedPressure_LFT = selectedPressure_LFT - 0.25;
          selectedPressure_RFT = selectedPressure_RFT - 0.25;
          selectedPressure_RRT = selectedPressure_RRT - 0.25;
        }
        if(selectedPressure >= 6) // ef þrýstingur er yfir 6
        {
          selectedPressure = selectedPressure - 1.0; // Lækkum við um 1psi í einu.
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
      updateValues(); // Uppfærum gildin á skjá.
      }

    } // - pressure closes


    // Ef ýtt er á hækka þrýsting örina.
    if(menuval == 0 && (x > 250) && (x<320) && (selectedPressure < 35)) // Athugum staðsetningu á x ás og hvort þrýstingur sé undir 35psi.
    {
      if((y>50) && y< 150)
      {
        adjust = false;
        delay(150); // töf svo við hækkum ekki of hratt up
        if(selectedPressure >= 6 && manual == false) // sé þrýstingur yfir 6psi hækkum við um 1psi í skrefi
        {
          selectedPressure = selectedPressure + 1.0; // Við hækkum gildið um 1psi
          selectedPressure_LRT = selectedPressure_LRT + 1.0;
          selectedPressure_LFT = selectedPressure_LFT + 1.0;
          selectedPressure_RFT = selectedPressure_RFT + 1.0;
          selectedPressure_RRT = selectedPressure_RRT + 1.0;
        }


        if((selectedPressure < 35 && (selectedPressure < 6))) // Sé þrýstingurinn undir 6psi hækkum við um 0.25psi í hverju skrefi.
        {
          if(selectedTire == 0)
          {
            selectedPressure = selectedPressure + 0.25; // bætum 0,25psi við valið gildi
            selectedPressure_LRT = selectedPressure_LRT + 0.25;
            selectedPressure_LFT = selectedPressure_LFT + 0.25;
            selectedPressure_RFT = selectedPressure_RFT + 0.25;
            selectedPressure_RRT = selectedPressure_RRT + 0.25;
          }

          if(selectedTire == 1)
          {
            selectedPressure_LRT = selectedPressure_LRT +0.25; // Bætum við 0.25psi
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
      tft.setCursor(20,220); // Veljum staðsetningu
      tft.println(sum); // Skrifum út gildið.
    }



    // Ef við erum ekki í menu og viljum stilla Vinstra afturdekk
    if( tiretoken == 1)
    {
      adjustLRT(); // svo stillum við vinstra afturdekk
    }//Stillifall fyrir Vinstra afturdekk lokar

    if(tiretoken == 2)
    {
      adjustLFT(); // athugum hvort stilla þurfi vinstra framdekk
    }
    // Ef við erum ekki í menu og það þarf að stilla hægra framdekk
    if(tiretoken == 3)
    {
      adjustRFT();
    }
    // Ef við erum ekki í menu og það þarf að stilla hægra afturdekk
    if(tiretoken == 4)
    {
      adjustRRT();
    }
    // Ef við erum ekki í menu og það þarf að stilla öll dekk
    if(tiretoken == 5)
    {
      adjustAllTires();
    }
  }


} // Lokum void loop lykkju
