


/*	MorseLib_Utilities.c
	Implementation of Utility functions and algorithms
	Used when working with manipulation of Morse Codes

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




/*///////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////	INTER-MODULE FUNCTION DECLARATIONS		/////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////*/



/*
 *
 * Function to compare to character by their ASCII value
 * Returns valueOf(k1) - valueOf(k2)
 *
*/
int cmp_character(const void *k1, const void *k2);



/*
 *
 * Function to compare to sequence of characters (string) by Lexicographic order
 * Returns StringCompare(k1, k2)
 *
*/
int cmp_string(const void *k1, const void *k2);

/*__inline__ int cmp_character(const void *k1, const void *k2) __attribute__((always_inline));
__inline__ int cmp_string(const void *k1, const void *k2) __attribute__((always_inline));*/






/*
 *
 * Internal (Static) function to build dynamic objects of Morse and ASCII characters
 * Using malloc() for dynamic allocation, and then store them
 * To their respective Queue data structure
 *
 * Returns 0 for successful creation, -1 for memory allocation failure
 * Returns thwo Queue data structure containing ASCII and MORSE character objects
 *
*/
static int morse_buildMorseAsciiObjectList(Queue *asciiQueue, Queue *morseQueue);











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




/*int morse_queueEnqueueString(Queue *queue, char *charSeq, int len) {*/

/*	char *newstr;*/
/*	newstr = malloc(len);*/

/*	memcpy((void*) newstr, (const void*) charSeq, len);*/
/*	return queue_enqueue(queue, (void*) newstr);*/
/*}*/


static int morse_buildMorseAsciiObjectList(Queue *asciiQueue, Queue *morseQueue) {


	unsigned int isMemoryAllocated;
	register unsigned int currentIndex;
	register char *asciiMemorySpace, *currentAsciiChar;
	register char *morseMemorySpace, *currentMorseString;
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


		/* Initialize the memory pointer variables to 0 */
		asciiMemorySpace = 0;
		morseMemorySpace = 0;


		/* Load the index of Input stream from where to copy characters */
		currentMorseString = morseCodes[currentIndex];
		currentAsciiChar = asciiChars + currentIndex;


		/* Request for specified amount of memory to where we copy characters */
		morseMemorySpace = (char*) malloc(strlen(currentMorseString) + 1);
		asciiMemorySpace = (char*) malloc(sizeof(char));


		/* Check we've got sufficient amount of memory for what we've requested */
		/* Just perform Biwtwise AND between two pointer variables*/
		/* If the result is 0, means any one of them points to 0 */
		/* Then we did not got some memory, and we return -1 to signal this failure */
		/* Safely cast our pointer variables to Unsigned Integers, because */
		/* Memory address can never be negative, it's size is equal to unsigned int */
		isMemoryAllocated =
					(unsigned int)asciiMemorySpace & (unsigned int)morseMemorySpace;
		if
		(isMemoryAllocated == 0) return -1;


		/* Copy the necessary characters to the recently allocated memory */
		strcpy(morseMemorySpace, (const char*) currentMorseString);
		memcpy((void*) asciiMemorySpace, (const void*) currentAsciiChar, sizeof(char));


		/* Last step, store the pointer of memory to the specified Queue data structure*/
		queue_enqueue(asciiQueue, (const void*) asciiMemorySpace);
		queue_enqueue(morseQueue, (const void*) morseMemorySpace);


		/* Then we start again */
		currentIndex = currentIndex + 1;
	}

	return 0;
}









/*///////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////	GLOBAL UTILITY FUNCTION IMPLEMENTATIONS	/////////////////////*/
/*///////////////////											/////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////*/




int morse_createMorseToBinaryMapping(BSTTree *morseToBinary) {

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

	return 0;
}





int morse_createBinaryToMorseMapping(BSTTree *binaryToMorse) {

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

	return 0;
}



int morse_createAsciiToMorseMapping(BSTTree *textToMorse) {

	Queue morseQueue, asciiQueue;
	void *asciiMemorySpace, *morseMemorySpace;
	int isObjectsBuilt, returnCode;


	/* We will copy the pointer addresses contained in these Queue to BST */
	/* For this reason, initialize Queue with NO destructor function */
	/* Even if they will conatin data which are dynamically initialized */
	queue_init(&morseQueue, 0);
	queue_init(&asciiQueue, 0);
	bst_init(textToMorse);


	/* Of course, out BST will ultimately contain objects which resides */
	/* On Heap area, so initialize our BST with 'free()' as destructor function */
	textToMorse->compare_key = cmp_character;
	textToMorse->destroy_key = free;
	textToMorse->destroy_data = free;


	/* Start building dynamically allocated ASCII and Morse objects */
	/* And store them on the Queue data structure that we have specified */
	isObjectsBuilt = morse_buildMorseAsciiObjectList(&asciiQueue, &morseQueue);
	if
		(isObjectsBuilt != 0) {
			returnCode = -1;
			goto CLEAN_UP;
		} else {
			returnCode = 0;
		}

	while (queue_size(&asciiQueue) > 0) {


		/* First, pull the address of each object from the Queue */
		/* And store them to the pointer variable specified below */
		queue_dequeue(&asciiQueue, (void**) &asciiMemorySpace);
		queue_dequeue(&morseQueue, (void**) &morseMemorySpace);


		/* Now insert addresses of pulled objects to the Binary Search Tree */
		/* For BST, one object will be a KEY and another object will be the DATA */
		bst_insert(textToMorse, (void*) asciiMemorySpace, (void*) morseMemorySpace);
	}

	CLEAN_UP:
	queue_destroy(&morseQueue);
	queue_destroy(&asciiQueue);

	return returnCode;
}





int morse_createMorseToAsciiMapping(BSTTree *morseToText) {

	Queue morseQueue, asciiQueue;
	void *asciiMemorySpace, *morseMemorySpace;
	int isObjectsBuilt, returnCode;


	/* We will copy the pointer addresses contained in these Queue to BST */
	/* For this reason, initialize Queue with NO destructor function */
	/* Even if they will conatin data which are dynamically initialized */
	queue_init(&morseQueue, 0);
	queue_init(&asciiQueue, 0);
	bst_init(morseToText);


	/* Of course, out BST will ultimately contain objects which resides */
	/* On Heap area, so initialize our BST with 'free()' as destructor function */
	morseToText->compare_key = cmp_string;
	morseToText->destroy_key = free;
	morseToText->destroy_data = free;


	/* Start building dynamically allocated ASCII and Morse objects */
	/* And store them on the Queue data structure that we have specified */
	isObjectsBuilt = morse_buildMorseAsciiObjectList(&asciiQueue, &morseQueue);
	if
		(isObjectsBuilt != 0) {
			returnCode = -1;
			goto CLEAN_UP;
		} else {
			returnCode = 0;
		}

	while (queue_size(&asciiQueue) > 0) {


		/* First, pull the address of each object from the Queue */
		/* And store them to the pointer variable specified below */
		queue_dequeue(&asciiQueue, (void**) &asciiMemorySpace);
		queue_dequeue(&morseQueue, (void**) &morseMemorySpace);


		/* Now insert addresses of pulled objects to the Binary Search Tree */
		/* For BST, one object will be a KEY and another object will be the DATA */
		bst_insert(morseToText, (void*) morseMemorySpace, (void*) asciiMemorySpace);
	}

	CLEAN_UP:
	queue_destroy(&morseQueue);
	queue_destroy(&asciiQueue);

	return returnCode;
}

