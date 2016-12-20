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

#define MOTOR_IN1 8
#define MOTOR_IN2 9
#define MOTOR_IN3 10
#define MOTOR_IN4 11

#define STEPS_TURN 4095
#define STEP_INTERVAL 1000

class Motor {
  private:
    boolean _direcaoHoraria;
    unsigned long _lastTime;
    int _steps;
    int _stepsLeft;

  protected:
    void direcao();
    void stepper(int xw);

  public:
    Motor();
    void setup();
    void roda();
    void rotacao(float graus);
    boolean estaParado();
    boolean direcaoHoraria();
    float grausRestantes();
};

#endif /* _MOTOR_H */
