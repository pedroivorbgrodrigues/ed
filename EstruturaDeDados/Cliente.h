#pragma once
#include "ListaEncadeadaSimples.hpp"

enum TipoCliente
{
	buscarMenorFila,
	buscaFilaComMenosProdutos
};

class Cliente
{
public:
	Cliente(void);
	~Cliente(void);
	int tempoNaFila(){return m_tempoDeSaidaDaFilaDoCaixa-m_tempoDeChegada;}

private:
	TipoCliente m_tipoCliente;
	bool m_pagarComCheque;//probabilidade de pagar com cheque é 20% randomizar no construtor(RC)
	int m_totalDeCompras;//RC entre 2-100
	ListaEncadeadaSimples<double> m_listaDeProdutos;//RC entre 1 e 90, tamanho da lista dado pelo total de compras
	int m_tempoDeChegada;
	int m_tempoDeSaidaDaFilaDoCaixa;

};

