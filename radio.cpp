/*
  radio.cpp - Gerenciamento de comunicacao


*/
#include "radio.h"

Radio::Radio(uint8_t rxPin, uint8_t txPin, boolean debug) : _serial(rxPin, txPin) {
  _debug = debug;
  if (_debug) {
      Logger::log("RADIO", "Inicializando");
  }
  _serial.begin(START_BAUD);
}

boolean Radio::initComm() {
  if (!_initComm) {
    enviarComandoAT("AT");
  }
}

boolean Radio::initNome() {
  if (!_initNome) {
    enviarComandoAT("AT");
  }
}

boolean Radio::initSenha() {
  if (!_initSenha) {
    enviarComandoAT("AT");
  }
}

boolean Radio::enviarComandoAT(String comando) {
  char caractere;
  _serial.println(comando);
  if (_debug) {
      Logger::log("RADIO", "TX: " + comando);
  }
  delay(AT_COMMAND_WAIT);
  while(_serial.available() > 0) {
    String retorno = _serial.readStringUntil('\n');
    if (_debug) {
      Logger::log("RADIO", "RX: " + retorno);
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

