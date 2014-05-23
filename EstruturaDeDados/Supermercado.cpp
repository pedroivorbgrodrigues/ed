#include "StdAfx.h"
#include "Supermercado.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Supermercado::Supermercado(std::string nomeDoSupermercado,std::vector<Eficiencia> eficienciaDosCaixas,int tempoMedioEmSegundosDeChegadaDeNovosClientes,int tempoTotalDeSimulacaoEmHoras, int tamanhoMaximoDasFilasParaDesistir)
{
}

std::vector<std::string> splitString(std::string original, char delimitador)
{
	std::vector<std::string> retorno;
	size_t pos = 0;
	std::string token;
	while ((pos = original.find(delimitador)) != std::string::npos) {
		token = original.substr(0, pos);
		retorno.push_back(token);
		original.erase(0, pos + 1);
	}
	return retorno;
}

Supermercado::Supermercado(std::string caminhoParaArquivo)
{
	std::string linha;
	std::ifstream arquivo(caminhoParaArquivo);
	std::vector<std::string> linhasArquivo;
	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			getline(arquivo,linha);
			if (!linha[0]=='#')
				linhasArquivo.push_back(linha);
		}
		arquivo.close();
	}
	int indiceLinhaAtual = 0;
	m_NomeDoSupermercado = linhasArquivo.at(indiceLinhaAtual++);
	m_tempoTotalDeSimulacaoEmHoras = atoi(linhasArquivo.at(indiceLinhaAtual++).c_str());
	m_tempoMedioEmSegundosDeChegadaDeNovosClientes = atoi(linhasArquivo.at(indiceLinhaAtual++).c_str());
	int quantidadeDeCaixas = atoi(linhasArquivo.at(indiceLinhaAtual++).c_str());
	for (int indiceCaixa = 0; indiceCaixa < quantidadeDeCaixas; indiceCaixa++)
	{
		std::vector<std::string> informacoesCaixa = splitString(linhasArquivo.at(indiceLinhaAtual++),' ');
		Caixa* novoCaixa = new Caixa(informacoesCaixa.at(0),atoi(informacoesCaixa.at(1).c_str()),atoi(informacoesCaixa.at(2).c_str()));
		m_listaDeCaixas.AdicionaDado(novoCaixa);
	}
}


Supermercado::~Supermercado(void)
{
}

void Supermercado::CacularEstatisticas()
{

}
