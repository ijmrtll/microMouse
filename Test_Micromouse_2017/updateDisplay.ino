int page = 1;
int lcdInterval = 5;
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
  if (lastUpdate > currentTime)   // check for time wrap around
    lastUpdate = currentTime;

  if (currentTime > lastUpdate + 100) {
    lastUpdate = currentTime;
    lcd.clear();
    lcdPage(page);
    if (page > 4) {
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
  lcd.setCursor(0, 0);
  lcd.print(F("vel_r: "));
  lcd.print(vel_r_new, 2);

  lcd.setCursor(0, 1);
  lcd.print(F("vel_l: "));
  lcd.print(vel_l_new, 2);

}

void pFour() {
  lcd.setCursor(0, 0);
  lcd.print(F("v: "));
  lcd.print(v);

  lcd.setCursor(0, 1);
  lcd.print(F("w: "));
  lcd.print(w);

}

void pFive() {

}
