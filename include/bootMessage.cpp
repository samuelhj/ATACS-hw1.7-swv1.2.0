 void bootMessage()
 {
  delay(500); //Gefum skjá tækifæri á að ræsa sig.
  backlightAdjust(255); // Kveikjum á baklýsingu.
  tft.setTextSize(2); // Stærð eitt fyrir texta í booti
  tft.setTextColor(GREEN); // Grænn texti fyrir smá nostalgíu 
 
  //tft.print("Bunadur nr: ");
  //tft.println(SERIALNUMBER);
  tft.println("ATACS Version: "); // Útgáfa
  tft.println(VERSION); // Utgáfa
  tft.println(BUILDDATE); //Dagsetning útgáfu
  tft.println("Hofundur:");
  tft.println("Samuel Hjaltalin");
  tft.println("https://ulfraf.space");

  
  if(debug == true)
  {
    Serial.begin(115200);
    Serial.println("ATACS Version: ");
    Serial.println(VERSION);
    Serial.println(BUILDDATE);
    Serial.println("Hofundur: ");
    Serial.println("Samuel Hjaltalin");
    Serial.println("https://ulfr.net/");
  }
 }
