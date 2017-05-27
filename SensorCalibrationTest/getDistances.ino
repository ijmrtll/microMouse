void getDistances()
{
  frontSensorVal = analogRead(frontSensorPin);

  if (frontSensorVal >= maxValFrontSensor) {
    frontSensorVal = maxValFrontSensor;
    frontSensorVal = frontSensorAverage.add(frontSensorVal);
  } else if (frontSensorVal <= minValFrontSensor) {
    frontSensorVal = minValFrontSensor;
    frontSensorVal = frontSensorAverage.add(frontSensorVal);
  }
  frontSensorDistance = polyvalFront(frontSensorVal);


  rightSensorDistance = analogRead(rightSensorPin);

  if (rightSensorVal >= maxValRightSensor) {
    rightSensorVal = maxValRightSensor;
    rightSensorVal = rightSensorAverage.add(rightSensorVal);
  } else if (rightSensorVal <= minValRightSensor) {
    rightSensorVal = minValRightSensor;
    rightSensorVal = rightSensorAverage.add(rightSensorVal);
  }
  
  rightSensorDistance = polyvalRight(rightSensorDistance);

  leftSensorDistance = analogRead(leftSensorPin);

  if (leftSensorVal >= maxValLeftSensor) {
    leftSensorVal = maxValLeftSensor;
    leftSensorVal = leftSensorAverage.add(leftSensorVal);
  } else if (leftSensorVal <= minValLeftSensor) {
    leftSensorVal = minValLeftSensor;
    leftSensorVal = leftSensorAverage.add(leftSensorVal);
  }
  
  leftSensorDistance = polyvalLeft(leftSensorDistance);
}

float polyvalFront(float x) {
  float a3 = -0.000001074995176;
  float a2 = 0.000951122483150;
  float a1 = -0.287693191045458;
  float a0 = 33.267964922165120;
  return (((a3 * x + a2) * x + a1) * x + a0);
  //return x;
}

float polyvalRight(float x) {
  float a3 = -0.000000816548853;
  float a2 = 0.000729320219851;
  float a1 = -0.224894572640989;
  float a0 = 27.198228526330666;
  return (((a3 * x + a2) * x + a1) * x + a0);
  //return x;
}

float polyvalLeft(float x) {
  float a3 = -0.000000848871505;
  float a2 = 0.000750511720414;
  float a1 = -0.228745459757036;
  float a0 = 27.240908105269487;
  return (((a3 * x + a2) * x + a1) * x + a0);
  //return x;
}

