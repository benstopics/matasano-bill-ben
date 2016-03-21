/**********************************************
 * main.c                                     *
 * Ben Ward                                   *
 * Bill Nicholson nicholdw@ucmail.uc.edu      *
 **********************************************/

#include <stdio.h>
#include <string.h>
#include "set1.h"

void main() {
	//set1challenge1();

	//set1challenge2();

	// unsigned char a = 90, b = 10, c; c = (a ^ b) ^ b; printf("\n c = %d", c);

	unsigned char *sc3 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	set3challenge3(sc3, strlen(sc3) );

	getc(stdin);

}