#include "LCD12864.h"
#include "pin.h"

LCD12864 LCDA;

int cont = 0;
bool enc_A_stat;
bool enc_B_stat;

void setup() {
  
  // put your setup code here, to run once:
  LCDA.Initialise();
  
  pinMode(BUT_ENC, INPUT);
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  enc_A_stat = digitalRead(ENC_A);
  enc_B_stat = digitalRead(ENC_B);
  attachInterrupt(ENC_A, enc_A_int, FALLING);
  attachInterrupt(ENC_A, enc_B_int, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUT_ENC)) {
    analogWrite(BUZZ, 0);
  }
  else {
    analogWrite(BUZZ, 127);
  }
  LCDA.writeString(String(cont),6,1);
}

void enc_A_int() {
  cont++;
}

void enc_B_int() {
  cont--;
}

