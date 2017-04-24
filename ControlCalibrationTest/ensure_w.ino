//Values specific for the robot
double w_max_v0 = 6.202;  //rad/s of the robot//
double v_max_w0 = 0.2700; //m/s of the robot
double max_vel = 3.929;   //rad/s of the wheel

//variables
double vel_rl_max = 0;
double vel_rl_min = 0;
double vel_r_d = 0;
double vel_l_d = 0;

void ensure_w(double v, double w) {
  //This function ensures that w is respected as best as possible
  //by sacrificing v.
  
  //1. Limit v, w from controller to + / - of their max
  w = max(min(w, w_max_v0), -w_max_v0);
  v = max(min(v, v_max_w0), -v_max_w0);

  //2. Compute desired vel_r, vel_l needed to ensure w
  vel_r_d = (2 * v + w * L) / (2 * R); //This is the uni_to_diff
  vel_l_d = (2 * v - w * L) / (2 * R); //*

  //3. Find the max and min vel_r / vel_l
  vel_rl_max = max(vel_r_d, vel_l_d);
  vel_rl_min = min(vel_r_d, vel_l_d);

  //4. Shift vel_r and vel_l if they exceed max / min vel
  if (vel_rl_max > max_vel) {
    vel_r = vel_r_d - vel_rl_max + max_vel;
    vel_l = vel_l_d - vel_rl_max + max_vel;
  } else if (vel_rl_min < -max_vel) {
    vel_r = vel_r_d - vel_rl_min - max_vel;
    vel_l = vel_l_d - vel_rl_min - max_vel;
  } else {
    vel_r = vel_r_d;
    vel_l = vel_l_d;
  }
}
