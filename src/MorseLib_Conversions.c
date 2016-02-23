


/*	MorseLib_Conversions.c
	Implementation of core conversion algorithms
	related to Morse code manipulation

	Author:	Ashis Kumar Das
	Email:	akd.bracu@gmail.com
	BRAC University
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>
#include <BSTTree.h>
#include "MorseLib.h"






/*
 *
 * Function to compare to character by their ASCII value
 * Returns valueOf(k1) - valueOf(k2)
 *
*/
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


int morse_convAsciiToMorse (BSTTree *checkMap, char *AsciiInputString, int AsciiStringLen,
    							char *morseOutputString, int *morseStringLen)
{


	register int globalInputIndex;
	int findResult;
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


int morse_convMorseToAscii (BSTTree *checkMap, char *morseInputString, int morseStringLen,
    							char *AsciiOutputString, int *AsciiStringLen)
{


	register int letterIndex;
	int findResult;
	register int globalInputIndex, globalOutputCounter;
	char spaceChar, nulTerminator;
	char *currentMorseChar, *asciiChar, tempMorseBuffer[20];

	globalInputIndex = 0;
	globalOutputCounter = 0;
	spaceChar = ' ';
	nulTerminator = '\0';

	while (globalInputIndex < morseStringLen) {

		letterIndex = globalInputIndex;
		currentMorseChar = morseInputString + letterIndex;


		/* Search for length of a single letter in morse code	*/
		/* It means, search for the next Separator character in the input stream */
		/* When we get a separator, the characters counted thus far whould be */
		/* a sequence of character in morse, which identifies a character in ASCII */
		while ( letterIndex < morseStringLen
		        && *currentMorseChar != MORSE_LETTER_SEPARATOR
		        && *currentMorseChar != MORSE_WORD_SEPARATOR ) {

			letterIndex = letterIndex + 1;
			currentMorseChar = morseInputString + letterIndex;
		}


		/* We found a sequence of morse character, now get the corresponding ASCII char */
		/* First we copy the sequence into a temporary character buffer */
		memcpy((void*) tempMorseBuffer,
				(const void*) morseInputString + globalInputIndex, letterIndex - globalInputIndex);
		*(tempMorseBuffer + letterIndex - globalInputIndex) = nulTerminator;


		/* Now use the Morse sequence in buffer to find the corresponding ASCII character */
		/* If not found, the morse sequence is probably invalid, and we return abnormally */
		findResult = bst_findElement(checkMap, (void*) tempMorseBuffer, (void**) &asciiChar);
		if (findResult == -1) return -1;


		/* Copy the ASCII character we've found into the Output stream */
		/* In addition to that, we also increment the OutputCounter variable by 1 */
		memcpy((void*) AsciiOutputString + globalOutputCounter,
		       (const void*) asciiChar, sizeof(char));
		globalOutputCounter += sizeof(char);


		/* Ahead of us, the next character(s) can be morse word separator (|) */
		/* We have to skip next characters util we find a normal morse character */
		/* But, word separator means a SPACE character ( ), and should be written */
		/* a SPACE character in Output ASCII stream for each Word Separator we skip */
		while (*currentMorseChar == MORSE_WORD_SEPARATOR) {

			memcpy((void*) AsciiOutputString + globalOutputCounter,
			       (const void*) &spaceChar, sizeof(char));
			globalOutputCounter += sizeof(char);
			
			letterIndex = letterIndex + 1;
			currentMorseChar = morseInputString + letterIndex;
		}

		/* We assume that we've skipped all word separators in the Input Stream */
		/* We are now ready to handle another valid Morse character sequence */
		/* But, a Letter Separator can be present in Input stream this moment */
		/* If this is the case, we simply skip 1 character for Letter Separator */
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


int morse_convMorseToBinary (BSTTree *checkMap, char *morseInputSequence, int morseSequenceLen,
    							char *binaryOutputSequence, int *binarySequenceLen)
{


	register int globalInputIndex;
	register int globalOutputCounter;
	char *morseCharToken, *binaryTokenString;
	int searchResult;

	globalInputIndex = globalOutputCounter = 0;
	binaryTokenString = 0;

	while (globalInputIndex < morseSequenceLen) {

		morseCharToken = morseInputSequence + globalInputIndex;
		searchResult = bst_findElement(checkMap, (void*) morseCharToken, (void**) &binaryTokenString);

		if (searchResult == -1) return -1;

		strcpy(binaryOutputSequence + globalOutputCounter, (const char*) binaryTokenString);

		globalOutputCounter += strlen(binaryTokenString);
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


int morse_convBinaryToMorse (BSTTree *checkMap, char *binaryInputString, int binarySequenceLen,
    							char *morseOutputString, int *morseSequenceLen)
{

	Queue binaryCharQueue;

	register int globalInputIndex;
	register int bufferCounter;
	int globalOutputCounter;

	int searchResult;
	int returnResult;

	char currentInputChar;
	char binaryBuffer[20];
	char *binaryDigit, *morseCharToken;

	globalInputIndex = 0;
	bufferCounter = 0;
	globalOutputCounter = 0;
	returnResult = 0;
	queue_init(&binaryCharQueue, 0);

	while (globalInputIndex < binarySequenceLen) {

		currentInputChar = *(binaryInputString + globalInputIndex);

		/* Enqueue the binary character at hand to the Queue for later processing */
		queue_enqueue(&binaryCharQueue, (void*) (binaryInputString + globalInputIndex));
		globalInputIndex = globalInputIndex + 1;

		
		/* If current input character at hand is a '0', we have got a full segment */
		/* In this case, pop all the characters from the Queue and get the Morse character */
		if (currentInputChar == '0') {

			/* Dequeue all binary symbols from the Queue and store them to buffer */
			while (queue_size(&binaryCharQueue) > 0) {

				queue_dequeue(&binaryCharQueue, (void**) &binaryDigit);
				*(binaryBuffer + bufferCounter) = *binaryDigit;
				bufferCounter = bufferCounter + 1;
			}

			/* At the end of our buffer, place a NUL character to mark end of string */
			*(binaryBuffer + bufferCounter) = '\0';
			
			/* Search for the string from buffer for its corresponding Morse character */
			searchResult = bst_findElement(checkMap, (void*) binaryBuffer, (void**) &morseCharToken);
			returnResult = searchResult;

			/* If we cant find a Morse character for our binary string, its an error */
			if (returnResult == -1) goto EXIT_FUNCTION;

			/* Write the Morse character we have got to the Output stream */
			*(morseOutputString + globalOutputCounter) = *morseCharToken;
			globalOutputCounter++;

			/* printf("Chunk string in buffer: %s, Morse: %c\n", binaryBuffer, *morseCharToken);*/

			/* Clear the buffer, it is enough to set the buffer length to 0 */
			bufferCounter = 0;
		} /* End of IF condition (We just processed a single Morse character) */
		
		/* Start again */
	}
	
	
	/* Check the size of our temporary binary symbol queue */
	/* If elements still exist inside the queue, then it is considered an error */
	if (queue_size(&binaryCharQueue) > 0) {
		returnResult = -1;
		goto EXIT_FUNCTION;
	}

	*morseSequenceLen = globalOutputCounter;

EXIT_FUNCTION:

	/* Clean up and return to the caller */
	queue_destroy(&binaryCharQueue);
	return returnResult;

}

