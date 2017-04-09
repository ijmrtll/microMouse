#include <AFMotor.h>
AF_DCMotor RightMotor(1);
AF_DCMotor LeftMotor(3);


#include <LiquidCrystal.h>
LiquidCrystal lcd(53, 52, 50, 51, 48, 49);

#define encoderLeftPinA  2
#define encoderLeftPinB  5

#define encoderRightPinA  18
#define encoderRightPinB  A0

volatile  long encoderLeftPos = 0;
volatile  long encoderRightPos = 0;


void setup() {

  RightMotor.setSpeed(255);
  LeftMotor.setSpeed(255);
  RightMotor.run(RELEASE);
  LeftMotor.run(RELEASE);

  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);
  
  pinMode(encoderRightPinA, INPUT_PULLUP);
  digitalWrite(encoderRightPinA, HIGH);
  pinMode(encoderRightPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), doEncoderLeft, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(digitalPinToInterrupt(encoderRightPinA), doEncoderRight, CHANGE);  // encoder pin on interrupt 1 - pin 3

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print(F(" ..MicroMouse.. "));

  //BackLight
  pinMode(22 , OUTPUT);
  pinMode(23 , OUTPUT);
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);

  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print(F("  ..Running..  "));

}

long LeftPos_mm = 0;
long RightPos_mm = 0;

void loop() {
  RightMotor.run(FORWARD);
  LeftMotor.run(BACKWARD);

  LeftPos_mm = encoderLeftPos * 32 * 4 / 69;
  RightPos_mm = encoderRightPos * 32 * 4 / 69;

  lcd.setCursor(0, 1);
  lcd.print(F("L: "));
  lcd.print(LeftPos_mm, DEC);

  lcd.setCursor(9, 1);
  lcd.print(F("R: "));
  lcd.print(RightPos_mm, DEC);

  if (LeftPos_mm <= -100 && RightPos_mm >= 100) {
    RightMotor.run(RELEASE);
    LeftMotor.run(RELEASE);
    while (1) {
    }
  }

  delay(100);
}
