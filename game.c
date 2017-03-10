/*
 * game.c
 *
 *  Created on: 10 Mar 2017
 *      Author: Declan
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "changingValues.h"
#include "game.h"

/*  This array contains half-clever lines which are printed whenever it is the next player's turn  */
char questions[6][100] = {
	"life has offered you lemons. What shall thou do with them?",
	"how shalt thou directeth thy fate?",
	"what shall be thy decision?",
	"quickly now! What will you do?",
	"thy wish is the algorithm's command!",
	"the enemy is upon thy borders and knows no mercy! Thou must act quickly!"
};
/*	This boolean variable is used in function runGame for more control over when a turn can end, for example when a player
 	chooses to move when there is no possibility of movement, the variable will prevent the program from simply ending the turn  */
bool turn;

/*Creates a global variable called closest_players that is an integer array of size 5, it will store the distances
 * between the current player and the all of the other players.*/
int closest_players[5];


void runGame(struct player players[], struct slot slots[], int num_players, int num_slots){

	int i, ans;	//Declaring local variables

	/*	Print the board initially at the start of the game  */
	printf("The Board:\n");
	printMap(players, slots);

	printf("\nThe battle begins now!\n\n");

	srand(time(NULL));
	for (i = 0; i < num_players; i++){
		/*  Ask the next player to choose an action */
		printf("%s, %s\n", players[i].name, questions[rand() % 6]);	// 6 is the number of questions in the questions array defined in game.h
		printf("1: Move\n");		// Call the move function to move the player to a nearby slot
		printf("2: Attack\n");		// Call the attack function to attack a nearby player
		scanf("%d", &ans);			// Store the input in the integer variable ans

		/*If the answer is not a valid input then print an error and ask for a new input.*/
		while ((ans != 1) && (ans != 2) && (ans != 0)){
			printf("I'm sorry? I do not understand thy language.\n");
			scanf("%d", &ans);
		}

		/*Switch statement compares the answer input and calls the function that corresponds to the input.*/
		switch (ans){
		case 1:
			move(players, slots, i);
			printMap(players, slots);
			break;
		case 2:
			closestPlayer(players, slots, num_players, num_slots, i);
			printMap(players, slots);
			break;
		case 0:
			break;
		}
	}

	/*	Print the board and player details for the final results.  */
	printf("Final Board:\n");
	printMap(players, slots);
	printFinalResults(players, slots, num_players);
}

/*This function changes the capabilities based on the strength values of the current player and the attacked player.*/
void attackPlayer(struct player players[], int attacked_player, int current_player){

	attacked_player-=1; // Decrement attacked_player by 1.

	/*If the attacked_player strength is less than or equal to 70 then use the formula to change the attacked_player's life capability.
	 * Else if the attacked_player's strength is greater than 70 then use the formula to change the current_player's life capability.*/
	if(players[attacked_player].strength <=70){
		players[attacked_player].life = (players[attacked_player].life - (0.5 * players[attacked_player].strength));
	}else if(players[attacked_player].strength >70){
		players[current_player].life = (players[current_player].life - (0.3 * players[attacked_player].strength));
	}
}

/*This function finds the closest player in relation to the current_player.*/
void closestPlayer(struct player players[], struct slot slots[], int num_players, int num_slots, int current_player){

	/*Declaring local variables.*/
	int i=0, current_player_position, greatest_difference=20, tmp;
	int ans = 0;
	int j=0;
	int p1, p2;
	int c=0;

	/*Assign the current_player_position to be the value of the current players position.*/
	current_player_position = players[current_player].position;

	/*Iterate around the loop, num_players times.*/
	for(i=0; i<num_players; i++){
		if(players[i].position>current_player_position){			// If the position of the player is greater than the current_player_position then continue
			tmp = players[i].position - current_player_position;	// Assign the value of the players position minus the current_player_position to the temp variable (the distance between the two players)
			if(tmp<=greatest_difference){							// If the value stored in tmp is less than or equal to the greatest_difference, then continue.
				greatest_difference = tmp;							// Assign the value in tmp to the greatest_difference variable.
				closest_players[i] = tmp;							// Assign the value of tmp to the ith element of the closest_players array.
			}
		}else if(players[i].position<current_player_position){	// If the position of the player is less than the current_player_position then continue.
			tmp = current_player_position - players[i].position;// Assign the value of the current_player_position minus the players position to the variable temp (the distance between the two players).
			if(tmp<=greatest_difference){						// If tmp is less than or equal to the greatest_difference variable, then continue.
					greatest_difference = tmp;					// assign the value stored in tmp to the the greatest_difference variable.
					closest_players[i] = tmp;					// assign the value stored in tmp to the ith element of the closest_players array.
				}
		}
	}

	c=5; // Set c=5

	for(i=0; i<6; i++){
		for(j=i+1; j<6; j++){
			//If the two elements are the same value as the greatest_difference variable and the same as each other then continue.
			if((closest_players[i] == greatest_difference) && (closest_players[j] == greatest_difference)){
				p1 = i+1;
				p2 = j+1;
				printf("Player %d: %s and Player %d: %s are the same distance apart.\n", p1, players[p1].name, p2, players[p2].name);
				printf("Enter the number of the player you wish to attack: \n");
				scanf("%d", &ans);
				while(c<1){
					//If the value entered is not the same as one of the options then ask the user to enter the input again.
					if((ans != p1) || (ans != p2)){
						printf("Enter the number of the player you wish to attack: \n");
						scanf("%d", &ans);
						ans -=1;
					}else{
						c=2;// set c equal to 2.
					}
				}
				i=8;// Set i equal to 8.
			}else if(closest_players[i] == greatest_difference){ // if the ith element of the closest_players array is the same as greatest_difference variable then continue.
				ans = i+1;	// Set ans equal to i + 1.
			}else if(closest_players[j] == greatest_difference){ // if the jth element of the closest_players array is the same as greatest_difference variable then continue.
				ans = j+1; // set ans equal to j+1.
			}
		}
	}

	// Call the attack function
	attackPlayer(players, ans, current_player);

	//Set all the values in he closest_players array to 0.
	for(i=0; i<6; i++){
		closest_players[i] = 0;
	}
}
/*This function moves the player from one slot to another as well as chnaging th eplayer capabilities depending on the slot they move to.*/
void move(struct player players[], struct slot slots[], int current_player){
	bool moveLeft = true, moveRight = true;			// These variables represent the player's possibility of movement
	int position = players[current_player].position;	// This variable stores the current player's position
	int choice;

	/*  Check the player's left side for possibility of movement  */
	/*	If the player is on the leftmost slot or the slot to the left is occupied, the player cannot move left  */
	if (position == 1)
		moveLeft = false;
	else if (slots[(position - 1) - 1].player != 0)		// Slot number 1 is stored as slot 0 in an array
		moveLeft = false;

	/*  Check the player's right side for possibility of movement  */
	/*	If the player is on the rightmost slot or the slot to the right is occupied, the player cannot move right  */
	if (position == num_slots)
		moveRight = false;
	else if (slots[(position - 1) + 1].player != 0)
		moveRight = false;

	/*  Ask player to choose direction if there are 2 possibilities  */
	if (moveLeft && moveRight){
		printf("You have a choice! Which shall thou take?\n");
		printf("1: Move Left to slot %d\n", position - 1);
		printf("2: Move Right to slot %d\n", position + 1);
		scanf("%d", &choice);

		/*	If the player has chosen an invalid input  */
		while (choice != 1 && choice != 2){
			printf("I'm sorry, but you cannot go up!\n");
			scanf("%d", &choice);
		}
		if (choice == 1){		// Move the player to the left
			printf("You have decided to go left!");
			players[current_player].position -= 1;		// The player's position parameter is changed to the new slot's number
			slots[position - 1].player = 0;				// The old slot's player parameter is reset to 0 (unoccupied)
			slots[(position - 1) - 1].player = current_player + 1;		// The new slot's player parameter is set to the current player's number
			if(slots[(position - 1) - 1].type == HILL){//If the slot the player is moving to is a hill then continue.
				hillMovement(players, current_player);//Call the hillMovement function.
			}else if(slots[(position - 1) - 1].type == CITY){//If the slot the player is moving to is a city then continue.
				cityMovement(players, current_player);//Call the cityMovement function.
			}
		}
		else if (choice == 2){	// Move the player to the right
			printf("You have decided to go right!");
			players[current_player].position += 1;		// The player's position parameter is changed to the new slot number
			slots[position - 1].player = 0;				// The old slot's player parameter is reset to 0 (unoccupied)
			slots[(position - 1) + 1].player = current_player + 1;		// The new slot's player parameter is set to the current player's number
			if(slots[(position - 1) - 1].type == HILL){//If the slot the player is moving to is a hill then continue.
				hillMovement(players, current_player);//Call the hillMovement function.
			}else if(slots[(position - 1) - 1].type == CITY){//If the slot the player is moving to is a city then continue.
				cityMovement(players, current_player);//Call the cityMovement function.
			}
		}
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
	}
	/*	If the player can only go left  */
	else if (moveLeft && !moveRight){
		printf("The Gods have decided; you must go left!");
		players[current_player].position -= 1;			// The player's position parameter is changed to the new slot number
		slots[position - 1].player = 0;					// The old slot's player parameter is reset to 0 (unoccupied)
		slots[(position - 1) - 1].player = current_player + 1;			// The new slot's player parameter is set to the current player's number
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
		if(slots[(position - 1) - 1].type == HILL){//If the slot the player is moving to is a hill then continue.
			hillMovement(players, current_player);//Call the hillMovement function.
		}else if(slots[(position - 1) - 1].type == CITY){//If the slot the player is moving to is a city then continue.
			cityMovement(players, current_player);//Call the cityMovement function.
		}
	}
	/*	If the player can only go right  */
	else if (moveRight && !moveLeft){
		printf("The Gods have decided; you must go right!");
		players[current_player].position += 1;			// The player's position parameter is changed to the new slot number
		slots[position - 1].player = 0;					// The old slot's player parameter is reset to 0 (unoccupied)
		slots[(position - 1) + 1].player = current_player + 1;			// The new slot's player parameter is set to the current player's number
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
		if(slots[(position - 1) - 1].type == HILL){//If the slot the player is moving to is a hill then continue.
			hillMovement(players, current_player);//Call the hillMovement function.
		}else if(slots[(position - 1) - 1].type == CITY){//If the slot the player is moving to is a city then continue.
			cityMovement(players, current_player);//Call the cityMovement function.
		}
	}
	/*  If the player cannot move, turn is not set to false and the player chooses an action again  */
	else
		printf("You are surrounded, your honour! You must retaliate!");
		printf("\n\n");
}

/*	This function prints each of the slots, its type and the player who occupies it  */
void printMap(struct player players[], struct slot slots[]){
	int i;
	/*	Main loop of the function iterates through all slots  */
	for (i = 0; i < num_slots; i++){
		printf("(%d: ", i + 1);
		/*	Check the slot for its type  */
		if (slots[i].type == GROUND)
			printf("Ground -");
		if (slots[i].type == HILL)
			printf("Hill -");
		if (slots[i].type == CITY)
			printf("City -");

		/*	Check the slot for an occupying player  */
		if (slots[i].player == 0)	// If slots.player is 0 then the slot is unoccupied
			printf("--)");
		else
			printf(" %s)", players[slots[i].player - 1].name);	//player i in slots[].player is player i-1 in players[]
	}
	printf("\n\n");
}
/*This function changes the player capabilities if the player has moved to a hill slot.*/

void hillMovement(struct player players[], int current_player){
	int j;

	j = current_player;

	if(players[j].dexterity<50){
		if(players[j].strength<10){
			players[j].strength = 0;
		}else{
			players[j].strength -=10;
		}
	}else if(players[j].dexterity >=60){
		players[j].strength +=10;
	}
}
/*This function changes the player capabilities if the player has moved to a city slot.*/
void cityMovement(struct player players[], int current_player){
	int j;
	j = current_player;

	if(players[j].smartness<=50){
		if(players[j].dexterity<10){
			players[j].dexterity = 0;
		}else{
			players[j].dexterity -=10;
		}
	}else if(players[j].smartness >60){
		players[j].magic +=10;
	}
}

/*This function prints the final player values, e.g. name, player type and life points.*/
void printFinalResults(struct player players[], struct slot slots[], int num_players){

	int i;

	printf("----------------------------------------------------\n");
	printf("\t\tFinal Player Values\n");
	printf("----------------------------------------------------\n");
		/*Prints the players name and type.*/
		for(i=0; i<num_players; i++){
			printf("%s ", players[i].name);
			printf("(%s, %d)\n", players[i].type, players[i].life);
		}
		printf("----------------------------------------------------\n");
		printf("\n");
}
