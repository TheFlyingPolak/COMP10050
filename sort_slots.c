/*
 * sort_slots.c
 *
 *  Created on: 13 Feb 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/*Declaring the sortSlots function.*/
void sortSlots(void);

void sortSlots(void){

	/*Declaring the variables needed.*/
	int i, lineNum = 0, slot=0, j, last;
	char s[10][100], num[100], type[100], last_num[100], new[10][100];
	char comma[2] = ",";

	/*Open the text file.*/
	FILE *fp;
	fp = fopen("slots.txt", "r");

	/*If opening the file fails then print the error and set lineNum to -1.*/
	if(fp == NULL){
		perror("Error opening file");
		lineNum = -1;
	}else{
		/*Read each line in the text file and copy it into the s array, also
		 * increase the lineNum variable by 1 every time there is a new line.*/
		while(fgets(s[lineNum],sizeof(s[lineNum]), fp) != NULL){
			lineNum++;
		}
		/*Close the file.*/
		fclose(fp);
	}



	/*Go through the s array and find the line that has the character x.*/
	for(i=0; i<7; i++){
		/*Scan the s array and assign the values of the first, third and
		 * forth strings in the variables, num, type and last_num respectively.*/
		sscanf(s[i], "%s %*s %s %s", num, type, last_num);

			/*If the value in last_num is the same as the character x then continue.*/
			if(*last_num == 'x'){
				/*Copy the string concatenation of num and comma into the new array
				 * of the value of the lineNum variable.*/
				strcpy(new[--lineNum],(strcat(num, comma)));
				/*Copy the string concatenation of the current element in the new
				 * array with the type variable.*/
				strcpy(new[lineNum],(strcat(new[lineNum], type)));
				/*Convert the num variable into an integer and store it in the new
				 * variable named slot.*/
				slot = atoi(num);

			}

	}

	/*Go through the s array and find the line that has the last number that is the
	 * same value that is in the slot variable.*/
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){

			/*Scan the s array and assign the values of the first, third and
			 * forth strings in the variables, num, type and last_num respectively.*/
			sscanf(s[j], "%s %*s %s %s", num, type, last_num);
			/*Convert the last_num variable into an integer and store it in the new
			 * variable named last.*/
			last = atoi(last_num);

			/*If the value stored in last is the same as the value stored in slot
			 * then continue through the statements.*/
			if(last == slot){
				/*Copy the string concatenation of num and comma into the new array
				 * of the value of the lineNum variable.*/
				strcpy(new[--lineNum],(strcat(num, comma)));
				/*Copy the string concatenation of the current element in the new
				 * array with the type variable.*/
				strcpy(new[lineNum],(strcat(new[lineNum], type)));
				/*Convert the num variable into an integer and store it in the new
				 * variable named slot.*/
				slot = atoi(num);
				/*Increment i.*/
				i++;
			}

		}
	}

	printf("\nSorted Slots: \n");
	/*Print the resulting array.*/
	for(i=0; i<7; i++){
		/*If i is less than 6 then print the new array with the brackets and the arrow.*/
		if(i<6){
			printf("(%s)-->", new[i]);
		}
		/*Else print the new array with just brackets.*/
		else{
			printf("(%s)", new[i]);
		}
	}

	/*Return to the main function.*/
	return;
}

