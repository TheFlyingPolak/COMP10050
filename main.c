#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "setvalues.h"
#include "fromfile.h"
#include "game.h"

/*  These variables are called as global to make them readily available to all functions without having to declare them in the
	prototypes of a large number of functions  */
int num_players, num_slots;

int main(){
	setbuf(stdout, NULL);

	int ans;

	printf("Would you like to read Players and Slots from a file?\n");
	printf("Enter 1 for Yes.\n");
	printf("Enter 0 for No.\n");
	scanf("%d", &ans);

		if (ans == 1){	// Read players and slots from a file
			printf("You are going to read from a file.\n");
			fromFile();
		}

		else if (ans == 0){	// Generate players and slots based on user input
			printf("You are now going to enter the inputs.\n");
			/*Ask the user to input how many players are playing the game and store it
			in the variable num_players*/
			printf("How many players would you like to input (max 6): ");
			scanf("%d", &num_players);

			/*If the user inputs a number greater than the maximum number of players then
			tell them that there was an error and ask them to input the number again.*/
			while(num_players>6){
				printf("\nYou can only have a maximum of 6 players. Try again.");
				printf("\nHow many players would you like to input (max 6): ");
				scanf("%d", &num_players);
			}

			/*Creating a array named players of size num_players and it is of type struct
			player.*/
			struct player players[num_players];

			/*  Call function to generate the list of players  */
			playersFromUser(players);

			/*	Ask the user how many slots are to be generated  */
			printf("How many slots would you like to input (max 20): ");
			scanf("%d", &num_slots);

			/*	Produce an error if the input number is greater than 20 or less than the number of players  */
			while (num_slots < num_players || num_slots > 20){
				if (num_slots > 20){
					printf("You cannot create more than 20 slots. Please choose a different number.\n");
					printf("How many slots would you like to input (max 20): ");
					scanf("%d", &num_slots);
				}
				else if (num_slots < num_players){
					printf("How do you plan to squeeze %d players on %d slots?\n", num_players, num_slots);
					printf("How many slots would you like to input (max 20): ");
					scanf("%d", &num_slots);
				}
			}
			/*  Create array of size num_slots and type enum slot_types to store slots  */
			struct slot slots[num_slots];

			/*  Call function to generate list of slots  */
			slotsFromUser(slots);

			/*  Call function to populate the board  */
			populateBoard(players, slots);

			runGame(players, slots, num_players, num_slots);
		}

		else{
			printf("Please provide a valid input.\n");
		}

	return 0;
}
