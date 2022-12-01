#include "header.h"

void day1() {
	FILE* calorieGetter;
	calorieGetter = fopen("./data/day1CalorieData.txt", "r");
	if (calorieGetter == NULL) {
		perror("Error opening file");
		return(-1);
	}

	//find length of file
	fseek(calorieGetter, 0, SEEK_END);
	int fileLength = ftell(calorieGetter);
	fseek(calorieGetter, 0, SEEK_SET);

	//initialize array
	int elfCounter = 0;
	int* elfArr = calloc((elfCounter + 1), sizeof(int));
	if (elfArr == NULL) {
		perror("Unable to allocate memory\n");
		return -1;
	}

	int sum = 0;
	int* nullpCheck = 0;

	char calChar[16] = { '\0' }; //could also go character by character to determine how large these numbers can get I guess
	while (fgets(calChar, fileLength, calorieGetter) != NULL) {
		sum += atoi(calChar);

		if (atoi(calChar) == 0) {
			nullpCheck = realloc(elfArr, (elfCounter + 1) * sizeof(int)); //grow array
			if (nullpCheck == NULL) {
				perror("Unable to allocate memory\n");
				return -1;
			}
			else elfArr = nullpCheck;

			elfArr[elfCounter] = sum; //give sum of calories to the elf
			elfCounter++; //next elf
			sum = 0;
		}
	}
	fclose(calorieGetter);

	//repeatcode after null to get the last elf
	nullpCheck = realloc(elfArr, (elfCounter + 1) * sizeof(int));
	if (nullpCheck == NULL) {
		perror("Unable to allocate memory\n");
		return -1;
	}
	else elfArr = nullpCheck;
	elfArr[elfCounter] = sum;
	elfCounter++;
	sum = 0;

	//bubble sort lol
	int temp = 0;
	for (int i = 0; i < elfCounter; i++)
	{
		for (int j = 0; j < elfCounter; j++)
		{
			if (elfArr[j] > elfArr[i]) {
				temp = elfArr[i];
				elfArr[i] = elfArr[j];
				elfArr[j] = temp;
			}
		}
	}

	//print sums, largest at the bottom
	for (int i = 0; i < elfCounter; i++)
	{
		printf("%d\n", elfArr[i]);
	}

	//print sum of top 3
	sum = 0;
	for (int i = 0; i < 3; i++)
	{
		sum += elfArr[elfCounter - 3 + i];
	}
	printf("top3: %d\n", sum);

	free(elfArr);
}

