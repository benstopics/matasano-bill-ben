/**********************************
* set1challenge5.c                *
* Bill Nicholson                  *
* nicholdw@ucmail.uc.edu          *
* Ben Ward                        *
* wardb4@mail.uc.edu              *

http://cryptopals.com/sets/1/challenges/5/

Implement repeating-key XOR

Here is the opening stanza of an important work of the English language:

Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal

Encrypt it, under the key "ICE", using repeating-key XOR.

In repeating-key XOR, you'll sequentially apply each byte of the key; the first byte of plaintext will be XOR'd against I, the next C, the next E, then I again for the 4th byte, and so on.

It should come out to:

0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f

Encrypt a bunch of stuff using your repeating-key XOR function. Encrypt your mail. Encrypt your password file. Your .sig file. Get a feel for it. I promise, we aren't wasting your time with this.

***********************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encryption.h"

char *encodeWithrepeatingKeyXOR(unsigned char *plainText, unsigned char *key);

void set1Challenge5() {
	unsigned char *expectedResult = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
	unsigned char *result;
	//                                            1         2         3         4         5         6         7
	//                                  012345678901234567890123456789012345678901234567890123456789012345678901234
	result = encodeWithrepeatingKeyXOR("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal", "ICE");
	printf("Set 1 Challenge 5: %s", result);
	if (strcmp(result, expectedResult) == 0) {
		printf("\ntest passed");
	} else {
		printf("\ntest FAILED");
	}
}

char *encodeWithrepeatingKeyXOR(unsigned char *plainText, unsigned char *key) {
	int i, len, lenKey;
	len = strlen(plainText);
	lenKey = strlen(key);
	unsigned char *result = malloc((len * 2) + 1);
	unsigned char *resultIdx = result;
	unsigned char keyChar, encodedChar;
	int j = 0;
	for (i = 0; i < len; i++) {
		keyChar = *(key + (j % lenKey));
		encodedChar = *(plainText + i);
		encodedChar = encodedChar ^ keyChar;
		sprintf_s(resultIdx, len*2, "%02x", encodedChar);
		resultIdx += 2;
		j++;
	}
	// Add null terminator to the encoded string. 
	*(result + 2*len) = 0;
	return result;

}