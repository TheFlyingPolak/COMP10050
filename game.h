/*
 * game.h
 *
 *  Created on: 10 Mar 2017
 *      Author: Declan
 */

#ifndef GAME_H_
#define GAME_H_

void runGame(struct player players[], struct slot slots[], int num_players, int num_slots);
void hillMovement(struct player players[], int current_player);
void cityMovement(struct player players[], int current_player);
void closestPlayer(struct player players[], struct slot slots[], int num_players, int num_slots, int current_player);
void move(struct player players[], struct slot slots[], int current_player);
void attackPlayer(struct player players[], int attacked_player, int current_player);
void printMap(struct player players[], struct slot slots[]);
void printFinalResults(struct player players[], struct slot slots[], int num_players);

#endif /* GAME_H_ */
