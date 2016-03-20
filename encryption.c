#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned char shifter(unsigned char byte, int shift1, int shift2);

unsigned char hashTable[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
                             'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
							 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
unsigned char *Base2ToBase64(unsigned char *base2, size_t size)
{
	unsigned char *result;
	unsigned char buffer = 0;
	int len = (strlen(base2) / 3) + (strlen(base2) % 3) + 1;
	int i, numOfBits = 6;
	int bitsToShift = 2;
	int shifts[4] = {0,0,0,0};
	result = malloc(len);
	//unsigned char mask;
	int j = 0;
	for (i = 0; i < size - 1; i+=3) {
		printf("i = %d, j = %d, *(result + j + 0) = %u\n", i, j, *(result + j + 0));
	
		// Extract 4 6-bit digits from 3 bytes 
		*(result + j + 0) = hashTable[shifter(*(base2    ),  2, 0)];
		printf("hash --> %u = %c\n", *base2, hashTable[shifter(*(base2    ),  2, 0)]);
		*(result + j + 1) = hashTable[shifter(*(base2    ), -6, 2) & shifter(*(base2 + 1), 4, -4)];
		*(result + j + 2) = (i + 1 < size) ? hashTable[shifter(*(base2 + 1), -4, 4) & shifter(*(base2 + 2), 6,  0)] : '=';
		*(result + j + 3) = (i + 2 < size) ? hashTable[shifter(*(base2 + 2), -2, 2)] : '=';
		j += 4;
		base2 += 3;
	}
	
	result[strlen(result) - 1] = '\0';
	
	return result;
}
unsigned char shifter(unsigned char byte, int shift1, int shift2) {
	int i = 0;
	int len = 0;
	int j;
	if (shift1 > 0) {
		len = shift1;
		for (j = 0; j < len; j++) {	byte >> 1;}
	} else {			
		len = 0 - shift1;
		for (j = 0; j < len; j++) {byte << 1;}
	}
	if (shift2 > 0) {
		len = shift2;
		for (j = 0; j < len; j++) {	byte >> 1;}
	} else {			
		len = 0 - shift2;
		for (j = 0; j < len; j++) {byte << 1;}
	}
	return byte;
}

unsigned char buildMask(int numOfBits)
{
	int i;
	unsigned char mask = 1;
	for (i =0 ; i < numOfBits; i++) {
		mask << 1;
		mask += 1;
	}
	return mask;
}
unsigned int HexCharToBase10(unsigned char hex) {
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

unsigned char *HexToBase2(unsigned char *hex) {
	int hexlen = strlen(hex);
	unsigned char *result = (unsigned char *) malloc((hexlen / 2) + ((strlen(hex)%2 == 1) ? 1 : 0));
	printf("%d\n", hexlen);
	
	int i = 0;
	for (;i < hexlen; i+=2) {
		unsigned char leftnib = HexCharToBase10(hex[i]);
		unsigned char rightnib = (i+1 < hexlen) ? HexCharToBase10(hex[i+1]) : 0; // Append zero if odd length
		printf("nibs: %u %u\n", leftnib, rightnib);
		result[i/2] = (leftnib << 4) | rightnib;
		printf("i result: %d %u\n", i/2, result[i/2]);
	}
	
	return result;
}