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

/*	Defining a struct named slots with the needed variables  */
struct slot{
	enum slot_types type;
	int player;
};

/*Function prototypes that pass the pointer to a struct as the
input parameter.*/
void setElfValues(struct player *name);
void setHumanValues(struct player *name);
void setOgreValues(struct player *name);
void setWizardValues(struct player *name);
void playersFromUser(struct player players[]);
void slotsFromUser(struct slot slots[]);
void populateBoard(struct player players[], struct slot slots[]);

#endif /* SETVALUES_H_ */
