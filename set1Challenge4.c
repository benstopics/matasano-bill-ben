/**********************************
* set1challenge4.c                *
* Bill Nicholson                  *
*                                 *
http://cryptopals.com/sets/1/challenges/4/
Detect single-character XOR
One of the 60-character strings in this file has been encrypted by single-character XOR.
Find it.
(Your code from #3 should help.)
***********************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "encryption.h"
#include "set1.h"

#define DATAFILE "set1Challenge4.txt"
static long analyze(char *tmp);
static void processText(char *msg);

void set1Challenge4() {
	FILE *handle;
	fopen_s(&handle, DATAFILE, "r");
	char buffer[80];
	int i = 0;

	if (handle != NULL) {
		while (fgets(buffer, 80, handle) != 0) {
			
			printf("\n %d: processing %s", i, buffer);
			processText(buffer);



			i++;
		}

	} else {
		perror(DATAFILE);
		printf("\n Error opening %s", DATAFILE);
	}


}
static void processText(char *msg) {
	size_t size = GetHexSizeOfStr(msg);
	long score, highScore = -1;
	unsigned char *hexData = HexToBase2(msg);
	unsigned int i, j, highScoreIdx = 0;
	for (i = 0; i < 256; i++) {
		// XOR the original string with a constant value
		unsigned char *tmp = malloc(size + 1); // +1 for null terminator
		*(tmp + size) = 0; // null terminator
		//printf("%u ==> ", i);
		for (j = 0; j < size; j++) {
			*(tmp + j) = *(hexData + j) ^ i;
			//if (*(tmp + j) == 0) // Convert false null to space for printing
			//	*(tmp + j) = 32;
			//printf("%c", *(tmp + j));
		}
		score = 0;
		score = analyze(tmp);
		if (score > highScore) {
			highScore = score;
			highScoreIdx = i;
			printf("\n new high score = %ld  at index %d ==> ", score, i);
			for (j = 0; j < size; j++) {
				printf("%c", *(tmp + j));
			}

		}
	}
}

static long analyze(char *tmp) {
	long score = 0;
	int scoreArray[26];	// a bucket for each letter in the alphabet
	int i, idx, controlCharacterCount = 0, spaceCount = 0;;
	unsigned char letter;
	for (i = 0; i < 26; i++) scoreArray[i] = 0;

	// Count the instances of each letter in the english alphabet
	for (i = 0; *(tmp + i) != 0; i++) {
		letter = *(tmp + i);
		if (isspace(letter)) {
			spaceCount++;
		}
		else {
			if (iscntrl(letter)) {
				controlCharacterCount++;
			}
			else {
				letter = toupper(*(tmp + i));
				if (letter >= 'A' && letter <= 'Z') {
					idx = letter - 'A';
					scoreArray[idx]++;
				}
			}
		}
	}
	return score;
}