
// CSE240 Fall 2019 HW6
// Abraham Johnson
// Write the compiler used: Visual studio

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of employee records.
// Each record(struct) has this information: employee's name, supervisor's name, department of the employee, room number.
// The struct 'employeeRecord' holds information of one employee. Department is enum type.
// A linked list called 'list' is made to hold the list of employees.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.
// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. 10% deduction for not using comments *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_NAME_LENGTH 25

typedef enum { HR = 0, Marketing, IT } departmentType; // enum type 

struct employeeRecord {
	char employeeName[MAX_NAME_LENGTH];
	char supervisorName[MAX_NAME_LENGTH];
	departmentType department;
	unsigned int roomNumber;
	struct employeeRecord* next;	// pointer to next node
} *list = NULL;					// Declare linked list 'list'

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
int add(char* employeeName_input, char* supervisorName_input, char* department_input, unsigned int roomNumber_input); // 10 points
void displayList();						// 10 points
int countNodes();						// 5 points
int deleteNode(char* employeeName_input);	// 10 points
void swapNodes(struct employeeRecord* node1, struct employeeRecord* node2);	// 5 points
void sortList();						// 10 points


int main()
{	
	char selection = 'i';		// initialized to a dummy value
	printf("\nCSE240 HW6\n");
	do
	{
		printf("\nCurrently %d employee(s) on the list.", countNodes());	// NOTE: countNodes() called here
		printf("\nEnter your selection:\n");
		printf("\t a: add a new employee\n");
		printf("\t d: display employee list\n");
		printf("\t r: remove a employee from the list\n");
		printf("\t s: sort employee list by supervisor's name in descending order\n");
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
// Read the code in the function, case by case
void executeAction(char c)
{
	char employeeName_input[MAX_NAME_LENGTH], supervisorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, result = 0;
	char department_input[20];
	switch (c)
	{
	case 'a':	// add employee
		// input employee details from user
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
		result = add(employeeName_input, supervisorName_input, department_input, roomNumber_input);
		if (result == 0)
			printf("\nEmployee is already on the list! \n\n");
		else if (result == 1)
			printf("\nEmployee successfully added to the list! \n\n");
		
		break;

	case 'd':		// display the list
		displayList();
		break;

	case 'r':		// remove a employee
		printf("\nPlease enter employee name: ");
		fgets(employeeName_input, sizeof(employeeName_input), stdin);
		employeeName_input[strlen(employeeName_input) - 1] = '\0';	// discard the trailing '\n' char

		// delete the node
		result = deleteNode(employeeName_input);
		if (result == 0)
			printf("\nEmployee does not exist! \n\n");
		else if (result == 1)
			printf("\nEmployee successfully removed from the list. \n\n");
		else
			printf("\nList is empty! \n\n");
		break;

	case 's':		// sort the list
		sortList();
		break;

	case 'q':		// quit
		break;
	default: printf("%c is invalid input!\n",c);
	}
}

// Q1 : add (10 points)
// This function is used to insert a new employee into the list. You can insert the new employee to the end of the linked list.
// Do not allow the employee to be added to the list if that employee already exists in the list. You can do that by checking the names of the employees already in the list.
// If the employee already exists then return 0 without adding employee to the list. If the employee does not exist in the list then go on to add the employee at the end of the list and return 1.
// NOTE: You must convert the string 'department_input' to an enum type and store it in the list because the struct has enum type for department.

int add(char* employeeName_input, char* supervisorName_input, char* department_input, unsigned int roomNumber_input) // 20 points
{
	struct employeeRecord* tempList = list;	// work on a copy of 'list'
	// enter code here

	struct employeeRecord* addNew = (struct employeeRecord*)malloc(sizeof(struct employeeRecord));
	char H[] = "HR";
	char h[] = "hr";
	char M[] = "Marketing";
	char m[] = "marketing";
	char I[] = "IT";
	char i[] = "it";
    strcpy(addNew->employeeName,employeeName_input);									// copy employee name to addNew
    strcpy(addNew->supervisorName,supervisorName_input);   								// copy the supervisor name to addNew
    if(strcmp(department_input,H) == 0 || strcmp(department_input,h) == 0){
        addNew->department = 0;															// set department to 0 if input was HR
    }
    else if(strcmp(department_input,M) == 0 || strcmp(department_input,m) == 0){
        addNew->department = 1;															// set department to 1 if input was Marketing
    }
    else{
        addNew->department = 2;															// set department to 2 if input was IT
    }
	addNew->roomNumber=roomNumber_input;												// copy roomNumber to addNew
    addNew->next=NULL;																	// set the next node to NULL

		// checking for the same employee
	struct employeeRecord* tempList2 = list;
	while (tempList2 != NULL){
		if (strcmp(tempList2->employeeName, addNew->employeeName) == 0){				// see if the names are the same at this node
			return 0;
		}
		tempList2 = tempList2->next;													// move pointer on to the next node
	}

    if(list==NULL){
        list=(struct employeeRecord*)malloc(sizeof(struct employeeRecord));				// allocate memory for list if it is NULL
        list->next=addNew;																// put the new employee into the second node of the linked list
    }

    else if(list->next==NULL){
        list->next=addNew;																// put the new employee into the next node
    } else{
        while (tempList->next!=NULL) {
            tempList=tempList->next;													// traverse through the linked list to get to the end
        } 
        tempList->next = addNew;														// add the new employee to the next node once at the end
    }
    return 1; // edit this line as needed
}
				


	


// Q2 : displayList (10 points)
// This function displays the linked list of employees, with all details (struct elements). 
// Parse through the linked list and print the employee details one after the other. See expected output screenshots in homework question file.
// NOTE: Department is stored in the struct as enum type. You need to display a string for department.
void displayList()
{
	struct employeeRecord* tempList = list;				// work on a copy of 'list'
	// enter code here
	if (list == NULL || list->next == NULL){
		printf("The list is empty \n");
		return;
	} else{

		tempList = tempList->next;												// move pointer to node of first employee
		while (tempList != NULL){
			printf("\nEmployee name: %s \n", tempList->employeeName);
			printf("Supervisor name: %s \n", tempList->supervisorName);
			if (tempList->department == 0){
					printf("Department: HR \n");
			} else if (tempList->department == 1){
					printf("Department: Marketing \n");
			} else {			
					printf("Department: IT \n");
			}
			printf("Room number: %d \n", tempList->roomNumber);
			tempList = tempList->next;											// move pointer to node of next employee
		}
		return;
	}
}

// Q3: countNodes (5 points)
// This function counts the number of employees on the linked list and returns the number.
// You may use this function in other functions like deleteNode(), sortList(), addNode(), if needed. 
// It can helpful to call this function in other functions, but not necessary.
// This function is called in main() to display number of employees along with the user menu.
int countNodes()
{
	struct employeeRecord* tempList = list;
	int count = 0;									// start the count at zero employees
	if (list == NULL){								// return count as zero if the list is empty
		count = 0;
		return 0;
	} else {
		tempList = tempList->next;					// move pointer to first employee
		while (tempList != NULL){
			tempList = tempList->next;				// traverse through the list
			count++;								// add 1 to count each time a new node is traversed
		}
	}

	return count;	// edit this line as needed
}

// Q4 : deleteNode (10 points)
// This function deletes the node specified by the employee name.
// Parse through the linked list and remove the node containing this employee name.
// NOTE: After you remove the node, make sure that your linked list is not broken.
// (Hint: Visualize the list as: list......-> node1 -> node_to_remove -> node2 -> ...end. 
//        After removing "node_to_remove", the list is broken into "list ....node1" and "node2.... end". Stitch these lists.)

int deleteNode(char* employeeName_input)
{	
	struct employeeRecord* tempList = list;				// work on a copy of 'list'
	struct employeeRecord* tempList2 = list;

	if (list == NULL || list->next == NULL){
		return 2;
	}
	
	tempList2 = tempList; 								// set the pointers equal to eachother
	tempList = tempList->next;							// move the tempList pointer one node ahead of tempList2
	while (tempList != NULL){
		if (strcmp(tempList->employeeName, employeeName_input) == 0){
			tempList2->next = tempList->next;			// have tempList2 skip the node that tempList is currently at
			free(tempList);								// free the memory
			return 1;
		}
		tempList2 = tempList;							// set the pointers equal to eachother
		tempList = tempList->next;						// move the tempList pointer one node ahead of tempList2
	}
	
	return 0;			// edit this line as needed
}


// Q5 : swapNodes (5 points)
// This function swaps the elements of parameters 'node1' and 'node2' (Here node1 does NOT mean 1st node of the list. 'node1' is just the name of the node)
// This function should not alter the 'next' element of the nodes. Only then will the nodes be swapped.
// Hint: The swap logic is similar to swapping two simple integer/string variables.
// NOTE: This function can be used in the sorting logic in sortList()

void swapNodes(struct employeeRecord* node1, struct employeeRecord* node2)
{
	struct employeeRecord* tempList = (struct employeeRecord*)malloc(sizeof(struct employeeRecord));
	struct employeeRecord* tempList2 = (struct employeeRecord*)malloc(sizeof(struct employeeRecord));

	if (node1 == node2){
		return;
	}

	if (node1 == NULL || node2 == NULL){
		return;
	}


	// copy each node into temporary nodes so they may be swapped
	strcpy(tempList->employeeName, node1->employeeName);
	strcpy(tempList->supervisorName, node1->supervisorName);
	tempList->department = node1->department;
	tempList->roomNumber = node1->roomNumber;

	strcpy(tempList2->employeeName, node2->employeeName);
	strcpy(tempList2->supervisorName, node2->supervisorName);
	tempList2->department = node2->department;
	tempList2->roomNumber = node2->roomNumber;

	// copy the temporary nodes into the opposite node to swap
	strcpy(node1->employeeName, tempList2->employeeName);
	strcpy(node1->supervisorName, tempList2->supervisorName);
	node1->department = tempList2->department;
	node1->roomNumber = tempList2->roomNumber;

	strcpy(node2->employeeName, tempList->employeeName);
	strcpy(node2->supervisorName, tempList->supervisorName);
	node2->department = tempList->department;
	node2->roomNumber = tempList->roomNumber;
}



// Q6 : sortList (10 points)
// This function sorts the linked list by supervisor's name in descending order.
// Parse the list and compare the supervisor names to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new linked list of employees having sorted employees.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by employee name which is a string.
//       Use swapNodes() to swap the nodes in the sorting logic

void sortList()
{
	struct employeeRecord* tempList = list;				// work on a copy of 'list'
	// enter code here

	if (list == NULL || list->next == NULL){
		printf("The list is empty\n");
		return;
	}

	struct employeeRecord* bigger;													// make a pointer for the node that should go first
	while (tempList != NULL){
		bigger = tempList->next;													// set the pointer one node ahead
		while(bigger != NULL){
			if (strcmp(tempList->supervisorName, bigger->supervisorName) > 0){		// enters if statement if bigger should not go first
				swapNodes(tempList,bigger);											// swap the nodes
			}
			bigger = bigger->next;													// continue to traverse through the list in order to compare to the employee at tempList
		}
		tempList = tempList->next;													// move templist to the next employee in the list
	}
	
	printf("\nEmployee list sorted! Use display option 'd' to view sorted list.\n");
	
}

