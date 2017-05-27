#include <moving_average.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(53, 52, 50, 51, 48, 49);
/*  The circuit:
   LCD RS pin to pin 53
   LCD E  pin to pin 52
   LCD D4 pin to pin 50
   LCD D5 pin to pin 51
   LCD D6 pin to pin 48
   LCD D7 pin to pin 49
   LCD R/W pin to GND
   LCD VSS pin to GND
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 12)

*/

/*Sensors config and moving average config
  ===========================================
*/
// Front IR Sensor
#define frontSensorPin A0
#define maxValFrontSensor 450 // digital value
#define minValFrontSensor 70 // digital value
MovingAverage<int, 3> frontSensorAverage(maxValFrontSensor);
int frontSensorVal;
float frontSensorDistance;

//Right IR Sensor
#define rightSensorPin A1
#define maxValRightSensor 450 // digital value
#define minValRightSensor 70 // digital value
MovingAverage<int, 3> rightSensorAverage(maxValRightSensor);
int rightSensorVal;
float rightSensorDistance;

//Left IR Sensor
#define leftSensorPin A2
#define maxValLeftSensor 450 // digital value
#define minValLeftSensor 70 // digital value
MovingAverage<int, 3> leftSensorAverage(maxValLeftSensor);
int leftSensorVal;
float leftSensorDistance;

/*End sensors config and moving average config
  ===========================================
*/

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  createLCDChars();  //LCD special characters

  lcd.setCursor(0, 0);
  lcd.print(F("Sensor"));
  lcd.setCursor(5, 1);
  lcd.print(F("Calibration"));
  //BackLight
  pinMode(22 , OUTPUT);
  digitalWrite(22, LOW); // LCD backlight GND
  delay(1000);
  //countDown();

}

void loop() {
  getDistances();
  updateDisplay();
  delay(10);
}

void countDown() {
  lcd.clear();
  for (int i = 10; i >= 0; i--) {
    if (i == 2) {
      lcd.setCursor(0, 1);
    }
    lcd.print(i);
    lcd.print(" ");
    delay(500);
  }
  lcd.setCursor(5, 1);
  for (int i = 0; i < 3; i++) {
    lcd.print(".");
    delay(500);
  }
  lcd.setCursor(9, 1);
  lcd.print(F("Ready!"));
  delay(500);
}
