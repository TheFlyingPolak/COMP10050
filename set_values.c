/*
 * set_values.c
 *
 *  Created on: 2 Mar 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "setvalues.h"

/*setElfValues function that takes a struct pointer as an input parameter.*/
void setElfValues(struct player *name){
	int j;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%42+59;
	(*name).luck = j;

	j = rand()%32+69;
	(*name).smartness = j;

	j = rand()%50+1;
	(*name).strength = j;

	j = rand()%30+50;
	(*name).magic = j;

	j = rand()%100+1;
	(*name).dexterity = j;

	(*name).life = 100;
}

void setHumanValues(struct player *name){
	int j, total=301;

	/*While the total is greater than 300 then keep setting new values to the
	corresponding variable in the struct.*/
	while(total>300){
		j = rand()%100+1;
		(*name).luck = j;

		j = rand()%100+1;
		(*name).smartness = j;

		j = rand()%100+1;
		(*name).strength = j;

		j = rand()%100+1;
		(*name).dexterity = j;

		j = rand()%100+1;
		(*name).magic = j;

		(*name).life = 100;
		total = 0;
		total = ( (*name).luck + (*name).smartness + (*name).strength + (*name).dexterity + (*name).magic );
	}
}

void setOgreValues(struct player *name){
	int j, total;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%49+1;
	(*name).luck = j;

	j = rand()%20+1;
	(*name).smartness = j;

	j = rand()%22+79;
	(*name).strength = j;

	j = rand()%22+79;
	(*name).dexterity = j;

	(*name).magic = 0;

	(*name).life = 100;

	total = ( ((*name).luck) + ((*name).smartness) );
	/*If the total is greater than 50 then loop around and generate new
	random numbers to assign the corresponding variable in the struct.*/
	if(total>50){
		while(total>50){
			j = rand()%49+1;
			(*name).luck = j;

			j = rand()%20+1;
			(*name).smartness = j;

			total = ( ((*name).luck) + ((*name).smartness) );
		}
	}
}

void setWizardValues(struct player *name){
	int j;

	/*Generates a random number and sets it to the corresponding variable
	in the struct.*/
	j = rand()%52+49;
	(*name).luck = j;

	j = rand()%12+89;
	(*name).smartness = j;

	j = rand()%20+1;
	(*name).strength = j;

	j = rand()%100+1;
	(*name).dexterity = j;

	j = rand()%22+79;
	(*name).magic = j;

	(*name).life = 100;
}

void playersFromUser(struct player players[]){

	/*Declaring the variables needed.*/
		//int num_players, num_slots, i, type;
		int i, type;

		/*Generates different random numbers everytime the random function is called.*/
		srand(time(NULL));



		/*Loop around num_players times.*/
		for(i=0; i<num_players; i++){
			/*Ask the user to input a type for their player using the code given and
			store the input in an integer variable named type.*/
			printf("Please select a type for player %d.\n", i+1);
			printf("1 = Elf, 2 = Human, 3 = Ogre, 4 = Wizard\n");
			scanf("%d", &type);

			/*  Test the input to see if it is valid  */
			while (type < 1 || type > 4){
				printf("Such creature does not exist. Choose a different one.\n");
				scanf("%d", &type);
			}

			/*If the value of type corresponds to each case then do the following.*/
			switch(type){
				case 1:
					/*Compare the string stored in the players array of variable type to string "Elf".*/
					strcpy(players[i].type, "Elf");
					break;
				case 2:
					/*Compare the string stored in the players array of variable type to string "Human".*/
					strcpy(players[i].type, "Human");
					break;
				case 3:
					/*Compare the string stored in the players array of variable type to string "Ogre".*/
					strcpy(players[i].type, "Ogre");
					break;
				case 4:
					/*Compare the string stored in the players array of variable type to string "Wizard".*/
					strcpy(players[i].type, "Wizard");
					break;
			}

			/*Ask the user to input the name of the player and store it in the variable players[i].name*/
			printf("Enter the name of player %d: ", i+1);
			scanf("%s", players[i].name);
			printf("\n");
		}

		/*Loop around num_players times and compare the string in the players array of variable type is
		the same as the corresponding string, if they are the same then call the corresponding function
		to set the values.*/
		for(i=0; i<num_players; i++){
			if(strcmp(players[i].type, "Elf") == 0){
				setElfValues(&players[i]);
			}else if(strcmp(players[i].type, "Human") == 0){
				setHumanValues(&players[i]);
			}else if(strcmp(players[i].type, "Ogre") == 0){
				setOgreValues(&players[i]);
			}else if(strcmp(players[i].type, "Wizard") == 0){
				setWizardValues(&players[i]);
			}
		}

		/*Prints the players name and type.*/
		for(i=0; i<num_players; i++){
			printf("Player %d Details:\n", i+1);
			printf("Name: %s\n", players[i].name);
			printf("Type: %s\n", players[i].type);
			printf("Luck: %d\n", players[i].luck);
			printf("Smartness: %d\n", players[i].smartness);
			printf("Magic: %d\n", players[i].magic);
			printf("Strength: %d\n", players[i].strength);
			printf("Dexterity: %d\n", players[i].dexterity);
			printf("----------------------------------------------------\n");
		}
		printf("\n");
}

void slotsFromUser(struct slot slots[]){
	int i;

	/*  Generate slots  */
	for (i = 0; i < num_slots; i++){
		slots[i].type = rand() % 3;
		slots[i].player = 0;	// 0 is the default value for when the slot is unoccupied
	}

		/*  Print list of generated slots  */
		printf("Generated list of slots:\n");
		for (i = 0; i < num_slots; i++){
			printf("Slot %d: ", i + 1);
			if (slots[i].type == GROUND)
				printf("Ground\n");
			else if (slots[i].type == HILL)
				printf("Hill\n");
			else if (slots[i].type == CITY)
				printf("City\n");
		}
		printf("\n");

}

void populateBoard(struct player players[], struct slot slots[]){
	int i = 0, j, slot;
	bool taken;		// This variable is set to true when a slot number randomly selected is already occupied

	srand(time(NULL));

	while (i < num_players){
		taken = false;		// bool taken is reset after each iteration of the loop
		slot = rand() % num_slots;
		for (j = 0; j < i; j++){
			if (players[j].position == slot + 1){
				taken = true;
				break;
			}
		}

		/*  Variables players[].position and slots[].player all store numbers greater than 0.
		 	Variable slot stores an index, i.e. a number starting from 0  */

		if (!taken){							// slot stores the index of a slot in the slots array (number from 0)
			players[i].position = slot + 1;		// players[].position stores the slot number (number from 1)
			slots[slot].player = i + 1;			// slots[].player stores the player number (number from 1)
			i++;
		}
	}
	printf("Player positions:\n");
	for (i = 0; i < num_players; i++)
		printf("%s - Slot %d\n", players[i].name, players[i].position);
	printf("\n");
}
