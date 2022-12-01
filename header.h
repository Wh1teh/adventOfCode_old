#ifndef HEADER_FILE
#define HEADER_FILE

#pragma once
#pragma warning (disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef HEADER_FILE
for (int i = 0; i < 25; i++)
{
	#include "day%d.c", i + 1;
}
#endif

#endif