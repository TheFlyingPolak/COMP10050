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

/*  Variable r stores an enumerator of type slot_types  */
enum slot_types r;

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

	(*name).life = 100;

	//are they uppose to have dexterity?
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

	//Are they suppose to have magic?


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

	//are they suppose to have dexterity?
}

void playersFromUser(struct player players[], int num_players){

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
			printf("\n\n");
		}
}

void slotsFromUser(enum slot_types slots[], int num_slots){
	int i;

	/*  Generate slots  */
	for (i = 0; i < num_slots; i++){
		r = rand() % 3;
		slots[i] = r;
	}

		/*  Print list of generated slots  */
		printf("Generated list of slots:\n");
		for (i = 0; i < num_slots; i++){
			printf("Slot %d: ", i + 1);
			if (slots[i] == GROUND)
				printf("Ground\n");
			else if (slots[i] == HILL)
				printf("Hill\n");
			else if (slots[i] == CITY)
				printf("City\n");
		}
		printf("\n");

}

void populateBoard(struct player players[], enum slot_types slots[], int num_players, int num_slots){
	int i = 0, j, slot;
	bool occupied = false;	// This variable is set to true when a slot number randomly selected is already occupied
	int occupied_slots[num_slots];	// This array contains the numbers of the slots which are already occupied

	srand(time(NULL));

	while (i < num_players){
		slot = (rand() % num_slots) + 1;
		for (j = 0; j <= i; j++){
			if (players[j].position == slot)
				occupied = true;
		}
		if (!occupied){
			occupied_slots[i] = slot;
			players[i].position = slot;
			i++;
		}
	}
	printf("Player positions:\n");
	for (i = 0; i < num_players; i++)
		printf("%s - Slot %d", players[i].name, players[i].position - 1);
}
