/*
  radio.cpp - Gerenciamento de comunicacao


*/
#include "radio.h"

Radio::Radio(uint8_t rxPin, uint8_t txPin, boolean debug) : _serial(rxPin, txPin) {
  _debug = debug;
  if (_debug) {
      Logger::log("RADIO", "Inicializando");
  }
  _initNome = false;
  _initSenha = false;
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  _serial.begin(START_BAUD);
  _serial.setTimeout(AT_COMMAND_TIMEOUT);
}

boolean Radio::initComm() {
  return enviarComandoAT("AT");
}

boolean Radio::initNome(String nome) {
    return enviarComandoAT("AT+NAME=" + nome);
}

boolean Radio::initSenha(unsigned int senha) {
    return enviarComandoAT(String("AT+PSWD=") + senha);
}

void Radio::limpaBuffer() {
  while(_serial.available() > 0) {
    char t = _serial.read();
  }   
}

boolean Radio::enviarComandoAT(String comando) {
  char caractere;
  limpaBuffer();
  _serial.println(comando);
  _serial.flush();
  if (_debug) {
      Logger::log("RADIO", "TX: " + comando);
  }
  delay(AT_COMMAND_WAIT);
  if (_serial.available() == 0) {
    if (_debug) {
      Logger::log("RADIO", "AT Command sem resposta");
    }
  }
  unsigned int comando_envio = millis();
  while(_serial.available() > 0) {
    String retorno = _serial.readStringUntil('\n');
    if (_debug) {
      Logger::log("RADIO", "RX: " + retorno);
    }
    if (millis() > comando_envio + AT_COMMAND_TIMEOUT) {
      if (_debug) {
        Logger::log("RADIO", "AT command timeout");
      }
      return false;
    }
    if (retorno.startsWith("OK")) {
      return true;
    }
  }
}

boolean Radio::init(String nome, int senha) {
  if (! initComm()) {
    return false;
  }
  if (!_initNome) {
    if (!(_initNome = initNome(nome))) {
      return false;
    }
  }
  if (!_initSenha) {
    if (!(_initSenha = initSenha(senha))){
      return false;
    }
  }
  return true;
}

boolean Radio::reset() {
  return enviarComandoAT("AT+ORGL");
}

void Radio::escuta(uint8_t* retorno) {
  if (_serial.available()) {
    _serial.read();
  }
}

int Radio::disponivel() {
  return _serial.available();
}

boolean Radio::estaInicializado() {
  return _initSenha;
}

