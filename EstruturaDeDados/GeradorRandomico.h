#pragma once
#include <stdlib.h>
/**
* Gera um numero rand�mico entre 0 e 1 usando srand e rand
*/
inline double randomico()
{	
	double nRand = (double) (double(rand()) / RAND_MAX);
	return nRand;
}