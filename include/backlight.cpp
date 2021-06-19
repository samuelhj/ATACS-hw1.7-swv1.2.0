/*  To adjust backlight
*   Later 
*   Hvar er BACKLIGHT eiginlega skilgreint?
*/

int backlightAdjust(int val)
{
  
  if(backlight_auto == true)
  {
    //uint16_t a;
    val = analogRead(LITE_SENSE);
    val = val/4;
  }

  if(debug == true)
  {
    uint16_t a;
    a = analogRead(LITE_SENSE);
    Serial.print("Backlight PWM value: ");
    Serial.println(val);
    Serial.println(" ");
    Serial.print("Backlight sensor value: ");
    Serial.println(a);
    Serial.println(" ");
  }

  analogWrite(BACKLIGHT,val); // Breytum birtustigi
  return val; // Skilum völdu gildi
}

