#include <xc.h>          // Load the proper header for the processor

int main(void) {
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.

  while(1)
  {
    LATFbits.LATF0 = 1;    // Turn LED1 on and LED2 off.  These pins sink current
    LATFbits.LATF1 = 0;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
    while(!PORTDbits.RD7)
    {
      LATFbits.LATF0 = 0; // Flips LED 1 and LED 2
      LATFbits.LATF1 = 1;
    }
  }
}
