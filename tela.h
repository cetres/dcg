/*
  tela.h - Gerenciamento do motor

  Display (0.96 128x64 I2C - SSD1306):
    SDA >> A4
    SCL >> A5
  
*/
#ifndef _TELA_H
#define _TELA_H

#include <Arduino.h>
#include <U8glib.h>
#include "logger.h"

class Tela {
  private:
    U8GLIB_SSD1306_128X64 _u8g;
    boolean _debug;

  public:
    Tela(boolean debug = true);
    void titulo();
    void contagem(int passos, boolean direcao);
};

#endif /* _TELA_H */
