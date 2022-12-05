#include "header.h"

int day2() {
	FILE* rps;
	rps = fopen("./data/day2Data.txt", "r");
	if (rps == NULL) {
		perror("Error opening file");
		return(-1);
	}

	int sum = 0;

	//scoring
	int win = 6;
	int draw = 3;
	int loss = 0;
	int rock = 1;
	int paper = 2;
	int scissors = 3;

	char ch = '\0';
	char opponent = '\0';
	char you = '\0';
	int turn = 0;
	while ((ch = fgetc(rps)) != EOF) {
		printf("%c", ch);

		if (ch == ' ') {
			turn = 1;
		}
		else if (ch == '\n') {
			turn = 0;
		}

		switch (turn)
		{
		case 0:
			opponent = ch;
			break;
		case 1:
			you = ch;
			switch (opponent)
			{
			case 'A':
				switch (you)
				{
				case 'X':
					sum += draw + rock;
					break;
				case 'Y':
					sum += win + paper;
					break;
				case 'Z':
					sum += loss + scissors;
					break;
				default:
					break;
				}
				break;
			case 'B':
				switch (you)
				{
				case 'X':
					sum += loss + rock;
					break;
				case 'Y':
					sum += draw + paper;
					break;
				case 'Z':
					sum += win + scissors;
					break;
				default:
					break;
				}
				break;
			case 'C':
				switch (you)
				{
				case 'X':
					sum += win + rock;
					break;
				case 'Y':
					sum += loss + paper;
					break;
				case 'Z':
					sum += draw + scissors;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

	}
	fclose(rps);

	printf("%d", sum);

	//second problem
	rps = fopen("./data/day2Data.txt", "r");
	if (rps == NULL) {
		perror("Error opening file");
		return(-1);
	}

	sum = 0;
	while ((ch = fgetc(rps)) != EOF) {
		printf("%c", ch);

		if (ch == ' ') {
			turn = 1;
		}
		else if (ch == '\n') {
			turn = 0;
		}

		switch (turn)
		{
		case 0:
			opponent = ch;
			break;
		case 1:
			you = ch;
			switch (opponent)
			{
			case 'A':
				switch (you)
				{
				case 'X':
					sum += loss + scissors;
					break;
				case 'Y':
					sum += draw + rock;
					break;
				case 'Z':
					sum += win + paper;
					break;
				default:
					break;
				}
				break;
			case 'B':
				switch (you)
				{
				case 'X':
					sum += loss + rock;
					break;
				case 'Y':
					sum += draw + paper;
					break;
				case 'Z':
					sum += win + scissors;
					break;
				default:
					break;
				}
				break;
			case 'C':
				switch (you)
				{
				case 'X':
					sum += loss + paper;
					break;
				case 'Y':
					sum += draw + scissors;
					break;
				case 'Z':
					sum += win + rock;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

	}
	fclose(rps);

	printf("%d", sum);

	return 0;
}