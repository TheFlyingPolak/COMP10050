/*
 * from_file.c

 *
 *  Created on: 2 Mar 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "sortplayers.h"
#include "shuffleplayers.h"
#include "sortslots.h"
#include "setvalues.h"

void fromFile(void);

void fromFile(void){
	/*Declaring the variables needed.*/
		char answer[5][5];
		int i=0, j=0;

		/*Continue while j is equal to 0*/
		while(j == 0){
			/*Ask the user if they would like to sort and shuffle the players
			 * store the response in the answer array of element i.*/
			printf("Would you like to"
					" sort and shuffle the players? Y/N: ");
			scanf("%s", answer[i]);
			/*If the input is equal to a lowercase or uppercase y then call the functions
			 * increment i and exit the loop.*/
			if(strcmp(answer[i], "y")==0 || strcmp(answer[i], "Y")==0){
				sortPlayers();
				shufflePlayers();
				i++;
				j=-1;
			}/*If the input is equal to a lowercase or uppercase n then increment i,
			* also ask the user if they would like to sort the slots*/
			else if(strcmp(answer[i], "n")==0 || strcmp(answer[i], "N")==0){
				i++;
				printf("Would you like to sort the slots? Y/N: ");
				scanf("%s", answer[i]);
				/*If the input is equal to a lowercase or uppercase y then
				 * call the function and exit the loop.*/
				if(strcmp(answer[i], "y")==0 || strcmp(answer[i], "Y")==0){

				sortSlots();
				j=-1;
				}
			}/*If anything other then y or n is inputted print the error.*/
			else{
				printf("Please enter a correct character.");
				j=-1;
			}

		}

		/*If the answer to the first printf statement was a lowercase or uppercase
		 * y then ask the user if they would like to sort the slots.*/
		if(strcmp(answer[0], "y")==0 || strcmp(answer[0], "Y")==0){
			printf("Would you also like to sort the slots? Y/N: ");
			scanf("%s", answer[i]);
			/*If they want to sort the slots then call the function and increment i.*/
			if(strcmp(answer[0], "y")==0 || strcmp(answer[0], "Y")==0){
				sortSlots();
				i++;
			}/*If the answer stored in answer[1] was a lowercase or uppercase y then
			Increment i.*/
			else if ((strcmp(answer[1], "y")==0 || strcmp(answer[1], "Y")==0)){
				i++;
			}
		}
}
