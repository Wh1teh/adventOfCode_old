#include "header.h"

#define MONKEYS 8

typedef struct monkeyStruct {
	unsigned long long int items[100]; //item values
	unsigned long long int itemCount;
	unsigned long long int inspects;
	unsigned long long int operation[3]; //operand+-*/ and value, 2: flag 'old'
	unsigned long long int test; //divisible by value
	unsigned long long int dest[2]; //which monkey to throw to? [1] true, [0] false
}monkey;

unsigned long long int day11() {
	FILE* reader;
	reader = fopen("./data/day11Data.txt", "r");
	if (reader == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	monkey m[MONKEYS] = { { 0 } };

	//read input
	unsigned long long int count = 0;
	char line[64] = { '\0' };
	for (unsigned long long int i = 0; i < MONKEYS; i++)
	{
		//skip useless lines
		fgets(line, 64, reader);
		fgets(line, 64, reader);

		count = 0;
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
		sscanf(&line[25], "%llu", &m[i].operation[1]); //value

		//test
		fgets(line, 64, reader);
		sscanf(&line[21], "%llu", &m[i].test);

		//dest if true
		fgets(line, 64, reader);
		sscanf(&line[29], "%llu", &m[i].dest[1]);

		//dest if false
		fgets(line, 64, reader);
		sscanf(&line[30], "%llu", &m[i].dest[0]);

		TRACE("Got operation: %c %llu\n", m[i].operation[0], m[i].operation[1]);
		TRACE("Got divisible by: %llu\n", m[i].test);
		TRACE("Got if true throw to: %llu\n", m[i].dest[1]);
		TRACE("Got if false throw to: %llu\n", m[i].dest[0]);

		fgets(line, 64, reader); //skip empty line
	}
	fclose(reader);

	unsigned long long int modAll = 1;

	for (unsigned long long int j = 0; j < MONKEYS; j++) {
		modAll *= m[j].test;
	}
	printf("modAll: %llu\n", modAll);

	unsigned long long int rounds = 10000;
	unsigned long long int relief = 1;
	for (unsigned long long int ab = 0; ab < 1; ab++)
	{
		for (unsigned long long int i = 0; i < rounds; i++)
		{
			TRACE("\n\nROUND: %llu\n\n", i);
			for (unsigned long long int j = 0; j < MONKEYS; j++)
			{
				TRACE("\nMONKEY %llu:\n", j);

				count = 0;
				while (m[j].itemCount > 0) //while monkey has items
				{
					TRACE("count: %llu, itemCount: %llu\n", count, m[j].itemCount);
					//inspect
					TRACE("inspect: %llu\n", m[j].items[count]);
					if (m[j].operation[1] == 0 || m[j].operation[2] == 1) //operation value is 'old'
					{
						m[j].operation[2] = 1; //flag operation value as 'old'
						m[j].operation[1] = m[j].items[count];
						TRACE("'old': %llu\n", m[j].operation[1]);
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

					if (m[j].items[count] < 0)
					{
						printf("after mod: %llu\n", m[j].items[count]);
						while (1) {}
					}

					//m[j].items[count] /= relief; //relief
					TRACE("relief: %llu\n", m[j].items[count]);

					m[j].items[count] = m[j].items[count] % modAll; //modulus
					TRACE("after mod: %llu\n", m[j].items[count]);

					unsigned long long int dest = 0;
					if (m[j].items[count] % m[j].test == 0) //true, is divisible
					{
						dest = m[j].dest[1]; //destination if true
						TRACE("true, send to: %llu\n", dest);
						m[dest].items[m[dest].itemCount] = m[j].items[count]; //sends item to first free spot at destination
						m[dest].itemCount++; //destination monkey's item count increases
					}
					else //false
					{
						dest = m[j].dest[0]; //destination if false
						TRACE("false, send to: %llu\n", dest);
						m[dest].items[m[dest].itemCount] = m[j].items[count]; //sends item to first free spot at destination
						m[dest].itemCount++; //destination monkey's item count increases
					}

					m[j].itemCount--; //current monkey has one less item
					m[j].inspects++; //total inspects goes up
					count++; //next item
				}
			}
		}

		for (unsigned long long int i = 0; i < MONKEYS; i++)
		{
			printf("Monkey %llu inspected items %llu times\n", i, m[i].inspects);
		}

		//while(1){}

		relief = 1; //no more relief
		rounds = 20;
	}

	//find best two
	unsigned long long int best[2] = { 0 };
	for (int i = 0; i < MONKEYS; i++)
	{
		count = 0;
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
	printf("%llu\n", best[0] * best[1]);

	return 0;
}