#include <AFMotor.h>
AF_DCMotor RightMotor(4);
AF_DCMotor LeftMotor(1);


#define encoderLeftPinA  2
#define encoderLeftPinB  6

#define encoderRightPinA  18
#define encoderRightPinB  19

volatile  long encoderLeftPos = 0;
volatile  long encoderRightPos = 0;

int maxDigVel = 60;
float pdiff = 1.1;

void setup() {
  pinMode(encoderLeftPinA, INPUT_PULLUP);
  pinMode(encoderLeftPinB, INPUT_PULLUP);
  pinMode(encoderRightPinA, INPUT_PULLUP);
  pinMode(encoderRightPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderLeftPinA), doEncoderLeft, CHANGE);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(digitalPinToInterrupt(encoderRightPinA), doEncoderRight, CHANGE);  // encoder pin on interrupt 1 - pin 3
  
  RightMotor.setSpeed(int(pdiff*maxDigVel));
  LeftMotor.setSpeed(maxDigVel);
  RightMotor.run(FORWARD);
  LeftMotor.run(RELEASE);
  Serial.begin(115200);
}

double rev = 10;
int ticks_rev = 720;

void loop() {
  Serial.print("Right Encoder: ");
  Serial.println(encoderRightPos);
  Serial.print("Left  Encoder: ");
  Serial.println(encoderLeftPos);
  
  if (encoderRightPos >= rev*ticks_rev || encoderLeftPos >= rev*ticks_rev) {
    RightMotor.run(BACKWARD);
    LeftMotor.run(RELEASE);
    delay(10);
    RightMotor.run(RELEASE);
    LeftMotor.run(RELEASE);
    while (1)
    {
    }
  }
  delay(10);
}

void doEncoderLeft() {
  if (digitalRead(encoderLeftPinA) == digitalRead(encoderLeftPinB)) {
    encoderLeftPos++;
  } else {
    encoderLeftPos--;
  }
}

void doEncoderRight() {
  if (digitalRead(encoderRightPinA) == digitalRead(encoderRightPinB)) {
    encoderRightPos++;
  } else {
    encoderRightPos--;
  }
}
