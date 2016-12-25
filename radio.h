/*
  radio.h - Gerenciamento de comunicacao

  Display (0.96 128x64 I2C - SSD1306):
    SDA >> A4
    SCL >> A5
  
*/
#ifndef _RADIO_H
#define _RADIO_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "logger.h"

#define AT_COMMAND_WAIT    1000
#define START_BAUD      38400
#define TAM_BLOCO          32

class Radio {
  private:
    boolean _debug;
    SoftwareSerial _serial;
    char _bloco[TAM_BLOCO];
    boolean _initComm;
    boolean _initNome;
    boolean _initSenha;

  protected:
    boolean enviarComandoAT(String comando);
    boolean initComm();
    boolean initNome();
    boolean initSenha();

  public:
    Radio(uint8_t rxPin, uint8_t txPin, boolean debug = false);
    boolean init(String nome, int senha);
    void escuta(uint8_t* retorno);
    int disponivel();
};

#endif /* _RADIO_H */
