// Við skrifum vistuð gildi í EEPROM
void writeSelectedPressure()
{
  //EEPRON.put(ESERIALNUMBER,SERIALNUMBER); // Skrifum inn serial númer
  EEPROM.put(EPRESSURE,selectedPressure); //valinn þrýstingur
  EEPROM.put(EPRESSURE_LRT,selectedPressure_LRT); // Valinn þrýstingur per dekk
  EEPROM.put(EPRESSURE_LFT,selectedPressure_LFT);
  EEPROM.put(EPRESSURE_RFT,selectedPressure_RFT);
  EEPROM.put(EPRESSURE_RRT,selectedPressure_RRT);
}
