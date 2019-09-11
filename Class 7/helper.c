#include "helper.h"

void calculateGrowth(Investment *invp)
{
  int i;
  for (i = 1; i <= invp->years; i= i + 1)
  {
    invp->invarray[i] = invp->growth * invp->invarray[i-1];
  }
}
int getUserInput(Investment *invp)
{
  char str_write1[50],str_write2[50],str_write3[50],str_read[50];
  int valid;
  sprintf(str_write1,"Enter investment, growth rate, number of yrs (up to %d): ",MAX_YEARS);  // puts MAX_YEARS into string str_write1
  NU32_WriteUART3(str_write1);  // sends the string for printing
  NU32_ReadUART3(str_read, 50); // enters values into a string
  sscanf(str_read,"%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));  // modifies our variables with the string entered
  valid = (invp->inv0 > 0) && (invp->growth > 0) &&
  (invp->years > 0) && (invp->years <= MAX_YEARS);
  sprintf(str_write2,"Valid input? %d\n",valid);
  NU32_WriteUART3(str_write2);
  if (!valid)
  {
    sprintf(str_write3,"Invalid input; exiting.\n");
    NU32_WriteUART3(str_write3);
  }
  return(valid);
}
void sendOutput(double *arr, int yrs)
{
  int i;
  char outstring[100],str_write1[50],str_write2[50];
  sprintf(str_write1,"\nRESULTS:\n\n");
  NU32_WriteUART3(str_write1);
  for (i=0; i<=yrs; i++)
  {
    sprintf(outstring,"Year %3d: %10.2f\n",i,arr[i]);
    NU32_WriteUART3(outstring);
  }
  sprintf(str_write2,"\n");
  NU32_WriteUART3(str_write2);
}
