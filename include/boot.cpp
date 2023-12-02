void boot()
{
// Define outputs
  pinMode(AIR_IN, OUTPUT);
  pinMode(TIRE_RR, OUTPUT);
  pinMode(TIRE_RF, OUTPUT);
  pinMode(TIRE_LF, OUTPUT);
  pinMode(TIRE_LR, OUTPUT);
  pinMode(AIR_OUT, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT); // Baklýsing PWM
  pinMode(RESET,OUTPUT); // Reset á skjá
  air_base_close();

// Definitions for TFT
  digitalWrite(RESET,LOW); // Reset display
  delay(10); // delay
  digitalWrite(RESET,HIGH); // Start display
  delay(100); // Töf
  tft.begin(); // enable display
  tft.fillScreen(ILI9341_BLACK); // Clear display and make background black
  tft.setRotation(1); // Landscape
  tft.setSPISpeed(4000000); // Speed of the SPI 

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