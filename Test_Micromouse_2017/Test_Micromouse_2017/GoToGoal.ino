void GoToGoal() {
  
  x_g = goal_x[i];
  y_g = goal_y[i];
  //distance between goal and robot in x-direction
  u_x = x_g - x;
  //distance between goal and robot in y-direction
  u_y = y_g - y;
  //angle from robot to goal. Hint: use ATAN2, u_x, u_y here.
  theta_g = atan2(u_y, u_x);

  myPID.Compute();
}


//double e_k = 0;
//double E_k = 0;
//double e_k_1 = 0;
//double e_P = 0;
//double e_I = 0;
//double e_D = 0;
//

//
//void GoToGoal() {
//  dt = (finalTime - initTime) / 1000;
//
//  x_g = goal[0];
//  y_g = goal[1];
//
//  //distance between goal and robot in x-direction
//  u_x = x_g - x;
//
//  //distance between goal and robot in y-direction
//  u_y = y_g - y;
//
//  //angle from robot to goal. Hint: use ATAN2, u_x, u_y here.
//  theta_g = atan2(u_y, u_x);
//
//  //2. Calculate the heading error.
//  //error between the goal angle and robot's angle
//  e_k = theta_g - theta;
//  e_k = atan2(sin(e_k), cos(e_k));
//
//  //3. Calculate PID for the steering angle
//  //error for the proportional term
//  e_P = e_k;
//
//  //error for the integral term.
//  e_I = E_k + e_k * dt;
//
//  //error for the derivative term.
//  //e_D = (e_k - e_k_1) / dt;
//
//  w = Kp * e_P + Ki * e_I + Kd * e_D;
//  //w = Kp * e_P + Ki * e_I;
//
//  E_k = e_I;
//  e_k_1 = e_k;
//}
