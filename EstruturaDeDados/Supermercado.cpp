#include "StdAfx.h"
#include "Supermercado.h"
#include "GeradorRandomico.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Supermercado::Supermercado(std::string nomeDoSupermercado,	ListaCircular<std::string> *identificadoresDosCaixas, ListaCircular<Eficiencia> *eficienciaDosCaixas, 
	ListaCircular<double> *salariosDosCaixas,	int tempoMedioEmSegundosDeChegadaDeNovosClientes,	int tempoTotalDeSimulacaoEmHoras,	int tamanhoMaximoDasFilasParaDesistir) 
{
		this->m_NomeDoSupermercado = nomeDoSupermercado;
		this->m_relogioInterno = 0;
		this->m_tamanhoMaximoFilas = 10;
		this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes = tempoMedioEmSegundosDeChegadaDeNovosClientes;
		this->m_tempoTotalDeSimulacaoEmHoras = tempoTotalDeSimulacaoEmHoras;
		this->m_tempoDeChegadaDoProximoCliente = 0;
		for (int i = 0; i < identificadoresDosCaixas->obterTamanho(); i++) 
		{
			Caixa *novo = new Caixa(*identificadoresDosCaixas->retiraDoInicio(), *eficienciaDosCaixas->retiraDoInicio(), *salariosDosCaixas->retiraDoInicio(), false, this->m_relogioInterno);
			this->m_listaDeCaixas.adicionaNoFim(novo);
		}
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
	this->m_relogioInterno = 0;
	this->m_tamanhoMaximoFilas = 10;
	this->m_tempoDeChegadaDoProximoCliente = 0;

	std::string linha;
	std::ifstream arquivo(caminhoParaArquivo);
	std::vector<std::string> linhasArquivo;
	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			getline(arquivo,linha);
			if (linha[0]!='#')
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
		Caixa* novoCaixa = new Caixa(informacoesCaixa.at(0),(Eficiencia) (atoi(informacoesCaixa.at(1).c_str())),atoi(informacoesCaixa.at(2).c_str()),false,this->m_relogioInterno);
		m_listaDeCaixas.adicionaNoFim(novoCaixa);
	}
}


Supermercado::~Supermercado(void)
{
}

void Supermercado::CalcularEstatisticas() 
{
	using namespace std;
	cout << "Estatísticas do Supermercado " << this->m_NomeDoSupermercado << endl;
	cout << endl << "Faturamento por caixa:" << endl;
	
	double faturamentoTotal = 0;

	for (int i = 0; i < this->m_listaDeCaixas.obterTamanho(); i++) 
	{
		Caixa *atual = this->m_listaDeCaixas.retiraDoInicio();
		
		cout << atual->getIdentificador() << endl;
		cout << "Faturamento: " << atual->getFaturamento() << endl;
		
		int horasTrabalhadas = this->m_tempoTotalDeSimulacaoEmHoras - (int) (atual->getTempoDeEntrada() / (60 * 60));
		int desconto = atual->getSalario() * horasTrabalhadas;
		if (atual->getSobrehora()) 
		{
			desconto *= 2;
		}

		cout << "Lucro: " << atual->getFaturamento() - desconto;
		
		faturamentoTotal += atual->getFaturamento();
		this->m_listaDeCaixas.adicionaNoFim(atual);
	}
	cout << endl << "Faturamento médio por caixa: " << faturamentoTotal / this->m_listaDeCaixas.obterTamanho() << endl;
	double tempoMedioDeEsperaDeUmClienteNaFila = 0;

	for (int i = 0; i < this->m_clientesAtendidos.obterTamanho(); i++) 
	{
		Cliente *atual;
		atual = this->m_clientesAtendidos.retiraDoInicio();
		tempoMedioDeEsperaDeUmClienteNaFila += atual->getTempoSaida() - atual->getTempoChegada();
		this->m_clientesAtendidos.adicionaNoFim(atual);
	}
	tempoMedioDeEsperaDeUmClienteNaFila /= this->m_clientesAtendidos.obterTamanho();
	
	cout << "Tempo médio de espera de um cliente na fila: " << tempoMedioDeEsperaDeUmClienteNaFila << " segundos" << endl;
	cout << "Clientes desistentes: " << this->m_clientesDesistentes.obterTamanho();
	
	double faturamentoPerdido = 0;
	for (int i = 0; i < this->m_clientesDesistentes.obterTamanho(); i++) 
	{
		Cliente *atual = this->m_clientesDesistentes.retiraDoInicio();
		faturamentoPerdido += atual->getValorTotalCompras();
		this->m_clientesDesistentes.adicionaNoFim(atual);
	}

	cout << "Faturamento perdido: " << faturamentoPerdido * 3;
}

void Supermercado::rodarSimulacao() 
{
	while (this->m_relogioInterno < this->m_tempoTotalDeSimulacaoEmHoras * 60 * 60) 
	{
		bool precisaContratarNovoCaixa = true;
		for (int i = 0; i < this->m_listaDeCaixas.obterTamanho(); i++) 
		{
			Caixa *atual;
			Cliente *atendido;
			atual = this->m_listaDeCaixas.retiraDoInicio();
			atendido = atual->atendeCliente(this->m_relogioInterno);
			this->m_listaDeCaixas.adicionaNoFim(atual);
			if (atual->getNroClientes() < 10)
				precisaContratarNovoCaixa = false;
			if (atendido != NULL)
				this->m_clientesAtendidos.adicionaNoFim(atendido);
		}
		if (precisaContratarNovoCaixa) 
		{
			int numeroEficiencia = (int) ((randomico() * 3) + 1);
			Eficiencia eficiencia;
			double salario;
			switch (numeroEficiencia) 
			{
			case 1:
				eficiencia = eficiente;
				salario = 800;
				break;
			case 2:
				eficiencia = medio;
				salario = 540;
				break;
			case 3:
				eficiencia = ruim;
				salario = 180;
				break;
			}
			Caixa *novo = new Caixa("Extra", eficiencia, salario, true, this->m_relogioInterno);
			this->m_listaDeCaixas.adicionaNoFim(novo);
		}

		if (this->m_relogioInterno == this->m_tempoDeChegadaDoProximoCliente) 
		{
			this->gerarCliente(precisaContratarNovoCaixa);
		}
		this->m_relogioInterno += 1;
	}
	CalcularEstatisticas();
}

void Supermercado::gerarCliente(bool caixasCheios) 
{
	Cliente *novo = new Cliente(this->m_relogioInterno);
	if (caixasCheios) 
		this->m_clientesDesistentes.adicionaNoFim(novo);
	else 
	{
		switch (novo->getTipoCliente()) 
		{
		case buscaMenorFila:
			buscarMenorFila(novo);
			break;
		case buscaFilaComMenosProdutos:
			buscarFilaComMenosProdutos(novo);
			break;
		}
	}
	int intervalo = (int) ((randomico() * this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes) - (this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes / 2));
	this->m_tempoDeChegadaDoProximoCliente = this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes + intervalo;
}
void Supermercado::buscarMenorFila(Cliente *novo) {
	Caixa *escolhido, *teste;
	escolhido = this->m_listaDeCaixas.retiraDoInicio();
	this->m_listaDeCaixas.adicionaNoFim(escolhido);
	for (int i = 0; i < this->m_listaDeCaixas.obterTamanho() - 1; i++) {
		teste = this->m_listaDeCaixas.retiraDoInicio();
		if (teste->getNroClientes() < escolhido->getNroClientes()) {
			escolhido = teste;
		}
		this->m_listaDeCaixas.adicionaNoFim(teste);
	}
	escolhido->recebeCliente(novo, this->m_relogioInterno);
}
void Supermercado::buscarFilaComMenosProdutos(Cliente *novo) {
	Caixa *escolhido, *teste;
	escolhido = this->m_listaDeCaixas.retiraDoInicio();
	this->m_listaDeCaixas.adicionaNoFim(escolhido);
	for (int i = 0; i < this->m_listaDeCaixas.obterTamanho() - 1; i++) {
		teste = this->m_listaDeCaixas.retiraDoInicio();
		if (teste->getNroProdutos() < escolhido->getNroProdutos()) {
			escolhido = teste;
		}
		this->m_listaDeCaixas.adicionaNoFim(teste);
	}
	escolhido->recebeCliente(novo, this->m_relogioInterno);
}
