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
*
*
*/

void test()
{
  // Hleypum úr 10s per dekk
  digitalWrite(AIR_OUT,ON);
  delay(2000);
  digitalWrite(TIRE_LR,ON);
  delay(2000);
  digitalWrite(TIRE_LR,OFF);
  delay(1000);
  digitalWrite(TIRE_LF,ON);
  delay(2000);
  digitalWrite(TIRE_LF,OFF);
  delay(1000);
  digitalWrite(TIRE_RF,ON);
  delay(2000);
  digitalWrite(TIRE_RF,OFF);
  delay(1000);
  digitalWrite(TIRE_RR,ON);
  delay(2000);
  digitalWrite(TIRE_RR,OFF);
  delay(1000);
  digitalWrite(AIR_IN,ON); // Prófum dælu
  delay(5000);
  digitalWrite(AIR_OUT,OFF);
  delay(1000);
  // Dælum í 10s í hvert dekk

  digitalWrite(TIRE_LR,ON);
  delay(2000);
  digitalWrite(TIRE_LR,OFF);
  delay(1000);
  digitalWrite(TIRE_LF,ON);
  delay(2000);
  digitalWrite(TIRE_LF,OFF);
  delay(1000);
  digitalWrite(TIRE_RF,ON);
  delay(2000);
  digitalWrite(TIRE_RF,OFF);
  delay(1000);
  digitalWrite(TIRE_RR,ON);
  delay(2000);
  digitalWrite(TIRE_RR,OFF);
  delay(1000);
  digitalWrite(AIR_IN,OFF);
  delay(1000);

}