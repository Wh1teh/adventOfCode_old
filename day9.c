#include "header.h"
#define SIZE 1000

const int y = 0;
const int x = 1;
const int d = 2; //direction

int knot[10][3] = { 0 };

int posA[SIZE][SIZE] = { 0 };
int posB[SIZE][SIZE] = { 0 };

int moveTail(char dir, int k/*knotN*/) {
	int h = k - 1;

	//Due to the aforementioned Planck lengths, the rope must be quite short; in fact, 
	//the head (H) and tail (T) must always be touching (diagonally adjacent and even overlapping both count as touching):
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (knot[k][y] - 1 + i == knot[h][y] && knot[k][x] - 1 + j == knot[h][x])
			{
				return 0;
			}
		}
	}

#ifdef DEBUG
	printf("\x1b[%d;%dH ", knot[k][y] - (SIZE / 2) + 16, knot[k][x] - (SIZE / 2) + 16);
#endif

	//If the head is ever two steps directly up, down, left, or right from the tail, 
	//the tail must also move one step in that direction so it remains close enough:
	if (knot[h][y] == knot[k][y] || knot[h][x] == knot[k][x])
	{
#ifdef DEBUG
		printf("\x1b[20;40Hif  ");
#endif
		if (knot[h][y] > knot[k][y])
		{
			knot[k][y]++;
			knot[k][d] = 1;
		}
		else if (knot[h][y] < knot[k][y])
		{
			knot[k][y]--;
			knot[k][d] = 2;
		}
		else if (knot[h][x] > knot[k][x])
		{
			knot[k][x]++;
			knot[k][d] = 3;
		}
		else
		{
			knot[k][x]--;
			knot[k][d] = 4;
		}
	}
	//Otherwise, if the head and tail aren't touching and aren't in the same row or column, 
	//the tail always moves one step diagonally to keep up:
	else
	{
#ifdef DEBUG
		printf("\x1b[20;40Helse");
#endif
		switch (knot[h][d])
		{
		case 1: //U
			knot[k][y]++;
			if (knot[k][x] < knot[h][x])
			{
				knot[k][x]++;
			}
			else
			{
				knot[k][x]--;
			}
			knot[k][d] = 1;
			break;

		case 2: //D
			knot[k][y]--;
			if (knot[k][x] < knot[h][x])
			{
				knot[k][x]++;
			}
			else
			{
				knot[k][x]--;
			}
			knot[k][d] = 2;
			break;

		case 3: //R
			knot[k][x]++;
			if (knot[k][y] < knot[h][y])
			{
				knot[k][y]++;
			}
			else
			{
				knot[k][y]--;
			}
			knot[k][d] = 3;
			break;

		case 4: //L
			knot[k][x]--;
			if (knot[k][y] < knot[h][y])
			{
				knot[k][y]++;
			}
			else
			{
				knot[k][y]--;
			}
			knot[k][d] = 4;
			break;

		default:
			break;
		}
	}

#ifdef DEBUG
	printf("\x1b[%d;%dH%d", knot[k][y] - (SIZE / 2) + 16, knot[k][x] - (SIZE / 2) + 16, k);
	printf("\x1b[22;42H");
	Sleep(10);
#endif

	if (k == 1)
	{
		posA[knot[k][y]][knot[k][x]] = 1;
	}
	if (k == 9)
	{
		posB[knot[k][y]][knot[k][x]] = 1;
	}

	return 0;
}

int day9() {
	FILE* reader;
	reader = fopen("./data/day9Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	char ch;
	int dis;

	//starting positions
	for (int i = 0; i < 10; i++)
	{
		knot[i][y] = SIZE / 2;
		knot[i][x] = SIZE / 2;
	}

	while (fscanf(reader, "%c %d ", &ch, &dis) != EOF)
	{
		for (int i = 0; i < dis; i++)
		{
			switch (ch)
			{
			case 'U':
				knot[0][y]++;
				knot[0][d] = 1;
				break;

			case 'D':
				knot[0][y]--;
				knot[0][d] = 2;
				break;

			case 'R':
				knot[0][x]++;
				knot[0][d] = 3;
				break;

			case 'L':
				knot[0][x]--;
				knot[0][d] = 4;
				break;

			default:
				break;
			}
			for (int i = 0; i < 9; i++)
			{
				moveTail(ch, i + 1);
			}
		}
	}
	fclose(reader);

	int uniquePosA = 0;
	int uniquePosB = 0;
	posA[SIZE / 2][SIZE / 2] = 1; posB[SIZE / 2][SIZE / 2] = 1; //include starting positions
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (posA[i][j] == 1)
			{
				uniquePosA++;
			}
			if (posB[i][j] == 1)
			{
				uniquePosB++;
			}
		}
	}

	printf("Unique positions A: %d\n", uniquePosA);
	printf("Unique positions B: %d\n", uniquePosB);

	return 0;
}