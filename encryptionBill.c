// Encryption.c

#include <string.h>
#include "encryption.h"

unsigned char *HexToBase2(unsigned char *hex)
{
	unsigned char *result;
	int len = strlen(hex);
	int nibbleCount, targetIdx, resultLen;
	unsigned char mask = 0, buffer = 0;
	resultLen = malloc( len/2 + (len % 2) ? 1:0);
	result = malloc( len/2 + (len % 2) ? 1:0);
	
	nibbleCount = 1;
	targetIdx = result;
	for (i = len-1; i >= 0; i--) {
		switch (*(hex+i)) (
			case '0': mask = 0;					break;
			case '1': mask = 1;					break;
			case '2': mask = 2;					break;
			case '3': mask = 3;					break;
			case '4': mask = 4;					break;
			case '5': mask = 5;					break;
			case '6': mask = 6;					break;
			case '7': mask = 7;					break;
			case '8': mask = 8; 				break;
			case '9': mask = 9; 				break;
			case 'A': case 'a': 	mask = 10;	break;
			case 'B': case 'b':     mask = 11;	break;
			case 'C': case 'c':     mask = 12;	break;
			case 'D': case 'd':     mask = 13;	break;
			case 'E': case 'e':     mask = 14;	break;
			case 'F': case 'f':     mask = 15;	break;
		}
		buffer << 4;
		nibbleCount++;
		if (nibbleCount > 2) {
			result
		}
	}
	
	return result;
}
