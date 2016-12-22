/*
  radio.cpp - Gerenciamento de comunicacao


*/
#include "radio.h"

Radio::Radio(uint8_t rxPin, uint8_t txPin, boolean debug = false) : _serial(rxPin, txPin) {
  _debug = debug;
  if (_debug) {
      Serial.println("[RADIO] : Inicializando");
  }
  _serial.begin(START_BAUD);
}

boolean Radio::enviarComandoAT(String comando) {
  char caractere;
  _serial.println(comando);
  if (_debug) {
      Serial.println("[RADIO] > " + comando);
  }
  delay(AT_COMMAND_WAIT);
  while(_serial.available() > 0) {
    String retorno = _serial.readStringUntil('\n');
    if (_debug) {
      Serial.println("[RADIO] < " + retorno);
    }
  }
}

boolean Radio::init(String nome, int senha) {
  String comandos[] = { "AT+NAME=" + nome, "AT+PSWD=" + senha };
  for (uint8_t i=0; i<= sizeof(comandos); i++) {
    if (!enviarComandoAT(comandos[i])) {
      return false;
    }
  }
  return true;
}

void Radio::escuta(uint8_t* retorno) {
  if (_serial.available()) {
    _serial.read();
  }
}

int Radio::disponivel() {
  return _serial.available();
}

