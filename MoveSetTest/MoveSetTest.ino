#include <PID_v1.h>
#include <AFMotor.h>
AF_DCMotor RightMotor(4);
AF_DCMotor LeftMotor(1);

#include <LiquidCrystal.h>
LiquidCrystal lcd(53, 52, 50, 51, 48, 49);

#define encoderLeftPinA  2
#define encoderLeftPinB  6

#define encoderRightPinA  18
#define encoderRightPinB  19

volatile  long encoderLeftPos = 0;
volatile  long encoderRightPos = 0;

// Odometry variable
volatile long right_ticks = 0;
volatile long left_ticks = 0;
long prev_right_ticks = 0;
long prev_left_ticks = 0;

const double ticks_per_rev = 720;
const double R = 0.0345; // radious of the wheel
const double L = 0.0650; // cm

double Dr = 0;
double Dl = 0;
double Dc = 0;

double x = 0;
double y = 0;
double theta = 0;

double x_dt = 0;
double y_dt = 0;
double theta_dt = 0;

double theta_new = 0;
double x_new = 0;
double y_new = 0;

const double m_per_tick = 2 * (3.1416) * R / ticks_per_rev; // cm/tick

//wheels speeds
double vel_r = 0;
double vel_l = 0;

// distance to stop
double x_g = 0;
double y_g = 0;
double d_stop = 0.01;


//PID
const double Kp = 1.5;  // 1.5
const double Ki = 0.05; // 0.05
const double Kd = 0.15; // 0.15
double v = 0.1 * 0.27; // set to zero to not move. Range(0, 0.27)
double w = 0; // CV

//SetPoint (GOAL)
double target_x[] = {0.0, 0.1, 0.3, 0.3, 0.4, 0.0};
double target_y[] = {0.1, 0.1, 0.1, 0.0, 0.1, 0.0};
int nPoints = 6;

double goalPoint[] = {target_x[nPoints-1], target_y[nPoints-1]};

double theta_g = 0; //computed in loop

double u_x = 0;
double u_y = 0;
PID myPID(&theta_new, &w, &theta_g, Kp, Ki, Kd, DIRECT);

void setup() {
  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);
  pinMode(encoderRightPinA, INPUT_PULLUP);
  pinMode(encoderRightPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), doEncoderLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderRightPinA), doEncoderRight, CHANGE);

  // PID init
  myPID.SetSampleTime(100); // New Line
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-7, 7);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(F(" ..MicroMouse.. "));
  //BackLight
  pinMode(22 , OUTPUT);
  digitalWrite(22, LOW); // LCD backlight GND
  delay(1000);
  countDown();
}

int i = 0;
void loop() {
  update_odometry();
  x_g = target_x[i];
  y_g = target_y[i];
  u_x = x_g - x_new;
  u_y = y_g - y_new;
  theta_g = atan2(u_y, u_x);
  myPID.Compute();

  ensure_w(v, w);
  set_speeds(v, w);
  updateDisplay();

  isGoal();


}

void isGoal() {
  if (sqrt((x_g - x_new) * (x_g - x_new) + (y_g - y_new) * (y_g - y_new)) <= d_stop) {
    RightMotor.run(BACKWARD);
    LeftMotor.run(BACKWARD);
    delay(10);
    RightMotor.run(RELEASE);
    LeftMotor.run(RELEASE);
    i++;
    delay(10);
    if (x_g == goalPoint[0] && y_g == goalPoint[1]) {
      myPID.SetMode(MANUAL);
      RightMotor.run(RELEASE);
      LeftMotor.run(RELEASE);
      v = 0;
      w = 0;
      while (1) {
        updateDisplay();
      }
    }
    delay(1000);
  }
}

void countDown() {
  lcd.clear();
  for (int i = 10; i >= 0; i--) {
    if (i == 2) {
      lcd.setCursor(0, 1);
    }
    lcd.print(i);
    lcd.print(" ");
    delay(100);
  }
  lcd.setCursor(5, 1);
  for (int i = 0; i < 3; i++) {
    lcd.print(".");
    delay(50);
  }
  lcd.setCursor(9, 1);
  lcd.print(F("Ready!"));
  delay(500);
}
