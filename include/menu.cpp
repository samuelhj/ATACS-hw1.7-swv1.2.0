/*  This is the Menu // Þetta er Menu
Valmöguleikarnir eru:
    * 1 Stilla - Fer í auto ham
    * 2 Forval - Opnar valmynd fyrir fyrirfram ákveðin gildi
    * 3 Stilla dekk - Opnar valmynd til að stilla hvert dekk fyrir sig.
    * 4 Mæla - Mælir öll dekk.
    * 5 Stillingar - Baklýsing, og fleira
    *   Til baka
 
*/ 
 void menu()
 {

  TSPoint p = ts.getPoint();

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height()); // möppum lesið gildi á X ás með min/max þrýstingi á skjá
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width()); //möppum lesið gildi á y ás með min/max þrýstingi á skjá
    int y = tft.height() - p.x; // Y hnit eftir því hvernig skjár snýr
    int x = p.y;

    // Menu hluti byrjar.
    if(menuval == 0  && (x >MENU_X) && (x<(MENU_X+MENU_W))) // Ef ýtt er á x hnit Menu
    {
      if((y>MENU_Y) && (y <= (MENU_Y + MENU_H))) // ef ýtt er á Y hnit menu
      {

      drawMenu(); // Teiknum Menu útlit

      menuval = 1; // Þá er menuval 1 sem heldur okkur í Menu valglugganum
      x = 0; // Hreinsum X ásinn svo við hoppum ekki beint í annað
      y = 0; // Hreinsum Y ásinn svo við hoppum ekki beint í annað
      //delay(500); // 500ms töf svo við hoppum ekki beint í annað
      }
    } 

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
          timer_measure = millis(); // Endurstillum teljara svo hann mæli ekki strax aftur

        } // Lokum Mæla  lykkju
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
          delay(250); // Smá töf
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
          delay(250); // Smá töf
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
      // Sennilega væri best að breyta þessu, þessi virkni ætti að vera í aðalvalmynd frekar. TBD
      if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
      {
        if((menuval == 1) && (y>80) && (y<120))
        {
          if(manual != true)
          manual = true;
          else
          {
            manual = false;
          }
          menuval = 0; // Back to main menu
          drawMain();
          //menuval = 3; // Festum okkur í þessari valmynd.
          // Teiknum upp dekkin
         // drawTireSelection(); // Teiknum valmynd fyrir dekkjaval
        
        }
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
              delay(200); // töf til að koma í veg fyrir að hoppa of hratt á milli stiga.
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
              delay(200); // Hinkrum í smá stund svo hann hækki sig ekki upp of hratt
              backlightAdjust(backlight_selected); //stillum birtu
              // Sýnum gildið á skjá
              tft.fillRect(145,100,80,40,BLACK); // Hreinsum eldra gildi
              tft.setCursor(145,100); // Staðsetjum hvar við viljum teikna gildið
              tft.setTextSize(3); // Höfum textann í stærð 3
              tft.println(backlight_selected/10); // Skrifum gildið á skjá
            }
          }



    // Til baka úr menu eða úr undir-menu í menu.
    if((menuval > 0) &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á tilbaka takkanum
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
}// Main menu touch sense closes
