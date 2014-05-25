#include "stdafx.h"
#include "Supermercado.h"
#include <string>
#include <ctime>

int main() 
{
	srand(time(NULL));
	std::string arquivoConfiguracao = "naocompre.dat";
	Supermercado mercado(arquivoConfiguracao);
	mercado.rodarSimulacao();
	return 0;
}

