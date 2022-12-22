#include "header.h"

#define MONKEYS 8

typedef struct monkeyStruct {
	int items[100]; //item values
	int itemCount;
	int inspects;
	int operation[3]; //operand+-*/ and value, 2: flag 'old'
	int test; //divisible by value
	int dest[2]; //which monkey to throw to? [1] true, [0] false
}monkey;

int day11() {
	FILE* reader;
	reader = fopen("./data/day11Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	monkey m[MONKEYS] = { { 0 } };

	int count = 0;
	char ch;
	char line[64] = { '\0' };
	for (int i = 0; i < MONKEYS; i++)
	{
		//skip useless lines
		fgets(line, 64, reader);
		fgets(line, 64, reader);

		count = 0;
		while (line[count] != NULL)
		{
			sscanf(&line[count + 18], "%d%c", &m[i].items[count / 4], &ch);
			TRACE("got item: %d, slot %d\n", m[i].items[count / 4], count / 4);
			count += 4; //jump to next item
			m[i].itemCount++;

			if (ch == '\n') //end of starting items
			{
				TRACE("NEWLINE, final item count: %d\n", m[i].itemCount);
				break;
			}
		}

		//operation
		fgets(line, 64, reader);
		m[i].operation[0] = line[23]; //operand
		sscanf(&line[25], "%d", &m[i].operation[1]); //value

		//test
		fgets(line, 64, reader);
		sscanf(&line[21], "%d", &m[i].test);

		//dest if true
		fgets(line, 64, reader);
		sscanf(&line[29], "%d", &m[i].dest[1]);

		//dest if false
		fgets(line, 64, reader);
		sscanf(&line[30], "%d", &m[i].dest[0]);

		TRACE("Got operation: %c %d\n", m[i].operation[0], m[i].operation[1]);
		TRACE("Got divisible by: %d\n", m[i].test);
		TRACE("Got if true throw to: %d\n", m[i].dest[1]);
		TRACE("Got if false throw to: %d\n", m[i].dest[0]);

		fgets(line, 64, reader); //skip empty line
	}

	int rounds = 20;
	int relief = 3;
	for (int ab = 0; ab < 2; ab++)
	{
		for (int i = 0; i < rounds; i++)
		{
			TRACE("\n\nROUND: %d\n\n", i);
			for (int j = 0; j < MONKEYS; j++)
			{
				TRACE("\nMONKEY %d:\n", j);

				count = 0;
				while (m[j].itemCount > 0) //while monkey has items
				{
					TRACE("count: %d, itemCount: %d\n", count, m[j].itemCount);
					//inspect
					TRACE("inspect: %d\n", m[j].items[count]);
					if (m[j].operation[1] == 0 || m[j].operation[2] == 1) //operation value is 'old'
					{
						m[j].operation[2] = 1; //flag operation value as 'old'
						m[j].operation[1] = m[j].items[count];
						TRACE("'old': %d\n", m[j].operation[1]);
					}
					switch (m[j].operation[0]) //operand
					{
					case '+':
						m[j].items[count] += m[j].operation[1];
						break;

					case '-':
						m[j].items[count] -= m[j].operation[1];
						break;

					case '*':
						m[j].items[count] *= m[j].operation[1];
						break;

					case '/':
						m[j].items[count] /= m[j].operation[1];
						break;

					default:
						break;
					}
					TRACE("worry now: %d\n", m[j].items[count]);

					m[j].items[count] /= relief; //relief
					TRACE("relief: %d\n", m[j].items[count]);

					int dest = 0;
					if (m[j].items[count] % m[j].test == 0) //true, is divisible
					{
						dest = m[j].dest[1]; //destination if true
						TRACE("true, send to: %d\n", dest);
						m[dest].items[m[dest].itemCount] = m[j].items[count]; //sends item to first free spot at destination
						m[dest].itemCount++; //destination monkey's item count increases
					}
					else //false
					{
						dest = m[j].dest[0]; //destination if false
						TRACE("false, send to: %d\n", dest);
						m[dest].items[m[dest].itemCount] = m[j].items[count]; //sends item to first free spot at destination
						m[dest].itemCount++; //destination monkey's item count increases
					}

					m[j].itemCount--; //current monkey has one less item
					m[j].inspects++; //total inspects goes up
					count++; //next item
				}
			}
		}

		for (int i = 0; i < MONKEYS; i++)
		{
			printf("Monkey %d inspected items %d times\n", i, m[i].inspects);
		}

		//while(1){}

		relief = 1; //no more relief
		rounds = 10000;
	}

	return 0;
}