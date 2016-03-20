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
	char *base64Result;
	unsigned char *test1 = "0";
	unsigned char *test2 = "0049";
	unsigned char *test3 = "105";
	//testhextobase2(test1);
	//testhextobase2(test2);
	//testhextobase2(test3);

	unsigned char *testFromMatasano = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	unsigned char *result = HexToBase2(testFromMatasano);
	int len = strlen(testFromMatasano) / 2;	// 4 bits per hex digit = 1 byte per every 2 chars in the string.
	base64Result = Base2ToBase64(result, len);

	printf("Binary to Base64: the binary number %s \n encodes to \n %s", testFromMatasano, base64Result);
	free(base64Result);

	/*
	unsigned char *test4 = malloc(1);
	*test4 = 1;		// Should be AQ== I think.
	base64Result = Base2ToBase64(test4, 1);
	printf("Binary to Base64: the binary number %d encodes to %s", *test4, base64Result);	

	unsigned char *test5 = malloc(1);
	*test5 = 'M';	// should encode to TQ== , see https://en.wikipedia.org/wiki/Base64#Padding
	base64Result = Base2ToBase64(test5, 1);
	printf("Binary to Base64: the character %c encodes to %s", *test5, base64Result);

	*/
	//testbase2tobase64(test2, strlen(test2));
	//testbase2tobase64(test3, strlen(test3));
	

	getc(stdin);
}