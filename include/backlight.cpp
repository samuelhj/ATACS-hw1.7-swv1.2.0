/*  To adjust backlight
*   Later 
*   Hvar er BACKLIGHT eiginlega skilgreint?
*/

int backlightAdjust(int val)
{
    analogWrite(BACKLIGHT,val); // Breytum birtustigi
    return val; // Skilum völdu gildi
    
}
