// Ef við viljum lita Menu hnappinn
void toggleMenu()
{
  if(adjust == true)
  {
    tft.fillRect(MENU_X, MENU_Y, (MENU_W-20), MENU_H, DARKGREEN);    // Teiknum menu takka dökkgrænan ef við erum í stillingu
  }
  else
  tft.drawRect(MENU_X, MENU_Y, (MENU_W-20), MENU_H, WHITE);
}