#pragma once
#include "Cliente.h"

enum Eficiencia
{
	eficiente = 1,
	medio = 2,
	ruim = 3
};

class Caixa
{
public:
	Caixa(void);
	~Caixa(void);
	double FaturamentoMedio(){return m_clientesAtendidos == 0 ? 0 : m_faturamentoTotal/m_clientesAtendidos;}
	double TempoMedioNaFila(){return m_clientesAtendidos == 0 ? 0 : m_tempoTotalDeClientesNaFila/m_clientesAtendidos;}
	
private:
	std::string identificador;
	double salario;
	ListaEncadeadaSimples<Cliente> m_filaDeClientes;
	Eficiencia m_eficiencia;
	double m_faturamentoTotal;
	int m_clientesAtendidos;
	int m_tempoTotalDeClientesNaFila;
	int tempoDePagamento(bool cheque)
	{
		if (!cheque)
			return 0;
		if (m_eficiencia == eficiente)
			return 10;
		else if (m_eficiencia == medio)
			return 25;
		else return 60;
	}

};

