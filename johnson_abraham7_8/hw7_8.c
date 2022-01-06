// CSE240 Fall 2019 HW 7 & 8
// Abe Johnson
// Write the compiler used: Visual studio

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of employee information.
// The global linked list 'list' is a list of employees with each node being struct 'employeeList'.
// 'employeeList' consists of struct 'employee' which has: employee name, room number, and a linked list of 'supervisors'.
// The linked list of supervisors has each node containing simply the name of the supervisor.
// HW7 ignores the 'supervisors' linked list since there is no operation/manipulation to be done on 'supervisors' list in HW7.
// HW8 has operations/manipulations to be done with 'supervisors' list like add a supervisor, display last added supervisor.

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// Yyou are not allowed to modify main ().
// You can use string library functions.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****
// ***** Before implementing any function, see how it is called in executeAction() *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio

#define MAX_NAME 30

// global linked list 'list' contains the list of employees
struct employeeList {
	struct employee* employee;
	struct employeeList* next;
} *list = NULL;				// currently empty list

// structure "employee" contains the employee's name, room number and linked list of supervisors
struct employee {
	char name[MAX_NAME];
	unsigned int roomNumber;
	struct supervisor* supervisors;		// linked list 'supervisors' contains names of supervisors
};

//  structure 'supervisor' contains supervisor's name 
struct supervisor {
	char name[MAX_NAME];
	struct supervisor* next;
};

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
// HW 7
void addEmployee(char* employeeNameInput, unsigned int roomNumInput); // 20 points
void displayEmployeeList(struct employeeList* tempList);	      // 15 points
struct employee* searchEmployee(char* employeeNameInput);	      // 15 points
//HW 8
void addSupervisor(char* employeeNameInput, char* supervisorNameInput);	// 15 points
char* lastSupervisor(char* employeeNameInput);				// 15 points
void removeEmployee(char* employeeNameInput);			        // 20 points

int main()
{
	char selection = 'a';		// initialized to a dummy value
	do
	{
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new employee to the list\n");
		printf("\t d: display employee list (no supervisors)\n");
		printf("\t b: search for an employee on the list\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a supervisor of a employee\n");
		printf("\t l: display last added supervisor of a employee\n");
		printf("\t r: remove a employee\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char employeeNameInput[MAX_NAME], supervisorNameInput[MAX_NAME];
	unsigned int roomNumInput;
	struct employee* searchResult = NULL;

	switch (c)
	{
	case 'a':	// add employee
				// input employee details from user
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter room number: ");
		scanf("%d", &roomNumInput);
		flushStdIn();

		//if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		if (1)									// comment out this line after implementing searchEmployee()
		{
			addEmployee(employeeNameInput, roomNumInput);
			printf("\nEmployee successfully added to the list!\n");
		}
		else
			printf("\nThat employee is already on the list!\n");
		break;

	case 'd':		// display the list
		displayEmployeeList(list);
		break;

	case 'b':		// search for an employee on the list
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (0)									// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nEmployee name exists on the list! \n\n");
		}
		break;

	case 'r':		// remove employee
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		//if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		if (0)									// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			removeEmployee(employeeNameInput);
			printf("\nEmployee successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add supervisor
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		//if (0)										// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter supervisor's name: ");
			fgets(supervisorNameInput, sizeof(supervisorNameInput), stdin);
			supervisorNameInput[strlen(supervisorNameInput) - 1] = '\0';	// discard the trailing '\n' char

			addSupervisor(employeeNameInput, supervisorNameInput);
			printf("\nSupervisor added! \n\n");
		}
		break;

	case 'l':		// last supervisor
		printf("\nPlease enter employee's name: ");
		fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
		employeeNameInput[strlen(employeeNameInput) - 1] = '\0';	// discard the trailing '\n' char

		//if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
		if (0)										// comment out this line after implementing searchEmployee()
			printf("\nEmployee name does not exist or the list is empty! \n\n");
		else
		{
			printf("\nLast supervisor added: %s\n\n", lastSupervisor(employeeNameInput));
		}
		break;

	case 'q':		// quit
		break;

	default: printf("%c is invalid input!\n", c);
	}
}

// HW7 Q1: addEmployee (20 points)
// This function is used to insert a new employee in the linked list. 
// You must insert the new employee to the head of linked list 'list'.
// You need NOT check if the employee already exists in the list because that is taken care by searchEmployee() called in executeAction(). Look at how this function is used in executeAction().
// Don't bother to check how to implement searchEmployee() while implementing this function. Simply assume that employee does not exist in the list while implementing this function.
// NOTE: The function needs to add the employee to the head of the list.
// NOTE: This function does not add supervisors to the employee info. There is another function addSupervisor() in HW8 for that.
// Hint: In this question, no supervisors means NULL supervisors.

void addEmployee(char* employeeNameInput, unsigned int roomNumInput)
{
	struct employeeList* addNew = (struct employeeList*)malloc(sizeof(struct employeeList));
	addNew->employee = (struct employee*)malloc(sizeof(struct employee));
	strcpy(addNew->employee->name,employeeNameInput);
	addNew->employee->roomNumber = roomNumInput;
	addNew->employee->supervisors = NULL;
	addNew->next = NULL;
	
	if (list != NULL){
		addNew->next = list;
		list = addNew;
	} else {
		list = addNew;
	}
}

// HW7 Q2: displayEmployeeList (15 points)
// This function displays the employee details (struct elements) of each employee.
// Parse through the linked list 'list' and print the employee details ( name and room number) one after the other. See expected output screenshots in homework question file.
// You should not display supervisor names (because they are not added in HW7).
// You MUST use recursion in the function to get full points. Notice that 'list' is passed to the function argument. Use recursion to keep calling this function till end of list.

void displayEmployeeList(struct employeeList* tempList)
{
	struct employeeList* tempTempList = list;
	// enter code here
	if (tempTempList == NULL){
		printf("The list is empty \n");
		return;
	} else if (tempList == NULL) {
		return;
	} else{
		printf("\nEmployee name: %s \n", tempList->employee->name);
		printf("Room number: %d \n", tempList->employee->roomNumber);
		displayEmployeeList(tempList->next);
		return;
	}
	
}

// HW7 Q3: searchEmployee (15 points)
// This function searches the 'list' to check if the given employee exists in the list. Search by employee name.
// If it exists then return that 'employee' node of the list. Notice the return type of this function.
// If the employee does not exist in the list, then return NULL.
// NOTE: After implementing this fucntion, go to executeAction() to comment and un-comment the lines mentioned there which use searchEmployee()
//       in case 'a', case 'r', case 'l' (total 3 places)
struct employee* searchEmployee(char* employeeNameInput)
{
	struct employeeList* tempList = list;					// Make a temporary pointer to the head
	while (tempList != NULL){
		if (strcmp(employeeNameInput,tempList->employee->name) == 0){
			return tempList->employee;						// If the employee names are equal, return the employee node with that name
		} else{
			tempList = tempList->next;
		}
	}
	
	return NULL;	// edit this line as needed
}



// HW8 Q1: addSupervisor (15 points)
// This function adds supervisor's name to a employee node.
// Parse the list to locate the employee and add the supervisor to that employee's 'supervisors' linked list. No need to check if the employee name exists on the list. That is done in executeAction().
// If the 'supervisors' list is empty, then add the supervisor. If the employee has existing supervisors, then you may add the new supervisor to the head or the tail of the 'supervisors' list.
// You can assume that the same supervisor name does not exist. So no need to check for existing supervisor names, like we do when we add new employee.
// NOTE: Make note of whether you add the supervisor to the head or tail of 'supervisors' list. You will need that info when you implement lastSupervisor()
//       (Sample solution has supervisor added to the tail of 'supervisors' list. You are free to add new supervisor to head or tail of 'supervisors' list.)

void addSupervisor(char* employeeNameInput, char* supervisorNameInput)
{
	struct employeeList* tempList = list;		// work on a copy of 'list'
	struct supervisor* addNew1 = (struct supervisor*)malloc(sizeof(struct supervisor));
	strcpy(addNew1->name,supervisorNameInput);
	while (strcmp(tempList->employee->name,employeeNameInput) != 0) {
		tempList = tempList->next;				// continue traversing through list until finding matching employee
	}
	// put new supervisor into the head of the new supervisor linked list
	addNew1->next = tempList->employee->supervisors;
	tempList->employee->supervisors = addNew1;
}

// HW8 Q2: lastSupervisor (15 points)
// This function returns the name of the last (most recently) added supervisor of a employee.
// Parse the list to locate the employee. No need to check if the employee name exists in the list. That is done in executeAction().
// Then parse the supervisor names to return the most recently added supervisor.
// NOTE: Last supervisor does not necessarily mean the tail of 'supervisors' list. It means the most recently added supervisor. 
//       If you are adding supervisor to the head of the list in addSupervisor(), then you should return that supervisor accordingly.

char* lastSupervisor(char* employeeNameInput)
{

	struct employeeList* tempList = list;			// work on a copy of 'list'
	// enter code here
	while (strcmp(tempList->employee->name,employeeNameInput) != 0) {
		tempList = tempList->next;					// continue traversing through list until finding matching employee
	}
	return tempList->employee->supervisors->name;	// return the name at the head of the list, since new supervisors are always input at the head

	//return NULL;		// edit this line as needed
}

// HW8 Q3: removeEmployee (20 points)
// This function removes an employee from the list.
// Parse the list to locate the employee and delete that 'employee' node.
// You need not check if the employee exists because that is done in executeAction()
//removeEmployee() is supposed to remove employee details like name and room number.
// The function will remove supervisors of the employee too.
// When the employee is located in the 'list', after removing the employee name and room number, parse the 'supervisors' list of that employee
// and remove the supervisors.

void removeEmployee(char* employeeNameInput)
{

	struct employeeList* tempList = list;	// work on a copy of 'list'
	struct employeeList* tempList2;
	struct supervisor* tempSV = list->employee->supervisors;


	while (tempList != NULL){
		if(tempList!=NULL && strcmp(tempList->employee->name,employeeNameInput) == 0){
           tempList2 = tempList;
		   while (tempList2->employee->supervisors != NULL){
			   tempSV = tempList2->employee->supervisors;
			   tempList2->employee->supervisors = tempList2->employee->supervisors->next;
			   free(tempSV);					// free the node of the deleted supervisors
		   }
		   list = tempList->next;
           free(tempList);						// free the node of the deleted employee
           return;
        }
		tempList = tempList->next;				// traverse to next node
	}
	
	
}


