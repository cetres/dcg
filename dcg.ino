/*
 dcg.ino
 Distribuidor de cafe GEINF
 
*/
#include "tela.h"
#include "motor.h"
#include "radio.h"

#define DEBUG_BAUD          115200
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
Motor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4);
Radio radio(RADIO_RX, RADIO_TX, debug);
boolean radio_inicializado = false;

void setup(void) {
#ifdef DEBUG
  Serial.begin(DEBUG_BAUD);
#endif
}

void loop(void) {
  if (!radio_inicializado) {
    if (millis() > RADIO_INIT_TIME) {
#ifdef DEBUG
      Serial.println("Iniciando Radio...");
#endif 
      radio_inicializado = radio.init(RADIO_NOME, RADIO_SENHA);
    }
  }
  if (motor.estaParado()) {
    tela.titulo();
    delay(2000);
    motor.rotacao(90);
  } else {
#ifdef DEBUG
    char sentido[3] = (motor.direcaoHoraria())?"H":"AH";
    Serial.println("Graus: %0.1f / Sentido: %s", motor.grausRestantes(), sentido);
#endif 
    tela.contgem(motor.grausRestantes(), motor.direcaoHoraria());
  }
  motor.roda();
}

