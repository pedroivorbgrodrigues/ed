#include "StdAfx.h"
#include "Cliente.h"
#include <stdlib.h>
#include <ctime>

Cliente::Cliente(int tempoAtual) 
{
	srand(time(NULL));
	int aleatorio = (int) ((rand() / RAND_MAX) * 2);
	if (aleatorio == 0) {
		this->m_tipoCliente = buscaMenorFila;
	} else {
		this->m_tipoCliente = buscaFilaComMenosProdutos;
	}
	srand(time(NULL));
	aleatorio = (int) ((rand() / RAND_MAX) * 5);
	if (aleatorio < 1) {
		this->m_pagarComCheque = true;
	} else {
		this->m_pagarComCheque = false;
	}
	srand(time(NULL));
	aleatorio = (int) (((rand() / RAND_MAX) * 99) + 2);
	this->m_totalDeCompras = aleatorio;
	this->m_valorTotalDosProdutos = 0;
	for(int i = 0; i < this->m_totalDeCompras; i ++){
		srand(time(NULL));
		aleatorio = (int) (((rand() / RAND_MAX) * 9000) + 100);
		this->m_valorTotalDosProdutos += aleatorio/100;
	}
	this->m_tempoDeChegada = tempoAtual;
	this->m_tempoDeSaidaDaFilaDoCaixa = 0;
}

Cliente::~Cliente() 
{

}
int Cliente::getNumeroDeProdutos() 
{
	return this->m_totalDeCompras;
}

bool Cliente::vaiPagarComCheque() 
{
	return this->m_pagarComCheque;
}

void Cliente::setTempoSaida(int tempoDeSaida) 
{
	this->m_tempoDeSaidaDaFilaDoCaixa = tempoDeSaida;
}

int Cliente::getTempoSaida() 
{
	return this->m_tempoDeSaidaDaFilaDoCaixa;
}

int Cliente::getTempoChegada()
{
	return this->m_tempoDeChegada;
}

double Cliente::getValorTotalCompras() 
{
	return this->m_valorTotalDosProdutos;
}

TipoCliente Cliente::getTipoCliente() 
{
	return this->m_tipoCliente;
}
