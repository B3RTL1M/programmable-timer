#include "LCD12864.h"

extern "C" {
#include <wiring.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
}

// public functions

LCD12864::LCD12864() {
  this->DEFAULTTIME = 1;
  this->delaytime = DEFAULTTIME;
}

void LCD12864::Initialise() {
  
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_SID, OUTPUT);
  pinMode(LCD_SCLK, OUTPUT);
  
  endSerial();
  
  serialWriteInstruction(0x34);
  serialWriteInstruction(0x34);
  serialWriteInstruction(0x03);
  serialWriteInstruction(0x30);
  serialWriteInstruction(0x06);
  serialWriteInstruction(0x0c);
  serialWriteInstruction(0x01);
}

void LCD12864::endSerial() {
  digitalWrite(LCD_CS, 0);
  digitalWrite(LCD_SCLK,0);
}

void LCD12864::serialGenerateClock(byte nbr) {
  for(int i=0;i<nbr;i++) {
    delay(this->delaytime);
    digitalWrite(LCD_SCLK,1);
    delay(this->delaytime);
    digitalWrite(LCD_SCLK,0);
  }
}

void LCD12864::startSerial() {
  digitalWrite(LCD_CS,1);
  digitalWrite(LCD_SID,1);
  serialGenerateClock(5);
}

void LCD12864::serialInstructionCmd() {
  digitalWrite(LCD_SID,0);
  serialGenerateClock(3);
}

void LCD12864::serialDataCmd() {
  digitalWrite(LCD_SID,0);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,1);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,0);
  serialGenerateClock(1);
}

void LCD12864::serialWriteByte(byte value) {
  digitalWrite(LCD_SID,value&0x80);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x40);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x20);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x10);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,0);
  serialGenerateClock(4);
  digitalWrite(LCD_SID,value&0x08);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x04);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x02);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,value&0x01);
  serialGenerateClock(1);
  digitalWrite(LCD_SID,0);
  serialGenerateClock(4);
}

void LCD12864::serialWriteData(byte value) {
  startSerial();
  serialDataCmd();
  serialWriteByte(value);
  endSerial();
}

void LCD12864::serialWriteInstruction(byte value) {
  startSerial();
  serialInstructionCmd();
  serialWriteByte(value);
  endSerial();
}

void LCD12864::putCursor(unsigned int x, unsigned int y) {
  if (x<0) {
    x = 0;
  }
  else if (x>7) {
    x = 7;
  }
  if (y<0) {
    y = 0;
  }
  else if (y>3) {
    y = 3;
  }

  byte cmd = 0x80;

  switch(y) {
    case 0:
    cmd += 0x00;
    break;
    case 1:
    cmd += 0x10;
    break;
    case 2:
    cmd += 0x08;
    break;
    case 3:
    cmd += 0x18;
    break;
  }

  cmd += x;
  serialWriteInstruction((byte)cmd);
}

void LCD12864::clearScreen() {
  serialWriteInstruction(0x01);
}

void LCD12864::writeString(String msg, unsigned int x, unsigned int y) {
  if (x<0) {
    x = 0;
  }
  else if (x>15) {
    x = 15;
  }
  if (y<0) {
    y = 0;
  }
  else if (y>3) {
    y = 3;
  }
  putCursor(x/2,y);

  int i = 0;

  if(x%2!=0) {
    serialWriteData(' ');
  }

  while(i+x<=15 && msg[i]!='\0') {
    serialWriteData(msg[i]);
    i++;
  }
}


