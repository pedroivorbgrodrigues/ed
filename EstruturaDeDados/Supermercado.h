#pragma once
#include "Caixa.h"
#include "ListaCircular.hpp"

class Supermercado
{
public:
	Supermercado(std::string nomeDoSupermercado,
		ListaCircular<std::string> *identificadoresDosCaixas,
		ListaCircular<Eficiencia> *eficienciaDosCaixas,
		ListaCircular<double> *salariosDosCaixas,
		int tempoMedioEmSegundosDeChegadaDeNovosClientes,
		int tempoTotalDeSimulacaoEmHoras,
		int tamanhoMaximoDasFilasParaDesistir);
	Supermercado(std::string caminhoArquivoConfiguracao);
	~Supermercado(void);
	void rodarSimulacao();
	void CalcularEstatisticas();
private:
	std::string m_NomeDoSupermercado;
	ListaCircular<Caixa> m_listaDeCaixas;
	int m_relogioInterno; //tipo ciclos
	ListaCircular<Cliente> m_clientesDesistentes;
	int m_tamanhoMaximoFilas; //se TODOS os caixas estiverem com a fila desse tamanho ou mais deve-se contratar um novo caixa pagando em dobro a hora
	int m_tempoDeChegadaDoProximoCliente;
	int m_tempoMedioEmSegundosDeChegadaDeNovosClientes;
	int m_tempoTotalDeSimulacaoEmHoras;
	ListaCircular<Cliente> m_clientesAtendidos;
	void gerarCliente(bool caixasCheios);
	void buscarMenorFila(Cliente *novo);
	void buscarFilaComMenosProdutos(Cliente *novo);
};
/*
Gerar valores aleatorios com distribuição uniforme no intervalo 0 a 1, utilize as funções rand e srand.
Lembre-se de inicializar o sempre gerador de numeros aleatorios, antes de usar, para garantir de que sejam usados valores diferentes em cada simulação.
Para gerar um numero entre 0 e 1, voce precisa dividir o valor gerado por RAND_MAX, definido em stdlib.h.
Para gerar um numero aleatorio com distribuição uniforme em um intervalo, pegue este resultado, multiplique pelo tamanho do intervalo 
e adicione a valor do limite inferior do intervalo. 

Por exemplo: para gerar um valor aleatorio de compras entre 2 e 100, 
você pega o tamanho do intervalo, que é de 2 a 100 inclusive, logo 99 valores, 
e multiplica o seu numero aleatorio de 0 a 1 por 99. 
A seguir adiciona o limite inferior do intervalo, 2, ao resultado. 
Para que voce possa usar este numero ainda falta truncar, pegando so a parte inteira. Para isto basta fazer um typecasting: inteiro = (int) real;
*/