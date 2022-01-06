
// CSE240 Fall 2019 HW5
// Abraham Johnson
// Write the compiler used: Visual studio 

// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of employees, like employees' record.
// Each record has this information: employee's name, supervisors's name, department of the employee, room number.
// The struct 'employeeRecord' holds information of one employee. Department is enum type.
// An array of structs called 'list' is made to hold the list of employees.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// WRITE COMMENTS FOR IMPORANT STEPS IN YOUR CODE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_EMPLOYEES 15
#define MAX_NAME_LENGTH 25

typedef enum { HR = 0, Marketing, IT } departmentType; // enum type 

struct employeeRecord {					// struct for emplyee details
	char employeeName[MAX_NAME_LENGTH];
	char supervisorName[MAX_NAME_LENGTH];
	departmentType department;
	unsigned int roomNumber;
};

struct employeeRecord list[MAX_EMPLOYEES]; 	// declare list of employees
int count = 0;								// the number of employees currently stored in the list (initialized to 0)

// functions already implmented
void flushStdIn();
void executeAction(char);
void save(char* fileName);

// functions that need implementation:
int add(char* employeeName_input, char* supervisorName_input, char* department_input, unsigned int roomNumber_input); // 20 points
void display();				// 10 points
void sort();				// 10 points
void load(char* fileName);	// 10 points

int main()
{
	char* fileName = "Employee_List.txt";
	load(fileName);	// load list of employees from file (if it exists). Initially there will be no file.
	char choice = 'i';		// initialized to a dummy value
	do
	{
		printf("\nEnter your selection:\n");
		printf("\t a: add a new employee\n");
		printf("\t d: display employee list\n");
		printf("\t s: sort employee list by name\n");				
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName); // save list of employees to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar(); 
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
	char employeeName_input[MAX_NAME_LENGTH], supervisorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, add_result= 0;
	char department_input[20];
	switch (c)
	{
	case 'a':
		// input employee record from user
		printf("\nEnter employee name: ");
		fgets(employeeName_input, sizeof(employeeName_input), stdin);
		employeeName_input[strlen(employeeName_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Enter supervisor name: ");
		fgets(supervisorName_input, sizeof(supervisorName_input), stdin);
		supervisorName_input[strlen(supervisorName_input) - 1] = '\0';	// discard the trailing '\n' char
		
		printf("Enter whether employee is in 'HR' or 'Marketing' or 'IT': ");
		fgets(department_input, sizeof(department_input), stdin);
		department_input[strlen(department_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumber_input);
		flushStdIn();

		// add the employee to the list
		add_result = add(employeeName_input, supervisorName_input, department_input, roomNumber_input);
		if (add_result == 0)
			printf("\nEmployee is already on the list! \n\n");
		else if (add_result == 1)
			printf("\nEmployee successfully added to the list! \n\n");
		else
			printf("\nUnable to add. Employee list is full! \n\n");

		break;
	case 'd': display();	break;
	case 's': sort();		break;
	
	case 'q': break;
	default: printf("%c is invalid input!\n",c);
	}
}

// Q1 : add (20 points)
// This function is used to add a employee into the list. You can simply add the new employee to the end of list (array of structs).
// Do not allow the employee to be added to the list if it already exists in the list. You can do that by checking employee names already in the list.
// If the employee already exists then return 0 without adding it to the list. If the employee does not exist in the list then go on to add the employee at the end of the list and return 1.
// If employee list is full, then do not add new employee to the list and return 2.
// NOTE: Notice how return type of add() is checked in case 'a' of executeAction()
// NOTE: You must convert the string 'department_input' to an enum type and store it in the list because the department has enum type (not string type).
// The list should be case sensitive. For instance, 'Roger' and 'roger' should be considered two different names.
// Hint: 'count' holds the number of employees currently in the list
int add(char* employeeName_input, char* supervisorName_input, char* department_input, unsigned int roomNumber_input)
{
	int same = 0;
	for (int i = 0; i < count; i++){
		if (strcmp(list[i].employeeName, employeeName_input) == 0){		// test if the employee has already been added
			same = 1;	
		}
	}
	if (same == 1 && count < MAX_EMPLOYEES){
		return 0;														// if employee has already been added return 0
	} else if (same == 0 && count < MAX_EMPLOYEES){
		char h[] = "HR";
		char m[] = "Marketing";
		char i[] = "IT";
		struct employeeRecord employee;									// declare struct variable
		strcpy(employee.employeeName, employeeName_input);				// copy input to the employeeRecord
		strcpy(employee.supervisorName, supervisorName_input);			// copy input to the employeeRecord
		if (strcmp(department_input, h) == 0){
			employee.department = 0;									// set department to 0 if input was HR
		} else if (strcmp(department_input, m) == 0){
			employee.department = 1;									// set department to 1 if input was Marketing
		} else {
			employee.department = 2;									// set department to 2 if input is something else (IT)
		}
		employee.roomNumber = roomNumber_input;							// copy input to employeeRecord
		list[count] = employee;											// add the employee the the list at the spot of count
		count++;
		return 1;			// edit this line as needed
	} else if (count > MAX_EMPLOYEES) {
		return 2;														// if the employees list is full
	} else {
		return 0;
	}
}


// Q2 : display (10 points)
// This function displays the employee list with the details (struct elements) of each employee. 
// Parse through the list and print the employee details one after the other. See expected output screenshots in question pdf file.
// NOTE: Department is stored in the struct as enum type. You need to display 'HR','Marketing' or 'IT'
void display()
{
	for (int i = 0; i < count; i++){
		printf("Employee name: %s \n", list[i].employeeName);
		printf("Supervisor name: %s \n", list[i].supervisorName);
		if (list[i].department == 0){
			printf("Department: HR \n");
		} else if (list[i].department == 1){
			printf("Department: Marketing \n");
		} else {
			printf("Department: IT \n");
		}
		printf("Room number: %d \n", list[i].roomNumber);
	}
}

// Q3 : sort (10 points)
// This function is used to sort the list(array of structs) alphabetically by employee name.
// Parse the list and compare the employee names to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new array of structs having sorted employees.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by employee name which is a string.
//       Use a temp struct (already declared) if you need to swap two structs in your logic
void sort()
{	
	struct employeeRecord employeeTemp;	// needed for swapping structs. Not absolutely necessary to use.
	// enter code here
	for (int i = 0; i < count; i++){
		for (int j = i + 1; j < count; j++){
			if (strcmp(list[i].employeeName, list[j].employeeName) > 0){ 	// will return negative if list[i] should come before list[j]
				employeeTemp = list[i];										// if it returns positive execute the code and swap the employees
				list[i] = list[j];
				list[j] = employeeTemp;
			}
		}
	}


	// display message for user to check the result of sorting.
	printf("\nEmployee list sorted! Use display option 'd' to view sorted list.\n");
}

// save() is called at the end of main()
// This function saves the array of structures to file. It is already implemented.
// You should read and understand how this code works. It will help you with 'load()' function.
// save() is called at end of main() to save the employee list to a file.
// The file is saved at the same place as your C file. For VS, the default directory looks like this:
// C:\Users\<username>\Documents\Visual Studio 2017\Projects\Project1\Project1
// You can simply delete the file to 'reset the list' or to avoid loading from it.
void save(char* fileName)
{	
	FILE* file;
    int i, departmentValue=0;
	file = fopen(fileName, "wb");		// open file for writing
	
	fwrite(&count, sizeof(count), 1, file);		// First, store the number of employees in the list
	
	// Parse the list and write employee record to file
	// 
	for (i = 0; i < count; i++)
	{
		fwrite(list[i].employeeName, sizeof(list[i].employeeName), 1, file);
		fwrite(list[i].supervisorName, sizeof(list[i].supervisorName), 1, file);
		// convert enum to a number for storing
		if (list[i].department == HR)
			departmentValue = 0;		// 0 for HR
		else if (list[i].department == Marketing)
			departmentValue = 1;		// 1 for Marketing
		else
			departmentValue = 2;		// 2 for IT

		fwrite(&departmentValue, sizeof(departmentValue), 1, file);
		fwrite(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, file);
	}
	
	fclose(file);			// close the file after writing
}

// Q4:  load (10 points)
// This function is called in the beginning of main().
// This function reads the employee list from the saved file and builds the array of structures 'list'. 
// In the first run of the program, there will be no saved file because save() is called at the end of program.
// So at the begining of this function, write code to open the file and check if it exists. If file does not exist, then return from the function.
// (See expected output of add() in homework question file. It displays "Employee_List.txt not found" because the file did not exist initially.)
// If the file exists, then parse the employee list to read the employee details from the file.
// Use the save function given above as an example of how to write this function. Notice the order in which the struct elements are saved in save()
// You need to use the same order to read the list back.
// NOTE: The saved file is not exactly readable because all elements of the struct are not string or char type.
//       So you need to implement load() similar to how save() is implemented. Only then the 'list' will be loaded correctly.
//		You can simply delete the file to 'reset the list' or to avoid loading from it.
void load(char* fileName)
{
	FILE* file;
    int i, departmentValue=0;
	file = fopen(fileName, "rb");		// open file for reading
	
	if (file == NULL) {
		printf("Employee_List.txt not found \n");
	} else {
		// Parse the list and read employee record from file
		fread(&count, sizeof(count), 1, file);		// First, read the number of employees in the list
		for (i = 0; i < count; i++)
		{
			fread(list[i].employeeName, sizeof(list[i].employeeName), 1, file);
			fread(list[i].supervisorName, sizeof(list[i].supervisorName), 1, file);
			// convert enum to a number for reading
			fread(&departmentValue, sizeof(departmentValue), 1, file);
			if (departmentValue == 0){
				list[i].department = HR;
			} else if (departmentValue == 1){
				list[i].department = Marketing;
			} else {
				list[i].department = IT;
			} 
			fread(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, file);
		}	
		printf("Employee's record loaded from Employee_List.txt \n");
		fclose(file);			// close the file after reading
	}
}
	

