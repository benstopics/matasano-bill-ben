#include <stdio.h>
#include <string.h>

#include "encryption.h"

void runtest(unsigned char *test) {
	unsigned char *result = HexToBase2(test);
	int len = (strlen(test) + ((strlen(test)%2 == 1) ? 1 : 0)) / 2;
	printf("Test: %s converted to ", test);
	int i = 0;
	for(;i < len; i++) {
		printf("[%u]", result[i]);
	}
	printf("\n");
}

void main()
{
	unsigned char *test1 = "0";
	unsigned char *test2 = "0049";
	unsigned char *test3 = "105";
	runtest(test1);
	runtest(test2);
	runtest(test3);
}