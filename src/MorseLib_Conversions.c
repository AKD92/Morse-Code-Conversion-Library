


/*	MorseCode_Utilities.c
	Implementation of core conversion algorithms
	related to Morse code manipulation

	Author:	Ashis Kumar Das
	akd.bracu@gmail.com
	BRAC University
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <BSTTree.h>
#include "MorseLib.h"




int cmp_character(const void *k1, const void *k2);






/*
	Convert ASCII text string to morse code string
	The resulting morse code string does not contain a NUL terminator \0
	at the end of the string

	in:
		BSTTree checkMap			- Mapping of (key: ASCII character, value: Morse string)
		char* AsciiInputString      - ASCII text to convert
		int AsciiStringLen          - Length of ASCII text input
	out:
		char* morseOutputString		- Pre-allocated memory space to hold Morse characters
									  as output. Will not contain NUL terminator (\0) at the end
		int morseStringLen			- Length of morse string output

	Return 0 for successful, -1 for failure.
*/


int morse_convAsciiToMorse(
    BSTTree *checkMap,
    char *AsciiInputString, int AsciiStringLen,
    char *morseOutputString, int *morseStringLen
) {


	int globalInputIndex, findResult;
	register int globalOutputCounter;
	char *currentAscii, *morseSingleString;
	char morseLetterSeparator;
	char spaceChar;
	int morseSingleLen;

	unsigned int hasNextAscii, nextIsSpace, writtenBar;
	unsigned int writeLetterSeparator;

	findResult = -1;
	globalInputIndex = 0;
	globalOutputCounter = 0;
	spaceChar = ' ';
	morseLetterSeparator = MORSE_LETTER_SEPARATOR;

	while ( globalInputIndex < AsciiStringLen ) {

		currentAscii = AsciiInputString + globalInputIndex;
		findResult = bst_findElement(checkMap, (void*) currentAscii, (void**) &morseSingleString);

		if (findResult == -1) return -1;

		morseSingleLen = strlen(morseSingleString);
		memcpy((void *) morseOutputString + globalOutputCounter,
		       (const void *) morseSingleString, morseSingleLen);
		globalOutputCounter = globalOutputCounter + morseSingleLen;

		/*	detect if it is necessary to write a letter separator on the output stream	*/
		hasNextAscii = globalInputIndex == AsciiStringLen - 1 ? 0 : 1;
		nextIsSpace = hasNextAscii == 1
					  &&
		              (cmp_character((const void*) AsciiInputString + globalInputIndex + 1,
					  (const void*) &spaceChar) == 0) ? 1 : 0;
		writtenBar = *(morseOutputString + globalOutputCounter - 1) == MORSE_WORD_SEPARATOR ?
		             1 : 0;
		writeLetterSeparator = hasNextAscii & !(nextIsSpace | writtenBar);
		
/*		printf("hasNextAscii: %d nextSpace: %d writtenBar: %d\n", hasNextAscii, nextSpace, writtenBar);*/

		if (writeLetterSeparator == 1) {
			memcpy((void *) (morseOutputString + globalOutputCounter),
			       (const void *) &morseLetterSeparator, sizeof(char));
			globalOutputCounter = globalOutputCounter + sizeof(char);
		}

		globalInputIndex = globalInputIndex + 1;
	}
	*morseStringLen = globalOutputCounter;

	return 0;
}






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
) {


	register int letterIndex;
	int findResult;
	int globalInputIndex, globalOutputCounter;
	char spaceChar, nulTerminator;
	char *currentMorseChar, *asciiChar, tempBuffer[20];

	globalInputIndex = 0;
	globalOutputCounter = 0;
	spaceChar = ' ';
	nulTerminator = '\0';

	while (globalInputIndex < morseStringLen) {

		letterIndex = globalInputIndex;
		currentMorseChar = morseInputString + letterIndex;

		/*	Search for length of a single letter in morse code	*/
		while ( letterIndex < morseStringLen
		        && *currentMorseChar != MORSE_LETTER_SEPARATOR
		        && *currentMorseChar != MORSE_WORD_SEPARATOR ) {

			letterIndex = letterIndex + 1;
			currentMorseChar = morseInputString + letterIndex;
		}

		memcpy((void*) tempBuffer, (const void*) morseInputString + globalInputIndex,
		       letterIndex - globalInputIndex);
		*(tempBuffer + letterIndex - globalInputIndex) = nulTerminator;

		/*		printf("Buffer has : %s J is : %d\n", buffer, j);*/

		findResult = bst_findElement(checkMap, (void*) tempBuffer, (void**) &asciiChar);
		if (findResult == -1) return -1;

		memcpy((void*) AsciiOutputString + globalOutputCounter,
		       (const void*) asciiChar, sizeof(char));
		globalOutputCounter += sizeof(char);

		while (*currentMorseChar == MORSE_WORD_SEPARATOR) {

			memcpy((void*) AsciiOutputString + globalOutputCounter,
			       (const void*) &spaceChar, sizeof(char));
			globalOutputCounter += sizeof(char);
			
			letterIndex = letterIndex + 1;
			currentMorseChar = morseInputString + letterIndex;
		}

		if (*currentMorseChar == MORSE_LETTER_SEPARATOR) {
			letterIndex = letterIndex + 1;
		}
		
		globalInputIndex = letterIndex;
	}

	*AsciiStringLen = globalOutputCounter;

	return 0;
}








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
    char *morseInputSequence, int morseSequenceLen,
    char *binaryOutputSequence, int *binarySequenceLen
) {


	int globalInputIndex, globalOutputCounter;
	char *morseCharToken, *binaryTokenSequence;
	int searchResult;

	globalInputIndex = globalOutputCounter = 0;
	binaryTokenSequence = 0;

	while (globalInputIndex < morseSequenceLen) {

		morseCharToken = morseInputSequence + globalInputIndex;
		searchResult = bst_findElement(checkMap, (void*) morseCharToken, (void**) &binaryTokenSequence);

		if (searchResult == -1) return -1;

		strcpy(binaryOutputSequence + globalOutputCounter, (const char*) binaryTokenSequence);

		globalOutputCounter += strlen(binaryTokenSequence);
		globalInputIndex = globalInputIndex + 1;
	}

	*binarySequenceLen = globalOutputCounter;

	return 0;
}







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
    char *binaryInputString, int binarySequenceLen,
    char *morseOutputString, int *morseSequenceLen
) {

	Queue binSymbolQueue;

	int globalInputIndex;
	int bufferCounter;
	int globalOutputCounter;

	int searchResult;
	int returnResult;

	char currentInputChar;
	char binaryBuffer[20];
	char *binaryHotDigit;
	char *morseCharToken;

	queue_init(&binSymbolQueue, 0);

	globalInputIndex = 0;
	bufferCounter = 0;
	globalOutputCounter = 0;

	returnResult = 0;

	while (globalInputIndex < binarySequenceLen) {

		currentInputChar = *(binaryInputString + globalInputIndex);

		queue_enqueue(&binSymbolQueue, (void*) (binaryInputString + globalInputIndex));
		globalInputIndex = globalInputIndex + 1;

		if (currentInputChar == '0') {

			while (queue_size(&binSymbolQueue) > 0) {

				queue_dequeue(&binSymbolQueue, (void**) &binaryHotDigit);
				*(binaryBuffer + bufferCounter) = *binaryHotDigit;
				bufferCounter++;
			}

			*(binaryBuffer + bufferCounter) = '\0';
			searchResult = bst_findElement(checkMap, (void*) binaryBuffer, (void**) &morseCharToken);
			returnResult = searchResult;

			if (returnResult == -1) goto EXIT_FUNCTION;

			*(morseOutputString + globalOutputCounter) = *morseCharToken;
			globalOutputCounter++;

			/*	printf("Chunk string in buffer: %s, Morse: %c\n", binaryBuffer, *morseCharToken);*/

			bufferCounter = 0;
		}

	}

	*morseSequenceLen = globalOutputCounter;

EXIT_FUNCTION:

	queue_destroy(&binSymbolQueue);
	return returnResult;

}
