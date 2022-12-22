#include "header.h"

int day04() {
	FILE* reader;
	reader = fopen("./data/day04Data.txt", "r");
	if (reader == NULL) {
		perror("Error opening file");
		return(-1);
	}

	int lenght = 0;
	int overlapCounter = 0; //first part
	int partialCounter = 0;	//second part
	int pairCounter = 0;
	int numberCounter = 0;
	int assignments[2][2] = { 0 };
	char pairs[16];
	while (fgets(pairs, 16, reader) != NULL) {
		lenght = strlen(pairs) - 1; //get line lenght
		//printf("this line: %s", pairs); //debug
		//printf("lenght: %d\n", lenght); //debug
		for (int i = 0; i < lenght; i++)
		{
			//next assigment
			if (pairs[i] == '-') {
				numberCounter++;
			}
			//next elf
			else if (pairs[i] == ',') {
				pairCounter++;
				numberCounter = 0;
			}
			//parse number
			else {
				//if we are at second digit
				if (assignments[pairCounter][numberCounter] > 0) {
					assignments[pairCounter][numberCounter] *= 10; //first digit gets multiplied accordingly
				}
				assignments[pairCounter][numberCounter] += pairs[i] - '0'; //add to number
				//printf("%d-%d,%d-%d\n", assignments[0][0], assignments[0][1], assignments[1][0], assignments[1][1]); //debug
			}
		}
		//printf("%d-%d,%d-%d\n", assignments[0][0], assignments[0][1], assignments[1][0], assignments[1][1]); //debug

		//check for overlap
		if ((assignments[0][0] >= assignments[1][0] && assignments[0][1] <= assignments[1][1]) || 
			(assignments[1][0] >= assignments[0][0] && assignments[1][1] <= assignments[0][1])) {
			overlapCounter++;

			//printf("found overlap\n"); //debug
		}

		//check for partial overlap
		if ((assignments[0][1] >= assignments[1][0] && assignments[0][0] <= assignments[1][1])) {
			partialCounter++;

			//printf("found partial overlap\n"); //debug
		}

		//reset assignments array
		memset(assignments, 0, sizeof(assignments));
		pairCounter = 0;
		numberCounter = 0;
	}
	fclose(reader);

	printf("pairs with full overlap: %d\n", overlapCounter);
	printf("pairs with any overlap: %d\n", partialCounter);

	return 0;
}
