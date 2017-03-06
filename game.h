/*
 * game.h
 *
 *  Created on: 4 Mar 2017
 *      Author: Jakub
 */

#ifndef GAME_H_
#define GAME_H_

void runGame(struct player players[], struct slot slots[], int num_players, int num_slots);
void printMap(struct player players[], struct slot slots[]);
void move(struct player players[], struct slot slots[], int currentPlayer);
void attack(struct player players[], struct slot slots[], int currentPlayer);

#endif /* GAME_H_ */
