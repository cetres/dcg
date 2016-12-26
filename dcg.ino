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

#define TELA_SDA                 4    //A4
#define TELA_SCL                 5    //A5

#define RADIO_KEY                7    //D7
#define MOTOR_IN1                8    //D8
#define MOTOR_IN2                9    //D9
#define MOTOR_IN3               10    //D10
#define MOTOR_IN4               11    //D11
#define RADIO_RX                12    //D12
#define RADIO_TX                13    //D13

#ifdef DEBUG
boolean debug = true;
#else
boolean debug = false;
#endif

Tela tela(debug);
Motor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4, false);
Radio radio(RADIO_RX, RADIO_TX, RADIO_KEY, debug);
unsigned int radio_init = 0;

void setup(void) {
#ifdef DEBUG
  Serial.begin(DEBUG_BAUD);
  Logger::log("SETUP", "Executando...");
#endif
  radio_init = millis() + RADIO_INIT_TIME;
  tela.init();
  tela.titulo();
}

void loop(void) {
  unsigned int agora = millis();
  if (! radio.estaInicializado()) {
    if (agora > radio_init) {
      if (!radio.init(RADIO_NOME, RADIO_SENHA)) {
        radio_init = agora + RADIO_INIT_TIME;
      }
    }
  }
  if (motor.estaParado()) {
    delay(2000);
    //motor.rotacao(30);
    tela.contagem(motor.grausRestantes(), motor.direcaoHoraria());
  } else {
    motor.roda();
  }
}

