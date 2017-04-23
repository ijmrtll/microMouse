void getDistances()
{
  frontSensorDistance = analogRead(frontSensorPin);
  if (frontSensorDistance <= 0) {
    frontSensorDistance = maxDistanceFrontSensor;
  }
  frontSensorDistance = frontSensorAverage.add(frontSensorDistance);

  rightSensorDistance = analogRead(rightSensorPin);
  if (rightSensorDistance <= 0) {
    rightSensorDistance = maxDistanceRightSensor;
  }
  rightSensorDistance = rightSensorAverage.add(rightSensorDistance);

  leftSensorDistance = analogRead(leftSensorPin);
  if (leftSensorDistance <= 0) {
    leftSensorDistance = maxDistanceLeftSensor;
  }
  leftSensorDistance = leftSensorAverage.add(leftSensorDistance);

}

