#ifndef LCD12684_DEF
#define LCD12684_DEF

#include "pin.h"
#include <avr/pgmspace.h>
#include <inttypes.h>
#include "Arduino.h"

class LCD12864 {
  typedef unsigned char byte;

  public:

  LCD12864();

  // General functions
  void Initialise(void);

  void writeString(String msg, unsigned int x, unsigned int y);
  void putCursor(unsigned int x, unsigned int y);
  void clearScreen();

  void serialWriteData(byte value);
  void serialWriteInstruction(byte value);

  private:

  // Serial functions
  void endSerial(void);
  void serialGenerateClock(byte nbr);
  void startSerial(void);
  void serialInstructionCmd(void);
  void serialDataCmd(void);
  void serialWriteByte(byte value);

  // variables
  byte delaytime;
  byte DEFAULTTIME;

  
};
//extern LCD12864 LCDA;

#endif
