#include "header.h"

#define MONKEYS 8

typedef struct monkeyStruct {
	unsigned long long int items[100]; //item values
	int itemCount;
	int inspects;
	int operation[3]; //operand+-*/ and value, 2: flag 'old'
	int test; //divisible by value
	int dest[2]; //which monkey to throw to? [1] true, [0] false
}monkey;

int readInput(monkey m[]) {
	FILE* reader;
	reader = fopen("./data/day11Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	char line[64] = { '\0' };
	for (int i = 0; i < MONKEYS; i++)
	{
		//skip useless lines
		fgets(line, 64, reader);
		fgets(line, 64, reader);

		int count = 0;
		while (line[count] != NULL)
		{
			sscanf(&line[count + 18], "%llu%c", &m[i].items[count / 4], &line[0]);
			TRACE("got item: %llu, slot %llu\n", m[i].items[count / 4], count / 4);
			count += 4; //jump to next item
			m[i].itemCount++;

			if (line[0] == '\n') //end of starting items
			{
				TRACE("NEWLINE, final item count: %llu\n", m[i].itemCount);
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

		TRACE("Got operation: %c %llu\n", m[i].operation[0], m[i].operation[1]);
		TRACE("Got divisible by: %llu\n", m[i].test);
		TRACE("Got if true throw to: %llu\n", m[i].dest[1]);
		TRACE("Got if false throw to: %llu\n", m[i].dest[0]);

		fgets(line, 64, reader); //skip empty line
	}
	fclose(reader);

	return 0;
}

int executeRounds(int rounds, int relief, int modAll, monkey m[]) {
	for (int i = 0; i < rounds; i++)
	{
		TRACE("\n\nROUND: %d\n\n", i);
		for (int j = 0; j < MONKEYS; j++)
		{
			TRACE("\nMONKEY %d:\n", j);

			int count = 0;
			while (m[j].itemCount > 0) //while monkey has items
			{
				TRACE("count: %d, itemCount: %d\n", count, m[j].itemCount);
				//inspect
				TRACE("inspect: %llu\n", m[j].items[count]);
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
				TRACE("worry now: %llu\n", m[j].items[count]);

#ifdef DEBUG
				if (m[j].items[count] < 0)
				{
					TRACE("after mod: %llu\n", m[j].items[count]);
					while (1) {}
				}
#endif

				m[j].items[count] /= relief; //relief
				TRACE("relief: %llu\n", m[j].items[count]);

				m[j].items[count] = m[j].items[count] % modAll; //modulus
				TRACE("after mod: %llu\n", m[j].items[count]);

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

	return 0;
}

int printMonkeys(monkey m[]) {
	//find two of the most active
	unsigned long long int best[2] = { 0 };
	for (int i = 0; i < MONKEYS; i++)
	{
		int count = 0;
		for (int j = 0; j < MONKEYS; j++)
		{
			if (m[i].inspects < m[j].inspects)
			{
				count++;
			}
		}
		if (count <= 1)
		{
			best[count] = m[i].inspects;
		}
	}

	for (int i = 0; i < MONKEYS; i++)
	{
		if (m[i].inspects >= best[1])
		{
			printf("Monkey %d inspected items \x1b[31m%d\x1b[0m times.\n", i, m[i].inspects);
		}
		else
		{
			printf("Monkey %d inspected items %d times.\n", i, m[i].inspects);
		}
	}

	printf("Level of monkey business: \x1b[33m%llu\x1b[0m\n\n", best[0] * best[1]);

	return 0;
}

int day11() {
	int rounds = 20;
	int relief = 3;
	for (int i = 0; i < 2; i++)
	{
		monkey m[MONKEYS] = { { 0 } };

		readInput(m);

		//the modulo trick
		int modAll = 1;
		for (int j = 0; j < MONKEYS; j++) {
			modAll *= m[j].test;
		}
		TRACE("modAll: %d\n", modAll);

		executeRounds(rounds, relief, modAll, m);

		printMonkeys(m);

		rounds = 10000;
		relief = 1;
	}

	return 0;
}