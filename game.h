/*
 * game.h
 *
 *  Created on: 4 Mar 2017
 *      Author: Jakub
 */

#ifndef GAME_H_
#define GAME_H_

void runGame(struct player players[], struct slot slots[], int num_players, int num_slots);
void printMap(struct slot slots[]);
void move(struct player players[], struct slot slots[]);
void attack(struct player players[], struct slot slots[]);

#endif /* GAME_H_ */
