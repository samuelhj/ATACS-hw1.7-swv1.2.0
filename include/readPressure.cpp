// Lesum þrýsting á skynjara og skilum gildi


float readPressure()
{
    /* Skynjarinn er MPX5700 og les max 100psi
     *     100psi MAX pressure
     * 6,4mV/0.145psi
     * Við viljum lesa eins nákvæmt og hægt er, en þó ekki birta gögnin nema með 0.25psi nákvæmni.
     * 11mV/0.250psi
     */

  int val = analogRead(P_SENSOR); // Lesum gildi
  psi = val*100; // færum það upp um 100
  psi = map(psi,4100,94000,0,10000); // efri/neðri mörk

  float pressure = 0.00f; // Færum í fljótandi gildi
  pressure = psi;
  pressure = pressure/100.00f; // Umreiknum

  if(pressure < 0 || pressure > 650) // Komum í veg fyrir "buffer overflow"
  {
    pressure = 0;
  }
  return pressure;
} //readPressure fall lokar


void read_LRT() // Lesum vinstra afturdekk
{
  tirePaint(C_MAELING,1); // Litum dekk rauðgult.
  air_base_close(); // Lokum kistunni
  digitalWrite(TIRE_LR,ON); // Opnum loka fyrir Vinstra afturdekk
  delay(AIR_DELAY); // hinkrum
  pressure_LRT = readPressure(); // Lesum þrýsting
  digitalWrite(TIRE_LR,OFF);
  warningCheck(); // Athugum hvort allt sé með felldu
  //previousMillis = millis(); // endurstillum teljarann
}

void read_LFT() // Lesa vinstra framdekk
{
  tirePaint(C_MAELING,2); // Litum dekk rauðgult meðan við mælum.
  air_base_close(); // Verum viss um að kista sé lokuð
  delay(AIR_DELAY); // Hinkrum í 300ms
  digitalWrite(TIRE_LF,ON); // Opnum fyrir dekk LF
  delay(AIR_DELAY); // töf meðan kista fyllist
  pressure_LFT = readPressure(); // Lesum þrýsting
  digitalWrite(TIRE_LF,OFF); // Lokum kistunni
  warningCheck(); // Athugum hvort allt sé með felldu
}

void read_RFT() // Lesa Hægra framdekk
{
  tirePaint(C_MAELING,3);
  air_base_close();
  delay(AIR_DELAY); // Hinkrum í 300ms
  digitalWrite(TIRE_RF,ON); // Opnum fyrir dekk
  delay(AIR_DELAY); // Töf á meðan kistan fyllist.
  pressure_RFT = readPressure(); // lesum þrýsting í dekki
  digitalWrite(TIRE_RF,OFF); // Lokum kistunni
  warningCheck(); // Athugum hvort allt sé með felldu
}

void read_RRT() // Lesa hægra afturdekk
{
  tirePaint(C_MAELING,4);// Litum dekk rauðgult
  air_base_close(); // Lokum kistunni
  delay(AIR_DELAY); // Töf
  digitalWrite(TIRE_RR,ON); // Opnum fyrir dekk
  delay(AIR_DELAY); // Töf á meðan kistan fyllist.
  pressure_RRT = readPressure(); // Lesum þrýsting í dekki.
  digitalWrite(TIRE_RR,OFF); // Lokum kistunni.
  warningCheck(); // Athugum hvort allt sé með felldu
}

