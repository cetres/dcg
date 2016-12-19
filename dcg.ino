/*
 dcg.ino
 Distribuidor de cafe GEINF

 Pinagem:

 Display (0.96 128x64 I2C - SSD1306):
   SDA >> A4
   SCL >> A5
 
 Stepper Motor Driver Module (28BYJ-48):
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
*/
#include "U8glib.h"

#define MOTOR_IN1 8
#define MOTOR_IN2 9
#define MOTOR_IN3 10
#define MOTOR_IN4 11

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

int iteracoes = 0;
int steps = 0;
boolean direcao = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left = 2;
long time;

void tela_titulo(void) {
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_osb21);
    u8g.drawStr( 0, 22, "Nespresso");
    u8g.drawStr( 20, 52, "GEINF");
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 96, 64, "2016");
  } while ( u8g.nextPage() );
}

void tela_contgem(int numero, boolean direcao) {
  u8g.firstPage();  
  do {
    char num_str[15];
    char dir_str[15];
    sprintf(num_str, "Numero: %03d", numero);
    if (direcao) {
      sprintf(dir_str, "Direcao: CCW");
    } else {
      sprintf(dir_str, "Direcao: CW");
    }
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 0, 22, num_str);
    u8g.drawStr( 0, 38, dir_str);
  } while ( u8g.nextPage() );
}

void define_direcao(){
  if (direcao==1) {
    steps++;
  }
  if (direcao==0) {
    steps--;
  }
  if (steps>7) {
    steps=0;
  }
  if (steps<0) {
    steps=7;
  }
}

void stepper(int xw) {
  for (int x=0; x<xw; x++) {
    switch(steps) {
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
    define_direcao();
  }
}

void setup(void) {

  // Configuracoes do display
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  // Configuracoes do motor
  Serial.begin(115200);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
}

void loop(void) {
  if (iteracoes == 0) {
    tela_titulo();
  } else {
    tela_contgem(iteracoes, direcao);
  }
  iteracoes++;
  while (steps_left > 0){
    currentMillis = micros();
    if (currentMillis - last_time >= 1000) {
      stepper(1); 
      time = time + micros() - last_time;
      last_time = micros();
      steps_left--;
    }
  }
  
  Serial.println(time);
  Serial.println("Aguardando...!");
  
  delay(2000);
  direcao = ! direcao;
  steps_left=4095;
}

