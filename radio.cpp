/*
  radio.cpp - Gerenciamento de comunicacao


*/
#include "radio.h"

Radio::Radio(uint8_t rxPin, uint8_t txPin) {
  SoftwareSerial _serial(rxPin, txPin);
  _serial.begin(START_BAUD);
}

void Radio::escuta(uint8_t* retorno) {
  if (_serial.available()) {
    _serial.read();
  }
}

