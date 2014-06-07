#pragma once
#include "Caixa.h"
#include "ListaCircular.hpp"
/**
*@brief  Responsável pelo armazenamento dos parametros de execução e por conter a lógica da aplicação\n
* A funcionalidade relacionada com a desistencia de compra pelos clientes não está ocorrendo devido ao parametro padrão definido nos requisitos do projeto ser mutualmente exclusivo com a contratação de novos caixas.
*/
class Supermercado
{
public:
	/**
	*@param tamanhoMaximoDasFilasParaDesistir Quando todos os caixas estiverem com esse numero de clientes na fila e um novo cliente chegar este desiste da compra.
	*/
	Supermercado(std::string nomeDoSupermercado,
		ListaCircular<std::string> *identificadoresDosCaixas,
		ListaCircular<Caixa::Eficiencia> *eficienciaDosCaixas,
		ListaCircular<double> *salariosDosCaixas,
		int tempoMedioEmSegundosDeChegadaDeNovosClientes,
		int tempoTotalDeSimulacaoEmHoras,
		int tamanhoMaximoDasFilasParaDesistir);
	/**
	* Construtor que recebe o arquivo de configuração de onde os parametros serão extraidos
	*/
	Supermercado(std::string caminhoArquivoConfiguracao);
	~Supermercado(void);
	/**
	*  Método principal responsável por simular o funcionamento do Supermercado e apresentar as estatísticas no final da execução
	*/
	void rodarSimulacao();	
private:
	std::string m_NomeDoSupermercado;
	ListaCircular<Caixa> m_listaDeCaixas;
	int m_relogioInterno; //tipo ciclos
	ListaCircular<Cliente> m_clientesDesistentes;
	int m_tamanhoMaximoFilas; //se TODOS os caixas estiverem com a fila desse tamanho ou mais deve-se contratar um novo caixa pagando em dobro a hora
	int m_tempoDeChegadaDoProximoCliente;
	int m_tempoMedioEmSegundosDeChegadaDeNovosClientes;
	int m_tempoTotalDeSimulacaoEmHoras;
	void gerarCliente(bool caixasCheios);
	void buscarMenorFila(Cliente *novo);
	void buscarFilaComMenosProdutos(Cliente *novo);
	void CalcularEstatisticas();
};