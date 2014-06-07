#pragma once
#include "ListaCircular.hpp"

/**
*@brief  Representa um cliente de supermercado
*/
class Cliente {
public:
	/**
	*  Representa o modo como o cliente escolherá o caixa em que quer ser atendido
	*/
	enum TipoCliente 
	{
		buscaMenorFila, 
		buscaFilaComMenosProdutos
	};

	Cliente(int tempoDeChegadaNoSupermercado);
	~Cliente();
	/**
	*  Retorna o numero de produtos comprados pelo clientes
	*/
	int getNumeroDeProdutos();
	/**
	*  Indica se o cliente irá pagar com cheque
	*/
	bool vaiPagarComCheque();
	/**
	*  Defini o "horário" em que o caixa atenderá o cliente
	*/
	void setTempoSaida(int tempoDeSaida);
	/**
	*  Retorna o "horário" em que o caixa atenderá o cliente
	*/
	int getTempoSaida();
	/**
	*  Retorna o "horário" em que o cliente chegou no supermercado
	*/
	int getTempoChegada();
	/**
	*  Retorna o valor total da compra do cliente
	*/
	double getValorTotalCompras();
	/**
	*  Retorna o tipo de cliente, se ele bsuca pela menor fila ou a fila com menos produtos
	*/
	TipoCliente getTipoCliente();
private:
	TipoCliente m_tipoCliente;
	bool m_pagarComCheque; //probabilidade de pagar com cheque é 20% randomizar no construtor(RC)
	int m_totalDeCompras; //RC entre 2-100
	double m_valorTotalDosProdutos; //RC entre 1 e 90, tamanho da lista dado pelo total de compras
	int m_tempoDeChegada;
	int m_tempoDeSaidaDaFilaDoCaixa;
};


