#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define ALPHABET_SIZE 26
#define EXIT_SUCCESS 0

typedef struct Pyramid {
	char** words;
	int numWords;
} Pyramid;



/** 
 * Sort the words in a pyramid by ascending word length
 * @param pyramid the word pyramid
 * @post pyramid is an out-parameter and its words will be sorted when this function finishes
 */
void sortPyramid(Pyramid* pyramid) {
	// Use qsort to sort the words by length
	qsort(pyramid->words, pyramid->numWords, sizeof(char*), (int(*)(const void*, const void*)) strlen);
}

/** 
 * Create and populate the buckets with the letter occurrences
 *
 * @param word: the letters that need to be counted
 * @param buckets: counters for each letter in the alphabet
 * @pre buckets: are initialized to 0
 */
void populateWordBuckets(const char* word, int buckets[ALPHABET_SIZE]) {
	int wordLength = strlen(word);
	for (int i = 0; i < wordLength; i++) {
		char c = tolower(word[i]);
		int index = c - 'a';
		buckets[index]++;
	}
}

/** 
 * Adds a dynamically allocated word to the dynamic word array of the pyramid struct
 *
 * @param pyramid pyramid struct containg the word and number of words
 * @param word const char to add to the word
 * @pre the pyramid is initialized with words = NULL and numWords = 0.
 */
void addWordToPyramid(Pyramid* pyramid, char* word) {
	// Allocate memory for the new word and add it to the list
	char* newWord = malloc((strlen(word) + 1) * sizeof(char));
	strcpy(newWord, word);
	pyramid->words = realloc(pyramid->words, (pyramid->numWords + 1) * sizeof(char*));
	pyramid->words[pyramid->numWords] = newWord;
	pyramid->numWords++;
}


/** 
 * Check if a list of words can form a pyramid
 * @param pyramid the word pyramid
 */
bool isWordPyramid(const Pyramid* pyramid) {
	// Check if the words in the pyramid have the correct number of letters
	for (int i = 0; i < pyramid->numWords - 1; i++) {
		// The current word must have two more letters than the previous word
		if (strlen(pyramid->words[i]) + 2 != strlen(pyramid->words[i + 1])) {
			return false;
		}
		// Check if the current word has all the letters of the previous word plus two additional letters
		int buckets[ALPHABET_SIZE] = {0};
		populateWordBuckets(pyramid->words[i], buckets);
		for (int j = 0; j < strlen(pyramid->words[i + 1]); j++) {
			char c = pyramid->words[i + 1][j];
			if (c >= 'A' && c <= 'Z') {
				c += 'a' - 'A';
			}
			if (buckets[c - 'a'] > 0) {
				buckets[c - 'a']--;
			}
			else {
				return false;
			}
		}
	}
	return true;
}


/**
 * Print the words in a formatted word pyramid
 * @param pyramid the word pyramid
 */
void printPyramid(const Pyramid* pyramid) {
	// Calculate the maximum length of the words in the pyramid
	int maxLength = 0;
	for (int i = 0; i < pyramid->numWords; i++) {
		maxLength = max(maxLength, (int) strlen(pyramid->words[i]));
	}
	// Print the pyramid
	for (int i = 0; i < pyramid->numWords; i++) {
		// Calculate the number of spaces to align the words
		int numSpaces = (maxLength - strlen(pyramid->words[i])) / 2;
		// Print the spaces and the word
		for (int j = 0; j < numSpaces; j++) {
			printf(" ");
		}
		printf("%s\n", pyramid->words[i]);
		// Print the spaces after the word
		for (int j = 0; j < numSpaces; j++) {
			printf(" ");
		}
		// Print the spaces between words
		for (int j = 0; j < maxLength; j++) {
			printf(" ");
		}
		printf("\n");
	}
}

/**
 * Unit test helper: Call the isWordPyramid() function and compare the result to the truth
 * @param pyramid the word pyramid
 * @param truth: the expected result of the isWordPyramid() function
 */
void testIsWordPyramidCase(const Pyramid* pyramid, bool truth) {
	bool result = isWordPyramid(pyramid);

	result == truth ? printf("[PASS] ") : printf("[FAIL] ");
	printPyramid(pyramid);
	printf("\n -> %d (expected: %d)\n", result, truth);
}

/**
 * Unit test for the isWordPyramid() function
 */
void testIsWordPyramid() {
	Pyramid pyramid1 = { NULL , 0 };
	addWordToPyramid(&pyramid1, "macht");
	addWordToPyramid(&pyramid1, "ach");
	addWordToPyramid(&pyramid1, "misacht");
	testIsWordPyramidCase(&pyramid1, true);

	Pyramid pyramid2 = { NULL, 0 };
	addWordToPyramid(&pyramid2, "en");
	addWordToPyramid(&pyramid2, "dekens");
	addWordToPyramid(&pyramid2, "eend");
	testIsWordPyramidCase(&pyramid2, true);

	const char* words3[] = { "AtOmISCHe", "Mosachtiger", "triomfgeschal" };
	Pyramid pyramid3 = { NULL, 0 };
	addWordToPyramid(&pyramid3, "AtOmISCHe");
	addWordToPyramid(&pyramid3, "Mosachtiger");
	addWordToPyramid(&pyramid3, "triomfgeschal");
	testIsWordPyramidCase(&pyramid3, true);

	const char* words4[] = { "misacht", "atomisch", "mosachtiger" };
	Pyramid pyramid4 = { NULL, 0 };
	addWordToPyramid(&pyramid4, "misacht");
	addWordToPyramid(&pyramid4, "atomisch");
	addWordToPyramid(&pyramid4, "mosachtiger");
	testIsWordPyramidCase(&pyramid4, false);

	const char* words5[] = { "a" };
	Pyramid pyramid5 = { NULL, 0 };
	addWordToPyramid(&pyramid5, "a");
	testIsWordPyramidCase(&pyramid5, false);

	// Other test cases
}
void freeMemory() {
	for (int i = 0; i < pyramid->numWords; i++) {
		free(pyramid->words[i]);
	}
	free(pyramid->words);
}

/**
 * Check if the console arguments make up a pyramid.
 * If no input is given, execute the unit tests instead
 */
int main(int argc, char** argv) {
	if (argc == 1) {
		// Execute the unit tests
		testIsWordPyramid();
	}
	else {
        
		// Create a pyramid from the console arguments
		Pyramid pyramid = { NULL, 0 };
		for (int i = 1; i < argc; i++) {
			addWordToPyramid(&pyramid, argv[i]);
		}
		// Check if the pyramid is valid
		if (isWordPyramid(&pyramid)) {
			printf("The words form a word pyramid!\n");
		}
		else {
			printf("The words do not form a word pyramid!\n");
		}
        sortPyramid(&pyramid);
		// Print the pyramid
		printPyramid(&pyramid);
	}

	// TODO: avoid memory leaks!
	freeMemory();

	return EXIT_SUCCESS;
}


