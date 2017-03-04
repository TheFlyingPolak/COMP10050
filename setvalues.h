/*
 * setvalues.h
 *
 *  Created on: 2 Mar 2017
 *      Author: Declan
 */

#ifndef SETVALUES_H_
#define SETVALUES_H_

/*Defining a struct named players with the needed variables.*/
struct player{
		char type[20];
		char name[50];
		int smartness;
		int strength;
		int dexterity;
		int magic;
		int luck;
		int life;
		int position;
};

/*	Defining an enumerator which includes slot types  */
enum slot_types{
	GROUND,
	HILL,
	CITY,
};

/*Function prototypes that pass the pointer to a struct as the
input parameter.*/
void setElfValues(struct player *name);
void setHumanValues(struct player *name);
void setOgreValues(struct player *name);
void setWizardValues(struct player *name);
void playersFromUser(struct player players[], int num_players);
void slotsFromUser(enum slot_types slots[], int num_slots);
void populateBoard(struct player players[], enum slot_types slots[], int num_players, int num_slots);

#endif /* SETVALUES_H_ */
