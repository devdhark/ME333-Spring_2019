#include "NU32.h"          // constants, functions for startup and UART

#define NUMSAMPS 1000      // number of points in waveform
static volatile int Waveform[NUMSAMPS];   // Waveform

void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) {
  static int counter = 0;   // initialize counter once
  OC1RS = Waveform[counter];           // update duty cycle
  counter++;
  if(counter == NUMSAMPS) {
    counter = 0;           // roll the counter when needed
  }
  IFS0bits.T2IF = 0;    // clear interrupt flag
}

void makeWaveform();    // function declaration

int main(void) {
  NU32_Startup();          // cache on, interrupts on, LED/button init, UART init

  makeWaveform();
  T3CONbits.TCKPS = 0;     // Timer3 prescaler N=1 (1:1)
  PR3 = 3999;              // period = (PR2+1) * N * 12.5 ns = 50 us, 20 kHz
  TMR3 = 0;                // initial TMR3 count is 0
  OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
  OC1RS = 3000;             // duty cycle = OC1RS/(PR2+1) = 75%
  OC1R = 3000;              // initialize before turning OC1 on; afterward it is read-only
  T3CONbits.ON = 1;        // turn on Timer3
  OC1CONbits.ON = 1;       // turn on OC1
  OC1CONbits.OCTSEL = 1;   // use timer3 for OC
  __builtin_disable_interrupts();
  PR2 = 19999;
  T2CONbits.TCKPS = 2;     // Timer3 prescaler N=4 (1:4)
  TMR2 = 0;
  T2CONbits.ON = 1;        // turn on Timer2
  IPC2bits.T2IP = 5;       // step 5
  IFS0bits.T2IF = 0;       // step 6
  IEC0bits.T2IE = 1;       // step 7
  __builtin_enable_interrupts();
  while(1) {
    ;   // infinite loop
  }
  return 0;
}

void makeWaveform() {
  int i = 0, center = 2000, A = 1000;
  for(i = 0; i < NUMSAMPS; ++i) {
    if(i < NUMSAMPS/2){
      Waveform[i] = center + A;
    }
    else {
      Waveform[i] = center - A;
    }
  }
}
