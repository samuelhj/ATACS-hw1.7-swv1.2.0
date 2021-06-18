// Er kominn tími til að mæla dekk? 10 mín ef við erum ekki í stillingu/vöktun
// Prófum að athuga hvort við erum yfir 20 psi.
void tireMonitor()
{
  if(selectedPressure < 20)
  {
    interval_measure = 600000;
  }
  if(selectedPressure < 10)
  {
    interval_measure = 300000;
  }
  if(selectedPressure < 3)
  {
    interval_measure = 120000;
  }
  
  if(menuval == 0 ) 
  {

    if((millis() - timer_measure) > interval_measure) // Athugum hve langt er liðið frá síðustu uppfærslu gilda
    {
      read_LRT(); // Lesum vinstra afturdekk
      updateValues(); // uppfærum gildi
      read_LFT(); // Lesum vinstra framdekk
      updateValues(); // uppfærum gildi
      read_RFT(); // Lesum hægra framdekk
      updateValues(); // Uppfærum gildi
      read_RRT(); // Lesum hægra afturdekk
      updateValues(); // Lesum gildi.
      warningCheck(); // Athugum hvort eitthvað dekk sé í veseni.
      timer_measure = millis(); // Endurstillum teljara
    }
  }//Lokum athugunarfalli

  if(debug == true)
  {
    Serial.print("Interval Measure: ");
    Serial.println(interval_measure);
    Serial.println();
  }

}