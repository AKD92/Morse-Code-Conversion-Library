



/*	MorseCode.h
	Morse Code functions header file

	Author:	Ashis Kumar Das <akd.bracu@gmail.com>
	BRAC University
*/






#ifndef MORSECODE_H
#define MORSECODE_H







#include <BSTTree.h>


#define MORSE_DOT '.'
#define MORSE_DASH '-'
#define MORSE_LETTER_SEPARATOR '/'
#define MORSE_WORD_SEPARATOR '|'

#define BINARY_DOT "0"
#define BINARY_DASH "10"
#define BINARY_LETTER_SEPARATOR "110"
#define BINARY_WORD_SEPARATOR "1110"



void morse_createAsciiToMorseMapping(BSTTree *textToMorse);

void morse_createMorseToAsciiMapping(BSTTree *morseToText);

void morse_createMorseToBinaryMapping(BSTTree *morseToBinary);

void morse_createBinaryToMorseMapping(BSTTree *binaryToMorse);












/*
	Converts binary bit string into morse string
	You can obtain a BSTTree Morse-To-Binary mapping through the function
	morse_createMorseToBinaryMapping(BSTTree *morseToBinary)
	
	in:
		BSTTree *checkMap			- Mapping of Binary string to Morse characters
		char *bnaryInputString		- Binary string for input, eg. 1101001101101010
		int binaryStringLen			- Length of binary string input
	out:
		char *morseOutputString		- Pre-allocated memory space to hold morse characters
									  as output. Will not contain NUL terminator (\0) at the end
		int *morseStringLen			- Length of morse characters output

	Returns 0 for successfule convertion, -1 otherwisw
*/

int morse_convBinaryToMorse(
    BSTTree *checkMap,
    char *binaryInputString, int binaryStringLen,
    char *morseOutputString, int *morseStringLen
);








/*
	Converts morse string into binary bit string
	You can obtain a BSTTree Binary-to-Morse mapping through the function
	morse_createBinaryToMorseMapping(BSTTree *binaryToMorse)
	
	in:
		BSTTree *checkMap			- Mapping of Morse characters to Binary strings
		char *morseInputString		- Morse string for input, eg. .../---/... (SOS)
		int morseStringLen			- Length of morse string input
	out:
		char *binaryOutputString	- Pre-allocated memory space to hold binary bit characters
									  as output. Will not contain NUL terminator (\0) at the end
		int *binaryStringLen		- Length of binary bits output

	Returns 0 for successfule convertion, -1 otherwisw
*/


int morse_convMorseToBinary(
    BSTTree *checkMap,
    char *morseInputString, int morseStringLen,
    char *binaryOutputString, int *binaryStringLen
);










/*
	Convert ASCII text string to morse code string
	The resulting morse code string does not contain a NUL terminator \0
	at the end of the string

	in:
		BSTTree checkMap			- Mapping of (key: ASCII character, value: Morse string)
		char *AsciiInputString		- ASCII text to convert
		int AsciiStringLen			- Length of ASCII text input
	out:
		char *morseOutputString		- Pre-allocated memory space to hold Morse characters
									  as output. Will not contain NUL terminator (\0) at the end
		int *morseStringLen			- Length of morse string output

	Return 0 for successful, -1 for failure.
*/


int morse_convAsciiToMorse(
    BSTTree *checkMap,
    char *AsciiInputString, int AsciiStringLen,
    char *morseOutputString, int *morseStringLen
);











/*
	Convert morse code string to ASCII text string
	The resulting morse code string does not contain a NUL terminator \0
	at the end of the string

	in:
		BSTTree checkMap			- Mapping of (key: Morse string, value: ASCII character)
		char *morseInputString		- Morse characters to convert
		int morseStringLen			- Length of Morse character input
	out:
		char *AsciiOutputString   	- Pre-allocated memory space to hold ASCII characters
									  as output. Will not contain NUL terminator (\0) at the end
		int *AsciiStringLen			- Length of ASCII character output

	Return 0 for successful, -1 for failure.
*/


int morse_convMorseToAscii(
    BSTTree *checkMap,
    char *morseInputString, int morseStringLen,
    char *AsciiOutputString, int *AsciiStringLen
);











#endif
