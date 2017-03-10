void update_odometry()
{
  x = x_new;
  y = y_new;
  theta = theta_new;

  prev_left_ticks = left_ticks;
  prev_right_ticks = right_ticks;

  right_ticks = encoderLeftPos;
  left_ticks = encoderRightPos;

  Dr = m_per_tick * (right_ticks - prev_right_ticks);
  Dl = m_per_tick * (left_ticks - prev_left_ticks);
  Dc = (Dr + Dl) / 2;

  x_dt = Dc * cos(theta);
  y_dt = Dc * sin(theta);
  
  theta_dt = (Dr - Dl) / L;

  theta_new = theta + theta_dt;
  x_new = x + x_dt;
  y_new = y + y_dt;
}
