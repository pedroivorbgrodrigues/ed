#pragma once
#include "Cliente.h"
#include "FilaEncadeada.hpp"
#include <string>
/**
*@brief  Representa um caixa de supermercado
*/
class Caixa {
public:
	/**
	*  Representa a eficiencia de um caixa, sendo que esta afeta o tempo para se atender um cliente da seguinte forma:\n
	*  Tempo para atender cliente  = quantidade de produtos multiplicado pelo tempo de digitação de cada item (em segundos) + tempo para receber o cheque (em segundos)
	*/
	enum Eficiencia 
	{
		eficiente = 1, /**< Tempo de digitação p/ produto = 1s , Tempo para receber cheque = 10s */
		medio = 2, /**< Tempo de digitação p/ produto = 2s , Tempo para receber cheque = 25 */
		ruim = 3/**< Tempo de digitação p/ produto = 4s , Tempo para receber cheque = 60s */
	};
	/**
	*@param sobrehora Indica se este é um caixa extra e portanto deve receber em dobro
	*@param tempoAtual Tempo em que o caixa foi contratado
	*/
	Caixa(std::string identificador, Eficiencia desempenho, double salarioPorHora, bool sobrehora, int tempoAtual);
	~Caixa();
	/**
	* Responsável por adicionar um cliente na fila do caixa e calcular em qual "horário" este será atendido
	*/
	void recebeCliente(Cliente *clienteAdicionar, int tempoDeEntradaNaFila);
	/**
	* Responsável por verificar se o cliente já pode ser atendido de acordo com a hora do supermercado
	*/
	Cliente* atendeCliente(int tempoAtualSupermercado);
	/**
	* Retorna o numero de clientes na fila
	*/
	int getNroClientes();
	/**
	* Retorna o numero de clientes já atendidos
	*/
	int getNroClientesAtendidos();
	/**
	* Retorna o tempo médio de espera na fila do caixa
	*/
	int getTempoEspera();
	/**
	* Retorna o faturamento total do caixa
	*/
	double getFaturamento();
	/**
	* Retorna o identificado do caixa
	*/
	std::string getIdentificador();
	/**
	* Retorna qual o nível de eficiencia do caixa
	*/
	int getDesempenho();
	/**
	* Retorna a quantidade total de produtos a serem processados pelo caixa
	*/
	int getNroProdutos();
	/**
	* Retorna o salário do caixa
	*/
	int getSalario();
	/**
	* Retorna se o caixa é extra ou não
	*/
	bool getSobrehora();
	/**
	* Retorna o tempo de contratação do caixa
	*/
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
