#include "StdAfx.h"
#include "Cliente.h"
#include "GeradorRandomico.h"

Cliente::Cliente(int tempoAtual) 
{
	int aleatorio = (int) (randomico() * 2);
	if (aleatorio == 0) 
		this->m_tipoCliente = buscaMenorFila;
	else
		this->m_tipoCliente = buscaFilaComMenosProdutos;

	aleatorio = (int) (randomico() * 5);
	if (aleatorio < 1)
		this->m_pagarComCheque = true;
	else
		this->m_pagarComCheque = false;
	
	aleatorio = (int) ((randomico() * 99) + 2);
	this->m_totalDeCompras = aleatorio;
	this->m_valorTotalDosProdutos = 0;
	for(int i = 0; i < this->m_totalDeCompras; i ++)
	{
		aleatorio = (int) ((randomico() * 9000) + 100);
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
