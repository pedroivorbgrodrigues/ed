#pragma once
#include "Cliente.h"
#include "FilaEncadeada.hpp"
#include <string>

enum Eficiencia
{
	eficiente = 1,
	medio = 2,
	ruim = 3
};

class Caixa
{
public:
	Caixa(std::string identificador, int desempenho, int salario);
	~Caixa();
	void recebeCliente(Cliente *novo, int tempoAtual);
	int atendeCliente(int tempoAtual);
	int getNroClientes();
	int getNroClientesAtendidos();
	int getTempoEspera();
	double getFaturamento();
	double getFaturamentoMedio();
	std::string getIdentificador();
	int getDesempenho();
	int getNroProdutos();
private:
	FilaEncadeadaCircular<Cliente> *m_clientes;
	int m_numeroDeClientesNaFila;
	int m_numeroDeClientesAtendidos;
	int m_tempoMedioDeEsperaDeUmClienteNaFila;
	double m_faturamentoTotal;
	double m_faturamentoMedio;
	std::string m_identificador;
	int m_eficiencia;
	int m_salario;

};

