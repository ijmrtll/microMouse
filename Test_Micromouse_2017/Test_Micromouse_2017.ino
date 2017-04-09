#include <Math.h>
#include <AFMotor.h>
#include <PID_v1.h>
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

// Odometry variable
volatile long right_ticks = 0;
volatile long left_ticks = 0;
volatile long prev_right_ticks = 0;
volatile long prev_left_ticks = 0;

#define ticks_per_rev 64
#define R  0.0345
#define L 0.075

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

const double m_per_tick = 2 * (3.1416) * R / ticks_per_rev;

//wheels speeds
double vel_r;
double vel_l;


//idk
unsigned long initTime;
unsigned long finalTime;
unsigned long dt;

double v = 1;
double w = 0;

double x_g = 0;
double y_g = 0;

double goal_x[] = {0.4, 0, 0.4, 1};
double goal_y[] = {0.5, 0.5, 0.1, 0.6};

double d_stop = 0.05;


//PID
const double Kp = 5;
const double Ki = 0;
const double Kd = 0;
double u_x = 0;
double u_y = 0;
double theta_g = 0;

PID myPID(&theta, &w, &theta_g, Kp, Ki, Kd, REVERSE);

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
  lcd.clear();
  lcd.print(F(" ..MicroMouse.. "));

  //BackLight
  pinMode(22 , OUTPUT);
  pinMode(23 , OUTPUT);
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);

  delay(1000);
  lcd.setCursor(0, 0);
  //lcd.print(F("  ..Running..  "));
  lcd.clear();
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-5, 5);

}

int i = 0;
void loop() {
  //initTime = millis();
  update_odometry();
  GoToGoal();

  set_speeds(v, w);


  if (sqrt((x_g - x_new) * (x_g - x_new) + (x_g - x_new) * (x_g - x_new)) <= d_stop) {
    RightMotor.run(RELEASE);
    LeftMotor.run(RELEASE);
    i++;
    delay(10);
    if (i > 3) {
      myPID.SetMode(MANUAL);
      RightMotor.run(RELEASE);
      LeftMotor.run(RELEASE);
      v = 0;
      w = 0;
      while (1) {
      }
    }
    delay(1000);
  }

  updateDisplay();
  delay(10);
  //finalTime = millis();
}
