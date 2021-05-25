


// Við veljum tíma fyrir interval
void timerSelector()
{
  // Hér þurfum við að bera saman selectedPressure og pressure
  // Byrjum á ALL
  if(((selectedPressure - pressure_ALL) > 10.00) && ((selectedPressure - pressure_ALL) < 20.00))
  {
    interval_ALL = TIMER10PSI; // 30 sekúndur
  }
  // Ef þrýstingsmunur á völdu gildi og raungildi er milli 5 og 10
  if(((selectedPressure - pressure_ALL) > 5.00) && ((selectedPressure - pressure_ALL) < 10.00))
  {
    interval_ALL = TIMER5PSI; // 10 sekúndur
  }
  if(((selectedPressure - pressure_ALL) > 1.00) && ((selectedPressure - pressure_ALL) < 5.00))
  {
    interval_ALL = TIMER1PSI; // 6 sekúndur
  }
  if(((selectedPressure - pressure_ALL) > 0.00) && ((selectedPressure - pressure_ALL) < 1.00))
  {
    interval_ALL = TIMER025PSI; // 3 sekúndur
  }

  // Næst LRT
  if(((selectedPressure_LRT - pressure_LRT) > 10.00) && ((selectedPressure_LRT - pressure_LRT) < 30.00))
  {
    interval_LRT = TIMER10PSI; // 30 sekúndur
  }
  // Ef þrýstingsmunur á völdu gildi og raungildi er milli 5 og 10
  if(((selectedPressure_LRT - pressure_LRT) > 5.00) && ((selectedPressure_LRT - pressure_LRT) < 10.00))
  {
    interval_LRT = TIMER5PSI; // 10 sekúndur
  }
  if(((selectedPressure_LRT - pressure_LRT) > 1.00) && ((selectedPressure_LRT - pressure_LRT) < 5.00))
  {
    interval_LRT = TIMER1PSI; // 6 sekúndur
  }
  if(((selectedPressure_LRT - pressure_LRT) > 0.00) && ((selectedPressure_LRT - pressure_LRT) < 1.00))
  {
    interval_LRT = TIMER025PSI; // 3 sekúndur
  }

  // Næst LFT
  if(((selectedPressure_LFT - pressure_LFT) > 10.00) && ((selectedPressure_LFT - pressure_LFT) < 20.00))
  {
    interval_LFT = TIMER10PSI; // 30 sekúndur
  }
  // Ef þrýstingsmunur á völdu gildi og raungildi er milli 5 og 10
  if(((selectedPressure_LFT - pressure_LFT) > 5.00) && ((selectedPressure_LFT - pressure_LFT) < 10.00))
  {
    interval_LFT = TIMER5PSI; // 10 sekúndur
  }
  if(((selectedPressure_LFT - pressure_LFT) > 1.00) && ((selectedPressure_LFT - pressure_LFT) < 5.00))
  {
    interval_LFT = TIMER1PSI; // 6 sekúndur
  }
  if(((selectedPressure_LFT - pressure_LFT) > 0.00) && ((selectedPressure_LFT - pressure_LFT) < 1.00))
  {
    interval_LFT = TIMER025PSI; // 3 sekúndur
  }

  // RFT
  if(((selectedPressure_RRT - pressure_RFT) > 10.00) && ((selectedPressure_RFT - pressure_RFT) < 20.00))
  {
    interval_RFT = TIMER10PSI; // 30 sekúndur
  }
  // Ef þrýstingsmunur á völdu gildi og raungildi er milli 5 og 10
  if(((selectedPressure_RFT - pressure_RFT) > 5.00) && ((selectedPressure_RFT - pressure_RFT) < 10.00))
  {
    interval_RFT = TIMER5PSI; // 10 sekúndur
  }
  if(((selectedPressure_RFT - pressure_RFT) > 1.00) && ((selectedPressure_RFT - pressure_RFT) < 5.00))
  {
    interval_RFT = TIMER1PSI; // 6 sekúndur
  }
  if(((selectedPressure_RFT - pressure_RFT) > 0.00) && ((selectedPressure_RFT - pressure_RFT) < 1.00))
  {
    interval_RFT = TIMER025PSI; // 3 sekúndur
  }

  // RRT
  if(((selectedPressure_RRT - pressure_RRT) > 10.00) && ((selectedPressure_RRT - pressure_RRT) < 20.00))
  {
    interval_RRT = TIMER10PSI; // 30 sekúndur
  }
  // Ef þrýstingsmunur á völdu gildi og raungildi er milli 5 og 10
  if(((selectedPressure_RRT - pressure_RRT) > 5.00) && ((selectedPressure_RRT - pressure_RRT) < 10.00))
  {
    interval_RRT = TIMER5PSI; // 10 sekúndur
  }
  if(((selectedPressure_RRT - pressure_RRT) > 1.00) && ((selectedPressure_RRT - pressure_RRT) < 5.00))
  {
    interval_RRT = TIMER1PSI; // 6 sekúndur
  }
  if(((selectedPressure_RRT - pressure_RRT) > 0.00) && ((selectedPressure_RRT - pressure_RRT) < 1.00))
  {
    interval_RRT = TIMER025PSI; // 3 sekúndur
  }

}

// More sophisticated method of determing the time
int timerSelector2(float Pt, float Pv, float Pd, float time)
{
  /*
  * values are
  * Pt = Pressure tire
  * Pv = selected pressure
  * t = time
  * tP = time pressure 
  * Pd = Pressure   
  * Pds = Pressure delta per second
  * 
  * To find time: (Pt-Pd)/t
  * To find time to decrease pressure: (Pt-Pv)/(Pd/s)
  * 
  */
 
 // Let's do a measurement here, this needs to change in the future and needs to be implemented in a more
 // sane manner.
  
  
if(Pt< Pv)
{
  //digitalWrite(AIR_IN,ON); 
  //digitalWrite()
}
  //uint16_t t = 10;
  float tP;  // time Pressure 
  float Pds; // Pressure delta / second

  Pds = (Pt-Pd)/time;
  tP = (Pt-Pv)/Pds;
    // let's ensure Pds is always positive number.
  tP = fabs(tP);

  return tP;
}