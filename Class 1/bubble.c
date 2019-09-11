#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100 // max length of string input
void getString(char *str); // helper prototypes
void printResult(char *str);
int greaterThan(char ch1, char ch2);
void swap(char *str, int index1, int index2);
int main(void)
{
	int len; // length of the entered string
	char str[MAXLENGTH]; // input should be no longer than MAXLENGTH
	getString(str);
	len = strlen(str); // get length of the string, from string.h
	for(int i=len-1; i>0; i--)
	{
		for(int j=0; j<i; j++)		// prevents the last character, which is already sorted, to be checked again
		{
			if(greaterThan(str[j], str[j+1]))	// checks whether ascii number of 1st char is greater than ascii of 2nd
				swap(str, j, j+1);	// swaps two consecutive characters if condition is satisfied
		}
	}
	printResult(str);
	return(0);
}
// helper functions go here
void getString(char *str)
{
	printf("Enter the string you would like to sort: ");
	scanf("%s", str);	// input
}
void printResult(char *str)
{
	printf("The sorted string is: %s", str);	// output
}
int greaterThan(char ch1, char ch2)
{
	if(ch1>ch2)
		return 1;
	else
		return 0;
}
void swap(char *str, int index1, int index2)
{
	char temp;
	// swapping two array elements
	temp = str[index1];
	str[index1] = str[index2];
	str[index2] = temp;
}
