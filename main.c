#include <stdio.h>
#include <string.h>

#include "encryption.h"

void main()
{
	unsigned char *test1 = "0049";
	
	unsigned char *result = HexToBase2(test1);
	
	int base2len = strlen(test1)/2;
	printf("%d Test #1: %s converted to ", base2len, test1);
	int i = 0;
	for(;i < base2len; i++)
		printf("[%d]", result[i]);
	printf("\n");
}