#include "header.h"

int day5()
{
    FILE *crane;
    crane = fopen("./data/day5Data.txt", "r");
    if (crane == NULL)
    {
        perror("Error opening file");
        return (-1);
    }

    char stack[9][100] = {'\0'};

    // get stack data
    char ch[40] = {'\0'};
    for (int i = 7; i > -1; i--)
    {
        fgets(ch, 40, crane);

        for (int j = 0; j < 9; j++)
        {
            stack[j][i] = ch[1 + (j * 4)];
        }
    }

    // clone array
    char cloneStack[9][100] = {'\0'};
    for (int i = 0; i < 9; i++)
    {
        strncpy(cloneStack[i], stack[i], 9);
    }

    // skip two lines
    fgets(ch, 40, crane);
    fgets(ch, 40, crane);

    // remember instructions starting position
    int startPos = ftell(crane);
    //printf("%d\n", startPos);

    // start executing instructions
    int move = 0;
    int from = 0;
    int to = 0;
    int fromCount = 0;
    int toCount = 0;
    while (fscanf(crane, "move %d from %d to %d ", &move, &from, &to) != EOF)
    {
        //printf("move %d from %d to %d\n", move, from, to); // debug
        from--;
        to--;

        // first part
        for (int i = 0; i < move; i++)
        {
            //get stack height
            while (stack[from][fromCount] != ' ' && stack[from][fromCount] != '\0')
            {
                fromCount++;
            }
            fromCount--;

            //get stack height
            while (stack[to][toCount] != ' ' && stack[to][toCount] != '\0')
            {
                toCount++;
            }

            //move the crate
            stack[to][toCount] = stack[from][fromCount];
            stack[from][fromCount] = '\0'; // null out place where crate was taken

            fromCount = 0;
            toCount = 0;
        }
    }

    printf("\npart one answer:\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%s\n", stack[i]);
    }

    // second part
    fseek(crane, startPos, SEEK_SET); // back to start of instructions
    while (fscanf(crane, "move %d from %d to %d ", &move, &from, &to) != EOF)
    {
        from--;
        to--;

        //get stack height
        while (cloneStack[from][fromCount] != ' ' && cloneStack[from][fromCount] != '\0')
        {
            fromCount++;
        }
        fromCount -= move;

        //get stack height
        while (cloneStack[to][toCount] != ' ' && cloneStack[to][toCount] != '\0')
        {
            toCount++;
        }

        //move the crateS
        for (int j = 0; j < move; j++)
        {
            cloneStack[to][toCount + j] = cloneStack[from][fromCount + j];
            cloneStack[from][fromCount + j] = '\0'; // null out place where crate was taken
        }

        fromCount = 0;
        toCount = 0;
    }
    fclose(crane);

    printf("\npart two answer:\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%s\n", cloneStack[i]);
    }

    return 0;
}