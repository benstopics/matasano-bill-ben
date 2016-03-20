#include <stdio.h>
#include <string.h>

#include "encryption.h"

void set1challenge2() {
	unsigned char *hexA = "1c0111001f010100061a024b53535009181c";
	printf("%s\nXOR\n", hexA);
	unsigned char *hexB = "686974207468652062756c6c277320657965";
	printf("%s\n=\n", hexB);
	unsigned char *xorData = XorEqualLengthBuffers(HexToBase2(hexA), HexToBase2(hexB), (strlen(hexA) / 2) + (strlen(hexA) % 2)); // integer half of strlen + remainder, if odd
	unsigned char *result = EncodeHexString(xorData, strlen(hexA) / 2);
	printf("746865206b696420646f6e277420706c6179\n%s\nMatches?\n", result);

	getc(stdin);
}