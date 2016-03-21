/**********************************
* set1challenge3.c                *
* Bill Nicholson                  *
*                                 *
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include "set1challenge3.h"

unsigned char *set3challenge3(unsigned char *msg, size_t size) {
	unsigned char *result = malloc(size);
	unsigned char *tmp = malloc(size + 1);
	unsigned char j;
	int i;
	unsigned char highNibble, lowNibble;
	unsigned char ASCIIChar;

	for (i = 0; i < 256; i++) {
		// XOR the original string with a constant value
		for (j = 0; j < size; j++) {
			*(tmp + j) = *(msg + j) ^ i;
		}
		// Convert the newly created string to ASCII characters. We assume that the newly created string contains 2-byte ASII hex codes.
		for (j = 0; j < size; j += 2) {
			highNibble = *(tmp + j);
			lowNibble = *(tmp + j + 1);
			ASCIIChar = (ASCIIhexToBinary(highNibble) * 16) + ASCIIhexToBinary(lowNibble);
			*(tmp + j) = ASCIIChar;
		}
		*(tmp + j) = 0;
		printf("\n %d <%s>", i, tmp);
	}
	return result;
}

int ASCIIhexToBinary(unsigned char digit) {
	switch (digit) {
		case '0':            digit = 0;  break;
		case '1':            digit = 1;  break;
		case '2':            digit = 2;  break;
		case '3':            digit = 3;  break;
		case '4':            digit = 4;  break;
		case '5':            digit = 5;  break;
		case '6':            digit = 6;  break;
		case '7':            digit = 7;  break;
		case '8':            digit = 8;  break;
		case '9':            digit = 9;  break;
		case 'a': case 'A':  digit = 10; break;
		case 'b': case 'B':  digit = 11; break;
		case 'c': case 'C':  digit = 12; break;
		case 'd': case 'D':  digit = 13; break;
		case 'e': case 'E':  digit = 14; break;
		case 'f': case 'F':  digit = 15; break;
	}
	return digit;
}
