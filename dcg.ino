/*
  dcg.ino
  Distribuidor de cafe GEINF

*/
#include "logger.h"
#include "tela.h"
#include "motor.h"
#include "radio.h"

#define DEBUG

#define DEBUG_BAUD            9600
#define RADIO_INIT_TIME       5000  // Aguardar 5 seg. para inicializar o modulo Bluetooth
#define RADIO_NOME      "Nespresso"
#define RADIO_SENHA           1234

#define TELA_SDA                 4
#define TELA_SCL                 5
#define MOTOR_IN1                8
#define MOTOR_IN2                9
#define MOTOR_IN3               10
#define MOTOR_IN4               11
#define RADIO_RX                12
#define RADIO_TX                13

#ifdef DEBUG
boolean debug = true;
#else
boolean debug = false;
#endif

Tela tela;
Motor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4, false);
Radio radio(RADIO_RX, RADIO_TX, debug);
boolean radio_inicializado = false;
unsigned int radio_tentativa = 0;

void setup(void) {
#ifdef DEBUG
  Serial.begin(DEBUG_BAUD);
  Logger::log("SETUP", "Executando...");
#endif
  tela.titulo();
}

void loop(void) {
  unsigned int agora = millis();
  if (!radio_inicializado) {
    if (agora > RADIO_INIT_TIME && agora > (radio_tentativa + 2000)) {
      radio_inicializado = radio.init(RADIO_NOME, RADIO_SENHA);
      radio_tentativa = agora;
    }
  }
  if (motor.estaParado()) {
    delay(20000);
    motor.rotacao(30);
    tela.contagem(motor.grausRestantes(), motor.direcaoHoraria());
  } else {
    motor.roda();
  }
}

