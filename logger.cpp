/*
  logger.cpp - Gerenciamento de log


*/
#include "logger.h"

void Logger::log(char const *modulo, char const *conteudo) {
  char saida[80];
  char tempo[8];
  dtostrf(( (float)millis() / 1000.0), 5, 3, tempo);
  sprintf(saida, "%s [%s] %s\n", tempo, modulo, conteudo);
  Serial.print(saida);
}

void Logger::log(char const *modulo, String conteudo) {
  char log_str[LOG_MAX_SIZE];
  conteudo.toCharArray(log_str, LOG_MAX_SIZE);
  log(modulo, log_str);
}

