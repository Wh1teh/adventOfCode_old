#include "header.h"

//#define MAPH 5//41
//#define MAPW 8//159
static enum {
	MAPH = 5,
	MAPW = 8,
};

typedef struct nodeStruct {
	int value;
	int paths[4]; //up down left right
}mapNode;

static int insertPaths(int y, int x, mapNode node[MAPH][MAPW]) {
	if (y != 0) //look up
	{
		//a + 1 >= b && b >= a - 1
		if (node[y - 1][x].value + 1 >= node[y][x].value && node[y][x].value >= node[y - 1][x].value - 1)
		{
			node[y][x].paths[0] = 1;
		}
	}
	if (y != MAPH) //look down
	{
		if (node[y + 1][x].value + 1 >= node[y][x].value && node[y][x].value >= node[y + 1][x].value - 1)
		{
			node[y][x].paths[1] = 1;
		}
	}
	if (x != 0) //look left
	{
		if (node[y][x - 1].value + 1 >= node[y][x].value && node[y][x].value >= node[y][x - 1].value - 1)
		{
			node[y][x].paths[2] = 1;
		}
	}
	if (x != MAPW) //look right
	{
		if (node[y][x + 1].value + 1 >= node[y][x].value && node[y][x].value >= node[y][x + 1].value - 1)
		{
			node[y][x].paths[3] = 1;
		}
	}
}

static int readInput(mapNode node[MAPH][MAPW]) {
	FILE* reader;
	reader = fopen("./data/day12Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	char line[MAPW + 2] = { '\0' };
	for (int i = 0; i < MAPH; i++)
	{
		fgets(line, MAPW + 2, reader);
		TRACE("line: %s", line);
		for (int j = 0; j < MAPW; j++)
		{
			if (line[j] == 'S')
			{
				node[i][j].value = -1;
			}
			else if (line[j] == 'E')
			{
				node[i][j].value = 26;
			}
			else node[i][j].value = line[j] - 'a';
		}
	}

#ifdef DEBUG
	for (int i = 0; i < MAPH; i++)
	{
		printf("\n");
		for (int j = 0; j < MAPW; j++)
		{
			printf("%d\t", node[i][j].value);
		}
	}
#endif
}

int day12() {
	mapNode node[MAPH][MAPW] = { { { 0 } } };

	readInput(node);

	for (int i = 0; i < MAPH; i++)
	{
		printf("\n");
		for (int j = 0; j < MAPW; j++)
		{
			insertPaths(i, j, node);
			printf("%d,%d,%d,%d ", node[i][j].paths[0], node[i][j].paths[1], node[i][j].paths[2], node[i][j].paths[3]);
		}
		
	}

	return 0;
}