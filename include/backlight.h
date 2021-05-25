/*  To adjust backlight
*   Later 
*
*/

int backlightAdjust(int val)
{
    analogWrite(BACKLIGHT,val); // Breytum birtustigi
    return val; // Skilum völdu gildi
    
}
