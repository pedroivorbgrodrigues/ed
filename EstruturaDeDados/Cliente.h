#pragma once
#include "ListaCircular.hpp"

enum TipoCliente {
	buscaMenorFila, buscaFilaComMenosProdutos
};

class Cliente {
public:
	Cliente(int tempoAtual);
	~Cliente();
	int getNumeroDeProdutos();
	bool vaiPagarComCheque();
	void setTempoSaida(int tempoDeSaida);
	int getTempoSaida();
	int getTempoChegada();
	double getValorTotalCompras();
	TipoCliente getTipoCliente();
private:
	TipoCliente m_tipoCliente;
	bool m_pagarComCheque; //probabilidade de pagar com cheque é 20% randomizar no construtor(RC)
	int m_totalDeCompras; //RC entre 2-100
	double m_valorTotalDosProdutos; //RC entre 1 e 90, tamanho da lista dado pelo total de compras
	int m_tempoDeChegada;
	int m_tempoDeSaidaDaFilaDoCaixa;
};


