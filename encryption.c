#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "encryption.h"

size_t GetHexSizeOfStr(unsigned char *str) {
	return (strlen(str) / 2) + (strlen(str) % 2);
}

unsigned char base64HashTable[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
unsigned char *Base2ToBase64(unsigned char *originalBase2, size_t size)
{
	unsigned char *result, *base2;
	unsigned char buffer = 0;
	int totalBitsNeeded;
	int len;
	// # of bytes in the base 64 number will be 4*(ceil(size/3)). This is with padding.
	// If size == 1 then we have a problem because we need bits from the second byte of base for the lower 4 bits of the second hex digit, but there are no such bytes.
	switch (size) {
	case 1:			// We need at least 2 bytes so we will add a zero at the end
		len = 4;
		base2 = malloc(2);
		memcpy(base2, originalBase2, size);
		*(base2 + 1) = 0;
		break;
	case 2:			// If we only have two bytes then the logic below will detect that and we'll skip it.
		len = 4;
		base2 = malloc(2);
		memcpy(base2, originalBase2, size);
		break;
	case 3:
		len = 4;
		base2 = malloc(3);
		memcpy(base2, originalBase2, size);
		break;

	default:
		len = (4 * (size / 3));
		len = len + (3 - (len % 3));
		base2 = malloc(size);
		memcpy(base2, originalBase2, size);
		break;
	}
	size_t i;
	unsigned int nib1, nib2, index;
	result = malloc(len + 1);	// Allocate space for the base 64 string and the null terminator
	int j = 0;
	for (i = 0; i < size; i += 3) {
		printf("i = %d, j = %d, *(result + j + 0) = %u\n", i, j, *(result + j + 0));

		// Extract 4 6-bit digits from 3 bytes 
		*(result + (j + 0)) = base64HashTable[shifter(*base2, ((int[2]) { 2, 0 }))];
		printf("hash --> %u = %c\n", *base2, base64HashTable[shifter(*(base2), (int[]) { 2, 0 })]);


		nib1 = shifter(*(base2), (int[]) { -6, 2, 0 });
		nib2 = shifter(*(base2 + 1), (int[]) { 4, 0 });
		index = nib1 | nib2;

		*(result + (j + 1)) = base64HashTable[index];

		*(result + (j + 2)) = (i + 1 < size) ? base64HashTable[shifter(*(base2 + 1), (int[]) { -4, 2, 0 }) | shifter(*(base2 + 2), (int[]) { 6, 0 })] : '=';

		*(result + (j + 3)) = (i + 2 < size) ? base64HashTable[shifter(*(base2 + 2), (int[]) { -2, 2, 0 })] : '=';
		j += 4;
		base2 += 3;
	}

	result[len] = '\0';	// We allocated space for the null terminator. It's all good.

	return result;
}
unsigned char shifter(unsigned char byte, int shift[]) {
	int i = 0;
	int len = 0;
	int j;
	while (shift[i] != 0) {
		if (shift[i] > 0) {
			len = shift[i];
			for (j = 0; j < len; j++) { byte = byte >> 1; }
		}
		else {
			len = 0 - shift[i];
			for (j = 0; j < len; j++) { byte = byte << 1; }
		}
		i++;
	}
	return byte;
}

unsigned char buildMask(int numOfBits)
{
	int i;
	unsigned char mask = 1;
	for (i = 0; i < numOfBits; i++) {
		mask << 1;
		mask += 1;
	}
	return mask;
}

unsigned char hexHashTable[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
unsigned char *Base2ToHex(unsigned char datum) {
	unsigned char *result = (unsigned char *)malloc(2);

	result[0] = hexHashTable[shifter(datum, (int[]) { 4, 0 })]; // left nibble
	//printf("%u = %c", datum, result[0]);
	result[1] = hexHashTable[shifter(datum, (int[]) { -4, 4, 0 })]; // right nibble
	//printf("%c\n", result[1]);

	return result;
}
unsigned char *EncodeHexString(unsigned char *buffer, size_t size) {
	unsigned char *result = (unsigned char *)malloc((size * 2) + 1); // each byte is 2 hex characters. Alloc 1 for null terminator
	//printf("%u", size);
	result[size * 2] = '\0';
	int i;
	for (i = 0; i < size; i++) {
		unsigned char *twoHexChars = Base2ToHex(buffer[i]);
		result[(i * 2) + 0] = twoHexChars[0];
		result[(i * 2) + 1] = twoHexChars[1];
		//printf("%c%c", twoHexChars[0], twoHexChars[1]);
		free(twoHexChars);
	}
	//printf("\n");

	return result;
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
	unsigned char *result = (unsigned char *)malloc((hexlen / 2) + (strlen(hex) % 2));
	//printf("%d\n", hexlen);

	int i = 0;
	for (; i < hexlen; i += 2) {
		unsigned char leftnib = HexCharToBase10(hex[i]);
		unsigned char rightnib = (i + 1 < hexlen) ? HexCharToBase10(hex[i + 1]) : 0; // Append zero if odd length
		//printf("nibs: %u %u\n", leftnib, rightnib);
		result[i / 2] = (leftnib << 4) | rightnib;
		//printf("i result: %d %u\n", i / 2, result[i / 2]);
	}

	return result;
}

unsigned char *XorEqualLengthBuffers(unsigned char *bufferA, unsigned char *bufferB, size_t size) {
	unsigned char *result = (unsigned char *)malloc(size);
	int i;
	for (i = 0; i < size; i++)
		result[i] = bufferA[i] ^ bufferB[i]; // xor

	return result;
}