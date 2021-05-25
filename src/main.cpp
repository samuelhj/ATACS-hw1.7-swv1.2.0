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
#include "Warningcheck.cpp" // 
#include "readPressure.cpp"
#include "adjustPressure.cpp"
#include "timerSelector.cpp"
#include "updateValues.cpp"
#include "backlight.cpp"
#include "draw.cpp"
#include "solenoids.cpp"
#include "tirePaint.cpp"
#include "toggleMenu.cpp"
#include "bootMessage.cpp"
#include "menu.cpp"

// Við skrifum vistuð gildi í EEPROM
void writeSelectedPressure()
{
  //EEPRON.put(ESERIALNUMBER,SERIALNUMBER); // Skrifum inn serial númer
  EEPROM.put(EPRESSURE,selectedPressure); //valinn þrýstingur
  EEPROM.put(EPRESSURE_LRT,selectedPressure_LRT); // Valinn þrýstingur per dekk
  EEPROM.put(EPRESSURE_LFT,selectedPressure_LFT);
  EEPROM.put(EPRESSURE_RFT,selectedPressure_RFT);
  EEPROM.put(EPRESSURE_RRT,selectedPressure_RRT);
}



void setup()
{ 

// Skilgreinum eftirfarandi sem útganga
  pinMode(AIR_IN, OUTPUT);
  pinMode(TIRE_RR, OUTPUT);
  pinMode(TIRE_RF, OUTPUT);
  pinMode(TIRE_LF, OUTPUT);
  pinMode(TIRE_LR, OUTPUT);
  pinMode(AIR_OUT, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT); // Baklýsing PWM
  pinMode(RESET,OUTPUT); // Reset á skjá
  air_base_close();

// Næst koma skilgreiningar fyrir TFT skjá
  //delay(5000); // Gefum þéttum og öðru tíma til að hlaðast upp svo skjárinn komi rétt upp.
  digitalWrite(RESET,LOW); // Endurræsing á skjá.
  //delay(10); // töf
  digitalWrite(RESET,HIGH); // Ræsum skjá
  delay(100); // Töf
  tft.begin(); // Virkjum skjáinn
  tft.fillScreen(ILI9341_BLACK); // Hreinsum skjáinn og skrifum svartan bakgrunn.
  tft.setRotation(1); // Við stillum skjá í landscape ham.

  // Hér lesum við úr minni eldri stillingar
  backlight_selected = EEPROM.read(EBACKLIGHT);
  EEPROM.get(EPRESSURE,selectedPressure); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_LRT,selectedPressure_LRT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_LFT,selectedPressure_LFT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_RFT,selectedPressure_RFT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_RRT,selectedPressure_RRT); // Lesum þrýsting úr minni

  // Boot skilaboð
  bootMessage();

  warningCheck(); // teiknum dekk rauð fyrir mælingu
  read_LRT(); // Lesum vinstra afturdekk
  read_LFT(); // Lesum vinstra framdekk
  read_RFT(); // Lesum hægra framdekk
  read_RRT(); // Lesum hægra afturdekki
  tft.fillScreen(BLACK); // Hreinsum skjá.
  tft.setTextColor(WHITE); // Breytum textanum yfir í hvítt
  drawMain(); // Teiknum grunn útlit.
}//Void Setup lokar

//Aðalfall

void loop()
{
  //timerSelector(); // Ákveðum lengd á tímanum sem þarf að dæla í

    //millis() = millis(); // Tími fyrir teljara 0
    //unsigned long millis1 = millis(); // Tími fyrir teljara 1
    //unsigned long millis()2 = millis(); // Tími fyrir teljara 2
    /* Það þarf að endursmíða alla teljara
    * Tillaga:
    * Timer
    * 
    */
    backlightAdjust(backlight_selected); // Við kveikjum á skjá.

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

    // Hér erum við í aðalvalmynd.

    // Ef ýtt er á lækka þrýsting örina.
    if(menuval == 0 && (x > 10) && (x<100)) // Athugum staðsetningu á x ásnum
    {
      if((y>50) && y< 150) // Athugum staðsetningu á y ásnum.
      {
        adjust = false; // Við hættum að stilla
        if((selectedPressure < 6) && (selectedPressure > 0)) // Ef þrýstingur er undir 6 psi en yfir 0psi
        {
          selectedPressure = selectedPressure - 0.25; // Þá lækkum við um 0.25 psi
          selectedPressure_LRT = selectedPressure_LRT - 0.25;
          selectedPressure_LFT = selectedPressure_LFT - 0.25;
          selectedPressure_RFT = selectedPressure_RFT - 0.25;
          selectedPressure_RRT = selectedPressure_RRT - 0.25;
          
          delay(100); // töf til að koma í veg fyrir að hoppa of hratt á milli stiga.

        }
        if(selectedPressure >= 6) // ef þrýstingur er yfir 6
        {
          selectedPressure = selectedPressure - 1.0; // Lækkum við um 1psi í einu.
          selectedPressure_LRT = selectedPressure_LRT - 1.0;
          selectedPressure_LFT = selectedPressure_LFT - 1.0;
          selectedPressure_RFT = selectedPressure_RFT - 1.0;
          selectedPressure_RRT = selectedPressure_RRT - 1.0;
          
          delay(500); // Töf til að koma í veg fyrir að hoppa of hratt milli stiga.
        }
        adjust = true; // byrjum aftur að stilla
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
        if(selectedPressure >= 6) // sé þrýstingur yfir 6psi hækkum við um 1psi í skrefi
        {
          selectedPressure = selectedPressure + 1.0; // Við hækkum gildið um 1psi
          selectedPressure_LRT = selectedPressure_LRT + 1.0;
          selectedPressure_LFT = selectedPressure_LFT + 1.0;
          selectedPressure_RFT = selectedPressure_RFT + 1.0;
          selectedPressure_RRT = selectedPressure_RRT + 1.0;
          delay(500); // Hinkrum í smá stund svo hann hækki sig ekki upp of hratt
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

            delay(500); // töf svo við hækkum ekki of hratt upp
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
        tiretoken = 0;
        adjust = true; // förum aftur að stilla
        toggleMenu();
        updateValues(); // Uppfærum gildi á skjá.

      }

    } // + pressure ends



      // Er kominn tími til að mæla dekk? 10 mín ef við erum ekki í stillingu/vöktun
      // Tökum út adjust == false til prufu.
      // Prófum að athuga hvort við erum yfir 20 psi.
        if(menuval == 0 && tiretoken == 0 && selectedPressure < 20) // Ef við erum ekki í menu og erum ekki að stilla ákveðið dekk
        {

          if((millis() - previousMillis1) > interval1) // Athugum hve langt er liðið frá síðustu uppfærslu gilda
          {
            read_LRT(); // Lesum vinstra afturdekk
            updateValues(); // uppfærum gildi
            read_LFT(); // Lesum vinstra framdekk
            updateValues(); // uppfærum gildi
            read_RFT(); // Lesum hægra framdekk
            updateValues(); // Uppfærum gildi
            read_RRT(); // Lesum hægra afturdekk
            updateValues(); // Lesum gildi.
            //warningCheck(); // Athugum hvort eitthvað dekk sé í veseni.
            previousMillis1 = millis(); // Endurstillum teljara
          }
        }//Lokum athugunarfalli


        if(manual == false) // Ef við erum ekki með kerfið stillt á manual.
        {
          // Ef við erum ekki í menu og erum að vakta dekkin, en ekki að stilla stakt dekk

          if(menuval == 0 && adjust == true && tiretoken == 0)
          {
            uint16_t test_LRT = pressure_LRT*100;
            uint16_t test_LFT = pressure_LFT*100;
            uint16_t test_RFT = pressure_RFT*100;
            uint16_t test_RRT = pressure_RRT*100;
            // Reynist summa allra vera hærri en valins þrýstings.
            if(((test_LRT + test_LFT) - (test_RFT + test_RRT) <= 100))
            {
              // Þá leiðréttum við öll dekk í einu
              tiretoken = 5; // Setjum okkur aftur í að stilla öll dekk
            }
          }
          // Ef við erum ekki í menu og viljum stilla Vinstra afturdekk
          if(menuval == 0 && adjust == true && (tiretoken == 0 || tiretoken == 1))
          {
            adjustLRT(); // svo stillum við vinstra afturdekk
          }//Stillifall fyrir Vinstra afturdekk lokar

          if(menuval == 0 && adjust == true && (tiretoken == 0 || tiretoken == 2))
          {
            adjustLFT(); // athugum hvort stilla þurfi vinstra framdekk
          }
          // Ef við erum ekki í menu og það þarf að stilla hægra framdekk
          if(menuval == 0 && adjust == true && (tiretoken == 0 || tiretoken == 3))
          {
            adjustRFT();
          }
          // Ef við erum ekki í menu og það þarf að stilla hægra afturdekk
          if(menuval == 0 && adjust == true && (tiretoken == 0 || tiretoken == 4))
          {
            adjustRRT();
          }
          // Ef við erum ekki í menu og það þarf að stilla öll dekk
          if(menuval == 0 && adjust == true && (tiretoken == 0 || tiretoken == 5))
          {
            adjustAllTires();
          }
        }
  }
} // Lokum void loop lykkju
