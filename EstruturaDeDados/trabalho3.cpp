#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ListaContabil.hpp"
#include "Lancamento.h"
#include <sstream>
#include <cstring>

using namespace std;

string listaAtualTexto = "Débitos";
char opcao;
string mensagem = "";
ListaContabil<Lancamento> listaCredito;
ListaContabil<Lancamento> listaDebito;
ListaContabil<Lancamento>* listaAtual = &listaDebito;

void listarTran() {
	if (listaAtual->EstruturaVazia())
		printf("Lista vazia! Impossível imprimir\n");
	else {
		for (int i = 0; i <= listaAtual->ObterIndiceTopo(); i++) {
			cout << i << " " << listaAtual->ObterLancamentoPelaPosicao(i);
		}
	}
}

void remTran() {
	string input = "";
	bool sair = false;
	int valor;
	while (!sair) {
		printf("Menu remover:\n\n"
				"(t) Remover todas as transações\n"
				"(r) Remover transação específica\n"
				"(s) Sair\n"
				"\nLista atual: %s \n", listaAtualTexto.c_str());
		listarTran();
		opcao = getchar();
		getchar();
		switch (opcao) {
		case 't':
			listaAtual->InicializaEstrutura();
			printf("Lista destruída!");
		   sair = true;
			break;
		case 'r':
			while (true) {
				printf("Entre com o número do lançamento:\n");
				getline(cin, input);
				stringstream myStream(input);
				if (myStream >> valor)
					if (valor >= 0 && valor <= listaAtual->ObterIndiceTopo())
						break;
				printf(						"Número inválido... Entre com um"
								" número válido, inteiro, maior ou igual a 0 e menor ou igual a %i !\n",
						listaAtual->ObterIndiceTopo());
			}
			try
			{
				listaAtual->RetiraDaPosicao(valor);
				printf("Lancamento removido com sucesso!\n");
			}
			catch (invalid_argument& e)
			{
				printf("Se você chegou aqui o progamador é um burro!");
			}
			sair = true;
			break;
		case 's':
			printf(
					"Você saiu do menu de remoção.");
			sair = true;
			break;
		default:
			printf("Opção inválida");
		}
	}
}

void lancarTran() {
	string nome = "";
	double valor;
	string input = "";

	printf("Entre com o nome do lançamento:\n");
	getline(cin, nome);
	while (true) {

		printf("Entre com o valor do lançamento:\n");
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> valor)
			if (valor > 0)
				break;

		printf("Número inválido... Entre com um"
				" número válido, real, maior ou igual a 0 !\n");

	}
   /*
   ATENCAO: Voce tem que garantir que o char * recebido do string nome
   tem que ser tratado no construtor do lançamento para ocupar o menor
   espaço em memoria possivel. Isso vale 1 ponto na nota do trabalho!
   */
	Lancamento lan = Lancamento(nome, valor);
	try
	{
		listaAtual->AdicionaDado(lan);
		printf("Lancamento adicionado com sucesso!");
	}
	catch (overflow_error& e)
	{
		printf("Impossível adicionar nova transação! Erro de lista cheia!");
	}
}

void mostraSaldo() {
	double tCredito = 0;
	double tDebito = 0;

	for (int i = 0; i <= listaCredito.ObterIndiceTopo(); i++)
		tCredito += listaCredito.ObterLancamentoPelaPosicao(i).Valor();
	for (int i = 0; i <= listaDebito.ObterIndiceTopo(); i++)
		tDebito += listaDebito.ObterLancamentoPelaPosicao(i).Valor();

	printf("\nTotal (Créditos - Débitos): \n     %.2f", tCredito - tDebito);
}
int main() {
    
	bool sair = false;

	while (!sair) {
     

		printf("\n Menu:\n"
				"(c) Seleciona Lista de Créditos\n"
				"(d) Seleciona Lista de Débitos\n"
				"(l) Lançar Transação\n"
				"(t) Listar Transações\n"
				"(r) Remover Transações\n"
				"(s) Mostar Saldo (total créditos - total de débitos)\n"
				"(q) Sair do Programa\n"
				"\nLista atual: %s \n%s\n", listaAtualTexto.c_str(),
				mensagem.c_str());

		opcao = getchar();
		getchar(); 
		switch (opcao) {
		case 'c':
			mensagem = "";
			listaAtualTexto = "Créditos";
			listaAtual = &listaCredito;
			break;
		case 'd':
			mensagem = "";
			listaAtualTexto = "Débitos";
			listaAtual = &listaDebito;
			break;
		case 'l':
			mensagem = "";
			lancarTran();
			break;
		case 't':
			listarTran();
			break;
		case 'r':
			remTran();
			break;
		case 's':
			mostraSaldo();
			break;
		case 'q':
			sair = true;
			break;
		default:
			mensagem = "\nOpção inválida selecione uma"
					" das opções listadas acima!";
		} 
	}

}

