#include "stdio.h"
#include "stdlib.h"

int main(void) 
{

	volatile int * led = (int *) 0xFF200040; //red LED address
	volatile int * switchptr = (int *) 0xFF200030; //SW slider switch address
	volatile int * hex3_hex0addr = (int *) 0xFF200020; //red LED addres
	volatile int * hex5_hex4addr = (int *) 0xFF200010; //red LED addres
	volatile int * push = (int *) 0xFF200000;
	char a[32];
	char b[32];
	char c[32];
   int i;

   printf("Please input an integer value: ");
   scanf("%s", &a);
	
	for(i=0; i<strlen(a); i++)
	{
		if (!isdigit(a[i])){
			printf("youre dumb");
			break;
		}
	}
	int anew = atoi(a);
	printf("You entered: %d\n", anew);
	
   printf("Please input an integer value: ");
   scanf("%s", &b);
	for(i=0; i<strlen(b); i++)
	{
	if (!isdigit(b[i]))
	{
	printf("youre dumb\n");
	break;
	}
}
	int bnew = atoi(b);
	printf("You entered: %d\n", bnew);
   printf("Please input an integer value: ");
   scanf("%s", &c);
	for(i=0; i<strlen(c); i++)
	{
	if (!isdigit(c[i]))
	{
	printf("youre dumb");
	break;
	}
	}
	int cnew = atoi(c);
	printf("You entered: %d\n", cnew);
   return 0;
}
