/*
  tela.cpp - Gerenciamento do motor


*/
#include "tela.h"

Tela::Tela() {
  U8GLIB_SSD1306_128X64 _u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
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
  _u8g.firstPage();  
  do {
    _u8g.setFont(u8g_font_osb21);
    _u8g.drawStr( 0, 22, "Nespresso");
    _u8g.drawStr( 20, 52, "GEINF");
    _u8g.setFont(u8g_font_unifont);
    _u8g.drawStr( 96, 64, "2016");
  } while ( _u8g.nextPage() );
}

void Tela::contgem(int passos, boolean direcao) {
  _u8g.firstPage();  
  do {
    char num_str[15];
    char dir_str[15];
    sprintf(num_str, "Passos: %04d", passos);
    if (direcao) {
      sprintf(dir_str, "Direcao: CCW");
    } else {
      sprintf(dir_str, "Direcao: CW");
    }
    _u8g.setFont(u8g_font_unifont);
    _u8g.drawStr( 0, 22, num_str);
    _u8g.drawStr( 0, 38, dir_str);
  } while ( _u8g.nextPage() );
}
