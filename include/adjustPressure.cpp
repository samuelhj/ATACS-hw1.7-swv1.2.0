// Stillum öll dekk í einu.
// Þetta þarf sennilega að bæta...
void adjustAllTires()
{
  //unsigned long millis() = millis(); //Uppfærum teljara
  if(((pressure_ALL*100-selectedPressure*100))>25) // þegar það er of mikill þrýstingur
  {
    tiretoken = 5; // Við höldum token til að stilla öll dekk
    digitalWrite(AIR_IN,OFF);
    digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
    digitalWrite(TIRE_LF,ON);
    digitalWrite(TIRE_RF,ON);
    digitalWrite(TIRE_RR, ON);
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út
    tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt

    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu
      previousMillis2 = millis(); // Endurstillum teljarann
    }

    if(millis() - previousMillis > interval_ALL) // ef það er kominn tími á að mæla
    {
      read_LRT(); // Lesum þrýsting
      read_LFT();
      read_RFT();
      read_RRT();
      previousMillis = millis(); //endurstillum teljara
      updateValues();
      // Hérna myndum við vilja bera saman þrýsting á öllum dekkjum
      // Við breytum öllu í heiltölu í centiPSI, fyrir lesanleika
      uint16_t test_LRT = pressure_LRT*100;
      uint16_t test_LFT = pressure_LFT*100;
      uint16_t test_RFT = pressure_RFT*100;
      uint16_t test_RRT = pressure_RRT*100;

      // Reynist summa allra vera hærri en valins þrýstings.
      if((test_LRT + test_LFT + test_RFT + test_RRT)  > (selectedPressure*400))
      {
        // Þá leiðréttum við hvert dekk fyrir sig, og höldum svo áfram.
        adjustLRT(); // Stillum vinstra afturdekk
        adjustLFT(); // Stillum vinstra framdekk
        adjustRFT(); // Stillum hægra framdekk
        adjustRRT(); // Stillum hægra afturdekk
        tiretoken = 5; // Setjum okkur aftur í að stilla öll dekk
      }
      else
      pressure_ALL = pressure_LRT; // öll dekk hafa sama þrýsting.
    }
  } // Lækkun þrýstings fall lokar

      if((selectedPressure*100 - pressure_ALL*100)>25) // þegar það er of lítill þrýstingur
      {
        tiretoken = 5; // Við höldum token til að stilla öll dekk
        digitalWrite(AIR_OUT,OFF); // Verum viss um að loft sé ekki að fara út
        digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
        digitalWrite(TIRE_LF,ON);
        digitalWrite(TIRE_RF,ON);
        digitalWrite(TIRE_RR,ON);
        digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
        tirePaint(C_INNDAELING,tiretoken);

        if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
        {
          updateBaseValue(); // Uppfærum mælingu á kistu
          previousMillis2 = millis(); // Endurstillum teljarann

        }

        if(millis() - previousMillis > interval_ALL) // Ef það er kominn tími til að mæla
        {
          air_base_close(); // Lokum kistu
          read_LRT(); // Lesum þrýsting
          read_LFT();
          read_RFT();
          read_RRT();
          updateValues();
          previousMillis = millis(); //endurstillum teljara

          // Hérna myndum við vilja bera saman þrýsting á öllum dekkjum
          // Við breytum öllu í heiltölu í milliPSI, fyrir lesanleika
          int test_LRT = pressure_LRT*100;
          int test_LFT = pressure_LFT*100;
          int test_RFT = pressure_RFT*100;
          int test_RRT = pressure_RRT*100;

          // Reynist summa allra vera lægri en valins þrýstings.
          if((selectedPressure*400) < (test_LRT + test_LFT + test_RFT + test_RRT))
          {
            // Þá leiðréttum við hvert dekk fyrir sig, og höldum svo áfram.
            adjustLRT(); // Stillum vinstra afturdekk
            adjustLFT(); // Stillum vinstra framdekk
            adjustRFT(); // Stillum hægra framdekk
            adjustRRT(); // Stillum hægra afturdekk
            tiretoken = 5; // Setjum okkur aftur í að stilla öll dekk
          }
          else
          pressure_ALL = pressure_LRT; // öll dekk hafa sama þrýsting.
        }
      }// Hækkun þrýstings fall lokar

    //Við athugum hvort við séum innan skekkjumarka. Sé svo þá stillum við hvert dekk fyrir sig.
    if(((pressure_ALL*100)-(selectedPressure*100))<=200 && (((selectedPressure*100) - (pressure_ALL*100))<=200 ))
    {
      air_base_close();
      timerTire = 0; // Núllstillum teljara
      tiretoken = 1; // Færum okkur í fyrsta dekk og stillum hvert fyrir sig.
    }
    //Við athugum hvort við séum innan skekkjumarka

}// Lokum adjustAll



//Stillum vinstra afturdekk
void adjustLRT()
{

  if(((pressure_LRT*100)-(selectedPressure*100))>25) // þegar það er of mikill þrýstingur
  {
    tiretoken = 1; // Við höldum token til að stilla þetta dekk
    digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
    digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út
    tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
    // Mælum þrýsting á kistu
    if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
    {
      updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
      previousMillis2 = millis(); // Endurstillum teljarann
    }

    if((millis() - previousMillis) > interval_LRT) // ef það er kominn tími á að mæla
    {
      tiretoken = tiretoken+1; //Förum síðan í næsta dekk eftir þessa mælingu
      read_LRT(); // Lesum þrýsting
      updateValues();
      previousMillis = millis(); //endurstillum teljara
    }
  } // Lækkun þrýstings fall lokar

      if(((selectedPressure*100) - (pressure_LRT*100))>25) // þegar það er of lítill þrýstingur
      {
        tiretoken = 1; // Við höldum token til að stilla þetta dekk
        digitalWrite(TIRE_LR,ON); // Opnum loka í dekk
        digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
        tirePaint(C_INNDAELING,tiretoken);

        // Mælum þrýsting á kistu
        if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
        {
          updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
          previousMillis2 = millis(); // Endurstillum teljarann
        }

        // Ef það er kominn tími til að mæla
        if(millis() - previousMillis > interval_LRT)
        {
          tiretoken = tiretoken+1; //Förum síðan í næsta dekk eftir þessa mælingu
          digitalWrite(TIRE_LR,OFF); // Lokum loka
          delay(AIR_DELAY); // Hinkrum
          digitalWrite(AIR_OUT,OFF); // Lokum fyrir loft út
          delay(AIR_DELAY); // Hinkrum
          read_LRT(); // Lesum vinstra afturdekk
          updateValues(); // Uppfærum gildin
          previousMillis = millis(); // endurstillum teljarann
        }
      }// Hækkun þrýstings fall lokar

    //Við athugum hvort við séum innan skekkjumarka
    if(((pressure_LRT*100)-(selectedPressure*100))<=25 && (((selectedPressure*100) - (pressure_LRT*100))<=25 ))
    {
      air_base_close();
      timerTire = 0; // Núllstillum teljara
      tiretoken = 2; // Færum okkur í næsta dekk
    }
    //millis() += millis();
} //Lokum adjustLRT

//Við stillum vinstra framdekk
void adjustLFT()
{
    if(((pressure_LFT*100)-(selectedPressure*100))>25) // þegar það er of mikill þrýstingur
    {
      tiretoken = 2; // Við höldum token til að stilla þetta dekk
      digitalWrite(TIRE_LF,ON); // Opnum loka í dekk
      digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      // Mælum þrýsting á kistu
      if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
      {
        updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
        previousMillis2 = millis(); // Endurstillum teljarann
      }

      if(millis() - previousMillis > interval_LFT) // ef það er kominn tími á að mæla
      {
        tiretoken = 3; //Förum síðan í næsta dekk eftir þessa mælingu
        air_base_close(); // Lokum kistu
        read_LFT(); // Lesum þrýsting
        updateValues(); // Uppfærum gildi
        previousMillis = millis(); //endurstillum teljara
      }

    }// Lækkun þrýstings fall lokar

        if(((selectedPressure*100) - (pressure_LFT*100))>25) // þegar það er of lítill þrýstingur
        {
          tiretoken = 2; // Við höldum token til að stilla þetta dekk
          digitalWrite(TIRE_LF,ON); // Opnum loka í dekk
          digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
          tirePaint(C_INNDAELING,tiretoken);
          // Mælum þrýsting á kistu
          if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
          {
            updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
            previousMillis2 = millis(); // Endurstillum teljarann
          }
        }// Hækkun þrýstings fall lokar

        if(millis() - previousMillis > interval_LFT) // Ef það er kominn tími til að mæla
        {
          tiretoken = 3; //Förum síðan í næsta dekk eftir þessa mælingu
          air_base_close(); // Lokum kistu
          delay(100); // Hinkrum
          read_LFT(); // Lesum vinstra framdekk
          updateValues(); // Uppfærum gildin
          previousMillis = millis(); // endurstillum teljarann
        }

      //Við athugum hvort við séum innan skekkjumarka (0.25psi frá völdu gildi)
      if(((pressure_LFT*100)-(selectedPressure*100))<=25 && (((selectedPressure*100) - (pressure_LFT*100))<=25 ))
      {
        air_base_close(); // Lokum kistunni
        timerTire = 0; // Núllstillum teljara
        tiretoken = 3; // Færum okkur í næsta dekk
      }
}// Lokum adjustLFT

//Til að stilla hægra framdekk
void adjustRFT()
{
  {
    if(((pressure_RFT*100)-(selectedPressure*100))>25) // þegar það er of mikill þrýstingur
    {
      tiretoken = 3; // Við höldum token til að stilla þetta dekk
      digitalWrite(TIRE_RF,ON); // Opnum loka í dekk
      digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      // Mælum þrýsting á kistu
      if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
      {
        updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
        previousMillis2 = millis(); // Endurstillum teljarann
      }

      if(millis() - previousMillis > interval_RFT) // ef það er kominn tími á að mæla
      {
        tiretoken = 4; //Förum síðan í næsta dekk eftir þessa mælingu
        air_base_close(); // Lokum kistu
        read_RFT(); // Lesum þrýsting
        updateValues(); // Uppfærum gildi
        previousMillis = millis(); //endurstillum teljara
      }

    }// Lækkun þrýstings fall lokar

        if(((selectedPressure*100) - (pressure_RFT*100))>25) // þegar það er of lítill þrýstingur
        {
          tiretoken = 3; // Við höldum token til að stilla þetta dekk
          digitalWrite(TIRE_RF,ON); // Opnum loka í dekk
          digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
          tirePaint(C_INNDAELING,tiretoken);
          // Mælum þrýsting á kistu
          if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
          {
            updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
            previousMillis2 = millis(); // Endurstillum teljarann
          }
        }// Hækkun þrýstings fall lokar

        if(millis() - previousMillis > interval_RFT) // Ef það er kominn tími til að mæla
        {
          tiretoken = 4; //Förum síðan í næsta dekk eftir þessa mælingu
          air_base_close(); // Lokum kistu
          delay(100); // Hinkrum
          read_RFT(); // Lesum vinstra afturdekk
          updateValues(); // Uppfærum Gildin
          previousMillis = millis(); // endurstillum teljarann
        }

      //Við athugum hvort við séum innan skekkjumarka
      if(((pressure_RFT*100)-(selectedPressure*100))<=25 && (((selectedPressure*100) - (pressure_RFT*100))<=25 ))
      {
        air_base_close(); // Lokum kistu
        timerTire = 0; // Núllstillum teljara
        tiretoken = 4; // Færum okkur í næsta dekk
      }
    }
}// Lokum adjustRFT

//Til að stilla hægra afturdekk
void adjustRRT()
{
  {
    if(((pressure_RRT*100)-(selectedPressure*100))>25) // þegar það er of mikill þrýstingur
    {
      tiretoken = 4; // Við höldum token til að stilla þetta dekk
      digitalWrite(TIRE_RR,ON); // Opnum loka í dekk
      digitalWrite(AIR_OUT,ON); // Opnum fyrir loft út
      tirePaint(C_URHLEYPING,tiretoken); // Litum dekk fjólublátt
      // Mælum þrýsting á kistu
      if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
      {
        updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
        previousMillis2 = millis(); // Endurstillum teljarann
      }

      if(millis() - previousMillis > interval_RRT) // ef það er kominn tími á að mæla
      {
        tiretoken = 1; //Förum síðan í næsta dekk eftir þessa mælingu
        air_base_close(); // Lokum kistu
        read_RRT(); // Lesum þrýsting
        updateValues(); // Uppfærum gildi
        previousMillis = millis(); // endurstillum teljarann
      }

    }// Lækkun þrýstings fall lokar

        if(((selectedPressure*100) - (pressure_RRT*100))>25) // þegar það er of lítill þrýstingur
        {
          tiretoken = 4; // Við höldum token til að stilla þetta dekk
          digitalWrite(TIRE_RR,ON); // Opnum loka í dekk
          digitalWrite(AIR_IN,ON); // Opnum fyrir loft inn
          tirePaint(C_INNDAELING,tiretoken); //Litum dekk
          // Mælum þrýsting á kistu
          if(millis() - previousMillis2 > 1000) // Ef það er kominn tími til að mæla
          {
            updateBaseValue(); // Uppfærum mælingu á kistu (Þetta er experimental)
            previousMillis2 = millis(); // Endurstillum teljarann
          }
        }// Hækkun þrýstings fall lokar

        if(millis() - previousMillis > interval_RRT) // Ef það er kominn tími til að mæla
        {
          tiretoken = 1; //Förum síðan í næsta dekk eftir þessa mælingu
          air_base_close(); // Lokum kistu
          delay(100); // Hinkrum
          read_RRT(); // Lesum vinstra afturdekk
          updateValues(); // Uppfærum gildin
          previousMillis = millis(); // endurstillum teljarann
        }
      //Við athugum hvort við séum innan skekkjumarka
      if(((pressure_RRT*100)-(selectedPressure*100))<=25 && (((selectedPressure*100) - (pressure_RRT*100))<=25 ))
      {
        air_base_close(); // Lokum kistu
        timerTire = 0; // Núllstillum teljara
        tiretoken = 1; // Færum okkur í næsta dekk
      }
    }
}// Lokum adjustRRT