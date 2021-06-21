/*
* 	Here we adjust the pressure in the tires
*   This needs a lot of rework
*   
*
*
*/

void adjustAllTires()
{
  timerSelector();

  // DEFLATE
  if(pressure_ALL - selectedPressure > 0.25) // þegar það er of mikill þrýstingur
  {
    digitalWrite(AIR_IN,OFF);
    digitalWrite(TIRE_LR,ON); 
    digitalWrite(TIRE_LF,ON);
    digitalWrite(TIRE_RF,ON);
    digitalWrite(TIRE_RR, ON);
    digitalWrite(AIR_OUT,ON); 

    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_URHLEYPING,tiretoken);
      timer_deflate = timer_deflate + 1000;
    }
  
    if(timer_deflate >= interval_deflate) 
    {
      /*
      read_LRT();
      read_LFT();
      read_RFT();
      read_RRT();
      */
      read_ALL();
      timer_deflate = 0; //endurstillum teljara
      updateValues();
      tiretoken = 0;
    }

  } // Lækkun þrýstings fall lokar

  // INFLATE
  if(selectedPressure - pressure_ALL > 0.25) // þegar það er of lítill þrýstingur
  {
    digitalWrite(AIR_OUT,OFF); // Verum viss um að loft sé ekki að fara út
    digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
    digitalWrite(TIRE_LF,ON);
    digitalWrite(TIRE_RF,ON);
    digitalWrite(TIRE_RR,ON);
    digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn

    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate = timer_inflate + 1000;
    }

    if(timer_inflate >= interval_inflate) // Ef það er kominn tími til að mæla
    {
      /*
      read_LRT();
      read_LFT();
      read_RFT();
      read_RRT();
      */
      read_ALL();
      updateValues();
      timer_inflate = 0; //endurstillum teljara
      tiretoken = 0;
    }          
  }// Hækkun þrýstings fall lokar
}// Lokum adjustAll



//Stillum vinstra afturdekk
void adjustLRT()
{
  timerSelector();
  // DEFLATE
  if(pressure_LRT - selectedPressure_LRT > 0.25) // þegar það er of mikill þrýstingur
  {
    digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      timer_deflate_LRT = timer_deflate_LRT+1000;
    }

    //if(millis() - timer_deflate_LRT > interval_deflate_LRT) // ef það er kominn tími á að mæla
    if(timer_deflate_LRT >= interval_deflate_LRT)
    {
      tiretoken = 2; //Förum síðan í næsta dekk eftir þessa mælingu
      read_LRT(); // Lesum þrýsting
      updateValues();
      timer_deflate_LRT = 0;
      timer_measure = millis();
    }
  } // Lækkun þrýstings fall lokar

  if(selectedPressure_LRT - pressure_LRT>0.25) // þegar það er of lítill þrýstingur
  {
    digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
    digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_LRT = timer_inflate_LRT+1000;
    }

    if(timer_inflate_LRT >= interval_inflate_LRT)
    {
      tiretoken = 2; //Förum síðan í næsta dekk eftir þessa mælingu
      read_LRT(); // Lesum vinstra afturdekk
      updateValues(); // Uppfærum gildin
      timer_inflate_LRT = 0; // rest timer
      timer_measure = millis();
    }
  }// Hækkun þrýstings fall lokar

  else if(((pressure_LRT)-(selectedPressure_LRT))<=0.25 && (((selectedPressure_LRT) - (pressure_LRT))<=0.25 ))
  {
    tiretoken = 2;
    timer_inflate_LRT = 0;
    timer_deflate_LRT = 0;
    timer_measure = millis();
  }
} //End of adjustLRT

//Adjust Left Front Tire
void adjustLFT()
{
  timerSelector();
  //DEFLATE
  if(pressure_LFT - selectedPressure_LFT > 0.25) // þegar það er of mikill þrýstingur
  {
    digitalWrite(TIRE_LF,ON); // Opnum loka í dekk
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      timer_deflate_LFT = timer_deflate_LFT + 1000;
    }

    if(timer_deflate_LFT >= interval_deflate_LFT) // ef það er kominn tími á að mæla
    {
      tiretoken = 3; //Förum síðan í næsta dekk eftir þessa mælingu
      read_LFT(); // Lesum þrýsting
      updateValues(); // Uppfærum gildi
      timer_deflate_LFT = 0; //endurstillum teljara
      timer_measure = millis();
    }

  }// DEFLATE closes

  // INFLATE
  if(selectedPressure_LFT - pressure_LFT > 0.25) 
  {
    digitalWrite(TIRE_LF,ON);
    digitalWrite(AIR_IN,ON); 

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); 
      previousMillis2 = millis(); 
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_LFT = timer_inflate_LFT + 1000;
    }

    if(timer_inflate_LFT >= interval_inflate_LFT) // Ef það er kominn tími til að mæla
    {
      tiretoken = 3; // Let us advance to next tire
      read_LFT(); // Lesum vinstra framdekk
      updateValues(); // Uppfærum gildin
      timer_inflate_LFT = 0; // endurstillum teljarann
      timer_measure = millis();
    }
  }// INFLATE closes

  else if(((pressure_LFT)-(selectedPressure_LFT))<=0.25 && (((selectedPressure_LFT) - (pressure_LFT))<=0.25 ))
  {
    tiretoken = 3;
    timer_inflate_LFT = 0;
    timer_deflate_LFT = 0;
    timer_measure = millis();
  }

}// adjustLFT ends

//Til að stilla hægra framdekk
void adjustRFT()
{
  timerSelector();
  // DEFLATE
  if(pressure_RFT - selectedPressure_RFT > 0.25) // þegar það er of mikill þrýstingur
  {
    digitalWrite(TIRE_RF,ON); // Opnum loka í dekk
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      timer_deflate_RFT = timer_deflate_RFT+1000;
    }

    //if(millis() - timer_deflate_LRT > interval_deflate_LRT) // ef það er kominn tími á að mæla
    if(timer_deflate_RFT >= interval_deflate_RFT)
    {
      tiretoken = 4; //Förum síðan í næsta dekk eftir þessa mælingu
      read_RFT(); // Lesum þrýsting
      updateValues();
      timer_deflate_RFT = 0;
      timer_measure = millis();
    }
  } // DEFLATE Close

  // INFLATE
  if(selectedPressure_RFT - pressure_RFT>0.25) // þegar það er of lítill þrýstingur
  {
    digitalWrite(TIRE_RF,ON); // Opnum loka í dekk
    digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_RFT = timer_inflate_RFT+1000;
    }

    if(timer_inflate_RFT >= interval_inflate_RFT)
    {
      tiretoken = 4; //Förum síðan í næsta dekk eftir þessa mælingu
      read_LRT(); // Lesum vinstra afturdekk
      updateValues(); // Uppfærum gildin
      timer_inflate_LRT = 0; // rest timer
      timer_measure = millis();
    }
  }// Hækkun þrýstings fall lokar

  else if(((pressure_RFT)-(selectedPressure_RFT))<=0.25 && (((selectedPressure_RFT) - (pressure_RFT))<=0.25 ))
  {
    tiretoken = 4;
    timer_inflate_RFT = 0;
    timer_deflate_RFT = 0;
    timer_measure = millis();
  }
}// Lokum adjustRFT

//Til að stilla hægra afturdekk
void adjustRRT()
{
  timerSelector();
  // DEFLATE
  if(pressure_RRT -selectedPressure > 0.25) // þegar það er of mikill þrýstingur
  {
    digitalWrite(TIRE_RR,ON); // Opnum loka í dekk
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út

    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      timer_deflate_RRT = timer_deflate_RRT + 1000;
    }

    if(timer_deflate_RRT >= interval_deflate_RRT) // ef það er kominn tími á að mæla
    {
      tiretoken = 1; //Förum síðan í næsta dekk eftir þessa mælingu
      read_RRT(); // Lesum þrýsting
      updateValues(); // Uppfærum gildi
      timer_deflate_RRT = 0; // endurstillum teljarann
      timer_measure = millis();
    }

  }// DEFLATE closes

  // INFLATE
  if(selectedPressure - pressure_RRT > 0.25) // þegar það er of lítill þrýstingur
  {
    digitalWrite(TIRE_RR,ON); // Opnum loka í dekk
    digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
      timer_inflate_RRT = timer_inflate_RRT + 1000;
      tirePaint(C_INNDAELING,tiretoken); //Litum dekk
    }

    if(timer_inflate_RRT > interval_inflate_RRT) // Ef það er kominn tími til að mæla
    {
      tiretoken = 1; //Förum síðan í næsta dekk eftir þessa mælingu
      read_RRT(); // Lesum vinstra afturdekk
      updateValues(); // Uppfærum gildin
      timer_inflate_RRT = 0; // endurstillum teljarann
      timer_measure = millis();
    }
  }// Hækkun þrýstings fall lokar

  else if(((pressure_RRT)-(selectedPressure_RRT))<=0.25 && (((selectedPressure_RRT) - (pressure_RRT))<=0.25 ))
  {
    tiretoken = 1;
    timer_inflate_RRT = 0;
    timer_deflate_RRT = 0;
    timer_measure = millis();
  }
    
}// Lokum adjustRRT