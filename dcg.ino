/*
 dcg.ino
 Distribuidor de cafe GEINF
 
*/
#include "tela.h"
#include "motor.h"

Tela tela;
Motor motor;

void setup(void) {
  motor.setup();
#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop(void) {
  if (motor.estaParado()) {
#ifdef DEBUG
  Serial.println(time);
  Serial.println("Iniciando...");
#endif 
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

