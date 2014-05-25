#pragma once
#include <stdlib.h>

inline double randomico()
{	
	double nRand = (double) (double(rand()) / RAND_MAX);
	return nRand;
}