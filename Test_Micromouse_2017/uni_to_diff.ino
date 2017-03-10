void uni_to_diff(double v, double w) {
  vel_r = (2 * v + w * L) / (2 * R);
  vel_l = (2 * v - w * L) / (2 * R);
  
}
