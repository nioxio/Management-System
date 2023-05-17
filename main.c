#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#pragma warning(disable:4996)
#define EMPLOYEE_LIMIT 100

int length = 0;
struct Employee {
	int Index;
	char FullName[64];
	int Age;
	char Role[64];
	int Salary;
	char SSN[14];
} employee[EMPLOYEE_LIMIT];

char filePath[1024];

// forward declare functions
char* stringInput(int maxLength);
void addEmployee();
void editEmployee();
void removeEmployee();
void listEmployees();
void searchEmployees();
void searchIndex();
void searchFullName();
void searchRole();
void searchSSN();
void saveEmployees();
void loadEmployees();
void printEmployee(int i, int a);

int main(void) {
	snprintf(filePath, 1024, "%s%s\\Desktop\\Jonny TE21 Management-System.txt", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
	loadEmployees();
	while (1) {
		system("cls");
		printf("\033[0;36m###################\n");
		printf(" Management system \n");
		printf("###################\n");
		printf("(1) Add Employee\n");
		printf("(2) Edit Employee\n");
		printf("(3) Remove Employee\n");
		printf("(4) List Employees\n");
		printf("(5) Search Employee\n");
		printf("(Q) Exit program.\033[0;37m\n");
		switch (getch()) {
		case '1':
			addEmployee();
			saveEmployees();
			break;
		case '2':
			editEmployee();
			saveEmployees();
			break;
		case '3':
			removeEmployee();
			saveEmployees();
			break;
		case '4':
			listEmployees();
			break;
		case '5':
			searchEmployees();
			break;
		case 'q':
		case 'Q':
			return;
		}
	}
}

// function for adding a new employee
void addEmployee() {
	// if the employee limit has been reached, exit early
	if (length-1 > EMPLOYEE_LIMIT) {
		printf("\033[0;31mToo many employees added, consider editing or removing existing employees!\033[0;37m\n");
		getch();
		return;
	}
	system("cls");
	printf("\033[0;36mFull Name : \033[0;33m");
	// Take Full Name input
	char* name = stringInput(64);
	strcpy_s(employee[length].FullName, strlen(name) + 1, name);
	system("cls");
	printf("\033[0;36mAge : \033[0;33m");
	// Take Age input
	employee[length].Age = intInput(64);
	system("cls");
	printf("\033[0;36mRole : \033[0;33m");
	// Take Role input
	char* role = stringInput(64);
	strcpy_s(employee[length].Role, strlen(role) + 1, role);
	system("cls");
	printf("\033[0;36mSalary : \033[0;33m");
	// Take Salary input
	employee[length].Salary = intInput(64);
	system("cls");
	printf("\033[0;36mSocial Security Number (yyyymmdd-xxxx): \033[0;33m");
	// Take Social Security Number input
	char* ssn = stringInput(14);
	strcpy_s(employee[length].SSN, strlen(ssn) + 1, ssn);
	employee[length].Index = length;
	// increase length variable (says how many entries there are in the struct employee array)
	length++;
	return;
}

// function for editing employee information
void editEmployee() {
	system("cls");
	printf("\033[0;36mEnter index of the entry you wish to edit : \033[0;33m");
	int index = intInput(64)-1;
	// if inputed index has no entry to it, exit early
	if (index >= length) {
		printf("\033[0;31mThat index is out of bounds! Try something lower or make a new entry!\033[0;37m\n");
		getch();
		return;
	}
	// show the information and ask which part of it the user wants to edit
	while (1) {
		system("cls");
		printEmployee(index, 1);
		printf("\033[0;36mPress the number for the part you wish to edit! Or any other key to continue.\n");
		switch (getch()) {
		case '1':
			// edit Full Name of entry
			system("cls");
			printf("\033[0;36mFull Name : \033[0;33m");
			char* name = stringInput(64);
			strcpy_s(employee[index].FullName, strlen(name) + 1, name);
			break;
		case '2':
			// edit Age of entry
			system("cls");
			printf("\033[0;36mAge : \033[0;33m");
			employee[index].Age = intInput(64);
			break;
		case '3':
			// edit Role of entry
			system("cls");
			printf("\033[0;36mRole : \033[0;33m");
			char* role = stringInput(64);
			strcpy_s(employee[index].Role, strlen(role) + 1, role);
			break;
		case '4':
			// edit Salary of entry
			system("cls");
			printf("\033[0;36mSalary : \033[0;33m");
			employee[index].Salary = intInput(64);
			break;
		case '5':
			// edit Social Security Number of entry
			system("cls");
			printf("\033[0;36mSocial Security Number (yyyymmdd-xxxx): \033[0;33m");
			char* ssn = stringInput(14);
			strcpy_s(employee[index].SSN, strlen(ssn) + 1, ssn);
			break;
		default:
			// exit if the user presses another key
			system("cls");
			return;
		}
	}
}

// function for removing employees
void removeEmployee() {
	system("cls");
	// if there are no entries, exit early
	if (length == 0) {
		printf("\033[0;31mThere are no entries to remove!\033[0;37m");
		getch();
		return;
	}
	printf("\033[0;36mEnter index of the entry you wish to remove : \033[0;33m");
	int index = intInput(64)-1;
	// if inputed index has no entry to it, exit early
	if (index >= length) {
		printf("\033[0;31mThat index is out of bounds! Try something lower or make a new entry!\033[0;37m\n");
		getch();
		return;
	}
	system("cls");
	// if entry exists, show it then ask if the user wishes to remove it
	printEmployee(index, 2);
	printf("\033[0;33mAre you sure you wish to remove this entry? (y/n)\033[0;37m\n");
	int a = 0;
	switch (getch()) {
	case 'y':
		break;
	default:
		return;
	}
	// if the user decides to remove it, remove it and move all entries after the removed one back one step
	int destination = index;
	int source = index+1;
	while (source < length+3) {
		strcpy_s(employee[destination].FullName, 64, employee[source].FullName);
		employee[destination].Age = employee[source].Age;
		strcpy_s(employee[destination].Role, 64, employee[source].Role);
		employee[destination].Salary = employee[source].Salary;
		strcpy_s(employee[destination].SSN, 14, employee[source].SSN);
		destination++;
		source++;
	}
	// decrease length variable (says how many entries there are in the struct employee array)
	length--;
	return;
}

// function for listing all employees
void listEmployees() {
	system("cls");
	for (int i = 0; i < length; i++) {
		printEmployee(i, 0);
		printf("\n");
	}
	printf("\033[0;36mPress any key to continue.\033[0;37m");
	getch();
	return;
}

// Ask user which type to search for
void searchEmployees() {
	system("cls");
	printf("\033[0;36mSearch by:\n");
	printf(" (1) Index\n");
	printf(" (2) Full Name\n");
	printf(" (3) Role\n");
	printf(" (4) Social Security Number\033[0;37m\n");
	switch (getch()) {
	case '1':
		searchIndex();
		break;
	case '2':
		searchFullName();
		break;
	case '3':
		searchRole();
		break;
	case '4':
		searchSSN();
		break;
	default:
		printf("\033[0;31mInvalid search type.\n");
		printf("\033[0;36mPress any key to continue...\033[0;37m\n");
		getch();
		break;
	}
	return;
}

// search function for index
void searchIndex() {
	system("cls");
	printf("\033[0;36mEnter index of the employee: \033[0;33m");
	// take integer input
	int input = intInput(64) - 1;
	if (input < length && input >= 0) {
		system("cls");
		// print the array with index of the same input
		printEmployee(input, 0);
	}
	else {
		printf("\033[0;31mThat index is out of bounds.\nPress any key to continue\033[0;37m\n");
	}
	getch();
	return;
}

// search function for Full Name
void searchFullName() {
	system("cls");
	printf("\033[0;36mEnter name to search for: \033[0;33m");
	char buffer[64];
	// take string input
	while (1) {
		fgets(buffer, 64, stdin);
		if (strlen(buffer) > 1)
			break;
	}
	buffer[strcspn(buffer, "\n")] = 0;
	system("cls");
	int results = 0;
	// if input matches with any Role entries inside of the struct employee array, print them to console
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < strlen(buffer)+1; j++) {
			// if this part of the loop reaches j == strlen(buffer) without exiting it means the values match
			if (j == strlen(buffer)) {
				printEmployee(i, 0);
				printf("\n");
				results++;
				break;
			}
			// if input does not match this entry, exit this part of the loop early
			if (tolower(buffer[j]) != tolower(employee[i].FullName[j])) {
				break;
			}
		}
	}
	if (results > 0)
		printf("\033[0;32m%d result(s) were successfully found!\033[0;37m", results);
	else
		printf("\033[0;31mNo results were found for that search.\033[0;37m");
	getch();
	return;
}

// search function for role
void searchRole() {
	system("cls");
	printf("\033[0;36mEnter role to search for: \033[0;33m");
	char buffer[64];
	// take string input
	while (1) {
		fgets(buffer, 64, stdin);
		if (strlen(buffer) > 1)
			break;
	}
	buffer[strcspn(buffer, "\n")] = 0;
	system("cls");
	int results = 0;
	// if input matches with any Role entries inside of the struct employee array, print them to console
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < strlen(buffer) + 1; j++) {
			// if this part of the loop reaches j == strlen(buffer) without exiting it means the values match
			if (j == strlen(buffer)) {
				printEmployee(i, 0);
				printf("\n");
				results++;
				break;
			}
			// if input does not match this entry, exit this part of the loop early
			if (tolower(buffer[j]) != tolower(employee[i].Role[j])) {
				break;
			}
		}
	}
	if (results > 0) {
		printf("\033[0;32m%d result(s) were successfully found!\033[0;37m", results);
	}
	else {
		printf("\033[0;31mNo results were found for that search.\033[0;37m");
	}
	getch();
	return;
}

// search function for Social Security Number
void searchSSN() {
	system("cls");
	printf("\033[0;36mEnter Social Security Number to search for: \033[0;33m");
	// take string input
	char buffer[64];
	while (1) {
		fgets(buffer, 64, stdin);
		if (strlen(buffer) > 1)
			break;
	}
	buffer[strcspn(buffer, "\n")] = 0;
	system("cls");
	int results = 0;
	// if input matches with any SSN entries inside of the struct employee array, print them to console
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < strlen(buffer) + 1; j++) {
			// if this part of the loop reaches j == strlen(buffer) without exiting it means the values match
			if (j == strlen(buffer)) {
				printEmployee(i, 0);
				printf("\n");
				results++;
				break;
			}
			// if input does not match this entry, exit this part of the loop
			if (tolower(buffer[j]) != tolower(employee[i].SSN[j])) {
				break;
			}
		}
	}
	// This is the same as the first loop, except it accounts for an input with shortened year date (yymmdd-xxxx) instead of the standard (yyyymmdd-xxxx)
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < strlen(buffer) + 1; j++) {
			if (j == strlen(buffer)) {
				printEmployee(i, 0);
				printf("\n");
				results++;
				break;
			}
			if (tolower(buffer[j]) != tolower(employee[i].SSN[j+2])) {
				break;
			}
		}
	}
	if (results > 0) {
		printf("\033[0;32m%d result(s) were successfully found!\033[0;37m", results);
	}
	else {
		printf("\033[0;31mNo results were found for that search.\033[0;37m");
	}
	getch();
	return;
}

// function for saving employee information to an external file
void saveEmployees() {
	FILE* file;
	// open specified file in writing mode
	file = fopen(filePath, "w");
	// add disclaimer at the beginning of file
	fprintf(file, "! Manually editing this file may result in unexpected behaviour !");
	// take all values from the struct employee array and write them inside of the file
	for (int i = 0; i < length; i++) {
		fprintf(file, "\n");
		fprintf(file, "%s\n", employee[i].FullName);
		fprintf(file, "%d\n", employee[i].Age);
		fprintf(file, "%s\n", employee[i].Role);
		fprintf(file, "%d\n", employee[i].Salary);
		fprintf(file, "%s", employee[i].SSN);
	}
	// close file once completed
	fclose(file);
	return;
}

// function for loading employee information from an external file
void loadEmployees() {
	length = 0;
	FILE* file;
	// open specified file in reading mode
	file = fopen(filePath, "r");
	if (!file) {
		saveEmployees();
		return;
	}
	char ch;
	// go past the first 67 characters (warning inside of file)
	for (int i = 0; i < 67; i++) {
		ch = getc(file);
	}
	while (1) {
		char temp[64];
		int i;
		// See if EOF has been reached
		if (ch == EOF) {
			// close file
			fclose(file);
			break;
		}
		// retrieve FullName of an entry inside of file
		for (i = 0; ch != '\n'; i++) {
			temp[i] = ch;
			ch = getc(file);
		}
		temp[i] = '\0';
		// copy the FullName retrieved from file into the struct employee array
		strcpy_s(employee[length].FullName, 64, temp);
		ch = getc(file);
		// retrieve Age of an entry inside of file
		for (i = 0; ch != '\n'; i++) {
			temp[i] = ch;
			ch = getc(file);
		}
		temp[i] = '\0';
		// convert Age from string to integer and add it to the struct employee array
		employee[length].Age = atoi(temp);
		ch = getc(file);
		// retrieve Role of an entry inside of file
		for (i = 0; ch != '\n'; i++) {
			temp[i] = ch;
			ch = getc(file);
		}
		temp[i] = '\0';
		// copy the Role retrieved from file into the struct employee array
		strcpy_s(employee[length].Role, 64, temp);
		ch = getc(file);
		// retrieve Salary of an entry inside of file
		for (i = 0; ch != '\n'; i++) {
			temp[i] = ch;
			ch = getc(file);
		}
		temp[i] = '\0';
		// convert Salary from string to integer and add it to the struct employee array
		employee[length].Salary = atoi(temp);
		ch = getc(file);
		// retrieve SSN of an entry inside of file
		for (i = 0; ch != '\n' && ch != EOF; i++) {
			temp[i] = ch;
			ch = getc(file);
		}
		temp[i] = '\0';
		// copy the SSN retrieved from file into the struct employee array
		strcpy_s(employee[length].SSN, 64, temp);
		ch = getc(file);
		employee[length].Index = length;
		length++;
	}
	return;
}

// function to print all values of an employee entry
void printEmployee(int i, int a) {
	if (a == 1){
		printf("\033[0;36m(1) Name   : %s\n", employee[i].FullName);
		printf("(2) Age    : %d\n", employee[i].Age);
		printf("(3) Role   : %s\n", employee[i].Role);
		printf("(4) Salary : %d\n", employee[i].Salary);
		printf("(5) SSN    : %s\033[0;37m\n", employee[i].SSN);
	}
	else {
		if (a == 0) {
			printf("\033[0;36mIndex  : %d\n", employee[i].Index + 1);
		}
		printf("\033[0;36mName   : %s\n", employee[i].FullName);
		printf("Age    : %d\n", employee[i].Age);
		printf("Role   : %s\n", employee[i].Role);
		printf("Salary : %d\n", employee[i].Salary);
		printf("SSN    : %s\033[0;37m\n", employee[i].SSN);
	}
	return;
}

// function for taking string input
char* stringInput(int maxLength) {
	char buffer[1024];
	while (1) {
		// Take input from user, end on new line or when maxLength is reached
		fgets(buffer, maxLength, stdin);
		// Exit loop if input is longer than 1 (only a new line character)
		if (strlen(buffer) > 1)
			break;
	}
	// "remove" new line characters
	buffer[strcspn(buffer, "\n")] = 0;
	// return the input string
	return buffer;
}

// function for taking integer input
int intInput(int maxLength) {
	char buffer[1024];
	int age;
	while (1) {
		// Take input from user, end on new line or when maxLength is reached
		fgets(buffer, maxLength, stdin);
		char* endPointer;
		// Convert input from string to integer
		age = strtol(buffer, &endPointer, 10);
		// Exit loop if the converted input resulted in an actual integer
		if (age != NULL)
			break;
	}
	// return the input integer
	return age;
}