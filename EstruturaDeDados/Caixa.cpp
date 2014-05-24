#include "StdAfx.h"
#include "Caixa.h"
#include <string.h>

Caixa::Caixa(std::string identificador, Eficiencia desempenho, double salario,	bool sobrehora, int tempoAtual) 
{
	this->m_clientes = new FilaEncadeadaCircular<Cliente>();
	this->m_numeroDeClientesNaFila = 0;
	this->m_numeroDeClientesAtendidos = 0;
	this->m_tempoMedioDeEsperaDeUmClienteNaFila = 0;
	this->m_faturamentoTotal = 0;
	this->m_identificador = identificador;
	this->m_eficiencia = desempenho;
	this->m_salario = salario;
	this->m_sobrehora = sobrehora;
	this->m_tempoDeInicioDeExpediente = tempoAtual;
}

Caixa::~Caixa() 
{
}

void Caixa::recebeCliente(Cliente *novo, int tempoAtual) 
{
	this->m_clientes->adiciona(novo);
	this->m_numeroDeClientesNaFila += 1;
	int tempo = novo->getNumeroDeProdutos();
	switch (m_eficiencia) {
	case eficiente:
		if (novo->vaiPagarComCheque())
			tempo += 10;
		break;
	case medio:
		tempo = tempo * 2;
		if (novo->vaiPagarComCheque())
			tempo += 25;
		break;
	case ruim:
		tempo = tempo * 4;
		if (novo->vaiPagarComCheque())
			tempo += 60;
	}
	this->m_tempoMedioDeEsperaDeUmClienteNaFila += tempo;
	novo->setTempoSaida(
		tempo + this->m_tempoMedioDeEsperaDeUmClienteNaFila + tempoAtual);
}

Cliente* Caixa::atendeCliente(int tempoAtual) 
{
	this->m_tempoMedioDeEsperaDeUmClienteNaFila -= 1;
	//try{
	Cliente *proximo = m_clientes->retira();
	if (proximo->getTempoSaida() == tempoAtual) {
		this->m_faturamentoTotal += proximo->getValorTotalCompras();
		this->m_numeroDeClientesAtendidos += 1;
		this->m_numeroDeClientesNaFila -= 1;
		return proximo;
	}
	this->m_clientes->adicionaNoInicio(proximo);
	return NULL; //} catch(){}
}

int Caixa::getNroClientes() 
{
	return this->m_numeroDeClientesNaFila;
}

int Caixa::getNroClientesAtendidos() 
{
	return this->m_numeroDeClientesAtendidos;
}

int Caixa::getTempoEspera() 
{
	return this->m_tempoMedioDeEsperaDeUmClienteNaFila;
}

double Caixa::getFaturamento() 
{
	return this->m_faturamentoTotal;
}

std::string Caixa::getIdentificador() 
{
	return this->m_identificador;
}

int Caixa::getDesempenho() 
{
	return this->m_eficiencia;
}
int Caixa::getNroProdutos() 
{
	int numero = 0;
	Cliente *atual;
	for (int i = 0; i < this->m_clientes->obterTamanho(); i++) {
		atual = this->m_clientes->retira();
		numero += atual->getNumeroDeProdutos();
		this->m_clientes->adiciona(atual);
	}
	return numero;
}

int Caixa::getSalario() 
{
	return this->m_salario;
}

bool Caixa::getSobrehora() 
{
	return this->m_sobrehora;
}

int Caixa::getTempoDeEntrada() 
{
	return this->m_tempoDeInicioDeExpediente;
}
