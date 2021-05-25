/*
*   Til að stilla hvert dekk fyrir sig
*   Þetta þarf sennilega að skrifa frá grunni. 
*
*/
void eachTire()
{
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
    }



} // Each tire fall lokar