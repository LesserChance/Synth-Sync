#include <SPI.h>

byte dataCharacter;
byte dataDigit;
byte dataArrayCharacter[10];
byte dataArrayDigit[4];

void initDigits() {
  pinMode(DIGIT_LATCH_PIN, OUTPUT);
  pinMode(DIGIT_CLOCK_PIN, OUTPUT);
  pinMode(DIGIT_DATA_PIN, OUTPUT);

  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  
  //ABCDEFGH, 1 = off
  dataArrayCharacter[0] = B00000011;
  dataArrayCharacter[1] = B10011111;
  dataArrayCharacter[2] = B00100101;
  dataArrayCharacter[3] = B00001101;
  dataArrayCharacter[4] = B10011001;
  dataArrayCharacter[5] = B01001001;
  dataArrayCharacter[6] = B01000001;
  dataArrayCharacter[7] = B00011111;
  dataArrayCharacter[8] = B00000001;
  dataArrayCharacter[9] = B00011001;

  //X1234XXXX, 1 = on
  dataArrayDigit[0] = B01000000;
  dataArrayDigit[1] = B00100000;
  dataArrayDigit[2] = B00010000;
  dataArrayDigit[3] = B00001000;
}

void outputString(String output) {
  for (int i = 0; i < 4; i++) {
    dataDigit = dataArrayDigit[i];
    dataCharacter = dataArrayCharacter[output.charAt(i) - '0'];

    PORTB |= _BV(PB0); // latch pin HIGH
    SPI.transfer(dataDigit);
    SPI.transfer(dataCharacter);
    PORTB &= ~_BV(PB0); // latch pin LOW
  }
}

