/*
 * game.c
 *
 *
 *  Created on: 4 Mar 2017
 *      Author: Jakub
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "setvalues.h"
#include "game.h"

/*  This statement allows these global variables, declared in main.c, to be accessed by this file  */
//extern int num_players, num_slots;

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

/*	This function is the main block of code which runs the actual game  */
void runGame(struct player players[], struct slot slots[], int num_players, int num_slots){
	int i, ans;

	srand(time(NULL));

	/*	Print the board initially at the start of the game  */
	printMap(players, slots);

	printf("\nThe battle begins now!\n\n");

	/*	Main loop which iterates through all players  */
	for (i = 0; i < num_players; i++){
		turn = true;		// Bool turn is reset to true at the start of each player's turn
		if (i != 0)
			printMap(players, slots);	// Prevent program from printing the map a second time at the start of the game

		/*  Ask the next player to choose an action  */
		printf("%s, %s\n", players[i].name, questions[rand() % 6]);	// 6 is the number of questions in the questions array defined in game.h

		/*	This loop runs throughout a single player's turn. When it is time to end the player's turn, bool turn is set to false
		 * 	and the loop can stop, beginning the next player's turn  */
		while (turn){
			printf("1: Move\n");		// Call the move function to move the player to a nearby slot
			printf("2: Attack\n");		// Call the attack function to attack a nearby player
			printf("0: Skip turn\n");	// Do nothing and skip turn
			scanf("%d", &ans);

			/*	Print error message if the player's input is invalid  */
			while (ans != 1 && ans != 2 && ans != 0){
				printf("I'm sorry? I do not understand thy language.\n\n");
				printf("1: Move\n");
				printf("2: Attack\n");
				printf("0: Skip turn\n");
				scanf("%d", &ans);
			}

			switch (ans){
			case 1:
				/*	Call the move function to move the player to a nearby slot  */
				move(players, slots, i);
				break;
			case 2:
				/*  Call the attack function to attack a nearby player  */
				closestPlayer(players, slots, num_players, num_slots, i);
				break;
			case 0:
				/*	Print this taunt and skip to the next player in sequence  */
				printf("You passive coward! Your treachery shall not be forgiven!\n\n");
				turn = false;
				sleep(2);
				break;
			}
		}
	}
	/*	Final printing of the map at the end of the game  */
	printMap(players, slots);
}

/*	This function prints each of the slots, its type and the player who occupies it  */
void printMap(struct player players[], struct slot slots[]){
	int i;

	printf("The board:\n");

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

/*	This function checks the board for possibility of movement and moves the player if possible  */
void move(struct player players[], struct slot slots[], int currentPlayer){
	bool moveLeft = true, moveRight = true;			// These variables represent the player's possibility of movement
	int position = players[currentPlayer].position;	// This variable stores the current player's position
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
			players[currentPlayer].position -= 1;		// The player's position parameter is changed to the new slot's number
			slots[position - 1].player = 0;				// The old slot's player parameter is reset to 0 (unoccupied)
			slots[(position - 1) - 1].player = currentPlayer + 1;		// The new slot's player parameter is set to the current player's number
										// currentPlayer stores an array index, i.e. if the player's number is 1, then currentPlayer = 0
		}
		else if (choice == 2){	// Move the player to the right
			printf("You have decided to go right!");
			players[currentPlayer].position += 1;		// The player's position parameter is changed to the new slot number
			slots[position - 1].player = 0;				// The old slot's player parameter is reset to 0 (unoccupied)
			slots[(position - 1) + 1].player = currentPlayer + 1;		// The new slot's player parameter is set to the current player's number
		}
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
	}
	/*	If the player can only go left  */
	else if (moveLeft && !moveRight){
		printf("The Gods have decided; you must go left!");
		players[currentPlayer].position -= 1;			// The player's position parameter is changed to the new slot number
		slots[position - 1].player = 0;					// The old slot's player parameter is reset to 0 (unoccupied)
		slots[(position - 1) - 1].player = currentPlayer + 1;			// The new slot's player parameter is set to the current player's number
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
	}
	/*	If the player can only go right  */
	else if (moveRight && !moveLeft){
		printf("The Gods have decided; you must go right!");
		players[currentPlayer].position += 1;			// The player's position parameter is changed to the new slot number
		slots[position - 1].player = 0;					// The old slot's player parameter is reset to 0 (unoccupied)
		slots[(position - 1) + 1].player = currentPlayer + 1;			// The new slot's player parameter is set to the current player's number
		turn = false;		//bool turn is set to false so the turn can now end
		sleep(2);
	}
	/*  If the player cannot move, turn is not set to false and the player chooses an action again  */
	else
		printf("You are surrounded, your honour! You must retaliate!");
	printf("\n\n");
}

void attackPlayer(struct player players[], int attacked_player, int current_player){
	
	attacked_player-=1;
	
	if(players[attacked_player].strength <=70){
		players[attacked_player].life = (players[attacked_player].life - (0.5 * players[attacked_player].strength));
	}else if(players[attacked_player].strength >70){
		players[current_player].life = (players[current_player].life - (0.3 * players[attacked_player].strength));
	}
}

void closestPlayer(struct player players[], struct slot slots[], int num_players, int num_slots, int current_player){
	
	int i=0, current_player_position, greatest_difference=20, tmp;
	int ans = 0;
	int j=0;
	int p1, p2;
	int c=0;
	
	current_player_position = players[current_player].position;
	printf("Current Player Position : %d.", current_player_position);
	

	for(i=0; i<num_players; i++){
		if(players[i].position>current_player_position){
			tmp = players[i].position - current_player_position;
			if(tmp<=greatest_difference){
				greatest_difference = tmp;
				closest_players[i] = tmp;
			}
		}else if(players[i].position<current_player_position){
			tmp = current_player_position - players[i].position;
			if(tmp<=greatest_difference){
					greatest_difference = tmp;
					closest_players[i] = tmp;
				}
		}
	}
	
	c=5;
	
	for(i=0; i<6; i++){
		for(j=i+1; j<6; j++){
			if((closest_players[i] == greatest_difference) && (closest_players[j] == greatest_difference)){
				p1 = i+1;
				p2 = j+1;
				printf("Player %d: %s and Player %d: %s are the same distance apart.\n", p1, players[p1].name, p2, players[p2].name);
				printf("Enter the number of the player you wish to attack: \n");
				scanf("%d", &ans);
				while(c<1){
					if((ans != p1) || (ans != p2)){
						printf("Enter the number of the player you wish to attack: \n");
						scanf("%d", &ans);
						ans -=1;
					}else{
						c=2;
					}
				}
				i=8;
			}else if(closest_players[i] == greatest_difference){
				ans = i+1;
			}else if(closest_players[j] == greatest_difference){
				ans = j+1;
			}
		}
	}

	attackPlayer(players, ans, current_player);
	
	for(i=0; i<6; i++){
		closest_players[i] = 0;
	}
}

