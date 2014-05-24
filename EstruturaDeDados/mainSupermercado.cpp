#include "stdafx.h"
#include "Supermercado.h"
#include <string>

int main() 
{
	std::string arquivoConfiguracao = "naocompre.dat";
	Supermercado mercado(arquivoConfiguracao);
	mercado.rodarSimulacao();
	mercado.CalcularEstatisticas();
	return 0;
}

