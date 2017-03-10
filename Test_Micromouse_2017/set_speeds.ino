int vel_r_new = 0;
int vel_l_new = 0;

boolean vel_r_prev = true;
boolean vel_l_prev = true;

void set_speeds(double v , double w) {
  ensure_w(v, w);

  vel_r_new = abs(vel_r);
  vel_l_new = abs(vel_l);

  vel_r_new = map(vel_r_new, 0, 5, 200, 255);
  vel_l_new = map(vel_l_new, 0, 5, 200, 255);

  constrain(vel_r_new, 200, 255);
  constrain(vel_l_new, 200, 255);

  RightMotor.setSpeed(vel_r_new);
  LeftMotor.setSpeed(vel_l_new);

  if (vel_r_new == vel_r > 0) {
    vel_r_new = vel_r > 0;
  } else {
    RightMotor.run(RELEASE);
    vel_r_new = vel_r > 0;
  }

  if (vel_l_new == vel_l > 0) {
    vel_l_new = vel_l > 0;
  } else {
    LeftMotor.run(RELEASE);
    vel_l_new = vel_l > 0;
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
