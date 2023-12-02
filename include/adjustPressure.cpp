/*
* 	Here we adjust the pressure in the tires
*   This needs a lot of rework
*   
*
*
*/

void adjustAllTires()
{
  timerSelector();

  // DEFLATE
  if(pressure_ALL - selectedPressure > 0.25) // If pressure is too high
  {
    digitalWrite(AIR_IN,OFF);
    digitalWrite(TIRE_LR,ON); 
    digitalWrite(TIRE_LF,ON);
    digitalWrite(TIRE_RF,ON);
    digitalWrite(TIRE_RR, ON);
    digitalWrite(AIR_OUT,ON); 

    if(millis() - previousMillis2 > 1000) // If there's time to measure
    {
      updateBaseValue(); // Update measurement on base
      previousMillis2 = millis(); // Reset counter 
      tirePaint(C_URHLEYPING,tiretoken);
      timer_deflate = timer_deflate + 1000;
    }
  
    if(timer_deflate >= interval_deflate) 
    {
      /*
      read_LRT();
      read_LFT();
      read_RFT();
      read_RRT();
      */
      read_ALL();
      timer_deflate = 0; // Reset counter
      updateValues();
      tiretoken = 0;
    }

  } // Decrement pressure function closes

  // INFLATE
  if(selectedPressure - pressure_ALL > 0.25) // If the pressure is too low
  {
    digitalWrite(AIR_OUT,OFF); // Make sure valve is closed
    digitalWrite(TIRE_LR,ON); // Open valve to tyre
    digitalWrite(TIRE_LF,ON);
    digitalWrite(TIRE_RF,ON);
    digitalWrite(TIRE_RR,ON);
    digitalWrite(AIR_IN,ON); // Open valve for air in

    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on valve base
      previousMillis2 = millis(); // Reset counter 
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate = timer_inflate + 1000;
    }

    if(timer_inflate >= interval_inflate) // If it's time to measure 
    {
      /*
      read_LRT();
      read_LFT();
      read_RFT();
      read_RRT();
      */
      read_ALL();
      updateValues();
      timer_inflate = 0; // reset counter 
      tiretoken = 0;
    }          
  }// Increment pressure function closes
}// Close adjustAll



// Adjust Left Rear Tyre
void adjustLRT()
{
  timerSelector();
  // DEFLATE
  if(pressure_LRT - selectedPressure_LRT > 0.25) // If the pressure is too high
  {
    digitalWrite(TIRE_LR,ON); // Open valve to tyre
    digitalWrite(AIR_OUT,ON); // Open valve out

    // Measure base
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_URHLEYPING,tiretoken); // Change colour of tyre to violet
      timer_deflate_LRT = timer_deflate_LRT+1000;
    }

    //if(millis() - timer_deflate_LRT > interval_deflate_LRT) // If it's time to measure
    if(timer_deflate_LRT >= interval_deflate_LRT)
    {
      tiretoken = 2; //Go to next tyre
      read_LRT(); // Read pressure
      updateValues();
      timer_deflate_LRT = 0;
      timer_measure = millis();
    }
  } // Decrement pressure function closes

  if(selectedPressure_LRT - pressure_LRT>0.25) // If pressure is too low
  {
    digitalWrite(TIRE_LR,ON); // Open valve to tyre
    digitalWrite(AIR_IN,ON); // Open valve for air in

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_LRT = timer_inflate_LRT+1000;
    }

    if(timer_inflate_LRT >= interval_inflate_LRT)
    {
      tiretoken = 2; //Go to next tyre
      read_LRT(); // Read Left Rear tyre
      updateValues(); // Update valuesn
      timer_inflate_LRT = 0; // Reset counter
      timer_measure = millis();
    }
  }// Increment pressure function closes

  else if(((pressure_LRT)-(selectedPressure_LRT))<=0.25 && (((selectedPressure_LRT) - (pressure_LRT))<=0.25 ))
  {
    tiretoken = 2;
    timer_inflate_LRT = 0;
    timer_deflate_LRT = 0;
    timer_measure = millis();
  }
} //End of adjustLRT

//Adjust Left Front Tire
void adjustLFT()
{
  timerSelector();
  //DEFLATE
  if(pressure_LFT - selectedPressure_LFT > 0.25) // If pressure is too high
  {
    digitalWrite(TIRE_LF,ON); // Open valve to tyre
    digitalWrite(AIR_OUT,ON); // Open valve to let out air

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_URHLEYPING,tiretoken); // Change colour of tyre to violet
      timer_deflate_LFT = timer_deflate_LFT + 1000;
    }

    if(timer_deflate_LFT >= interval_deflate_LFT) // If it's time to measure
    {
      tiretoken = 3; //Go to next tyre
      read_LFT(); // Read pressure
      updateValues(); // Update values
      timer_deflate_LFT = 0; //Reset counter
      timer_measure = millis();
    }

  }// DEFLATE closes

  // INFLATE
  if(selectedPressure_LFT - pressure_LFT > 0.25) 
  {
    digitalWrite(TIRE_LF,ON);
    digitalWrite(AIR_IN,ON); 

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); 
      previousMillis2 = millis(); 
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_LFT = timer_inflate_LFT + 1000;
    }

    if(timer_inflate_LFT >= interval_inflate_LFT) // If it's time to measure
    {
      tiretoken = 3; // Let us advance to next tire
      read_LFT(); // Read Left Front Tyre
      updateValues(); // Update valuesn
      timer_inflate_LFT = 0; // Reset counter
      timer_measure = millis();
    }
  }// INFLATE closes

  else if(((pressure_LFT)-(selectedPressure_LFT))<=0.25 && (((selectedPressure_LFT) - (pressure_LFT))<=0.25 ))
  {
    tiretoken = 3;
    timer_inflate_LFT = 0;
    timer_deflate_LFT = 0;
    timer_measure = millis();
  }

}// adjustLFT ends

//To adjust Right Front Tyre
void adjustRFT()
{
  timerSelector();
  // DEFLATE
  if(pressure_RFT - selectedPressure_RFT > 0.25) // If pressure is too high
  {
    digitalWrite(TIRE_RF,ON); // Open valve to tyre
    digitalWrite(AIR_OUT,ON); // Open valve to let out air

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_URHLEYPING,tiretoken); // Change colour of tyre to violet
      timer_deflate_RFT = timer_deflate_RFT+1000;
    }

    //if(millis() - timer_deflate_LRT > interval_deflate_LRT) // If it's time to measure
    if(timer_deflate_RFT >= interval_deflate_RFT)
    {
      tiretoken = 4; //Go to next tyre
      read_RFT(); // Read pressure
      updateValues();
      timer_deflate_RFT = 0;
      timer_measure = millis();
    }
  } // DEFLATE Close

  // INFLATE
  if(selectedPressure_RFT - pressure_RFT>0.25) // If pressure is too low
  {
    digitalWrite(TIRE_RF,ON); // Open valve to tyre
    digitalWrite(AIR_IN,ON); // Open valve for air in

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_INNDAELING,tiretoken);
      timer_inflate_RFT = timer_inflate_RFT+1000;
    }

    if(timer_inflate_RFT >= interval_inflate_RFT)
    {
      tiretoken = 4; //Go to next tyre
      read_LRT(); // Read Left Rear tyre
      updateValues(); // Update valuesn
      timer_inflate_LRT = 0; // Reset counter
      timer_measure = millis();
    }
  }// Increment pressure function closes

  else if(((pressure_RFT)-(selectedPressure_RFT))<=0.25 && (((selectedPressure_RFT) - (pressure_RFT))<=0.25 ))
  {
    tiretoken = 4;
    timer_inflate_RFT = 0;
    timer_deflate_RFT = 0;
    timer_measure = millis();
  }
}// Close adjustRFT

//To adjust Right Rear Tyre
void adjustRRT()
{
  timerSelector();
  // DEFLATE
  if(pressure_RRT -selectedPressure > 0.25) // If pressure is too high
  {
    digitalWrite(TIRE_RR,ON); // Open valve to tyre
    digitalWrite(AIR_OUT,ON); // Open valve to let out air

    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      tirePaint(C_URHLEYPING,tiretoken); // Change colour of tyre to violet
      timer_deflate_RRT = timer_deflate_RRT + 1000;
    }

    if(timer_deflate_RRT >= interval_deflate_RRT) // If it's time to measure
    {
      tiretoken = 1; //Go to next tyre
      read_RRT(); // Read pressure
      updateValues(); // Update values
      timer_deflate_RRT = 0; // Reset counter
      timer_measure = millis();
    }

  }// DEFLATE closes

  // INFLATE
  if(selectedPressure - pressure_RRT > 0.25) // If pressure is too low
  {
    digitalWrite(TIRE_RR,ON); // Open valve to tyre
    digitalWrite(AIR_IN,ON); // Open valve for air in
    // Measure valve base pressure
    if(millis() - previousMillis2 > 1000) // If it's time to measure
    {
      updateBaseValue(); // Update measurement on base valve (experimental)
      previousMillis2 = millis(); // Reset counter
      timer_inflate_RRT = timer_inflate_RRT + 1000;
      tirePaint(C_INNDAELING,tiretoken); //Change colour on tyre
    }

    if(timer_inflate_RRT > interval_inflate_RRT) // If it's time to measure
    {
      tiretoken = 1; // Go to next tyre
      read_RRT(); // Read Left Rear tyre
      updateValues(); // Update valuesn
      timer_inflate_RRT = 0; // Reset counter
      timer_measure = millis();
    }
  }// Increment pressure function closes

  else if(((pressure_RRT)-(selectedPressure_RRT))<=0.25 && (((selectedPressure_RRT) - (pressure_RRT))<=0.25 ))
  {
    tiretoken = 1;
    timer_inflate_RRT = 0;
    timer_deflate_RRT = 0;
    timer_measure = millis();
  }
    
}// Close adjustRRT