#include <stdio.h>
#include <string.h>

#include "encryption.h"

void testhextobase2(unsigned char *test) {
	unsigned char *result = HexToBase2(test);
	int len = (strlen(test) + ((strlen(test)%2 == 1) ? 1 : 0)) / 2;
	printf("Test: %s converted to:\n", test);
	int i = 0;
	for(;i < len; i++) {
		printf("[%u]", result[i]);
	}
	printf("\n");
}

void testbase2tobase64(unsigned char *test, size_t size) {
	unsigned char *result = Base2ToBase64(test, size);
	//printf("%s\n", result);
}

void main()
{
	unsigned char *test1 = "0";
	unsigned char *test2 = "0049";
	unsigned char *test3 = "105";
	testhextobase2(test1);
	testhextobase2(test2);
	testhextobase2(test3);
	testbase2tobase64(test1, strlen(test1));
	testbase2tobase64(test2, strlen(test2));
	testbase2tobase64(test3, strlen(test3));
	
}