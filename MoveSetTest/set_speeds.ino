double vel_r_new = 0;
double vel_l_new = 0;

boolean vel_r_prev = true;
boolean vel_l_prev = true;
boolean flagR = true;
boolean flagL = true;

//speed Limits of the wheels
float pdiff = 1.05;

int minDigVell = 20;
int maxDigVell = 100;

int minDigVelr = 20;
int maxDigVelr = pdiff*maxDigVell;

float map1();
void set_speeds(double v , double w) {
  vel_r_new = abs(vel_r);
  vel_l_new = abs(vel_l);

  vel_r_new = map1(vel_r_new, 0, max_vel, minDigVelr, maxDigVelr);
  vel_l_new = map1(vel_l_new, 0, max_vel, minDigVell, maxDigVell);
  vel_r_new = constrain(vel_r_new, minDigVelr, maxDigVell);
  vel_l_new = constrain(vel_l_new, minDigVell, maxDigVell);

  //Set speed before moving
  RightMotor.setSpeed(vel_r_new);
  LeftMotor.setSpeed(vel_l_new);

  //Stop the motor before a change in direction
  //for the right motor
  if (vel_r_prev != vel_r > 0) {
    RightMotor.run(RELEASE);
    vel_r_prev = vel_r > 0;
  }
  //for the left motor
  if (vel_l_prev != vel_l > 0) {
    LeftMotor.run(RELEASE);
    vel_l_prev = vel_l > 0;
  }

  //Set the direction and move the motors or apply a break if vel = 0
  if (vel_r < 0) {
    RightMotor.run(BACKWARD);
    flagR = true;
  } else if (vel_r > 0) {
    RightMotor.run(FORWARD);
    flagR = true;
  } else {
    if (vel_r_prev && flagR) {
      RightMotor.run(BACKWARD);
      delay(10);
      RightMotor.run(RELEASE);
      flagR = false;
    } else {
      RightMotor.run(FORWARD);
      delay(10);
      RightMotor.run(RELEASE);
      flagR = false;
    }
  }

  if (vel_l < 0) {
    LeftMotor.run(BACKWARD);
    flagL = true;
  } else if (vel_l > 0) {
    LeftMotor.run(FORWARD);
    flagL = true;
  } else {
    if (vel_l_prev && flagL) {
      LeftMotor.run(BACKWARD);
      delay(10);
      LeftMotor.run(RELEASE);
      flagL = false;
    } else {
      LeftMotor.run(FORWARD);
      delay(10);
      LeftMotor.run(RELEASE);
      flagL = false;
    }
  }
}

float map1(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
