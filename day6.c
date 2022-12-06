#include "header.h"

static char signal[5000] = { '\0' };

static void searchPacketFromSignal(int sizeOfPacket) {
	//start parsing
	for (int i = sizeOfPacket - 1; signal[i] != '\0'; i++)
	{
		//check last four
		for (int j = 0; j < sizeOfPacket; j++)
		{
			for (int k = 1; k < sizeOfPacket - j; k++)
			{
				if (signal[i - j] == signal[(i - j) - k])
				{
					goto nextChar; //same letter spotted so break out for loops
				}
			}
		}
		//answer
		printf("size-%d packet found: ", sizeOfPacket);
		for (int j = 0; j < sizeOfPacket; j++)
		{
			printf("%c", signal[i - (sizeOfPacket - 1) + j]);
		}
		printf("\nhad to process: %d characters\n", i + 1);
		break;
	nextChar:; //if found same character then skip to here
	}
}

int day6() {
	FILE* device;
	device = fopen("./data/day6Data.txt", "r");
	if (device == NULL)
	{
		perror("Error opening file");
		return (-1);
	}

	//read signal
	fgets(signal, 5000, device);
	fclose(device);

	searchPacketFromSignal(4); //first part
	searchPacketFromSignal(14); //second part

	return 0;
}
