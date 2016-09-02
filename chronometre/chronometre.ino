#include "LCD12864.h"
#include "pin.h"

LCD12864 LCDA;

int cont = 0;

void setup() {
  
  // put your setup code here, to run once:
  LCDA.Initialise();
  
  pinMode(BUT_ENC, INPUT);
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  
  attachInterrupt(ENC_A, enc_A_int, CHANGE);
  attachInterrupt(ENC_A, enc_B_int, CHANGE);
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
  if(digitalRead(ENC_A)!=digitalRead(ENC_B)) {
    cont++;
  }
}

void enc_B_int() {
  if(digitalRead(ENC_A)!=digitalRead(ENC_B)) {
    cont--;
  }
}

