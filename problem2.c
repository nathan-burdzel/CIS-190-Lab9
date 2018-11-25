/*Nathan Burdzel
  *CIS 190
  *Homework 4
  *Problem 3
  *Recursive solution for the map distance problem printing all possible routes
  *11/15/19
  */

/*Preprocessor directives*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Defined constants*/
#define BUFFER 128
#define QUIT_LETTER 113
#define MIN_INT 48
#define MAX_INT 57
#define MINUS 45

/*Function stubs*/
void getInput(char input[], int index);
int checkInt(char input[]);
void addInt(int input, int **list);
void mergeLists(int** first, int** second);
void printLists(int* first, int* second);
int checkIfRepeat(int* list, int test);
int main(void){
	/*Declare variables*/
	int *listOne, *listTwo;
	char input[BUFFER];
	int index = 0, test = 0;

	/*Create the array for the lists of ints*/
  listOne = malloc(sizeof(int));
  listTwo = malloc(sizeof(int));

  /*Initialize the first element to contain the number of elements contained in the arrays*/
  *listOne = 0;
  *listTwo = 0;

  /*get the numbers for the first list and add them to the array*/
  printf("Enter as many numbers as you want for array 1, enter a value again to quit\n");
	do {
    getInput(input, index);
		if(!(test = checkIfRepeat(listOne, atoi(input)))){
    	addInt((atoi(input)), &listOne);
			printf("%d", *listOne);
			index++;
		}
	} while(!test);

	/*get the numbers for the second list and add them to the array*/
	index = 0;
	printf("Enter as many numbers as you want for array 2, enter a value again to quit\n");
	do {
		getInput(input, index);
		if(!(test = checkIfRepeat(listTwo, atoi(input)))){
			addInt((atoi(input)), &listTwo);
			printf("%d", *listOne);
			index++;
		}
	} while(!test);

	/*Add the elements*/
  mergeLists(&listOne, &listTwo);
	/*Print the resulting lists*/
  printLists(listOne, listTwo);
	/*free the memory*/
	free(listOne);
	free(listTwo);

	return 0;
}

/*Adds the elements from the lists to each other if they don't exist*/
void mergeLists(int **first, int **second){
	/*local variables*/
	int i, j;
	/*For each element in the first list*/
  for(i = 1; i < (**first) + 1; i++){
		/*for each element in the second list*/
    for(j = 1; j < (**second) + 1; j++){
			/*If this is a match break*/
      if((*first)[i] == (*second)[j])
        break;
    }
		/*if no element is a match add element i of first list to second list*/
    if((*first)[i] != (*second)[j]){
      addInt((*first)[i], second);
    }
  }
	/*Same except swapping first and second list*/
  for(j = 1; j < (**second) + 1; j++){
    for(i = 1; i < (**first) + 1; i++){
      if((*first)[i] == (*second)[j])
        break;
    }
    if((*first)[i] != (*second)[j]){
      addInt((*second)[j], first);
    }
  }
}

/*Print out all the elements of both lists simultaneously*/
void printLists(int *listOne, int *listTwo){
	int index = 1;
  while(index < (*listOne) + 1){
    printf("Position %d is %d and %d\n", index - 1, listOne[index], listTwo[index]);
    index++;
  }
}

/*GetInput from user, if it's not an int return 0*/
void getInput(char input[], int index){
	printf("\nPlease enter the %dth element: ", index);
	do{
		fgets(input, BUFFER, stdin);
		input[strlen(input) - 1] = 0;
		if(!strlen(input))
			printf("Please enter something\n");
		else if(!checkInt(input))
			printf("Please enter an int\n");
	}while(!strlen(input) || !checkInt(input));
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

/*Adds an int to the list*/
void addInt(int input, int **list){
	*list = realloc(*list, (**list + 2) * sizeof(int));
	(**list)++;
  (*list)[**(list)] = input;
}

/*Checks to see if test already exists in list*/
int checkIfRepeat(int* list, int test){
	int i;
	for(i = 1; i < *list + 1; i++)
		if(list[i] == test)
			return 1;
	return 0;
}
