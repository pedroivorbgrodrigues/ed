#pragma once
#include "Cliente.h"
#include "FilaEncadeada.hpp"
#include <string>

enum Eficiencia 
{
	eficiente = 1, medio = 2, ruim = 3
};

class Caixa {
public:
	Caixa(std::string identificador, Eficiencia desempenho, double salario, bool sobrehora, int tempoAtual);
	~Caixa();
	void recebeCliente(Cliente *novo, int tempoAtual);
	Cliente* atendeCliente(int tempoAtual);
	int getNroClientes();
	int getNroClientesAtendidos();
	int getTempoEspera();
	double getFaturamento();
	std::string getIdentificador();
	int getDesempenho();
	int getNroProdutos();
	int getSalario();
	bool getSobrehora();
	int getTempoDeEntrada();
private:
	FilaEncadeadaCircular<Cliente> *m_clientes;
	int m_numeroDeClientesNaFila;
	int m_numeroDeClientesAtendidos;
	int m_tempoMedioDeEsperaDeUmClienteNaFila;
	double m_faturamentoTotal;
	std::string m_identificador;
	int m_eficiencia;
	double m_salario;
	bool m_sobrehora;
	int m_tempoDeInicioDeExpediente;
};
