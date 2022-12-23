#ifndef HEADER_FILE
#define HEADER_FILE

#define DEBUG
#ifndef DEBUG
#define TRACE( format, ... )
#else
#define TRACE( format, ... )   printf( "%s(%d) " format, __FUNCTION__,  __LINE__, __VA_ARGS__ )
#endif

#pragma once
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

//#ifndef HEADER_FILE
//#include "day01.c"
//#include "day02.c"
//#include "day03.c"
//#include "day04.c"
//#include "day05.c"
//#include "day06.c"
//#include "day07.c"
//#include "day08.c"
//#include "day09.c"
//#include "day10.c"
//#endif

#endif