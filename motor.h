/*
  motor.h - Gerenciamento do motor

  Stepper Motor Driver Module (28BYJ-48):
    IN1 >> D8
    IN2 >> D9
    IN3 >> D10
    IN4 >> D11
  
*/
#ifndef _MOTOR_H
#define _MOTOR_H

#include <Arduino.h>
#include "logger.h"

#define STEPS_IN1    B11100000
#define STEPS_IN2    B00111000
#define STEPS_IN3    B00001110
#define STEPS_IN4    B10000011

#define STEPS_TURN        4095
#define STEP_INTERVAL     1000

class Motor {
  private:
    uint8_t _in1, _in2, _in3, _in4;
    boolean _direcaoHoraria;
    unsigned long _lastTime;
    byte _steps;
    int _stepsLeft;
    boolean _debug;
    int _ultimoGrau;              // guarda o ultimo grau inteiro. Utilizado para debug

  protected:
    void stepperDirection();
    void stepper(uint8_t xw);

  public:
    Motor(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, boolean debug = false);
    void roda();
    void rotacao(float graus);
    boolean estaParado();
    boolean direcaoHoraria();
    char direcao();
    float grausRestantes();
};

#endif /* _MOTOR_H */
