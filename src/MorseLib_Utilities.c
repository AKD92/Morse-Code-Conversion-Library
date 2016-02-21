


/*	MorseCode_Utilities.c
	Implementation of Utility functions and algorithms
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




/*///////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////	INTER-MODULE FUNCTION DECLARATIONS		/////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////*/


int cmp_character(const void *k1, const void *k2);
int cmp_string(const void *k1, const void *k2);

/*__inline__ int cmp_character(const void *k1, const void *k2) __attribute__((always_inline));
__inline__ int cmp_string(const void *k1, const void *k2) __attribute__((always_inline));*/

void morse_buildMorseAsciiObjectList(Queue *asciiQueue, Queue *morseQueue);








/*///////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////	INTER-MODULE FUNCTION IMPLEMENTATIONS	/////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////*/



int cmp_character(const void *k1, const void *k2) {

	const char *c1, *c2;
	int compareValue;
	
	c1 = (const char*) k1;
	c2 = (const char*) k2;
	compareValue = *c1 - *c2;
	
	return compareValue;
}

int cmp_string(const void *k1, const void *k2) {

	const char *c1, *c2;
	int compareValue;

	c1 = (const char*) k1;
	c2 = (const char*) k2;
	compareValue = strcmp(c1, c2);
	
	return compareValue;
}





/*///////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////	GLOBAL UTILITY FUNCTION IMPLEMENTATIONS	/////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////*/




void morse_createMorseToBinaryMapping(BSTTree *morseToBinary) {

	char cdot, cdash, cspc_l, cspc_w;
	void *bdot, *bdash, *bspc_l ,*bspc_w;
	void *kdot, *kdash, *kspc_l, *kspc_w;

	cdot = MORSE_DOT;
	cdash = MORSE_DASH;
	cspc_l = MORSE_LETTER_SEPARATOR;
	cspc_w = MORSE_WORD_SEPARATOR;

	bdot = malloc(strlen(BINARY_DOT) + 1);
	bdash = malloc(strlen(BINARY_DASH) + 1);
	bspc_l = malloc(strlen(BINARY_LETTER_SEPARATOR) + 1);
	bspc_w = malloc(strlen(BINARY_WORD_SEPARATOR) + 1);

	kdot = malloc(sizeof(char));
	kdash = malloc(sizeof(char));
	kspc_l = malloc(sizeof(char));
	kspc_w = malloc(sizeof(char));

	strcpy((char*) bdot, BINARY_DOT);
	strcpy((char*) bdash, BINARY_DASH);
	strcpy((char*) bspc_l, BINARY_LETTER_SEPARATOR);
	strcpy((char*) bspc_w, BINARY_WORD_SEPARATOR);

	memcpy(kdot, (void*) &cdot, sizeof(char));
	memcpy(kdash, (void*) &cdash, sizeof(char));
	memcpy(kspc_l, (void*) &cspc_l, sizeof(char));
	memcpy(kspc_w, (void*) &cspc_w, sizeof(char));

	bst_init(morseToBinary);
	morseToBinary->compare_key = cmp_character;
	morseToBinary->destroy_key = free;
	morseToBinary->destroy_data = free;

	bst_insert(morseToBinary, kdot, bdot);
	bst_insert(morseToBinary, kdash, bdash);
	bst_insert(morseToBinary, kspc_l, bspc_l);
	bst_insert(morseToBinary, kspc_w, bspc_w);

	return;
}





void morse_createBinaryToMorseMapping(BSTTree *binaryToMorse) {

	char cdot, cdash, cspc_l, cspc_w;
	void *bdot, *bdash, *bspc_l, *bspc_w;
	void *kdot, *kdash, *kspc_l, *kspc_w;

	cdot = MORSE_DOT;
	cdash = MORSE_DASH;
	cspc_l = MORSE_LETTER_SEPARATOR;
	cspc_w = MORSE_WORD_SEPARATOR;

	bdot = malloc(strlen(BINARY_DOT) + 1);
	bdash = malloc(strlen(BINARY_DASH) + 1);
	bspc_l = malloc(strlen(BINARY_LETTER_SEPARATOR) + 1);
	bspc_w = malloc(strlen(BINARY_WORD_SEPARATOR) + 1);

	kdot = malloc(sizeof(char));
	kdash = malloc(sizeof(char));
	kspc_l = malloc(sizeof(char));
	kspc_w = malloc(sizeof(char));

	strcpy((char*) bdot, BINARY_DOT);
	strcpy((char*) bdash, BINARY_DASH);
	strcpy((char*) bspc_l, BINARY_LETTER_SEPARATOR);
	strcpy((char*) bspc_w, BINARY_WORD_SEPARATOR);

	memcpy(kdot, (void*) &cdot, sizeof(char));
	memcpy(kdash, (void*) &cdash, sizeof(char));
	memcpy(kspc_l, (void*) &cspc_l, sizeof(char));
	memcpy(kspc_w, (void*) &cspc_w, sizeof(char));

	bst_init(binaryToMorse);
	binaryToMorse->compare_key = cmp_string;
	binaryToMorse->destroy_key = free;
	binaryToMorse->destroy_data = free;

	bst_insert(binaryToMorse, bdot, kdot);
	bst_insert(binaryToMorse, bdash, kdash);
	bst_insert(binaryToMorse, bspc_l, kspc_l);
	bst_insert(binaryToMorse, bspc_w, kspc_w);

	return;
}






/*int morse_queueEnqueueString(Queue *queue, char *charSeq, int len) {*/

/*	char *newstr;*/
/*	newstr = malloc(len);*/

/*	memcpy((void*) newstr, (const void*) charSeq, len);*/
/*	return queue_enqueue(queue, (void*) newstr);*/
/*}*/








void morse_buildMorseAsciiObjectList(Queue *asciiQueue, Queue *morseQueue) {


	register unsigned int currentIndex;
	char *asciiMemorySpace, *currentAsciiChar;
	char *morseMemorySpace, *currentMorseString;
	char wordSeparator[3];

	sprintf(wordSeparator, "%c\0", MORSE_WORD_SEPARATOR);

	char *morseCodes[51] = {
		/*		From capital A to Z		*/
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
		"....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
		"--.-",
		".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
		/*		From 0 to 9	(numeric characters)	*/
		".----", "..---", "...--", "....-", ".....", "-....", "--...",
		"---..",
		"----.", "-----",
		/*		Special characters								*/
		/*		In order: <space> + - * / = ( ) ? ! . ' " , ;	*/
		wordSeparator,
		".-.-.", "-....-", "-.-.-", "-..-.", "-...-",
		"-.--.", "-.--.-", "..--..", "..--.-", ".-.-.-",
		".----.", ".-..-.", "--..--", "---..."
	};

	char asciiChars[51] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
	                        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	                        ' ',
	                        '+', '-', '*', '/', '=',
	                        '(', ')', '?', '!', '.',
	                        '\'', '"', ',', ';'
	                      };

	currentIndex = 0;
	morseMemorySpace = 0;
	asciiMemorySpace = 0;

	while ( currentIndex < 51 ) {

		currentMorseString = morseCodes[currentIndex];
		currentAsciiChar = asciiChars + currentIndex;

		morseMemorySpace = (char*) malloc(strlen(currentMorseString) + 1);
		asciiMemorySpace = (char*) malloc(sizeof(char));

		strcpy(morseMemorySpace, (const char*) currentMorseString);
		memcpy((void*) asciiMemorySpace, (const void*) currentAsciiChar, sizeof(char));

		queue_enqueue(asciiQueue, (const void*) asciiMemorySpace);
		queue_enqueue(morseQueue, (const void*) morseMemorySpace);

		currentIndex = currentIndex + 1;
	}

	return;
}





void morse_createAsciiToMorseMapping(BSTTree *textToMorse) {

	Queue morseQueue, asciiQueue;
	void *asciiMemorySpace, *morseMemorySpace;

	queue_init(&morseQueue, 0);
	queue_init(&asciiQueue, 0);
	bst_init(textToMorse);

	textToMorse->compare_key = cmp_character;
	textToMorse->destroy_key = free;
	textToMorse->destroy_data = free;

	morse_buildMorseAsciiObjectList(&asciiQueue, &morseQueue);

	while (queue_size(&asciiQueue) > 0) {

		queue_dequeue(&asciiQueue, (void**) &asciiMemorySpace);
		queue_dequeue(&morseQueue, (void**) &morseMemorySpace);

		bst_insert(textToMorse, (void*) asciiMemorySpace, (void*) morseMemorySpace);
	}

	queue_destroy(&morseQueue);
	queue_destroy(&asciiQueue);

	return;
}





void morse_createMorseToAsciiMapping(BSTTree *morseToText) {

	Queue morseQueue, asciiQueue;
	void *asciiMemorySpace, *morseMemorySpace;

	queue_init(&morseQueue, 0);
	queue_init(&asciiQueue, 0);
	bst_init(morseToText);

	morseToText->compare_key = cmp_string;
	morseToText->destroy_key = free;
	morseToText->destroy_data = free;

	morse_buildMorseAsciiObjectList(&asciiQueue, &morseQueue);

	while (queue_size(&asciiQueue) > 0) {

		queue_dequeue(&asciiQueue, (void**) &asciiMemorySpace);
		queue_dequeue(&morseQueue, (void**) &morseMemorySpace);

		bst_insert(morseToText, (void*) morseMemorySpace, (void*) asciiMemorySpace);
	}

	queue_destroy(&morseQueue);
	queue_destroy(&asciiQueue);

	return;
}

