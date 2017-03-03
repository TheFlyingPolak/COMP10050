#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "sortplayers.h"
#include "shuffleplayers.h"
#include "sortslots.h"
#include "setvalues.h"
#include "fromfile.h"

int main(){
	setbuf(stdout, NULL);

	int ans;

	printf("Would you like to read Players and Structs from a file?\n");
	printf("Enter 1 for Yes.\n");
	printf("Enter 0 for No.\n");
	scanf("%d", &ans);

	if(ans == 1){
		printf("You are going to read from a file.\n");
		fromFile();
	}else if(ans == 0){
		printf("You are now going to enter the inputs.\n");
		fromUser();
	}else{
		printf("Please provide a valid input.\n");
	}

	return 0;
}


