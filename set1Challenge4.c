/**********************************
* set1challenge4.c                *
* Bill Nicholson                  *
*                                 *
http://cryptopals.com/sets/1/challenges/4/
Detect single-character XOR
One of the 60-character strings in this file has been encrypted by single-character XOR.
Find it.
(Your code from #3 should help.)

Solution:
line # 170 (zero-based): XOR character = 53, high score = 15, decoded = Now that the party is jumping

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
	unsigned char XORCharacter;
	int highestScore;
	char *bestDecode;

	if (handle != NULL) {
		while (fgets(buffer, 80, handle) != 0) {
			//if (i == 170)
			//	i = i;
			//printf("\n %d: processing %s", i, buffer);
			processText(buffer, &XORCharacter, &highestScore, &bestDecode);
			if (highestScore > 0) {
				printf("\n line # %d: XOR character = %d, high score = %d, decoded = %s", i, XORCharacter, highestScore, bestDecode);
				int x = strlen(bestDecode);
				printf("\n 1 %u %c", bestDecode[x], bestDecode[x]);
				printf("\n 2 %u %c", bestDecode[x - 1], bestDecode[x-1]);
				printf("\n 3 %u %c", bestDecode[x - 2], bestDecode[x-2]);
				//printf("\n 3 %u", bestDecode[x + 1]);
			}
			i++;
			//break;
		}
	} else {
		perror(DATAFILE);
		printf("\n Error opening %s", DATAFILE);
	}
}
static void processText(char *msg, unsigned char *XORCharacter, int *highestScore, char **bestDecode) {

	// I think the GetHexSizeOfStr is adding one extra char. I subtract it off here. This prevents a spurious character a the end of the decoded string, after the line feed that is in the string. 
	size_t size = GetHexSizeOfStr(msg) - 1;
	
	long score, highScore = -1;
	unsigned char *hexData = HexToBase2(msg);
	unsigned int i, j, highScoreIdx = 0;
	*bestDecode = malloc(size + 1); // +1 for null terminator
	*(*bestDecode + size) = 0;
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
			//printf("\n new high score = %ld WITH XOR character %d ==> ", score, i);
			memcpy(*bestDecode, tmp, size);
			//for (j = 0; j < size; j++) {printf("%c", *(tmp + j));}
		}
	}
	*XORCharacter = highScoreIdx;
	*highestScore = highScore;
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
	// r,s,t,l,n,e occur most often according to Wheel of Fortune TV show
	// See also https://en.wikipedia.org/wiki/Letter_frequency
	score += scoreArray['R' - 'A'];
	score += scoreArray['S' - 'A'];
	score += scoreArray['T' - 'A'];
	score += scoreArray['L' - 'A'];
	score += scoreArray['N' - 'A'];
	score += scoreArray['A' - 'A'];
	score += scoreArray['E' - 'A'];
	score += scoreArray['I' - 'A'];
	score += scoreArray['O' - 'A'];
	score += scoreArray['U' - 'A'];

	if (controlCharacterCount > 0) score = 0;
	if (spaceCount < 5) score = 0;
	return score;
}