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

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE && menuval == 5)
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
      } // Lokum stilla lykkju
    }



  // Date - Dagsetning
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 5) && (y>120) && (y<160)) 
        {

        } 
    }

    //Forval val - Preselect select 
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((y>40) && (y < 80)) // Ef Y ásinn fellur á Forval
        {

        }
    } // Lokum forvals lykkju

    // Debug
    if((menuval == 5)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 1) && (y>80) && (y<120))
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
            }
        menuval = 0; // Back to main menu
        }
    }

    // Test solenoids - prófum segulloka 
    if((menuval == 1)  &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á takkanum
    {
        if((menuval == 1) && (y>180) && (y<200))
        {
            test();   
        }
    }



// Til baka úr menu eða úr undir-menu í menu.
if((menuval > 0) &&  (x > MENU_X) && (x < MENU_X+MENU_W)) // Ef við erum á tilbaka takkanum
{
    if((menuval == 1) && (y>200) && (y<240)) // Fyrir til baka
    {
        menuval = 0; // setjum gildið í 0 og þá skrifar hann hefðbundinn skjá á skjáinn.
        drawMain(); // Sennilega er betra að skrifa bara hefðbundinn skjá á til að losna við töfina.
        manual = false; 
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

