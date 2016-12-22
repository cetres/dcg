/*
  motor.cpp - Gerenciamento do motor


*/
#include "motor.h"

Motor::Motor(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4) {
  _direcaoHoraria = true;
  _lastTime = millis();
  _steps = 0;
  _stepsLeft = 0;
  _in1 = in1;
  _in2 = in2;
  _in3 = in3;
  _in4 = in4;
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_in3, OUTPUT);
  pinMode(_in4, OUTPUT);
}

void Motor::direcao() {
  if (_direcaoHoraria == 1) {
    _steps++;
  } else if (_direcaoHoraria == 0) {
    _steps--;
  }
  if (_steps > 7) {
    _steps = 0;
  } else if (_steps < 0) {
    _steps = 7;
  }
}

void Motor::stepper(uint8_t xw) {
  for (uint8_t x=0; x<xw; x++) {
    digitalWrite(_in1, STEPS_IN1 & ( 1 << _steps ));
    digitalWrite(_in2, STEPS_IN2 & ( 1 << _steps ));
    digitalWrite(_in3, STEPS_IN3 & ( 1 << _steps ));
    digitalWrite(_in4, STEPS_IN4 & ( 1 << _steps ));
    direcao();
  }
}

void Motor::roda() {
  if (_stepsLeft > 0) {
    if (micros() - _lastTime >= STEP_INTERVAL) {
      stepper(1);
      _lastTime = micros();
      _stepsLeft--;
    }
  }
}

void Motor::rotacao(float graus) {
  _stepsLeft = (graus/360) * STEPS_TURN;
  _direcaoHoraria = (graus > 0)? true : false;
}

boolean Motor::estaParado() {
  return (_stepsLeft == 0);
}

boolean Motor::direcaoHoraria() {
  return _direcaoHoraria;
}

float Motor::grausRestantes() {
  return (_stepsLeft/STEPS_TURN) * 360;
}

