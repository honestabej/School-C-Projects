#include <stdio.h>
#pragma warning(disable : 4996) // needed in VS

// CSE 240 Fall 2019 Homework 2 Question 3 (25 points)
// Note: You may notice some warnings when you compile in GCC or VS, that is okay.

#define isNegative(x) ((x < 0) ? x : 0)

#define polyMacro(a, b) ((a*a) + (8*a) + (3*a*b) - (b*b))

int polyFunc(int a, int b) { 
	return ((a*a) + (8*a) + (3*a*b) - (b*b));
}

// Part 1:
// We want to pass the value of -8 to isNegative and expect the result of isNegative to be -8, why is the result -9? Correct the error (5 points)
void part1(int x) {

	int result;
	result = isNegative(x--);

	printf("isNegative(-8) = %d \n\n", result);
	
	// Why did this error occur? Please provide the answer in your own words below.
	printf("Explanation: the x was incrementing before calling the macro so it was incrementing twice\n\n\n"); // (2.5 points)
}


// Part 2:
// We want to pass decremented values of x and y to the macro and function to compare their outputs in VS and GCC.
// Run this program in Visual Studio(VS) and then again in GCC. Fill the blanks below with the output values for polyFunc and polyMacro.
// Then correct/edit this function so that polyFunc and polyMacro produce same correct output of -52.			// (5 points)
// 
void part2(int x, int y) {
	int x_copy = x - 1, y_copy = y - 1;

	printf(" polyFunc(x, y) = %d \n polyMacro(x, y) = %d \n\n", polyFunc(--x, --y), polyMacro(x_copy, y_copy));


	// Replace the 4 blank spaces below with the actual output observed when running the code in VS and GCC.
	// The blanks should have the answers of unedited program. Keep the answers in blanks as they were, after editing the program.
	printf("In VS : the result of polyFunc = -52 and polyMacro = -74 \n"); 			// (5 points)
	printf("In GCC: the result of polyFunc = -52 and polyMacro = -65 \n\n"); 		// (5 points)

	// Explain in a short sentence why VS and GCC could possibly produce a different value for the same program and for the same input.
	printf("Explanation: the order that variables are evaluated and operated on depends on which compiler you are using\n\n"); //  (2.5 points)
}

// Do not edit main()  
int main()
{
	int x = -7, y = 3;

	printf("Part 1:\n\n");
	part1(x);
	printf("Part 2:\n\n");
	part2(x, y);

	while (1);	// needed to keep console open in VS
	return 0;
}
