#pragma once
#include <ctime>
#include <stdlib.h>

inline double randomico()
{
	srand(time(NULL));
	double nRand = (double) ((double)rand() / RAND_MAX);
	return nRand;
}