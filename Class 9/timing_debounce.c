#include "NU32.h"          // constants, funcs for startup and UART
#define DEBOUNCEtime 10
volatile unsigned int check = 0;            // to check "state of timer"

void __ISR(11, IPL6SRS) Ext2ISR(void) { // step 1: the ISR
  char stop_message[50], time_message[20];
  double time;
  delay(DEBOUNCEtime);
  if(!PORTDbits.RD9)
  {
    if(!check)
    {
      _CP0_SET_COUNT(0);
      sprintf(stop_message,"Press the USER button again to stop the timer");
      NU32_WriteUART3(stop_message);
    }
    else
    {
      time = (12.5/1000000000) * _CP0_GET_COUNT();  // converting into seconds
      sprintf(time_message,"3.2f",time);
      NU32_WriteUART3(time_message);
    }
    check = !check;       // toggles the state of the timer after every interrupt
  }
  IFS0bits.INT2IF = 0;            // clear interrupt flag IFS0<3>
}

int main(void) {
  char start_message[50];
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
  __builtin_disable_interrupts(); // step 2: disable interrupts
  INTCONbits.INT2EP = 0;          // step 3: INT0 triggers on falling edge
  IPC2bits.INT2IP = 6;            // step 4: interrupt priority 2
  IPC2bits.INT2IS = 0;            // step 4: interrupt priority 1
  IFS0bits.INT2IF = 0;            // step 5: clear the int flag
  IEC0bits.INT2IE = 1;            // step 6: enable INT0 by setting IEC0<3>
  __builtin_enable_interrupts();  // step 7: enable interrupts
                                  // Connect RD7 (USER button) to INT2
  sprintf(start_message,"Press the USER button to start the timer");
  NU32_WriteUART3(str1);
  while(1) {
      ; // do nothing, loop forever
  }

  return 0;
}
