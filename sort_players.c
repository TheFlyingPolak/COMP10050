/*
 * sort_players.c
 *
 *  Created on: 13 Feb 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <string.h>

/*Declaring the sortPlayers function.*/
void sortPlayers(void);

void sortPlayers(void){

	/*Declaring the variables needed.*/
	char s[11][100];
	char line[100], t[100];
	int i, j;

	/*Open the text file*/
	FILE *fp;
	fp = fopen("players.txt", "r");

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


	/*Organise the elements in the array to be i                                                                                                                                          n
	alphabetical order.*/
	for (i = 1; i < 11; i++) {
      for (j = 1; j < 11; j++) {
         if (strcmp(s[j - 1], s[j]) > 0) {
            strcpy(t, s[j - 1]);
            strcpy(s[j - 1], s[j]);
            strcpy(s[j], t);
         }
      }
   }

	printf("\nSorted Players: \n");
	/*Print the results of the organised array.*/
	for(i=0; i<11; i++){
		printf("%s", s[i]);
	}


	/*Return to the main function.*/
	return;
}

