void doEncoderRight() {
  if (digitalRead(encoderRightPinA) == digitalRead(encoderRightPinB)) {
    encoderRightPos++;

  } else {
    encoderRightPos--;
  }
}
