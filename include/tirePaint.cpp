/*
* 
*
* Veljum lit fyrir dekk og teiknum ferhyrning
*/

int tirePaint(int tire_colour, int tire)
{
  uint8_t tire_colour_LRT;
  uint8_t tire_colour_LFT;
  //Ef dekkið er nr 1, Vinstra afturdekk
  if(tire == 1 && tire_colour_LRT != tire_colour)
  {
    tft.fillRect(LRT_X, LRT_Y, TIRE_W, TIRE_H, BLACK); // Hreinsum vinstra afturhjól
    tft.fillRect(LRT_X, LRT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum vinstra afturhjól
  }
  // Ef dekkið er nr 2, vinstra framdekk
  if(tire == 2)
  {
    tft.fillRect(LFT_X, LFT_Y, TIRE_W, TIRE_H, BLACK); // Hreinsum vinstra framhjól
    tft.fillRect(LFT_X, LFT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum vinstra framhjól

  }
  // Ef dekkið er nr 3, hægra framdekk
  if(tire == 3)
  {
    tft.fillRect(RFT_X, RFT_Y, TIRE_W, TIRE_H, BLACK); // Hreinsum hægra framhjól
    tft.fillRect(RFT_X, RFT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum hægra framhjól
  }
  // Ef dekkið er nr 4, hægra afturdekk
  if(tire == 4)
  {
    tft.fillRect(RRT_X, RRT_Y, TIRE_W, TIRE_H, BLACK); // Hreinsum hægra afturhjól
    tft.fillRect(RRT_X, RRT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum hægra afturhjól
  }
  // Ef dekkið er nr 5 þá erum við að stilla öll dekk.
  if(tire == 5)
  {
      tft.fillRect(LRT_X, LRT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum vinstra afturhjól
      tft.fillRect(LFT_X, LFT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum vinstra framhjól
      tft.fillRect(RFT_X, RFT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum hægra framhjól
      tft.fillRect(RRT_X, RRT_Y, TIRE_W, TIRE_H, tire_colour); // Teiknum hægra afturhjól
  }

  return tire_colour; // Skilum lit, ekki notað í núverandi útgáfu en hugsað fyrir framtíðarviðbætur

}