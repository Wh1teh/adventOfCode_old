#include "header.h"

int day3() {
	FILE* rucksack;
	rucksack = fopen("./data/day3Data.txt", "r");
	if (rucksack == NULL) {
		perror("Error opening file");
		return(-1);
	}

	int sackSize = 0;

	int prioritySum = 0;

	char compartments[2][50] = { '\0' };
	int item = 0;

	char ch = '\0';

	//first problem
	while (1) {
		ch = fgetc(rucksack);

		//end of line
		if (ch == '\n' || ch == EOF) {
			if (ch == EOF) {
				fseek(rucksack, 2, SEEK_CUR); //EOF doesn't put us in the regular position so we make an exception
			}
			fseek(rucksack, -sackSize - 2, SEEK_CUR); //minus current position and newline

			fgets(compartments[0], sackSize / 2 + 1, rucksack);
			fgets(compartments[1], sackSize / 2 + 1, rucksack);

			//printf("%s - %s\n", compartments[0], compartments[1]); //debug

			//check for matching items
			for (int i = 0; i < sackSize / 2; i++)
			{
				for (int j = 0; j < sackSize / 2; j++)
				{
					//printf("%c against %c\n", compartments[0][i], compartments[1][j]); //debug

					//match found
					if (compartments[0][i] == compartments[1][j]) {
						item = compartments[0][i] - 96; //put ascii in priority range

						//item is a capital letter
						if (item < 0) {
							item += 58;
						}

						prioritySum += item;
						//printf("adding:%d because %d. %c = %d. %c\n", item, i + 1, compartments[0][i], j + 1, compartments[1][j]); //debug

						goto nextSack; //goto let's fucking go
					}
				}
			}
		nextSack:
			fseek(rucksack, 2, SEEK_CUR); //hop over newline

			//printf("position after:%d\n", ftell(rucksack)); //debug
			//printf("priority sum:%d\n", prioritySum); //debug

			sackSize = -1; //reset size counter
		}
		sackSize++;

		//end
		if (ch == EOF) {
			break;
		}
	}

	printf("1st problem, final sum: %d\n", prioritySum);

	//second problem
	prioritySum = 0; //reset priorities before next run

	int encountered = 0;
	char elfSack[3][50] = { '\0' };
	int sackLenght[3] = { 0 };

	fseek(rucksack, 0, SEEK_SET); //to the beginning
	while (1) {
		for (int i = 0; i < 3; i++)
		{
			sackLenght[i] = ftell(rucksack); //store arrival location
			//printf("arrival: %d", sackLenght[i]); //debug
			fgets(elfSack[i], 50, rucksack); //store line to string
			sackLenght[i] = ftell(rucksack) - 2 - sackLenght[i]; //subtract current position, newline and arrival location

			//printf("length of %d. elf: %d\n", i + 1, sackLenght[i]); //debug
		}

		//end, this is so ghetto lmao
		if (sackLenght[0] < 0) {
			break;
		}

		////debug
		//printf("1. %s", elfSack[0]);
		//printf("2. %s", elfSack[1]);
		//printf("3. %s", elfSack[2]);

		for (int i = 0; i < sackLenght[0]; i++)
		{
			for (int j = 0; j < sackLenght[1]; j++)
			{
				if (elfSack[0][i] == elfSack[1][j]) {
					//was not encountered yet
					if (encountered == 0) {
						encountered = 1;
					}
				}
			}

			for (int k = 0; k < sackLenght[2]; k++)
			{
				if (elfSack[0][i] == elfSack[2][k]) {
					//was also found on the 2nd elf
					if (encountered == 1) {
						item = elfSack[0][i] - 96; //put ascii in priority range

						//item is a capital letter
						if (item < 0) {
							item += 58;
						}

						prioritySum += item;
						//printf("adding:%d, because: %c\n", item, elfSack[0][i]); //debug

						encountered = 0; //reset

						goto nextGroup; //skip to next group
					}
				}
			}

			//was encountered on every elf
			if (encountered == 2) {
				item = elfSack[0][i] - 96; //put ascii in priority range

				//item is a capital letter
				if (item < 0) {
					item += 58;
				}

				prioritySum += item;
				//printf("adding:%d, because: %c\n", item, elfSack[0][i]); //debug

				goto nextGroup; //skip to next group
			}
			encountered = 0; //reset
		}
	nextGroup:;
	}
	fclose(rucksack);

	printf("2nd problem, final sum: %d\n", prioritySum);

	return 0;
}