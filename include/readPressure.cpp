// Lesum þrýsting á skynjara og skilum gildi
// read pressure at sensor and return value

float readPressure()
{
  /* Sensor is MPX5700 
  * 100psi max pressure readout
  * 6.4mV/0.145psi
  * We want to read as accurate as possible, but display with 0.25psi resolution
  * 11mV/0.250psi
  */ 

  int val = analogRead(P_SENSOR); // read value
  psi = val*100; 
  psi = map(psi,4100,94000,0,10000); 

  float pressure = 0.00f; // fix floating variable size
  pressure = psi;
  pressure = pressure/100.00f; // Recalculate

  if(pressure < 0 || pressure > 650) // We don't like "buffer overflow"
  {
    pressure = 0;
  }
  return pressure;
} //readPressure ends

void read_ALL()
{
  tirePaint(C_MAELING,1);
  air_base_close();
  digitalWrite(TIRE_LR,ON);
  digitalWrite(TIRE_LF,ON);
  digitalWrite(TIRE_RF,ON);
  digitalWrite(TIRE_RR,ON);
  delay(AIR_DELAY);
  pressure_ALL = readPressure();
  air_base_close();
  warningCheck();
}

void read_LRT() // Left rear tire
{
  tirePaint(C_MAELING,1);
  air_base_close();
  digitalWrite(TIRE_LR,ON); 
  delay(AIR_DELAY); 
  pressure_LRT = readPressure(); 
  digitalWrite(TIRE_LR,OFF);
  warningCheck(); // Athugum hvort allt sé með felldu
  //previousMillis = millis(); // endurstillum teljarann
}

void read_LFT() // Left front tire
{
  tirePaint(C_MAELING,2); 
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

