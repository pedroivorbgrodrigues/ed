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
	*  Tempo para atender cliente  = quantidade de produtos multiplicado pelo tempo de digita��o de cada item (em segundos) + tempo para receber o cheque (em segundos)
	*/
	enum Eficiencia 
	{
		eficiente = 1, /**< Tempo de digita��o p/ produto = 1s , Tempo para receber cheque = 10s */
		medio = 2, /**< Tempo de digita��o p/ produto = 2s , Tempo para receber cheque = 25 */
		ruim = 3/**< Tempo de digita��o p/ produto = 4s , Tempo para receber cheque = 60s */
	};
	/**
	*@param sobrehora Indica se este � um caixa extra e portanto deve receber em dobro
	*@param tempoAtual Tempo em que o caixa foi contratado
	*/
	Caixa(std::string identificador, Eficiencia desempenho, double salarioPorHora, bool sobrehora, int tempoAtual);
	~Caixa();
	/**
	* Respons�vel por adicionar um cliente na fila do caixa e calcular em qual "hor�rio" este ser� atendido
	*/
	void recebeCliente(Cliente *clienteAdicionar, int tempoDeEntradaNaFila);
	/**
	* Respons�vel por verificar se o cliente j� pode ser atendido de acordo com a hora do supermercado
	*/
	Cliente* atendeCliente(int tempoAtualSupermercado);
	/**
	* Retorna o numero de clientes na fila
	*/
	int getNroClientes();
	/**
	* Retorna o numero de clientes j� atendidos
	*/
	int getNroClientesAtendidos();
	/**
	* Retorna o tempo m�dio de espera na fila do caixa
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
	* Retorna qual o n�vel de eficiencia do caixa
	*/
	int getDesempenho();
	/**
	* Retorna a quantidade total de produtos a serem processados pelo caixa
	*/
	int getNroProdutos();
	/**
	* Retorna o sal�rio do caixa
	*/
	int getSalario();
	/**
	* Retorna se o caixa � extra ou n�o
	*/
	bool getSobrehora();
	/**
	* Retorna o tempo de contrata��o do caixa
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
