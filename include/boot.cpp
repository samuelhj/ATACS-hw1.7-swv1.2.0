void boot()
{
// Skilgreinum eftirfarandi sem útganga
  pinMode(AIR_IN, OUTPUT);
  pinMode(TIRE_RR, OUTPUT);
  pinMode(TIRE_RF, OUTPUT);
  pinMode(TIRE_LF, OUTPUT);
  pinMode(TIRE_LR, OUTPUT);
  pinMode(AIR_OUT, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT); // Baklýsing PWM
  pinMode(RESET,OUTPUT); // Reset á skjá
  air_base_close();

// Næst koma skilgreiningar fyrir TFT skjá
  digitalWrite(RESET,LOW); // Endurræsing á skjá.
  delay(10); // töf
  digitalWrite(RESET,HIGH); // Ræsum skjá
  delay(100); // Töf
  tft.begin(); // Virkjum skjáinn
  tft.fillScreen(ILI9341_BLACK); // Hreinsum skjáinn og skrifum svartan bakgrunn.
  tft.setRotation(1); // Landscape
  tft.setSPISpeed(4000000);

// Read from EEPROM
  backlight_selected = EEPROM.read(EBACKLIGHT);
  EEPROM.get(EPRESSURE,selectedPressure); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_LRT,selectedPressure_LRT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_LFT,selectedPressure_LFT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_RFT,selectedPressure_RFT); // Lesum þrýsting úr minni
  EEPROM.get(EPRESSURE_RRT,selectedPressure_RRT); // Lesum þrýsting úr minni
  debug = EEPROM.read(EDEBUG);
  
  // Boot message
  bootMessage();

  read_LRT(); // Lesum vinstra afturdekk
  read_LFT(); // Lesum vinstra framdekk
  read_RFT(); // Lesum hægra framdekk
  read_RRT(); // Lesum hægra afturdekki
  tft.fillScreen(BLACK); // Clean monitor
  tft.setTextColor(WHITE); 
  drawMain(); 
}