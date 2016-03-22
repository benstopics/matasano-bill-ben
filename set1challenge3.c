/**********************************
* set1challenge3.c                *
* Bill Nicholson                  *
*                                 *
***********************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "encryption.h"

unsigned char *set1challenge3(unsigned char *msg) {
	size_t size = GetHexSizeOfStr(msg);
	unsigned char *result = malloc(size + 1); // +1 for null terminator
	unsigned char *hexData = HexToBase2(msg);
	unsigned char j;
	unsigned int i, k;
	unsigned char highNibble, lowNibble;
	unsigned char ASCIIChar;

	for (i = 0; i < 256; i++) {
		// XOR the original string with a constant value
		unsigned char *tmp = malloc(size + 1); // +1 for null terminator
		*(tmp + size) = 0; // null terminator
		printf("%u ==> ", i);
		for (j = 0; j < size; j++) {
			*(tmp + j) = *(hexData + j) ^ i;
			if (*(tmp + j) == 0) // Convert false null to space for printing
				*(tmp + j) = 32;
			printf("%c", *(tmp + j));
		} printf("\n");

		// Eye-balled it
		if (i == 120)
			result = tmp;

		/*k = 0;
		// Convert the newly created string to ASCII characters. We assume that the newly created string contains 2-byte ASCII hex codes.
		for (j = 0; j < size; j += 2) {
			highNibble = *(tmp + j);
			lowNibble = *(tmp + j + 1);
			ASCIIChar = (ASCIIhexToBinary(highNibble) * 16) + ASCIIhexToBinary(lowNibble);
			*(tmp + k) = ASCIIChar;
			k++;
		}*/
		//printf("\n %d <%s>", i, tmp, size);
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
