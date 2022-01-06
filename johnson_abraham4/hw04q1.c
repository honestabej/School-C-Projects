//CSE240 Fall 2019 HW4

// Enter your name here
// State the IDE that you use: Visual Studio or GCC

#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// You are given a partially complete program. Complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// You shoud not modify the function return types or parameters.
// You can assume that all inputs are valid. Ex: If prompted for an integer, the user will input an integer.
// You can use only the strlen() of strings.h library to check string length. Do not use any other string functions 
// because you are supposed to use pointers for this homework. 
// **** DO NOT use arrays to store or to index the characters in the string ****

// Global Macro Values. They are used to define the size of 2D array of characters
#define NUM_STRINGS 4
#define STRING_LENGTH 50

// Forward Declarations
void initializeStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
void encryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void decryptStrings(char[NUM_STRINGS][STRING_LENGTH], int);
void reverseStrings(char strings[NUM_STRINGS][STRING_LENGTH]);
char* reverseOneString(char s[STRING_LENGTH]);
int isPalindrome(char s[STRING_LENGTH]);

// Problem 1: initializeStrings (5 points)
// Use pointer p to traverse the 2D array of characters variable 'strings' (input from user in main() ) and set all characters in each
// array to a null terminator so that there is a 4 row and 50 column 2D array full of null terminators.
// The null terminator '\0' is used to denote the end of a string.
void initializeStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	char *ptr ;
	// enter code here
	for (int i = 0; i < NUM_STRINGS; i++){
		for (int j = 0; j < STRING_LENGTH; j++){
			ptr = &strings[i][j];					//ptr is pointing to address of strings[i][j]
			*ptr = '\0';							//set the varible at the address ptr is pointing to equal to "\0"
		}
	}

}

// Problem 2: printStrings (5 points)
// Use pointer p to traverse the 2D character array "strings" and print each string.
// See the example outputs provided in the word document. Each string should be printed on a new line.
void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	char *ptr = &strings[0][0];
	// enter code here
	for (int i = 0; i < NUM_STRINGS; i++){
		ptr = &strings[i];
		printf("String: %s \n", ptr);
	}

}


// Problem 3: reverseOneString (15 points)
// Reverse the string s by using pointer.
// Use pointer p and 'temp' char to swap 1st char with last, then 2nd char with (last-1) and so on..
// Finally return pointer p which points to start of the reversed string.
// You may declare and use more pointers if needed.
// Hint: You might want to check if your logic works with even as well as odd length string.
//       You can write test code to print out the reversed string to check if your function works. (Don't include it in final submission)
char* reverseOneString(char s[STRING_LENGTH])
{
	char temp;								// not necessary to use this variable
	int length = strlen(s) - 1;								
	char *p = &s[0];						// pointer to start of string
	char *e = &s[length];					// pointer to end of string
	// enter code here
	for (int i = 0; i != length; i++){
		p = &s[i];
		e = &s[length];
		temp = *p;
		*p = *e;
		*e = temp;
		length--;
	}
	return p;
}

// Problem 4: reverseStrings (5 points)
// Reverse all the strings in 'strings[][]'
// For each string in 'strings', use the reverseOneString() to reverse it.
// You may declare and use more pointers if needed.
void reverseStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	char *ptr = &strings[0][0];
	char *tempptr;
	// enter code here
	char temp;
	int length;
	for (int i = 0; i < NUM_STRINGS; i++){
		length = strlen(strings[i]) -1;
		for (int j = 0; j < length; j++){
			ptr = &strings[i][j];
			tempptr = &strings[i][length];
			temp = *ptr;
			*ptr = *tempptr;
			*tempptr = temp;
			length--;
		}
	}
}

// Problem 5: encryptStrings (5 points)
// Use pointer ptr to traverse the 2D character array 'strings' and encrypt each string in 2 step as follows- 
// 1) Reverse the strings. Hint: Use 'reverseStrings()' for this step.
// 2) Shift the characters forward by the integer value of 'key'.
// If the string is "hello" and key = 2, reversing will get you "olleh" and adding key to it will result in "qnnfj".
// Once the value of 'key' gets larger, you will extend past alphabetical characters and reach non-alphabetical characters. Thats ok.
// NOTE: DO NOT encrypt the null terminator character. Use the null terminator to find the end string.
//		If you could not implement reverseStrings(), skip using it in this function. You will receive partial credit.
void encryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	char *p = &strings[0][0];
	// enter code here
	reverseStrings(strings);
	for (int i = 0; i < NUM_STRINGS; i++){
		for (int j = 0; j < STRING_LENGTH; j++){
			p = &strings[i][j];
			if (*p != '\0'){
				int shift = *p;
				*p = shift + key;
			} else {
				break;
			}
		}
	}

}
// Problem 6: decryptStrings (5 points)
// HINT: This should be very similiar to the encryption function defined above in encryptStrings().
// Use pointer p to traverse the 2D character array 'strings' and decrypt each string in 2 step as follows- 
// 1) Shift the characters backward by the integer value of 'key'.
// 2) Reverse the strings. Hint: Use 'reverseStrings()' for this step.
// NOTE: DO NOT decrypt the null characters.
//		If you could not implement reverseStrings(), skip using it in this function. You will receive partial credit.
void decryptStrings(char strings[NUM_STRINGS][STRING_LENGTH], int key)
{
	char *ptr = &strings[0][0];
	// enter code here
	for (int i = 0; i < NUM_STRINGS; i++){
		for (int j = 0; j < STRING_LENGTH; j++){
			ptr = &strings[i][j];
			if (*ptr != '\0'){
				int shift = *ptr;
				*ptr = shift - key;
			} else {
				break;
			}
		}
	}
	reverseStrings(strings);

}

// Problem 7: isPalindrome (10 points)
// Return 1 if string s is palindrome.
// Parse through the string to check if 1st char==last char, 2nd char == (last-1) char, and so on..
// Return 1 if string is palindrome. Return 0 if string is not palindrome.
// A palindrome is a sequence of characters which when reversed, is the same sequence of characters.
// Palindrome string examples: rotor, noon, madam
// Note: you may use reverseOneString() here but it is not necessary to use it. 
int isPalindrome(char s[STRING_LENGTH])
{
	char *p = s;
	int palindrome = 1;			// edit if needed
	// enter code here
	char *e = s;
	int length = strlen(s) - 1;
	for (int i = 0; i < length; i++){
		p = &s[i];
		e = &s[length];
		if (*p != *e){
			palindrome = 0;
			break;
		} else {
			length--;
		}
	}
	return palindrome;
}

// You should study and understand how main() works.
// *** DO NOT modify it in any way ***
int main()
{
	char strings[NUM_STRINGS][STRING_LENGTH]; // will store four strings each with a max length of 34
	char s[STRING_LENGTH];
	int i, key;
	char input[STRING_LENGTH];
	
	printf("CSE240 HW4: Pointers\n\n");
	initializeStrings(strings);
		
	for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("Enter a string: ");				// prompt for string
		fgets(input, sizeof(input), stdin);		// store input string
		input[strlen(input) - 1] = '\0';		// convert trailing '\n' char to '\0' (null terminator)
		strcpy(strings[i], input);				// copy input to 2D strings array
	}
	
	printf("\nEnter a key value for encryption: "); // prompt for integer key
	scanf("%d", &key); 
	
	encryptStrings(strings, key);
	printf("\nEncrypted Strings:\n");
	printStrings(strings);
	decryptStrings(strings, key);
	printf("\nDecrypted Strings:\n");
	printStrings(strings);

	getchar();									// flush out newline '\n' char

	printf("\nChecking for palindrome. Enter a string: ");				// prompt for string
	fgets(input, sizeof(input), stdin);		// store input string
	input[strlen(input) - 1] = '\0';		// convert trailing '\n' char to '\0' (null terminator)

	if (isPalindrome(input))
		printf("The string is a palindrome");
	else
		printf("The string is not a palindrome");

	getchar();									// keep VS console open
	return 0;
}