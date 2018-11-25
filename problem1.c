/*Nathan Burdzel
  *CIS 190
  *Lab 9
  *Problem 1
  *Dynamicall allocated data type sorting and storing
  *11/21/18
  */

/*Preprocessor directives*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Defined constants*/
#define BUFFER 128
#define QUIT_LETTER 113
#define MINUS 45
#define DECIMAL_POINT 46
#define MIN_INT 48
#define MAX_INT 57

/*Function stubs*/
void getInput(char input[]);
int checkInputs(char input[]);
int checkInt(char input[]);
int checkFloat(char input[]);
int checkChar(char input[]);
void addInt(char input[], int **ints, int* numberOfInts);
void addDouble(char input[], double **doubles, int* numberOfDoubles);
void addChar(char input[], char **chars, int* numberOfChars);
void addString(char input[], char ***strings, int* numberOfStrings);
void printList(char ** strings, int * ints, double * doubles, char * chars, int numberOfStrings, int numberOfInts, int numberOfDoubles, int numberOfChars);

int main(void){
	/*Declare variables*/
	char ** strings;
	int * ints;
	double * doubles;
	char * chars;
	int numberOfStrings = 0, numberOfInts = 0, numberOfDoubles = 0, numberOfChars = 0, test;
	char input[BUFFER];

	/*Create the arrays for each variable*/
	strings = malloc(0);
	ints = malloc(0);
	doubles = malloc(0);
	chars = malloc(0);

	/*Loop to get input until the user quits*/
	do {
	/*Get input from user*/
	getInput(input);
		/*Switch based on the results of the input*/
		switch(test = checkInputs(input)){
			/*If program should quit, break out of the switch*/
			case 0:
				break;
			/*If the input was an int add it to the list then print the lists*/
			case 1:
				addInt(input, &ints, &numberOfInts);
				printList(strings, ints, doubles, chars, numberOfStrings, numberOfInts, numberOfDoubles, numberOfChars);
				break;
			/*If the input was a double add it to the list of doubles then print the lists*/
			case 2:
				addDouble(input, &doubles, &numberOfDoubles);
				printList(strings, ints, doubles, chars, numberOfStrings, numberOfInts, numberOfDoubles, numberOfChars);
		 		break;
			/*If the input was a char add it to the list of chars then print the lists*/
			case 3:
				addChar(input, &chars, &numberOfChars);
				printList(strings, ints, doubles, chars, numberOfStrings, numberOfInts, numberOfDoubles, numberOfChars);
				break;
			/*If the input was a string add it to the list of strings then print the lists*/
		 	default:
		 		addString(input, &strings, &numberOfStrings);
		 		printList(strings, ints, doubles, chars, numberOfStrings, numberOfInts, numberOfDoubles, numberOfChars);
				break;
		}
	}while(test);

	/*Free the memory*/
	free(chars);
	free(doubles);
	free(ints);
	for(; numberOfStrings >= 0; numberOfStrings--)
		free(strings[numberOfStrings]);
	free(strings);

	return 0;
}

/*Prints out everything in the lists*/
void printList(char ** strings, int * ints, double * doubles, char * chars, int numberOfStrings, int numberOfInts, int numberOfDoubles, int numberOfChars){
	/*Local variables*/
	int i;
	/*Print the strings*/
	printf("\nString List: ");
	for(i = 0; i < numberOfStrings; i++)
		if(i == 0)
			printf("%s", strings[i]);
		else
		printf(", %s", strings[i]);
	/*Print the ints*/
	printf("\nInteger List: ");
	for(i = 0; i < numberOfInts; i++){
		if(!i)
			printf("%d", ints[i]);
		else
			printf(", %d", ints[i]);
	}
	/*print the doubles*/
	printf("\nDouble List: ");
	for(i = 0; i < numberOfDoubles; i++)
		if(i == 0)
			printf("%lf", doubles[i]);
		else
		printf(", %lf", doubles[i]);
	/*Print the characters*/
	printf("\nCharacter List: ");
	for(i = 0; i < numberOfChars; i++)
		if(i == 0)
			printf("%c", chars[i]);
		else
		printf(", %c", chars[i]);


}

/*GetInput*/
void getInput(char input[]){
	/*Loop to ensure input is entered*/
	do{
	/*Get the input*/
	printf("\nEnter your input or '%c' to quit: ", QUIT_LETTER);
	fgets(input, BUFFER, stdin);
	/*Strip the newline*/
	input[strlen(input) - 1] = 0;
	/*Print statement to tell the user how to enter good input*/
	if(!strlen(input))
		printf("Please enter some input");
	}while(!strlen(input));
}

/*Check to see what kind of input was entered, returns 0 to quit, 1 for an int, 2 for a float, 3 for  a char, and 4 for a string*/
int checkInputs(char input[]){
	int i;
	/*Check if it's an int*/
	if(checkInt(input))
		return 1;
	/*Check if it's a float*/
	if(checkFloat(input))
		return 2;
	/*Check if it's a char*/
	if(checkChar(input))
		/*If the letter used to quit was entered then return 0*/
		if(input[0] - QUIT_LETTER)
			return 3;
		else
			return 0;
	/*Otherwise it's a string*/
	return 4;
}

/*Checks if input is an int*/
int checkInt(char input[]){
	int i;
	/*If the first character isn't a number or the minus sign return 0*/
	if((input[0] < MIN_INT || input[0] > MAX_INT) && input[0] != MINUS)
		return 0;
	/*If there is more than a minus sign return 0*/
	else if(input[0] == MINUS)
		if(strlen(input) == 1)
			return 0;
	/*If any character isn't a valid int return 0*/
	for(i = 1; i < strlen(input); i++){
		if(input[i] < MIN_INT || input[i] > MAX_INT)
			return 0;
	}
	/*Otherwise return 1*/
	return 1;
}


/*Checks if input is a float(An int positive or negative, with a single decimal point, with numbers other than the decimal point)*/
int checkFloat(char input[]){
	int i, decimalCount;

	/*Initialize decimalCount to hold true if the first character is a decimal*/
	decimalCount = !(input[0] - DECIMAL_POINT);

	printf("%d fine\n", decimalCount);
	/*If the first character isn't a number or the minus sign or a period return 0*/
	if((input[0] < MIN_INT || input[0] > MAX_INT) && !(input[0] == MINUS || decimalCount)){
		printf("Not fine%d\n", !(input[0] == MINUS || decimalCount));
		return 0;
	}printf("Made it here");
	/*If there is just a minus sign or there isn't more than a minus and a decimal point*/
	if(input[0] == MINUS)
		if((strlen(input) == 1) || (strlen(input) == 2 && input[1] == DECIMAL_POINT))
			return 0;
	/*If there is just a period it is not a valid double*/
	if(input[0] == DECIMAL_POINT)
		if(strlen(input) == 1)
			return 0;
	/*If there are any characters that aren't ints or decimal points return 0*/
	for(i = 1; i < strlen(input); i++){
		if(input[i] < MIN_INT || input[i] > MAX_INT)
			if(input[i] == DECIMAL_POINT){
				/*if there is more than one decimal point return 0*/
				if (decimalCount)
					return 0;
				decimalCount++;
			}else return 0;
	}
	/*Otherwise return 1*/
	return 1;
}


/*Checks if input is a char*/
int checkChar(char input[]){
	/*If there is more than one char*/
	if(strlen(input) > 1)
		return 0;
	/*Otherwise return 1*/
	return 1;
}

/*Add an int to the array of ints*/
void addInt(char input[], int **ints, int* numberOfInts){
	*ints = realloc(*ints, (*numberOfInts + 1) * sizeof(int));
	(*ints)[*numberOfInts] = atoi(input);
	(*numberOfInts)++;
}

/*Add a double to the array of doubles*/
void addDouble(char input[], double **doubles, int* numberOfDoubles){
	*doubles = realloc(*doubles, (*numberOfDoubles + 1) * sizeof(double));
	(*doubles)[*numberOfDoubles] = atof(input);
	(*numberOfDoubles)++;
}

/*Add a char to the array of chars*/
void addChar(char input[], char **chars, int* numberOfChars){
	*chars = realloc(*chars, (*numberOfChars + 1) * sizeof(char));
	(*chars)[*numberOfChars] = input[0];
	(*numberOfChars)++;
}

/*Add a string to the array of strings*/
void addString(char input[], char ***strings, int* numberOfStrings){
	int i;
	*strings = realloc(*strings, (*numberOfStrings + 1) * sizeof(char*));
	(*strings)[*numberOfStrings] = malloc(sizeof(char) * strlen(input));
	for(i = strlen(input); i >= 0; i--)
	(*strings)[*numberOfStrings][i] = input[i];
	(*numberOfStrings)++;
}
