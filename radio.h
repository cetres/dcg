/*
  radio.h - Gerenciamento de comunicacao

    - RADIO_RX  D12
    - RADIO_TX  D13
  
*/
#ifndef _RADIO_H
#define _RADIO_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "logger.h"

#define AT_COMMAND_WAIT     500
#define AT_COMMAND_TIMEOUT 5000
#define START_BAUD        38400      // Padrao: 38400
#define TAM_BLOCO            32
#define MAX_NOME             32


class Radio {
  private:
    boolean _debug;
    SoftwareSerial _serial;
    char _bloco[TAM_BLOCO];
    boolean _initNome;
    boolean _initSenha;

  protected:
    void limpaBuffer();
    boolean enviarComandoAT(String comando);
    boolean initComm();
    boolean initNome(String nome);
    boolean initSenha(unsigned int senha);

  public:
    Radio(uint8_t rxPin, uint8_t txPin, boolean debug = false);
    boolean init(String nome, int senha);
    void escuta(uint8_t* retorno);
    int disponivel();
    boolean estaInicializado();
    boolean reset();
};

#endif /* _RADIO_H */
