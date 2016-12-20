/*
  motor.cpp - Gerenciamento do motor


*/
#include "motor.h"

Motor::Motor() {
  _direcaoHoraria = true;
  _lastTime = millis();
  _steps = 0;
  _stepsLeft = 0;
}

void Motor::setup() {
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
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

void Motor::stepper(int xw) {
  for (int x=0; x<xw; x++) {
    switch(_steps) {
      case 0:
        digitalWrite(MOTOR_IN1, LOW); 
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, HIGH);
        break; 
      case 1:
        digitalWrite(MOTOR_IN1, LOW); 
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, HIGH);
        digitalWrite(MOTOR_IN4, HIGH);
        break; 
      case 2:
        digitalWrite(MOTOR_IN1, LOW); 
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, HIGH);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
      case 3:
        digitalWrite(MOTOR_IN1, LOW); 
        digitalWrite(MOTOR_IN2, HIGH);
        digitalWrite(MOTOR_IN3, HIGH);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
      case 4:
        digitalWrite(MOTOR_IN1, LOW); 
        digitalWrite(MOTOR_IN2, HIGH);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
      case 5:
        digitalWrite(MOTOR_IN1, HIGH); 
        digitalWrite(MOTOR_IN2, HIGH);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
      case 6:
        digitalWrite(MOTOR_IN1, HIGH); 
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
      case 7:
        digitalWrite(MOTOR_IN1, HIGH); 
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, HIGH);
        break; 
      default:
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, LOW);
        digitalWrite(MOTOR_IN3, LOW);
        digitalWrite(MOTOR_IN4, LOW);
        break; 
    }
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

