#include "NU32.h"          // constants, funcs for startup and UART

#define MAX_MESSAGE_LENGTH 200

int main(void) {
  char message[MAX_MESSAGE_LENGTH];
  int count = 0;
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  LATFbits.LATF0 = 1;   // LED's off
  LATFbits.LATF1 = 1;
  while (1) {
    if(!PORTDbits.RD7)
    {
      count++;
      LATFbits.LATF0 = 0;   // LED's on
      LATFbits.LATF1 = 0;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 20000000) { ; } // delay for 20 M core ticks, 0.5 s
      sprintf(message,"Pressed %d times", count);
      NU32_WriteUART3(message);                     // send message back
      NU32_WriteUART3("\r\n");                      // carriage return and newline
      LATFbits.LATF0 = 1;   // LED's off
      LATFbits.LATF1 = 1;
      while(!PORTDbits.RD7)
      {
        ;     // do nothing until button is released.
      }
    }
  }
  return 0;
}
