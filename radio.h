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

#define START_BAUD 38400

class Radio {
  private:
    SoftwareSerial _serial;
    
  public:
    Radio(uint8_t rxPin, uint8_t txPin);
    void escuta(uint8_t* retorno);
};

#endif /* _RADIO_H */
