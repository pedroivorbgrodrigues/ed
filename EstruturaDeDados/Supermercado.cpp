#include "StdAfx.h"
#include "Supermercado.h"
#include "GeradorRandomico.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Supermercado::Supermercado(std::string nomeDoSupermercado,	ListaCircular<std::string> *identificadoresDosCaixas, ListaCircular<Caixa::Eficiencia> *eficienciaDosCaixas, 
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
		Caixa* novoCaixa = new Caixa(informacoesCaixa.at(0),(Caixa::Eficiencia) (atoi(informacoesCaixa.at(1).c_str())),atoi(informacoesCaixa.at(2).c_str()),false,this->m_relogioInterno);
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
	cout << endl << "Faturamento por caixa:" << endl << endl;
	
	double faturamentoTotal = 0;
	int totalClientes = 0;

	for (int i = 0; i < this->m_listaDeCaixas.obterTamanho(); i++) 
	{
		Caixa *atual = this->m_listaDeCaixas.retiraDoInicio();
		
		cout << atual->getIdentificador() << "  ";
		cout << "Faturamento: " << atual->getFaturamento() << "  ";
		
		int horasTrabalhadas = this->m_tempoTotalDeSimulacaoEmHoras - (int) (atual->getTempoDeEntrada() / (60 * 60));
		int desconto = atual->getSalario() * horasTrabalhadas;
		if (atual->getSobrehora()) 
		{
			desconto *= 2;
		}
		totalClientes+= atual->getNroClientesAtendidos();
		cout << "Faturamento medio: " << atual->getFaturamento()/atual->getNroClientesAtendidos() << "  ";
		cout << "Lucro: " << atual->getFaturamento() - desconto << endl;
		 
		
		faturamentoTotal += atual->getFaturamento();
		this->m_listaDeCaixas.adicionaNoFim(atual);
	}
	printf ("\nFaturamento total: %4.2f\n\n",faturamentoTotal);
	
	cout << "Tempo medio de espera de um cliente na fila: " << (double)this->m_relogioInterno/(double)totalClientes << " segundos" << endl << endl;
	cout << "Clientes desistentes: " << this->m_clientesDesistentes.obterTamanho();
	
	double faturamentoPerdido = 0;
	for (int i = 0; i < this->m_clientesDesistentes.obterTamanho(); i++) 
	{
		Cliente *atual = this->m_clientesDesistentes.retiraDoInicio();
		faturamentoPerdido += atual->getValorTotalCompras();
		this->m_clientesDesistentes.adicionaNoFim(atual);
	}

	cout << "  Faturamento perdido: " << faturamentoPerdido * 3;
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
		}
		if (precisaContratarNovoCaixa) 
		{
			int numeroEficiencia = (int) ((randomico() * 3) + 1);
			Caixa::Eficiencia eficiencia;
			double salario;
			switch (numeroEficiencia) 
			{
			case 1:
				eficiencia = Caixa::Eficiencia::eficiente;
				salario = 800;
				break;
			case 2:
				eficiencia = Caixa::Eficiencia::medio;
				salario = 540;
				break;
			case 3:
				eficiencia = Caixa::Eficiencia::ruim;
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
	{
		this->m_clientesDesistentes.adicionaNoFim(novo);
		return;
	}
	else 
	{
		switch (novo->getTipoCliente()) 
		{
		case Cliente::TipoCliente::buscaMenorFila:
			buscarMenorFila(novo);
			break;
		case Cliente::TipoCliente::buscaFilaComMenosProdutos:
			buscarFilaComMenosProdutos(novo);
			break;
		}
	}
	double randomTempoNovoCliente =  randomico() * this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes;	
	double metade = (this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes / 2);
	int tempoNovoCliente = this->m_tempoMedioEmSegundosDeChegadaDeNovosClientes;
	tempoNovoCliente += randomTempoNovoCliente - metade;
	if (tempoNovoCliente < 0)
		tempoNovoCliente *= -1;
	this->m_tempoDeChegadaDoProximoCliente = this->m_relogioInterno + tempoNovoCliente;
}
void Supermercado::buscarMenorFila(Cliente *novo) 
{
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

void Supermercado::buscarFilaComMenosProdutos(Cliente *novo) 
{
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
