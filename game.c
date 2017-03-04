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
	"the enemy is upon thy borders and knows no mercy! Thy must act quickly!"
};

void runGame(struct player players[], struct slot slots[], int num_players, int num_slots){
	int i, ans;

	srand(time(NULL));

	for (i = 0; i < num_players; i++){
		/*  Ask the next player to choose an action  */
		printf("%s, %s\n", players[i].name, questions[rand() % 6]);	// 6 is the number of questions in the questions array defined in game.h
		printf("1: Move\n");		// Call the move function to move the player to a nearby slot
		printf("2: Attack\n");		// Call the attack function to attack a nearby player
		printf("0: Skip turn\n");	// Do nothing and skip turn
		scanf("%d", &ans);

		while (ans != 1 && ans != 2 && ans != 0){
			printf("I'm sorry? I do not understand thy language.\n");
			scanf("%d", &ans);
		}

		switch (ans){
		case 1:
			move(players, slots);
			break;
		case 2:
			attack(players, slots);
			break;
		case 0:
			printf("You passive coward! Your treachery shall not be forgiven!\n\n");
			break;
		}
	}
}

void move(struct player players[], struct slot slots[], int currentPlayer){
	bool moveLeft = true, moveRight = true;
	int position = players[currentPlayer].position;

	/*  Check the player's left side for possibility of movement  */
	if (position == 1){
		moveLeft = false;
	}
	else if (slots[position ]){

	}

}

void attack(struct player players[], struct slot slots[]){

}
