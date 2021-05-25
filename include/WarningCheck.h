void warningCheck()
{
    /*
     * Hér kemur fall virkjar viðvörun á skjá þegar eitthvað fer úrskeiðis.
     * T.d. ef eitt dekk verður skyndilega loftlaust á ferð.
     * * ef eitt eða fleiri dekk eru skyndilega komin undir 0.5psi
     * Á skjánum mun birtast hvert dekkjanna er sýnir hættumerki ef viðvörun fer í gildi.
     */
  if(menuval == 0) // Ef við erum ekki í Menu
  {
      // Síðan þurfum við að tjekka hvaða dekk er í veseni.

      // Ef þrýstingur er undir 0.5psi eða yfir 35 psi í vinstra afturdekki
      if((pressure_LRT*100 < 25) || (pressure_LRT > 35))
      {
        tirePaint(C_WARNING,1); // Við litum dekkið rautt
      }
      // Ef ástand lagast, dekk er yfir 0.5psi og undir 35 psi
      if((pressure_LRT > 0.5) && (pressure_LRT < 35))
      {
        tirePaint(GREEN,1); // Litum dekkið grænt
      }

      // Ef vinstra framhjól er loftlaust eða of hár þrýstingur
      if((pressure_LFT*100 < 25) || (pressure_LFT > 35))
      {
        tirePaint(C_WARNING,2); // Teiknum vinstra framhjól
      }
      // Ef ástand lagast
      if((pressure_LFT*100 > 25) && (pressure_LFT < 35))
      {
        tirePaint(GREEN,2); // Litum dekk grænt
      }

      // Ef hægra framhjól er loftlaust eða of hár þrýstingur
      if((pressure_RFT*100 < 25) || (pressure_RFT > 35))
      {
        tirePaint(C_WARNING,3); // Teiknum hægra framhjól
      }
      if((pressure_RFT*100 > 25) && (pressure_RFT < 35))
      {
        tirePaint(GREEN,3); // Litum dekk grænt
      }
      // Ef hægra afturhjól er loftlaust eða of hár þrýstingur
      if((pressure_RRT*100 < 25 || pressure_RRT > 35))
      {
        tirePaint(C_WARNING,4); // Teiknum hægra afturhjól rautt
      }
      if((pressure_RRT*100 > 25) && (pressure_RRT < 35))
      {
        tirePaint(GREEN,4);  // Litum dekk grænt
      }
  }

} // Lokum warningCheck fallinu