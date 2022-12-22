#include "header.h"

//part 2
int drawSprite(int totalValue, int cycle) {
	if (totalValue - 1 <= cycle % 40 && cycle % 40 <= totalValue + 1) //position is withing sprite
	{
		TRACE("valid\n");
		printf("\x1b[31m#\x1b[0m");
	}
	else
	{
		TRACE("out of range\n");
		printf(".");
	}
	if ((cycle + 1) % 40 == 0) //line change
	{
		TRACE("cycle: %d", cycle);
		printf("\n");
	}

	return 0;
}

int day10() {
	FILE* reader;
	reader = fopen("./data/day10Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	int cycle = 0;
	int inputValue = 0;
	int totalValue = 1;
	int signalSum = 0;
	int overlap = 0; //1 left, 2 middle, 3 right

	char line[16] = { '\0' };
	while (fgets(line, 16, reader) != NULL)
	{
		//cycles and values
		if (line[0] != 'a')
		{
			drawSprite(totalValue, cycle);
			cycle++; 
			
			TRACE("noop\n");
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				drawSprite(totalValue, cycle);
				cycle++;
			}

			sscanf(&line[4], "%d", &inputValue);
			TRACE("addx %d to %d\n", inputValue, totalValue);
			totalValue += inputValue;
		}

		//part 1
		if ((cycle + 20) % 40 == 0 && line[0] == 'n') //after noop is even
		{
			signalSum += totalValue * cycle;
			TRACE("cycle: %d, value: %d, signal: %d, added: %d\n", cycle, totalValue, signalSum, totalValue * cycle);
		}
		else if (((cycle + 20) % 40 == 1 || (cycle + 20) % 40 == 0) && line[0] != 'n') //after addx is even or went over by one
		{
			totalValue -= inputValue; //redact latest value
			if ((cycle + 20) % 40 == 1)
			{
				signalSum += totalValue * (cycle - 1);
				TRACE("cycle: %d, value: %d, signal: %d, added: %d\n", cycle, totalValue, signalSum, totalValue * (cycle - 1));
			}
			else
			{
				signalSum += totalValue * (cycle);
				TRACE("cycle: %d, value: %d, signal: %d, added: %d\n", cycle, totalValue, signalSum, totalValue * (cycle));
			}
			totalValue += inputValue; //add value back
		}
	}
	fclose(reader);

	printf("sum A: %d\n", signalSum);

	return 0;
}