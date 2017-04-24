double vel_r_new = 0;
double vel_l_new = 0;

boolean vel_r_prev = true;
boolean vel_l_prev = true;
int minDigVelr = 30;
int maxDigVelr = 50;

int minDigVell = 30;
int maxDigVell = 50;

float map1();

void set_speeds(double v , double w) {
  ensure_w(v, w);

  vel_r_new = abs(vel_r);
  vel_l_new = abs(vel_l);
  
  vel_r_new = map1(vel_r_new, 0, max_vel, minDigVelr, maxDigVelr);
  vel_l_new = map1(vel_l_new, 0, max_vel, minDigVell, maxDigVell);

  vel_r_new = constrain(vel_r_new, minDigVelr, maxDigVell);
  vel_l_new = constrain(vel_l_new, minDigVell, maxDigVell);

  RightMotor.setSpeed(vel_r_new);
  LeftMotor.setSpeed(vel_l_new);

  if (vel_r_prev == vel_r > 0) {
    vel_r_prev = vel_r > 0;
  } else {
    RightMotor.run(RELEASE);
    vel_r_prev = vel_r > 0;
  }

  if (vel_l_prev == vel_l > 0) {
    vel_l_prev = vel_l > 0;
  } else {
    LeftMotor.run(RELEASE);
    vel_l_prev = vel_l > 0;
  }

  if (vel_r < 0)
    RightMotor.run(BACKWARD);
  else
    RightMotor.run(FORWARD);

  if (vel_l < 0)
    LeftMotor.run(BACKWARD);
  else
    LeftMotor.run(FORWARD);
}

float map1(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
