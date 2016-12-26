/*
  tela.cpp - Gerenciamento do motor


*/
#include "tela.h"

Tela::Tela(boolean debug) {
  _debug = debug;
}

void Tela::init() {
  if (_debug) {
      Logger::log("TELA", "Inicializando...");
  }
   _u8g = U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
  if ( _u8g.getMode() == U8G_MODE_R3G3B2 ) {
    _u8g.setColorIndex(255);     // white
  } else if ( _u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    _u8g.setColorIndex(3);         // max intensity
  } else if ( _u8g.getMode() == U8G_MODE_BW ) {
    _u8g.setColorIndex(1);         // pixel on
  } else if ( _u8g.getMode() == U8G_MODE_HICOLOR ) {
    _u8g.setHiColorByRGB(255,255,255);
  }
}
void Tela::titulo() {
  if (_debug) {
      Logger::log("TELA", "Exibindo tela inicial do titulo");
  }
  _u8g.firstPage();  
  do {
    _u8g.setFont(u8g_font_osb21);
    _u8g.drawStr(0, 22, "Nespresso");
    _u8g.drawStr(20, 52, "GEINF");
    _u8g.setFont(u8g_font_unifont);
    _u8g.drawStr(96, 64, "2016");
  } while ( _u8g.nextPage() );
}

void Tela::contagem(int passos, boolean direcao) {
  if (_debug) {
      Logger::log("TELA", "Exibindo tela de contagem");
  }
  _u8g.firstPage();  
  do {
    char num_str[15];
    char dir_str[3];
    if (direcao) {
      sprintf(dir_str, "H");
    } else {
      sprintf(dir_str, "AH");
    }
    sprintf(num_str, "Graus: %04d / Dir: %s", passos, dir_str);
    _u8g.setFont(u8g_font_unifont);
    _u8g.drawStr(0, 22, num_str);
  } while ( _u8g.nextPage() );
}
