#include <Math.h>
#include <moving_average.h>
#include <AFMotor.h>
#include <PID_v1.h>
AF_DCMotor RightMotor(4);
AF_DCMotor LeftMotor(1);

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
#define frontSensorPin A8
#define maxDistanceFrontSensor 100 //cm
MovingAverage<int, 3> frontSensorAverage(maxDistanceFrontSensor);
int frontSensorDistance;

//Right IR Sensor
#define rightSensorPin A9
#define maxDistanceRightSensor 100 //cm
MovingAverage<int, 3> rightSensorAverage(maxDistanceFrontSensor);
int rightSensorDistance;

//Left IR Sensor
#define leftSensorPin A10
#define maxDistanceLeftSensor 100 //cm
MovingAverage<int, 3> leftSensorAverage(maxDistanceFrontSensor);
int leftSensorDistance;

/*End sensors config and moving average config
  ===========================================
*/

#define encoderLeftPinA  18
#define encoderLeftPinB  19

#define encoderRightPinA  2
#define encoderRightPinB  6

volatile  long encoderLeftPos = 0;
volatile  long encoderRightPos = 0;

// Odometry variable
volatile long right_ticks = 0;
volatile long left_ticks = 0;
long prev_right_ticks = 0;
long prev_left_ticks = 0;

const double ticks_per_rev = 720;
const double R = 0.0345; //cm
const double L = 0.0650; //cm

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


//idk
unsigned long initTime = 0;
unsigned long finalTime = 0;
unsigned long dt = 0;

double v = 0.025;
double w = 0;

double x_g = 0.025;
double y_g = 0;

double goal_x[] = {0.4, 0, 0, 0};
double goal_y[] = {0, 0, 0, 0};

double d_stop = 0.01;


//PID
const double Kp = 0.5;
const double Ki = 0.01;
const double Kd = 0;
double u_x = 0;
double u_y = 0;
double theta_g = 0;

PID myPID(&theta_new, &w, &theta_g, Kp, Ki, Kd, REVERSE);

void setup() {

  RightMotor.setSpeed(255);
  LeftMotor.setSpeed(255);
  RightMotor.run(RELEASE);
  LeftMotor.run(RELEASE);

  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);

  pinMode(encoderRightPinA, INPUT_PULLUP);
  pinMode(encoderRightPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), doEncoderLeft, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(digitalPinToInterrupt(encoderRightPinA), doEncoderRight, CHANGE);  // encoder pin on interrupt 1 - pin 3

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(F(" ..MicroMouse.. "));

  //BackLight
  pinMode(22 , OUTPUT);
  digitalWrite(22, LOW); // LCD backlight GND

  delay(1000);
  lcd.setCursor(0, 0);
  //lcd.print(F("  ..Running..  "));
  lcd.clear();
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-5, 5);
  pinMode(41, INPUT_PULLUP);
}

int i = 0;
void loop() {
  //initTime = millis();
//  while (1) {
//    if (digitalRead(41) == LOW) {
//      RightMotor.setSpeed(50);
//      LeftMotor.setSpeed(50);
//      RightMotor.run(BACKWARD);
//      LeftMotor.run(BACKWARD);
//    } else {
//      RightMotor.run(RELEASE);
//      LeftMotor.run(RELEASE);
//    }
//
//    update_odometry();
//    updateDisplay();
//    delay(10);
//  }
  
  update_odometry();
  GoToGoal();
  set_speeds(v, w);

  if (sqrt((x_g - x_new) * (x_g - x_new) + (y_g - y_new) * (y_g - y_new)) <= d_stop) {
    RightMotor.run(BACKWARD);
    LeftMotor.run(BACKWARD);
    delay(10);
    RightMotor.run(RELEASE);
    LeftMotor.run(RELEASE);
    i++;
    delay(10);
    if (i >= 4) {
      myPID.SetMode(MANUAL);
      RightMotor.run(RELEASE);
      LeftMotor.run(RELEASE);
      v = 0;
      w = 0;
      //      lcd.clear();
      //      lcd.setCursor(0, 0);
      //      lcd.print(F(" ..MicroMouse.. "));
      //      lcd.setCursor(0, 1);
      //      lcd.print(F("   ...Done...   "));

      while (1) {
      }
    }
    delay(1000);
  }

  updateDisplay();
  delay(10);
  //finalTime = millis();
}
