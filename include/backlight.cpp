/*  To adjust backlight
*   Later 
*   Hvar er BACKLIGHT eiginlega skilgreint?
*/
int backlightAdjust(int val)
{
  
  if(backlight_auto == true)
  {
    //uint16_t a;
    val = analogRead(LIGHT_SENSE);
    if(val < 65)
      val = 100;
    if(val > 65)
      val = 255;
  
  //  val = val/4;
  }

  if(debug == true)
  {
    uint16_t a;
    a = analogRead(LIGHT_SENSE);
    Serial.print("Backlight PWM value: ");
    Serial.println(val);
    Serial.println(" ");
    Serial.print("Backlight sensor value: ");
    Serial.println(a);
    Serial.println(" ");
  }

  analogWrite(BACKLIGHT,val); // Write to backlight
  return val; // Return the selected value 
}

