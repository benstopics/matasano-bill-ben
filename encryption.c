#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char HexCharToBase10(unsigned char hex) {
	switch (hex) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
			return 10;
		case 'b':
			return 11;
		case 'c':
			return 12;
		case 'd':
			return 13;
		case 'e':
			return 14;
		case 'f':
			return 15;
	}
}

// Assumes 
unsigned char *HexToBase2(unsigned char *hex) {
	int hexlen = strlen(hex); // Length of string
	unsigned char *result = (unsigned char *) malloc(hexlen / 2);
	printf("%d\n", hexlen);
	
	int i = 0;
	for (;i < hexlen; i+=2) {
		unsigned char leftnib = HexCharToBase10(hex[i]);
		unsigned char rightnib = HexCharToBase10(hex[i+1]);
		printf("%d %d\n", leftnib, rightnib);
		result[i/2] = (leftnib << 4) | rightnib;
		printf("%d %d\n", i/2, result[i/2]);
	}
	
	return result;
}