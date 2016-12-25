/*
  logger.h - Gerenciamento de log

  
*/
#ifndef _LOGGER_H
#define _LOGGER_H

#include <Arduino.h>

#define LOG_MAX_SIZE   180

class Logger {
  public:
    static void log(char const *modulo, char const *conteudo);
    static void log(char const *modulo, String conteudo);
};
#endif /* _LOGGER_H */
