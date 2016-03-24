/**********************************
* set1challenge6.c                *
* Bill Nicholson                  *
* nicholdw@ucmail.uc.edu          *
* Ben Ward                        *
* wardb4@mail.uc.edu              *

http://cryptopals.com/sets/1/challenges/6/
***********************************/
#include <stdio.h>

int computeHammingDistance(unsigned char *s1, unsigned char *s2, int length);


void set1Challenge6() {
	// Test the Hamming Distance Function
	unsigned char *s1 = "this is a test";
	unsigned char *s2 = "wokka wokka!!!";
	int hammingDistance = computeHammingDistance(s1, s2, strlen(s1));
	printf("\nSet 1 Challenge 6: hamming distance between %s and %s is %d", s1, s2, hammingDistance);
	if (hammingDistance == 37) { printf("\n Test Passed"); } else { printf("\n Test FAILED"); }



}

// s1 and s2 should be the same length
int computeHammingDistance(unsigned char *s1, unsigned char *s2, int length){
	int hammingDistance = 0;
	int i;
	unsigned char xor;
	for (i = 0; i < length; i++) {
		xor = *(s1 + i) ^ *(s2 + i);
		while (xor > 0) {
			if (xor % 2) { hammingDistance++; }
			xor = xor >> 1;

		}
	}
	return hammingDistance;
}

