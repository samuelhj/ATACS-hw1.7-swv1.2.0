
void updateBaseValue() // Við uppfærum gildi á kistu
{
    // Hreinsum þar sem gildin eru á skjánum.
    tft.fillRect(120,60,240,18,BLACK); // Hreinsum gildi fyrir þrýsting kistu
    tft.fillRect(130,140,60,48,BLACK); // Hreinsum gildi fyrir valinn þrýsting burt.

    // Við skrifum mælt gildi á kistunni
    float basePressure = 0.0;
    basePressure = readPressure();
    pressure_ALL = basePressure; // þrýstingur úr öllum dekkjum
    tft.setTextSize(2);
    tft.setCursor(125,60);
    tft.println(basePressure);
    tft.setCursor(175,60);
    tft.println(" PSI");

    // ef það er kveikt á debug
    if(debug == true)
    {
      // Skrifum valið gildi á skjá
      tft.setTextSize(2); // Stillum textastærð á 2
      tft.setCursor(130,160); // Veljum staðsetningu
      float pressureall = pressure_ALL - selectedPressure;
      pressureall = fabs(pressureall);
      tft.println((pressure_ALL - selectedPressure)); // Skrifum út gildið.
      //
      uint16_t sekundur = millis()/1000;
      tft.println(interval_LFT);
      tft.setCursor(130,140); // Veljum staðsetningu
      tft.println(tiretoken);
    }
} //updateBaseValue function closes

    void updateValues() // Við uppfærum gildi
{
    // Hreinsum þar sem gildin eru á skjánum.
    //updateBaseValue();
    tft.setTextSize(2);
    tft.fillRect(20,170,60,50, BLACK); // Hreinsum gildið fyrir LRT
    tft.fillRect(20,20,60,50,BLACK); // Hreinsum gildið fyrir LFT
    tft.fillRect(240,20,60,50,BLACK); // Hreinsum gildið fyrir RFT
    tft.fillRect(240,170,60,50,BLACK); // Hreinsum gildið fyrir RRT
    //tft.fillRect(110,60,220,18,BLACK); // Hreinsum gildi fyrir hitastig

    // Skrifum mæld gildi.
    tft.setCursor(20,20); // Staðsetjum okkur v/m ofan
    if(selectedTire == 2)
    {
      tft.setTextColor(GREEN);
    }
    else
    {
      tft.setTextColor(WHITE);
    }
    tft.println(selectedPressure_LFT);
    tft.setCursor(20,40); // Erum fyrir neðan.
    tft.setTextColor(GREEN);
    tft.println(pressure_LFT); // Skrifum út gildi á staðsetningu

    tft.setCursor(240,20); // Staðsetjum okkur hægra megin að ofan
    if(selectedTire == 3)
    {
      tft.setTextColor(GREEN);
    }
    else
    {
      tft.setTextColor(WHITE);
    }
    tft.println(selectedPressure_RFT); // Valinn þrýstingur
    tft.setTextColor(GREEN);
    tft.setCursor(240,40); // Skrifum á RFT
    tft.println(pressure_RFT);


    tft.setCursor(20,170);
    if(selectedTire == 1)
    {
      tft.setTextColor(GREEN);
    }
    else
    {
      tft.setTextColor(WHITE);
    }
    tft.println(selectedPressure_LRT);
    tft.setTextColor(GREEN);
    tft.setCursor(20,190); // Skrifum á LRT
    tft.println(pressure_LRT);

    if(selectedTire == 4)
    {
      tft.setTextColor(GREEN);
    }
    else
    {
      tft.setTextColor(WHITE);
    }

    tft.setCursor(240,170);
    tft.println(selectedPressure_RRT);
    tft.setTextColor(GREEN);
    tft.setCursor(240,190); // Skrifum á RRT
    tft.println(pressure_RRT);

    // Skrifum menu textann
    tft.setTextColor(WHITE);
    tft.setTextSize(3); // Textastærð 3.
    tft.setCursor(130,20); // Setjum byrjunarreit
    tft.println("MENU"); // Skrifum Menu

    warningCheck(); //Athugum hvort viðvörun gildi á einhverju dekki
}