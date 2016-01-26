#include <Encoder.h>

Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);
long encoder_value = 0;

void readEncoder() {
  long new_encoder_value = (myEnc.read() + 2) / 4;
  
  if (new_encoder_value != encoder_value) {
    handleEncoderValue(new_encoder_value - encoder_value);
    encoder_value = new_encoder_value;
  }
}

void handleEncoderValue(int encoder_direction) {
  //todo: send encoder push state
  mode_handleEncoderChange(encoder_direction, LOW);
}

