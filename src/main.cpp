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


    Útgangar eru eftirfarandi:
    * 6 til að stýra loftlokum með MOSFET stýringu (Gefur jörð)
    * RS232 útgangur fyrir t.d. RS232 skjá eða samskipti við hvað annað sem mönnum
      gæti dottið í hug að bæta við seinna meir.
    * 15 pinna tengi fyrir SPI skjá.

      TODO OG ÖNNUR VANDAMÁL
      * x PWM fyrir backlight virkar ekki
      * x Klára tímasetningar fyrir loft í og úr dekkjunum
      * x Viðvörunarhluti
      * x úrhleypingar hluti
      * x Inndælingarhluti
      * x Baklýsing í menu
      * x Truflanir af völdum PWM vegna baklýsingar
      * x Virkja inndælingu/úrhleypingu dekkja úr menui
      * x EEPROM lestur og skrif fyrir stillingar.
      * x Viðvörunarhluti virkar ekki lengur! >:(
      * x Bæta tíma við inndælingu/úrhleypingu
      * þrepaskiptingu milli inndælingu/úrhleypingu m.v. þrýsting
      * adjust lúppa sem lærir á tímann sem tekur að dæla í dekk og hleypa úr
      * Valmöguleika til að stilla hvert dekk sér.
      * x Mæling dekkja í stillingu virkar ekki

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
#include <TouchScreen.h> // Við þurfum library til að lesa snertingu af skjá.
#include <Adafruit_GFX.h> // Við þurfum library til að teikna á skjá.
#include <Adafruit_ILI9341.h> // Við þurfum library til að tala við ILI9341 stýringu á skjá.

// Project specific includes
#include "cfg/config.h"  // include  for variables, defines, etc
#include "cfg/tft.h" // include for TFT 
#include "Warningcheck.h" // 
#include "readPressure.h"
#include "adjustPressure.h"
#include "timerSelector.h"
#include "updateValues.h"
#include "backlight.h"
#include "draw.h"
#include "solenoids.h"
#include "tirePaint.h"
#include "toggleMenu.h"

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
  delay(500); //Gefum skjá tækifæri á að ræsa sig.
  backlightAdjust(255); // Kveikjum á baklýsingu.
  tft.setTextSize(2); // Stærð eitt fyrir texta í booti
  tft.setTextColor(GREEN); // Grænn texti fyrir smá nostalgíu
  //tft.print("Bunadur nr: ");
  //tft.println(SERIALNUMBER);
  tft.print("ATACS Version: "); // Útgáfa
  tft.println(VERSION); // Utgáfa
  tft.println(BUILDDATE); //Dagsetning útgáfu
  tft.println("Hofundur:");
  tft.println("Samuel Hjaltalin");
  tft.println("https://ulfraf.space");
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
  timerSelector(); // Ákveðum lengd á tímanum sem þarf að dæla í

    //millis() = millis(); // Tími fyrir teljara 0
    //unsigned long millis1 = millis(); // Tími fyrir teljara 1
    //unsigned long millis()2 = millis(); // Tími fyrir teljara 2
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
          
          delay(500); // töf til að koma í veg fyrir að hoppa of hratt á milli stiga.

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

    }
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

    }
  // Hér lýkur aðalvalmynd.
  //Ef við veljum LRT
    if((menuval == 0) && (x>20) && (x<100))
    {
      if((y>180)&&(y<240))
      {
        if(selectedTire != 1) // Ef dekk LRT er ekki valið.
        {
          tft.fillRect(0,180,50,40, BLACK); // Hreinsum gildið fyrir LRT
          selectedTire = 1; // Þá veljum við það.
          selectedPressure_LRT = 20; // Test!
          updateValues(); // uppfærum gildi
        }
      }
    }

    if((menuval == 0) && (x>20) && (x<100))
    {
      if((y>20)&&(y<60))
      {
        selectedTire = 2; // Veljum LFT
        updateValues(); // uppfærum gildi
      }

    // Menu hluti byrjar.
    }
      if(menuval == 0  && (x >MENU_X) && (x<(MENU_X+MENU_W))) // Ef ýtt er á x hnit Menu
      {
        if((y>MENU_Y) && (y <= (MENU_Y + MENU_H))) // ef ýtt er á Y hnit menu
        {

          /* Valmöguleikarnir eru:
        * Stilla - Fer í auto ham
        * 2 Forval - Opnar valmynd fyrir fyrirfram ákveðin gildi
        * 3 Stilla dekk - Opnar valmynd til að stilla hvert dekk fyrir sig.
        * 4 Mæla - Mælir öll dekk.
        * 5 Stillingar - Baklýsing, og fleira
        *   Til baka
        */
        drawMenu(); // Teiknum Menu útlit

        menuval = 1; // Þá er menuval 1 sem heldur okkur í Menu valglugganum
        x = 0; // Hreinsum X ásinn svo við hoppum ekki beint í annað
        y = 0; // Hreinsum Y ásinn svo við hoppum ekki beint í annað
        //delay(500); // 500ms töf svo við hoppum ekki beint í annað
      }

    } // Lokum Menu lykkju

      // Ef valið er að stilla dekk
      if(menuval == 1  &&  (x > MENU_X) && (x < MENU_X+MENU_W))
      {
        if(menuval == 1 && (y>0) && (y<40)) // Ef ýtt er á stilla
        {
          if(adjust == true) // Ef við erum nú þegar að stilla þá hættum við
          {
            adjust = false; // Breytum gildi
            tiretoken = 0; // Ekkert dekk heldur tokeni
            menuval = 0;
            air_base_close(); // Gætum þess að kistan sé lokuð
          }
          else
          {
            adjust = true; // Setjum adjust gildið í true svo forritið byrji að stilla
            writeSelectedPressure(); // Skrifum valinn þrýsting í EEPROM.
            tiretoken = 0; // ekkert dekk heldur tokeni
            menuval = 0; // og við förum úr valmynd.
            delay(50); // Töf
          }
          drawMain(); // Teiknum aðalvalmynd
          x = 0; // Hreinsum X ásinn svo við hoppum ekki beint í annað
          y = 0; // Hreinsum Y ásinn svo við hoppum ekki beint í annað
        } // Lokum stilla lykkju
      }
      //Forval
      if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
      {
        if((y>40) && (y < 80)) // Ef Y ásinn fellur á Forval
        {
          //delay(500); // Hinkrum í 500ms til að skynja snertingu.
          menuval = 2; // Tveir er fyrir forval
          drawForval(); // Teiknum forvals valmynd
          delay(500);//  smá töf
          x = 0; // Núllstillum X ás
          y = 0; // Núllstillum Y ás
        }
      }
      // Forval
      // Ef ýtt er vinstra megin á skjáinn
      if((menuval == 2)  &&  (x > 20) && (x < 150)) // Ef við erum á takkanum
      {
        if((y>10) && (y<60)) // Ef það er valið 2 PSI forval.
        {
          delay(500); // Smá töf
          selectedPressure = 2.00; // Setjum valinn þrýsting í 4psi
          selectedPressure_LFT = 2.00; //
          selectedPressure_LRT = 2.00;
          selectedPressure_RFT = 2.00;
          selectedPressure_RRT = 2.00;
          adjust = true;
          writeSelectedPressure(); // Skrifum í minni
          tiretoken = 5; // við stillum öll dekk í einu
          menuval = 0; // förum úr menu
          drawMain(); // teiknum aðalvalmynd.
          previousMillis = millis(); // endursetjum teljara
        } // Lokum if setningu
        if(y>80 && y<130) // Ef það er valið 4 PSI forval
        {
          delay(500); // Smá töf
          selectedPressure = 4.00; // setjum valinn þrýsting í 4 psi
          selectedPressure_LRT = 4.00; //
          selectedPressure_LFT = 4.00;
          selectedPressure_RFT = 4.00;
          selectedPressure_RRT = 4.00;

          adjust = true; // Stillum dekk
          writeSelectedPressure(); // Skrifum í minni
          tiretoken = 5; // Stillum öll dekk
          menuval = 0; // förum úr menu
          drawMain(); // Teiknum aðalvalmynd
          previousMillis = millis(); // endursetjum teljara
        } // Lokum if setningu
        if((y>130) && (y<160)) // Ef 8 psi eru valin
        {
          delay(500); // Smá töf
          selectedPressure = 8.00; // Setjum valinn þrýsting á öll dekk í 8psi
          selectedPressure_LRT = 8.00;
          selectedPressure_LFT = 8.00;
          selectedPressure_RFT = 8.00;
          selectedPressure_RRT = 8.00;
          adjust = true;
          writeSelectedPressure(); // Skrifum í minni
          tiretoken = 5; // Stillum öll dekk
          menuval = 0; // Förum úr menu
          drawMain(); // Teiknum aðalvalmynd
          previousMillis = millis(); // endursetjum teljara
        }
      }
      // Ef ýtt er hægra megin á skjáinn (8,12,20,28 PSI)
      if(menuval == 2 && x> 160 && x < 320) // Ef við erum á takkanum
      {
        if(y>20 && y<80) // og við erum á takkanum á y ásnum
        {
          delay(500); // Smá töf
          selectedPressure = 12.00; // Valinn þrýstingur er 8 psi
          selectedPressure_LFT = 12.00; //
          selectedPressure_LRT = 12.00;
          selectedPressure_RFT = 12.00;
          selectedPressure_RRT = 12.00;
          adjust = true; // Stillum dekk
          writeSelectedPressure(); // Skrifum í minni
          tiretoken = 5; // stillum öll dekk í einu
          menuval = 0; // Við förum úr menui
          drawMain(); // Teiknum aðalvalmynd
        }
        if(y>80 && y<130) // og við erum á takkanum á y ásnum
        {
          delay(500); // smá töf
          selectedPressure = 20.00; // Þrýstingur er 28psi
          selectedPressure_LFT = 20; //
          selectedPressure_LRT = 20;
          selectedPressure_RFT = 20;
          selectedPressure_RRT = 20;
          adjust = true; // Stillum dekk
          writeSelectedPressure(); // Skrifum í minni
          tiretoken = 5;
          menuval = 0; // Förum úr menu
          drawMain(); // Teiknum aðalvalmynd
        }
        if(y>130 && y< 160)
        {
          delay(500);
          selectedPressure = 28.00;
          selectedPressure_LRT = 28.00;
          selectedPressure_LFT = 28.00;
          selectedPressure_RFT = 28.00;
          selectedPressure_RRT = 28.00;
          selectedPressure = 28.00;
          adjust = true;
          writeSelectedPressure();
          tiretoken = 5;
          menuval = 0;
          drawMain();
        }
        x = 0; // Núllstillum X ás
        y = 0; // Núllstillum Y ás
      } // Lokum forvals lykkju


      // Til að stilla hvert dekk fyrir sig
      if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
      {
        if((menuval == 1) && (y>80) && (y<120))
        {
          menuval = 3; // Festum okkur í þessari valmynd.
          // Teiknum upp dekkin
          drawTireSelection(); // Teiknum valmynd fyrir dekkjaval

        }
      }
      // Ef við veljum VA
      if((menuval == 3) && (x > 20) && (x < 100))
      {
        if((y > 160) && (y < 240))
        {
          // Tveir þríhyrningar fyrir hækka og lækka takkana.
          menuval = 31;
          tft.fillScreen(BLACK); // Hreinsum skjá
          tft.fillTriangle(120, 60, 170, 20, 220, 60, WHITE); // Teiknum efri þríhryning.
          tft.fillTriangle(120,120,170,160,220,120,WHITE); // Teiknum neðri þríhyrning.
          tft.setCursor(0,80); // Stillum á miðjuna
          tft.setTextSize(2);
          tft.print(" Vinstra Afturdekk: ");
          tft.println(selectedPressure_LRT);
          // Teiknum tilbaka takka
          tft.drawRect(100,5*MENU_H+10,MENU_W+20,MENU_H, WHITE); // Teiknum ramma fyrir tilbaka
          tft.setTextSize(2); // Textastærð í 2
          tft.setCursor(100,5*MENU_H+20); // Stillum hvar við viljum byrja að teikna
          tft.println(" Til baka "); // Prentum texta
          delay(500); // Töf
        }
      }

      // Ef við veljum VF
      if((menuval == 3) && (x > 20) && (x < 100))
      {
        if((y > 10) && (y < 120))
        {
          // Tveir þríhyrningar fyrir hækka og lækka takkana.
          menuval = 32;
          tft.fillScreen(BLACK); // Hreinsum skjá
          tft.fillTriangle(120, 60, 170, 20, 220, 60, WHITE); // Teiknum efri þríhryning.
          tft.fillTriangle(120,120,170,160,220,120,WHITE); // Teiknum neðri þríhyrning.
          tft.setCursor(0,80); // Stillum á miðjuna
          tft.setTextSize(2);
          tft.print(" Vinstra Framdekk: ");
          tft.println(selectedPressure_LFT);
          // Teiknum tilbaka takka
          tft.drawRect(100,5*MENU_H+10,MENU_W+20,MENU_H, WHITE); // Teiknum ramma fyrir tilbaka
          tft.setTextSize(2); // Textastærð í 2
          tft.setCursor(100,5*MENU_H+20); // Stillum hvar við viljum byrja að teikna
          tft.println(" Til baka "); // Prentum texta
          delay(500); // Töf
        }
      }
      // Ef við veljum HF
      if((menuval == 3) && (x > 220) && (x < 320))
      {
        if((y > 10) && (y < 120))
        {
          // Tveir þríhyrningar fyrir hækka og lækka takkana.
  //        tft.fillTriangle(100,110,160,40,200,110,WHITE)
          menuval = 33;
          tft.fillScreen(BLACK); // Hreinsum skjá
          tft.fillTriangle(120, 60, 170, 20, 220, 60, WHITE); // Teiknum efri þríhryning.
          tft.fillTriangle(120,120,170,160,220,120,WHITE); // Teiknum neðri þríhyrning.
          tft.setCursor(0,80); // Stillum á miðjuna
          tft.setTextSize(2);
          tft.print(" Haegra Framdekk: ");
          tft.println(selectedPressure_LFT);
          // Teiknum tilbaka takka
          tft.drawRect(100,5*MENU_H+10,MENU_W+20,MENU_H, WHITE); // Teiknum ramma fyrir tilbaka
          tft.setTextSize(2); // Textastærð í 2
          tft.setCursor(100,5*MENU_H+20); // Stillum hvar við viljum byrja að teikna
          tft.println(" Til baka "); // Prentum texta
          delay(500); // Töf
        }
      }
      // Ef við veljum hægra afturdekk
      if((menuval == 3) && (x > 220) && (x < 320))
      {
        if((y > 180) && (y < 220))
        {
          // Tveir þríhyrningar fyrir hækka og lækka takkana.
          tft.fillScreen(BLACK); // Hreinsum skjá
          menuval = 34; // Við erum í undirmenu af 3
          tft.fillTriangle(120, 60, 170, 20, 220, 60, WHITE); // Teiknum efri þríhryning.
          tft.fillTriangle(120,120,170,160,220,120,WHITE); // Teiknum neðri þríhyrning.
          tft.setCursor(0,80); // Stillum á miðjuna
          tft.setTextSize(2);
          tft.print("  Haegra Afturdekk: ");
          tft.println(selectedPressure_LFT);
          // Teiknum tilbaka takka
          tft.drawRect(100,5*MENU_H+10,MENU_W+20,MENU_H, WHITE); // Teiknum ramma fyrir tilbaka
          tft.setTextSize(2); // Textastærð í 2
          tft.setCursor(100,5*MENU_H+20); // Stillum hvar við viljum byrja að teikna
          tft.println(" Til baka "); // Prentum texta
          delay(500); // Töf
        }
      }

      // Hérna lesum við input fyrir handvirkar stillingar.
      // Vinstra afturdekk
      if((menuval == 31) && (x > 20) && (x < 100))
      {
        if((y > 140) && (y < 160))
        {
          //drawMain();
        }
        if((y>160) && (y<240))
        {

        }
      }

      // Vinstra framdekk
      if((menuval == 32) && (x > 20) && (x < 100))
      {
        if((y > 40) && (y < 80))
        {
          //drawMain();
        }
        if((y>160) && (y<240))
        {

        }
      }
  /*
      // Hægra framdekk
      if((menuval == 33) && (x > 20) && (x < 100))
      {
        if((y > 40) && (y < 80))
        {
          drawMain();
        }
        if((y>160) && (y<240))
        {

        }
      }

      // Hægra afturdekk
      if((menuval == 34) && (x > 20) && (x < 100))
      {
        if((y > 40) && (y < 80))
        {
          drawMain();
        }
        if((y>160) && (y<240))
        {

        }
      }

  */



  // Til að mæla dekk
      if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
      {
        if((menuval == 1) && (y>120) && (y<160)) // Ef ýtt er á maela
        {
          menuval = 0; // Förum úr menu
          adjust = 0; // Hættum að stilla
          drawMain(); // Teiknum aðalvalmynd
          read_LRT(); // Lesum vinstra afturdekk
          //updateValues(); // Uppfærum gildi
          read_LFT(); // Lesum vinstra framdekk
          //updateValues(); // Uppfærum gildin
          read_RFT(); // lesum hægra framdekk
          //updateValues(); // Uppfærum gildin
          read_RRT(); // Lesum hægra afturdekk
          updateValues(); // Uppfærum gildi
          previousMillis1 = millis(); // Endurstillum teljara svo hann mæli ekki strax aftur

        } // Lokum Mæla  lykkju
      }

  //stillingar
      if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
      {
        if((menuval == 1) && (y>180) && (y<200))
        {
          menuval = 5; // Við förum í stillingar
          //menuval = 4; // Segjum forritinu að við séum með menu baklýsing
          tft.fillScreen(BLACK); // Hreinsum skjá
          // Búum til örvatakka
          // Tveir þríhyrningar fyrir hækka og lækka takkana.
          tft.fillTriangle(INCREMENT_PRESSURE_X0, INCREMENT_PRESSURE_Y0, INCREMENT_PRESSURE_X1, INCREMENT_PRESSURE_Y1, INCREMENT_PRESSURE_X2, INCREMENT_PRESSURE_Y2, WHITE);
          tft.fillTriangle(DECREMENT_PRESSURE_X0, DECREMENT_PRESSURE_Y0, DECREMENT_PRESSURE_X1, DECREMENT_PRESSURE_Y1, DECREMENT_PRESSURE_X2, DECREMENT_PRESSURE_Y2, WHITE);
          // Sýnum núverandi gildið á skjá
          tft.setCursor(145,100); // Staðsetjum hvar við viljum teikna gildið
          tft.setTextSize(3); // Höfum textann í stærð 3
          tft.println(backlight_selected/10); // Skrifum gildið á skjá

          // Búum til tilbaka takka

          //tft.drawRect(100,5*MENU_H+10,MENU_W+20,MENU_H, WHITE); // Teiknum ramma fyrir tilbaka
          tft.setTextSize(2); // Textastærð í 2
          tft.setCursor(100,5*MENU_H+20); // Stillum hvar við viljum byrja að teikna
          tft.println(" Til baka "); // Prentum texta
          delay(500); // Töf
        } // Lokum baklýsingar hluta
      }


          // Ef ýtt er á lækka birtu örina.
          if(menuval == 5 && (x > 10) && (x<100) && (backlight_selected > 5)) // Athugum staðsetningu á x ásnum
          {
            if((y>50) && y< 150) // Athugum staðsetningu á y ásnum.
            {
              backlight_selected = backlight_selected - 25; // Þá lækkum við um 25 gildi
              delay(500); // töf til að koma í veg fyrir að hoppa of hratt á milli stiga.
              backlightAdjust(backlight_selected);
              // Sýnum gildið á skjá
              tft.fillRect(145,100,80,40,BLACK); // Hreinsum eldra gildi
              tft.setCursor(145,100); // Staðsetjum hvar við viljum teikna gildið
              tft.setTextSize(3); // Höfum textann í stærð 3
              tft.println(backlight_selected/10); // Skrifum gildið á skjá
            }
          }
          // Ef ýtt er á Hækka birtu örina.
          if(menuval == 5 && (x > 250) && (x<320) && (backlight_selected < 255)) // Athugum staðsetningu á x ás og hvort þrýstingur sé undir 35psi.
          {
            if((y>50) && y< 150)
            {
              backlight_selected = backlight_selected + 25; // Hækkum um 25 gildi
              delay(500); // Hinkrum í smá stund svo hann hækki sig ekki upp of hratt
              backlightAdjust(backlight_selected); //stillum birtu
              // Sýnum gildið á skjá
              tft.fillRect(145,100,80,40,BLACK); // Hreinsum eldra gildi
              tft.setCursor(145,100); // Staðsetjum hvar við viljum teikna gildið
              tft.setTextSize(3); // Höfum textann í stærð 3
              tft.println(backlight_selected/10); // Skrifum gildið á skjá
            }
        }

    // Til baka úr menu eða úr undir-menu í menu.
    if((menuval > 0) &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 1) && (y>200) && (y<240)) // Fyrir til baka
        {
          menuval = 0; // setjum gildið í 0 og þá skrifar hann hefðbundinn skjá á skjáinn.
          drawMain(); // Sennilega er betra að skrifa bara hefðbundinn skjá á til að losna við töfina.
        //  warningCheck(); // Athugum hvort ekki sé í lagi með dekk
        }
        // Ef við vorum í forvali
        if((menuval == 2) && (y>200) && (y<240))
        {
          drawMenu();
          menuval = 1; // Förum aftur í Menu
          delay(500);
        }
        // Ef við vorum að stilla hvert dekk fyrir sig
        if((menuval == 3) && (y>220) && (y<240))
        {
          drawMenu(); // Teiknum menu
          menuval = 1; // Höldum okkur í menu.
          delay(500);
        }
        if((menuval >30) && (menuval <35) && (y>200) && (y<240))
        {
          drawTireSelection(); // Teiknum valmynd fyrr handvirka stillingu.
          delay(500);
          menuval = 3; //
        }
        // Ef við vorum að stilla baklýsingu
        if((menuval == 5) && (y>200) && (y<240))
        {
            drawMenu(); // Teiknum menu.
            EEPROM.write(EBACKLIGHT,backlight_selected); // Geymum núverandi baklýsingu í EEPROM
            delay(100); // Töf
            menuval = 1;
        }
      }
    }

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



} // Lokum void loop lykkju
