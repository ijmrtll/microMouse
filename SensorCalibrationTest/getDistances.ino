void getDistances()
{
  frontSensorDistance = analogRead(frontSensorPin);
  frontSensorDistance = polyvalFront(frontSensorDistance);

  if (frontSensorDistance >= maxDistanceFrontSensor) {
    frontSensorDistance = maxDistanceFrontSensor;
  }
  frontSensorDistance = frontSensorAverage.add(frontSensorDistance);

  rightSensorDistance = analogRead(rightSensorPin);
  rightSensorDistance = polyvalRight(rightSensorDistance);

  if (rightSensorDistance >= maxDistanceFrontSensor) {
    rightSensorDistance = maxDistanceRightSensor;
  }
  rightSensorDistance = rightSensorAverage.add(rightSensorDistance);

  leftSensorDistance = analogRead(leftSensorPin);
  leftSensorDistance = polyvalLeft(leftSensorDistance);

  if (leftSensorDistance >= maxDistanceLeftSensor) {
    leftSensorDistance = maxDistanceLeftSensor;
  }
  leftSensorDistance = leftSensorAverage.add(leftSensorDistance);

}

float polyvalFront(float x) {
  float a3 = 1;
  float a2 = 1;
  float a1 = 1;
  float a0 = 1;
  //  return (a3 * x * x * x + a2 * x * x + a1 * x + a0);
  return x;
}

float polyvalRight(float x) {
  float a3 = 1;
  float a2 = 1;
  float a1 = 1;
  float a0 = 1;
  //  return (a3 * x * x * x + a2 * x * x + a1 * x + a0);
  return x;
}

float polyvalLeft(float x) {
  float a3 = 1;
  float a2 = 1;
  float a1 = 1;
  float a0 = 1;
  //  return (a3 * x * x * x + a2 * x * x + a1 * x + a0);
  return x;
}

