int page = 1;
int lcdInterval = 5;
int updateInterval = 200;
static unsigned long lastPage = 0;

void updateDisplay() {

  static unsigned long lastUpdate = millis();
  unsigned long currentTime;

  currentTime = millis();

  if (currentTime - lastPage > 1000 * lcdInterval) {
    lastPage = currentTime;
    page++;
  }

  // check time since last update
  if (lastUpdate > currentTime) {  // check for time wrap around
    lastUpdate = currentTime;
  }

  if (currentTime > lastUpdate + updateInterval) {
    lastUpdate = currentTime;
    lcd.clear();
    lcdPage(page);
    if (page > 2) {
      page = 1;
    }
  }
}
                      

void lcdPage(int page) {
  switch (page) {
    case 1:
      pOne();
      lcdInterval = 5;
      break;
    case 2:
      pTwo();
      lcdInterval = 5;
      break;
    case 3:
      pThree();
      lcdInterval = 5;
      break;
    case 4:
      pFour();
      lcdInterval = 2;
      break;
    case 5:
      pFive();
      lcdInterval = 5;
      break;
  }
}

void pOne() {
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print(F("x:"));
  lcd.print(x_new, 2);

  lcd.setCursor(8, 0);
  lcd.print(F("xg:"));
  lcd.print(x_g, 2);

  //Line 2
  lcd.setCursor(0, 1);
  lcd.print(F("y:"));
  lcd.print(y_new, 2);

  lcd.setCursor(8, 1);
  lcd.print(F("yg:"));
  lcd.print(y_g, 2);
}

void pTwo() {
  //Line 1
  lcd.setCursor(0, 0);
  lcd.print(F("Aa:"));
  lcd.print(theta_new, 2);

  lcd.setCursor(8, 0);
  lcd.print(F("Ag:"));
  lcd.print(theta_g, 2);

  //Linea 2
  lcd.setCursor(0, 1);
  lcd.print(F("ux:"));
  lcd.print(u_x, 2);

  lcd.setCursor(8, 1);
  lcd.print(F("uy:"));
  lcd.print(u_y, 2);
}

void pThree() {

}

void pFour() {
}

void pFive() {
}

void createLCDChars() {
  int lvl = 0;
  byte arry[8];
  for (int a = 7; a >= 0; a--)
  {
    for (int b = 0; b <= 7; b++)
    {
      if (b >= lvl)
        arry[b] = B11111;       // solid
      else
        //arry[b] = B00000;     // blank row
        arry[b] = B10001;       // hollow but with sides
    }
    lcd.createChar(a, arry);
    lvl++;
  }
}
