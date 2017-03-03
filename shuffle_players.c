/*
 * shuffle_players.c
 *
 *  Created on: 13 Feb 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*Declare the shufflePlayers function.*/
void shufflePlayers(void);

void shufflePlayers(void){

	/*Allows for the random function to generate a new set of random numbers everytime the program runs.*/
	srand(time(NULL));

	/*Declaring the variables needed.*/
	int i, j, n;
	char s[11][100];
	char line[100], t[100], type[100], type_1[100], type_2[100], type_3[100];

	/*Open the text file*/
	FILE *fp;
	fp = fopen("players.txt", "r");

	/*If opening the file fails then print the error.*/
	if(fp == NULL){
		perror("Error opening file");
	}else{

		/*Read each line using the fgets function and hold it in the
			 * buffer named line. Then copy the string that is in line into
			 * the character array named s.*/
		i=0;
		while(fgets(line, 100, fp)!= NULL){
			strcpy(s[i], line);
			i++;
		}
		/*Close the file.*/
		fclose(fp);
	}


	/*Generates a random number stored in j and shuffles the order of the array randomly.
	 * Based on the Fisher Yates algorithm.*/
	for(i=1; i<10; i++){

		j = rand()%(i+1);
		strcpy(t, s[j]);
		strcpy(s[j], s[i]);
		strcpy(s[i], t);

	}

	/*Checks for elements that are of the same type and placed consecutively in the array.*/
	for(i=1; i<10; i++){
		/*Scans the string before the current element in the array and also the current
		 * element in the array and assigns the first string that is called type into
		 * the variables type_1 and type*/
		sscanf(s[i-1],"%s, %*s, %*s, %*s", type_1);
		sscanf(s[i],"%s, %*s, %*s, %*s", type);

		/*Compare the two type variables and if they are the same then continue.*/
		if((strcmp(type_1, type)) == 0){

			/*Loop designed to check for two elements in the array that aren't the same
			 * type as the current element being moved.*/
			for(n=0; n<10; n++){

				/*Scan the line before and the line after the element that the duplicate
				 * element will be copied to. Scan the first string in both cases and
				 * store them in the variables type_2 and type_3.*/
				sscanf(s[n-1],"%s, %*s, %*s, %*s", type_2);
				sscanf(s[n+1],"%s, %*s, %*s, %*s", type_3);

				/*Compare the variable type_2 and type as well as comparing the variables
				 * type_3 and type. If both result in not being the same then continue.*/
				if((strcmp(type_2, type) != 0) && (strcmp(type_3, type) != 0)){
					/*Copying the duplicate string into its new position and copying
					 * the string that is in the new position to the position of the
					 * duplicate string.*/
					strcpy(t, s[n]);
					strcpy(s[n], s[i]);
					strcpy(s[i], t);
				}

			}
		/*Set i back to 1 to check if there are any more consecutive duplicate types
		 * and if there are then do the same sequence.*/
		i=1;
		}
	}

	printf("\nShuffled Players: \n");
	/*Prints the resulting array.*/
	for(i=0; i<10; i++){
		printf("%s", s[i]);
	}

	/*Return to the main function.*/
	return;
}

