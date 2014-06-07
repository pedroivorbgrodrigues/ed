#include "stdafx.h"
#include "Supermercado.h"
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

/** @mainpage Projeto 
 *
 * @section intro_sec Instruções
 *
 * O sistema modela e simula um Supermercado. Fornecendo dados como o número de caixas empregados, assim como sua eficiência, e o tempo médio de chegada de novos clientes ao estabelecimento, o programa devolve estatísticas que permitem ao proprietário a cognição do número ideal de caixas para atender seus fregueses e os custos de operação de seu negócio, em função do faturamento gerado por cada um de seus funcionários.\n
 * Ao iniciar o sistema, o usuário poderá escolher entre ler um arquivo que contém as informações de seu supermercado, ou digitá-las manualmente.\n
 * Caso escolha ler um arquivo pré-existente, o nome do arquivo (incluindo extensão) deve ser digitado quando solicitado. É indispensável que o arquivo encontre-se na mesma pasta que o programa. Caso contrário ele não será encontrado. O sistema reconhece arquivos das extensões .dat e .txt.\n
 * O arquivo de leitura deve estar configurado seguindo o formato da Figura 1. Qualquer linha pode ser utilizada para escrever um comentário, bastando inicia-la com o caractere #.\n
 *  Os seguintes dados devem ser digitados, um por linha, mantendo a ordem:
 * - Nome do Supermercado.
 * - Tempo desejado de simulação, em horas.
 * - Tempo médio da chegada de novos clientes, em segundos.
 * - Número de caixas empregados.
 * - Nas linhas subsequentes, os dados dos caixas devem ser fornecidos, um por linha, separando as informações existentes por espaços.
 * - Identificação (espaço) eficiência (espaço) salário.
 * - Em eficiência, deve-se digitar 1 (caixa eficiente), 2 (caixa médio) ou 3 (caixa ruim).
 *.
 * @image html arquivo.png
 * \n
 * Se os dados forem fornecidos corretamente, ou o arquivo de leitura esteja corretamente redigido, o programa deve rodar sem a existência de erros.\n
 * Após o início da simulação, o programa gerará clientes a intervalos randômicos calculados com base na média do tempo de chegada fornecida. \n
 * Cada cliente compra um número variável de produtos com preços variáveis. Os clientes podem procurar uma fila com um número menor de pessoas, ou uma fila onde haja um número menor de produtos. Caso o supermercado esteja muito cheio, ou seja, haja 10 ou mais pessoas em cada fila, o cliente abandona suas compras, e o valor referente a elas é calculado como faturamento que se deixou de obter. Na ocasião de desistência de um cliente, o sistema assume a necessidade da adição de um novo caixa. Este caixa, no entanto, possui custo em dobro, devido ao caráter de urgência.\n
 * Ao final da execução, serão fornecidos detalhadamente os resultados da simulação, mostrando ao proprietário a contabilidade de seu negócio, possibilitando um melhor planejamento quanto ao número e quadro de funcionários.\n
 *\n\n\n\n
 * @section diagram Diagrama UML
 *\n
 * @image html SupermercadoPB.png
 */
using namespace std;

int tratarEntradaNumero(bool eficiencia = false)
{
	string entrada;
	bool entradaValida = true;
	int retorno;
	cin >> entrada;
	for (int i =0 ; i < entrada.length(); i++ )
	{
		if (!isdigit(entrada[i]))
		{
			entradaValida = false;
			break;
		}
	}
	if (entradaValida)
	{
		retorno = atoi(entrada.c_str());
		if (eficiencia)
		{
			if (retorno >= 1 && retorno <= 3)
			{
				return retorno;
			}
		}
		else return retorno;
	}
	cout << std::endl << "Entrada invalida! Digite um numero!" << std::endl;
	return tratarEntradaNumero();

}

inline bool arquivoExiste (const std::string& nomeArquivo) {
	ifstream f(nomeArquivo.c_str());
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}   
}

void menu(Supermercado** mercado)
{
	cout << "Digite 0 para fornecer o nome do arquivo de configuracao ou 1 para fornecer manualmente os parametros:" << endl;
	int op = tratarEntradaNumero();
	if (op == 0)
	{
		cout << "Digite o nome do arquivo de configuracao: (Este deve estar na mesma pasta do executavel)" << endl;
		string nomeArquivo;
		cin >> nomeArquivo;
		if (arquivoExiste(nomeArquivo))
		{
			std::string arquivoConfiguracao = "naocompre.dat";
			*mercado = new Supermercado(arquivoConfiguracao);
			return;
		}
		else
		{
			cout << "Arquivo inexistente ou corrompido!" << endl;
			menu(mercado);
		}
	}
	else
	{
		ListaCircular<std::string> identificadoresCaixas;
		ListaCircular<Caixa::Eficiencia> eficienciaCaixas;
		ListaCircular<double> salarioCaixas;
		cout << "Digite o nome do mercado:" << endl;
		string nomeMercado;
		cin >> nomeMercado;
		cout << "Digite o tempo total de simulação em horas:" << endl;
		int tempoTotalSimulacao = tratarEntradaNumero();
		cout << "Digite o tempo médio em segundos da chegada de novos clientes:" << endl;
		int tempoMedioClentes = tratarEntradaNumero();
		cout << "Digite o  numero de caixas:" << endl;
		int numeroDeCaixas = tratarEntradaNumero();
		for (int i = 0; i < numeroDeCaixas; i++)
		{
			cout << "Digite o nome do caixa:" << endl;
			string nomeCaixa;
			cin >> nomeCaixa;
			cout << "Digite a eficiencia do caixa, 1 para eficiente, 2 para medio, 3 para ruim:" << endl;
			Caixa::Eficiencia eficiencia = (Caixa::Eficiencia) tratarEntradaNumero(true);
			cout << "Digite o salario do caixa:" << endl;
			int salario = tratarEntradaNumero();
			identificadoresCaixas.adicionaNoFim(new string(nomeCaixa));
			eficienciaCaixas.adicionaNoFim(new Caixa::Eficiencia(eficiencia));
			salarioCaixas.adicionaNoFim(new double(salario));
		}	
		*mercado = new Supermercado(nomeMercado,&identificadoresCaixas,&eficienciaCaixas,&salarioCaixas,tempoMedioClentes,tempoTotalSimulacao,10);
	}	
}

int main() 
{
	srand(time(NULL));
	Supermercado* mercado;
	menu(&mercado);
	mercado->rodarSimulacao();	
	return 0;
}

