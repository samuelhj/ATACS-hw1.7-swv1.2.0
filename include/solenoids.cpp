// Lokum öllum lokum í kistu
void air_base_close()
{
    digitalWrite(AIR_OUT,OFF); // Lokum aflestunarloka
    digitalWrite(AIR_IN,OFF); // Lokum inndælingarloka
    digitalWrite(TIRE_LR,OFF); // Lokum vinstra afturhjóli
    digitalWrite(TIRE_LF,OFF); // Lokum vinstra framhjóli
    digitalWrite(TIRE_RF,OFF); // lokum hægra framhjóli
    digitalWrite(TIRE_RR,OFF); // Lokum hægra afturhjóli.
    digitalWrite(AIR_OUT,ON); // Tæmum kistu
    delay(AIR_DELAY);
    digitalWrite(AIR_OUT,OFF); // Lokum út
  //  tirePaint(GREEN,5);
  //  warningCheck();
  if(debug == true)
  {
    Serial.println("Solenoids close");
  }
}

void air_base_inflate()
{
  digitalWrite(AIR_OUT,OFF);
  digitalWrite(TIRE_LR,ON);
  digitalWrite(TIRE_LF,ON);
  digitalWrite(TIRE_RF,ON);
  digitalWrite(TIRE_RR,ON);
  digitalWrite(AIR_IN,ON);
  tirePaint(C_INNDAELING,5);

  if(debug == true)
  {
    Serial.println("INFLATING");
  }

}

void air_base_deflate()
{
  digitalWrite(AIR_OUT,ON);
  digitalWrite(TIRE_LR,ON);
  digitalWrite(TIRE_LF,ON);
  digitalWrite(TIRE_RF,ON);
  digitalWrite(TIRE_RR,ON);
  digitalWrite(AIR_IN,OFF);
  tirePaint(C_URHLEYPING,5);

  if(debug == true)
  {
    Serial.println("DEFLATING");
  }

}


/*
*   Loops to test allt solenoids
*   Missing indicators which solenoid is active, and stuffs
*
*/

void test()
{
  if(debug == true)
  {
    Serial.println("Solenoid TEST loop begins");
  }

  tft.setCursor(130,220);
  tft.println("test");

  digitalWrite(AIR_IN,ON);
  delay(2000);
  digitalWrite(TIRE_LR,ON);
  tirePaint(C_INNDAELING,1);
  delay(2000);
  digitalWrite(TIRE_LR,OFF);
  tirePaint(GREEN,1);
  delay(1000);
  digitalWrite(TIRE_LF,ON);
  tirePaint(C_INNDAELING,2);
  delay(2000);
  digitalWrite(TIRE_LF,OFF);
  tirePaint(GREEN,2);
  delay(1000);
  digitalWrite(TIRE_RF,ON);
  tirePaint(C_INNDAELING,3);
  delay(2000);
  digitalWrite(TIRE_RF,OFF);
  tirePaint(GREEN,3);
  delay(1000);
  digitalWrite(TIRE_RR,ON);
  tirePaint(C_INNDAELING,4);
  delay(2000);
  digitalWrite(TIRE_RR,OFF);
  tirePaint(GREEN,4);
  delay(1000);
  digitalWrite(AIR_OUT,ON);
  delay(5000);
  air_base_close();
  delay(1000);
  tft.fillRect(120,220,240,20,BLACK); 
  if(debug == true)
    {
      Serial.println("Solenoid TEST loop ends");
    } 
}