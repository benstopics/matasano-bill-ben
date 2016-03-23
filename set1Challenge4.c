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

#define DATAFILE "setChallenge4.txt"

void setChallenge5() {
	FILE *handle = fopen(DATAFILE, "r");
	char * buffer[80];

	if (handle != NULL) {
		while (fgets(buffer, 80, handle) != 0) {
			printf("\n processing %s", buffer);

		}

	} else {
		perror(DATAFILE);
		printf("\n Error opening %s", DATAFILE);
	}


}