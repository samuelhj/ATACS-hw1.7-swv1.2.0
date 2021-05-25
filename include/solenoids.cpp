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
  delay(10000);
  digitalWrite(TIRE_LR,OFF);
  delay(1000);
  digitalWrite(TIRE_LF,ON);
  delay(10000);
  digitalWrite(TIRE_LF,OFF);
  delay(1000);
  digitalWrite(TIRE_RF,ON);
  delay(10000);
  digitalWrite(TIRE_RF,OFF);
  delay(1000);
  digitalWrite(TIRE_RR,ON);
  delay(10000);
  digitalWrite(TIRE_RR,OFF);
  delay(1000);
  digitalWrite(AIR_IN,ON); // Prófum dælu
  delay(5000);
  digitalWrite(AIR_OUT,OFF);
  delay(1000);
  // Dælum í 10s í hvert dekk

  digitalWrite(TIRE_LR,ON);
  delay(10000);
  digitalWrite(TIRE_LR,OFF);
  delay(1000);
  digitalWrite(TIRE_LF,ON);
  delay(10000);
  digitalWrite(TIRE_LF,OFF);
  delay(1000);
  digitalWrite(TIRE_RF,ON);
  delay(10000);
  digitalWrite(TIRE_RF,OFF);
  delay(1000);
  digitalWrite(TIRE_RR,ON);
  delay(10000);
  digitalWrite(TIRE_RR,OFF);
  delay(1000);
  digitalWrite(AIR_IN,OFF);
  delay(15000);

}