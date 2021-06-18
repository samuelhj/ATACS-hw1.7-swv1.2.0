
// Við veljum tíma fyrir interval
void timerSelector()
{
  // Hér þurfum við að bera saman selectedPressure og pressure
  // Byrjum á ALL
  if(tiretoken == 5)
  {
    float a;
    a = selectedPressure - pressure_ALL;
    a = fabs(a);

    if(a > 10)
    {
      interval_deflate = PTLONG;
      interval_inflate = PTLONG;
    }
    if(a > 5 && a < 10)
    {
      interval_deflate = PTMEDIUM;
      interval_inflate = PTMEDIUM;
    }
    if(a < 5)
    {
      interval_deflate = PTSHORT;
      interval_inflate = PTSHORT;
    }
  }// All closes

  if(tiretoken == 1)
  {
    float a;
    a = selectedPressure_LRT - pressure_LRT;
    a = fabs(a);
    
    if(a > 10)
    {
      interval_deflate_LRT = PTLONG;
      interval_inflate_LRT = PTLONG;
    }
    if(a > 5 && a < 10)
    {
      interval_deflate_LRT = PTMEDIUM;
      interval_inflate_LRT = PTMEDIUM;
    }
    if(a < 5)
    {
      interval_deflate_LRT = PTSHORT;
      interval_inflate_LRT = PTSHORT;
    }
  } // LRT (1) closes 

  if(tiretoken == 2)
  {
    float a;
    a = selectedPressure_LFT - pressure_LFT;
    a = fabs(a);
    
    if(a > 10)
    {
      interval_deflate_LFT = PTLONG;
      interval_inflate_LFT = PTLONG;
    }
    if(a > 5 && a < 10)
    {
      interval_deflate_LFT = PTMEDIUM;
      interval_inflate_LFT = PTMEDIUM;
    }
    if(a < 5)
    {
      interval_deflate_LFT = PTSHORT;
      interval_inflate_LFT = PTSHORT;
    }
  } // LFT (2) closes 

  if(tiretoken == 3)
  {
    float a;
    a = selectedPressure_RFT - pressure_RFT;
    a = fabs(a);
    
    if(a > 10)
    {
      interval_deflate_RFT = PTLONG;
      interval_inflate_RFT = PTLONG;
    }
    if(a > 5 && a < 10)
    {
      interval_deflate_RFT = PTMEDIUM;
      interval_inflate_RFT = PTMEDIUM;
    }
    if(a < 5)
    {
      interval_deflate_RFT = PTSHORT;
      interval_inflate_RFT = PTSHORT;
    }
  } // RFT (3) closes 

  if(tiretoken == 4)
  {
    float a;
    a = selectedPressure_RRT - pressure_RRT;
    a = fabs(a);
    
    if(a > 10)
    {
      interval_deflate_RRT = PTLONG;
      interval_inflate_RRT = PTLONG;
    }
    if(a > 5 && a < 10)
    {
      interval_deflate_RRT = PTMEDIUM;
      interval_inflate_RRT = PTMEDIUM;
    }
    if(a < 5)
    {
      interval_deflate_RRT = PTSHORT;
      interval_inflate_RRT = PTSHORT;
    }
  } // RRT (4) closes 
}//TimerSelector closes

// More sophisticated method of determing the time
float timerSelector2(float Pt, float Pv, float Pd, float time)
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

  float tP;  // time Pressure 
  float Pds; // Pressure delta / second

  Pds = (Pt-Pd)/time;
  tP = (Pt-Pv)/Pds;



  if(debug == true)
  {
    Serial.print("Pds = (Pt-Pd)/time: (");
    Serial.print(Pt);
    Serial.print(" - ");
    Serial.print(Pd);
    Serial.print(")/");
    Serial.print(time);
    Serial.print("=");
    Serial.println(Pds); 
    Serial.println("");
    Serial.print("tP = (Pt-Pv)/Pds : (");
    Serial.print(Pt); 
    Serial.print(" - ");
    Serial.print(Pv); 
    Serial.print(")/");
    Serial.print(Pds);
    Serial.print("=");
    Serial.println(tP);
    Serial.println(" ");
  }

  // let's ensure Pds is always positive number.
  tP = fabs(tP);

  // We implement an upper limit as an failsafe, in case something goes wrong so it wont just deflate/inflate forever...
  if(tP > 30)
  {
    tP = 30; // 30s max
  }
  // In case, for some reason the time is less than two seconds
  if(tP < 2)
  {
    tP = 2;
  }

  if(debug == true)
  {
    Serial.println("After timerSelector");
    Serial.print("time to inflate/deflate: ");
    Serial.println(tP);
    Serial.print("delta Pressure / second: ");
    Serial.println(Pds);
    Serial.println(" ");
  }

  // We need to change back to milliseconds
  tP = tP*1000;
  return tP;



}