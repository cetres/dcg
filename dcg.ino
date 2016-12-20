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
  Serial.println("Parado, iniciando...!");
#endif 
    tela.titulo();
    delay(2000);
    motor.rotacao(90);
  } else {
    tela.contgem(motor.grausRestantes(), motor.direcaoHoraria());
  }
  motor.roda();
}

