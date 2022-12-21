#include "header.h"
#define SIZE 99
char trees[SIZE + 2][SIZE + 2] = { '\0' };
int visible = 0;


void findVisible(char direction) {
}

int day8() {
	FILE* reader;
	reader = fopen("./data/day8Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	int line = 0;
	while (fgets(trees[line], SIZE + 2, reader) != NULL) {
		line++;
	}
	fclose(reader);

	int counted[SIZE + 2][SIZE + 2] = { 0 };

	int biggestTree = -1;
	for (int i = 0; i < SIZE; i++) //right
	{
		biggestTree = -1;
		for (int j = 0; j < SIZE; j++)
		{
			if (trees[i][j] > biggestTree)
			{
				biggestTree = trees[i][j];
				if (counted[i][j] == 0)
				{
					counted[i][j] = 1;
					visible++;
				}
			}
		}
	}

	for (int i = 0; i < SIZE; i++) //left
	{
		biggestTree = -1;
		for (int j = SIZE - 1; j >= 0; j--)
		{
			if (trees[i][j] > biggestTree)
			{
				biggestTree = trees[i][j];
				if (counted[i][j] == 0)
				{
					counted[i][j] = 1;
					visible++;
				}
			}
		}
	}

	for (int j = 0; j < SIZE; j++) //down
	{
		biggestTree = -1;
		for (int i = 0; i < SIZE; i++)
		{
			if (trees[i][j] > biggestTree)
			{
				biggestTree = trees[i][j];
				if (counted[i][j] == 0)
				{
					counted[i][j] = 1;
					visible++;
				}
			}
		}
	}

	for (int j = 0; j < SIZE; j++) //up
	{
		biggestTree = -1;
		for (int i = SIZE - 1; i >= 0; i--)
		{
			if (trees[i][j] > biggestTree)
			{
				biggestTree = trees[i][j];
				if (counted[i][j] == 0)
				{
					counted[i][j] = 1;
					visible++;
				}
			}
		}
	}

	//print
	for (int i = 0; i < SIZE; i++)
	{
		printf("\n");
		for (int j = 0; j < SIZE; j++)
		{
			if (counted[i][j] == 1)
			{
				printf("\x1b[31m%c\x1b[0m", trees[i][j]);
			}
			else printf("%c", trees[i][j]);
		}
	}

	printf("vis: %d", visible);

	return 0;
}