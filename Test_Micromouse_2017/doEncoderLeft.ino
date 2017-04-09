void doEncoderLeft() {
  if (digitalRead(encoderLeftPinA) == digitalRead(encoderLeftPinB)) {
    encoderLeftPos++;
  } else {
    encoderLeftPos--;
  }
}
