/*
*   Yet to be implemented
*   Should contain:
*   Backlight settings
*   Backlight Auto/manual setting
*   SPI Speed setting
*   date / time
*   Forval / preselection set pressure
*   Debug ON / OFF 
*   Test Solenoids

*
*/

 void settings()
 {

  TSPoint p = ts.getPoint();

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft.height()); // möppum lesið gildi á X ás með min/max þrýstingi á skjá
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft.width()); //möppum lesið gildi á y ás með min/max þrýstingi á skjá
    int y = tft.height() - p.x; // Y hnit eftir því hvernig skjár snýr
    int x = p.y;

    
    // Backlight - Baklýsing
    if(menuval == 5  &&  (x > MENU_X) && (x < MENU_X+MENU_W))
    {
      if(menuval == 5 && (y>0) && (y<40)) 
      {
          drawBacklight();
          menuval = 51;
      } // Lokum stilla lykkju
    }

    // Ef ýtt er á lækka birtu örina.
    if(menuval == 51 && (x > 10) && (x<100) && (backlight_selected > 5)) // Athugum staðsetningu á x ásnum
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
    if(menuval == 51 && (x > 250) && (x<320) && (backlight_selected < 255)) // Athugum staðsetningu á x ás og hvort þrýstingur sé undir 35psi.
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


  // Date - Dagsetning
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 5) && (y>40) && (y<80)) 
        {

        } 
    }

    //Forval val - Preselect select 
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((y>80) && (y < 120)) // Ef Y ásinn fellur á Forval
        {

        }
    } // Lokum forvals lykkju

    // Debug
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if( (y>120) && (y<160))
        {
            if(debug != true)
            {
            debug = true;
            drawMain();
            tft.setCursor(130,60);
            tft.println("debug");
            }
            else
            {
            debug = false;
            drawMain();
            tft.setCursor(130,60);
            tft.println("     ");
            }
        menuval = 0; // Back to main menu
        }
    }

    // Test solenoids - prófum segulloka 
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 5) && (y>160) && (y<200))
        {
            menuval = 0;
            drawMain();
            test();   
        }
    }



// Til baka úr menu eða úr undir-menu í menu.
if((menuval > 0) &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á tilbaka takkanum
{
    if((menuval == 5) && (y>200) && (y<240)) // Fyrir til baka
    {
        menuval = 1; 
        drawMenu(); 
        manual = false; 
    }
    // Ef við vorum að stilla baklýsingu
    if((menuval == 51) && (y>200) && (y<240))
    {
        drawSettings(); // Teiknum menu.
        EEPROM.write(EBACKLIGHT,backlight_selected); // Geymum núverandi baklýsingu í EEPROM
        delay(100); // Töf
        menuval = 5;
        EEPROM.write(EBACKLIGHT,backlight_selected); // Geymum núverandi baklýsingu í EEPROM
    }
    }
}
}// Settings close

