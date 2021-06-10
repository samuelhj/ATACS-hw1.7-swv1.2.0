void drawTireSelection()
{
  tft.fillScreen(BLACK); // Viljum vera viss um að skjárinn sé tómur.
  //tft.drawRect(FRAME_CAR_X, FRAME_CAR_Y-30, FRAME_CAR_W,FRAME_CAR_H, WHITE); // Teiknum kassann utan um bíl.
  tireval = 5; // Við erum í valmynd fyrir dekkjaval

  tft.setTextSize(3); // Textastærð
  tft.setCursor(50,110);
  tft.println(" Veldu dekk");
  tft.drawRect(20,30,80,50,WHITE); // Teiknum vinstra framdekk
  tft.setCursor(25,45);
  tft.println(" VF");
  tft.drawRect(220,30,80,50,WHITE); // Teiknum hægra framdekk
  tft.setCursor(225,45);
  tft.println(" HF");
  tft.drawRect(220,160,80,50,WHITE); // Teiknum hægra afturdekk
  tft.setCursor(225,175);
  tft.println(" HA");
  tft.drawRect(20,160,80,50,WHITE);// Teiknum vinstra afturdekk
  tft.setCursor(25,175);
  tft.println(" VA");
  //Teiknum fram og aftur
  tft.setCursor(120,45);
  tft.drawRect(100,30,120,50,WHITE);
  tft.println("Fram");
  tft.drawRect(100,160,120,50,WHITE); // Teiknum ramma
  tft.setCursor(120,175);
  tft.println("Aftur");

  // Til baka takki.
  tft.setCursor(110,220);
  tft.setTextSize(2);
  tft.println("Til baka");
} // Lokum valmynd 3

void drawMain()
{
    tft.fillScreen(BLACK); // Viljum vera viss um að skjárinn sé tómur.
    menuval = 0; // Slökkvum á menuvali
    tft.drawRect(FRAME_CAR_X, FRAME_CAR_Y, FRAME_CAR_W,FRAME_CAR_H, WHITE); // Teiknum kassann utan um bíl.


    // Tveir þríhyrningar fyrir hækka og lækka takkana.
    tft.fillTriangle(INCREMENT_PRESSURE_X0, INCREMENT_PRESSURE_Y0, INCREMENT_PRESSURE_X1, INCREMENT_PRESSURE_Y1, INCREMENT_PRESSURE_X2, INCREMENT_PRESSURE_Y2, WHITE);
    tft.fillTriangle(DECREMENT_PRESSURE_X0, DECREMENT_PRESSURE_Y0, DECREMENT_PRESSURE_X1, DECREMENT_PRESSURE_Y1, DECREMENT_PRESSURE_X2, DECREMENT_PRESSURE_Y2, WHITE);
    toggleMenu(); // litum Menu kassann grænan eða aflitum hann eftir því sem við á.
    updateValues(); // Uppfærum gildi

    if(adjust == false && tiretoken == 0)
    {
      for(int a=4;a>0;a--)
      {
        tirePaint(GREEN,a);
      }
    }

}// drawMain fall lokar

void drawMenu()
{
  /* Valmöguleikarnir eru:
     * Stilla - Fer í auto ham
     * 2 Forval - Opnar valmynd fyrir fyrirfram ákveðin gildi
     * 3 Stilla dekk - Opnar valmynd til að stilla hvert dekk fyrir sig.
     * 4 Mæla - Mælir öll dekk.
     * 5 Stillingar - Baklýsing, og fleira
     *   Til baka
     */
    tft.fillScreen(BLACK); // Hreinsum skjáinn fyrir Menu
    tft.setTextSize(2); // Stillum á stærð 2
    //Teiknum box fyrir takkana
    tft.drawRect(100,3,MENU_W+20,MENU_H, WHITE); // Teiknum Stilla box
    tft.drawRect(100,MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Forval box
    tft.drawRect(100,2*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Baklysing box
    tft.drawRect(100,3*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Maela box
    tft.drawRect(100,4*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Til baka box
    tft.drawRect(100,5*MENU_H+3,MENU_W+20,MENU_H,WHITE); //

    tft.setTextSize(2);
    tft.setCursor(120,20);
    tft.println(" Stilla");
    tft.setTextSize(2);
    tft.setCursor(100,MENU_H+20);
    tft.println(" Forval");
    tft.setTextSize(2);
    tft.setCursor(100,2*MENU_H+20);
    tft.println(" Handvirkt");
    tft.setTextSize(2);
    tft.setCursor(100,3*MENU_H+20);
    tft.println(" Maela");
    tft.setTextSize(2);
    tft.setCursor(100,4*MENU_H+20);
    tft.println(" Stillingar");
    tft.setTextSize(2);
    tft.setCursor(100,5*MENU_H+20);
    tft.println(" Til baka");
} // Lokum DrawMenu

// Teiknum forvalsvalmynd. 2,4,8,12,20,28 psi eru í boði.
void drawForval()
{
  tft.setTextSize(2); // Stillum á stærð 2
  tft.fillScreen(ILI9341_BLACK); // Hreinsum skjáinn fyrir Forval

  //tft.drawRect(20,MENU_H,MENU_W,MENU_H, WHITE); // Teiknum 2psi ramma
  tft.setCursor(20,30); // Stillum byrjunarreit
  tft.print("  2 PSI"); // Prentum texta

  //tft.drawRect(20,2*MENU_H,MENU_W,MENU_H, WHITE); //  Teiknum 4psi ramma
  tft.setCursor(20,80); // Stillum byrjunarreit
  tft.print("  4 PSI"); //  Prentum texta

  //tft.drawRect(20,3*MENU_H+10,MENU_W,MENU_H,WHITE); // Teiknum 8psi ramma
  tft.setCursor(20,130);
  tft.print("  8 PSI"); //prentum texta

  //tft.drawRect(180,2*MENU_H+10,MENU_W,MENU_H,WHITE); // 8psi rammi

  // Þarf að vinna að þessu ....
  //tft.drawRect(20,3*MENU_H+10,MENU_W,MENU_H, WHITE); // Teiknum 20psi ramma
  tft.setCursor(180,30);
  tft.print("  12 PSI");

  tft.setCursor(180,80);  // Stillum byrjunarreit
  tft.print("  20 PSI"); // Prentum texta
  //tft.drawRect(180,3*MENU_H+10,MENU_W,MENU_H, WHITE); // Teiknum 28psi ramma
  tft.setCursor(180,130); // Stillum byrjunarreit
  tft.print("  28 PSI"); // Prentum texta
  tft.drawRect(100,5*MENU_H+10,MENU_W,MENU_H, WHITE); // Teiknum til baka ramma
  tft.setCursor(100,5*MENU_H+20); // Stillum byrjunarreit
  tft.println(" Til baka "); // Prentum texta
}


void drawSettings()
{
/*  
*   Backlight settings
*   date / time
*   Forval / preselection set pressure
*   Debug ON / OFF 
*   Test Solenoids  
*/

  tft.fillScreen(BLACK); 
  tft.setTextSize(2);
  // Let's draw boxes
  tft.drawRect(100,3,MENU_W+20,MENU_H, WHITE); // Teiknum Stilla box
  tft.drawRect(100,MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Forval box
  tft.drawRect(100,2*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Baklysing box
  tft.drawRect(100,3*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Maela box
  tft.drawRect(100,4*MENU_H+3,MENU_W+20,MENU_H, WHITE); // Teiknum Til baka box
  tft.drawRect(100,5*MENU_H+3,MENU_W+20,MENU_H,WHITE); //

  tft.setTextSize(2);
  tft.setCursor(120,20);
  tft.println("Baklysing");
  tft.setTextSize(2);
  tft.setCursor(100,MENU_H+20);
  tft.println(" Dagsetning");
  tft.setTextSize(2);
  tft.setCursor(100,2*MENU_H+20);
  tft.println(" Forval val");
  tft.setTextSize(2);
  tft.setCursor(100,3*MENU_H+20);
  tft.println(" Debug ");
  tft.setTextSize(2);
  tft.setCursor(100,4*MENU_H+20);
  tft.println(" Test ");
  tft.setTextSize(2);
  tft.setCursor(100,5*MENU_H+20);
  tft.println(" Til baka");

}

void drawBacklight()
{
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
}