#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "ListaContabil.hpp"
#include "Lancamento.h"
#include <sstream>
#include <cstring>

using namespace std;

string listaAtualTexto = "D�bitos";
char opcao;
string mensagem = "";
ListaContabil<Lancamento> listaCredito;
ListaContabil<Lancamento> listaDebito;
ListaContabil<Lancamento>* listaAtual = &listaDebito;

void listarTran() {
	if (listaAtual->EstruturaVazia())
		printf("Lista vazia! Imposs�vel imprimir\n");
	else {
		for (int i = 0; i <= listaAtual->ObterIndiceTopo(); i++) {
			printf("(%i) %s %.2f\n", i, ((*listaAtual).mostra(i).nome()),
					(*listaAtual).mostra(i).valor());
		}
	}
}

void remTran() {
	string input = "";
	bool sair = false;
	int valor;
	while (!sair) {
		printf("Menu remover:\n\n"
				"(t) Remover todas as transa��es\n"
				"(r) Remover transa��o espec�fica\n"
				"(s) Sair\n"
				"\nLista atual: %s \n", listaAtualTexto.c_str());
		listarTran();
		opcao = getchar();
		getchar();
		switch (opcao) {
		case 't':
			listaAtual->destroiLista();
			printf("Lista destru�da!");
		   sair = true;
			break;
		case 'r':
			while (true) {
				printf("Entre com o n�mero do lan�amento:\n");
				getline(cin, input);
				stringstream myStream(input);
				if (myStream >> valor)
					if (valor >= 0 && valor <= listaAtual->verUltimo())
						break;
				printf(
						"N�mero inv�lido... Entre com um"
								" n�mero v�lido, inteiro, maior ou igual a 0 e menor ou igual a %i !\n",
						listaAtual->verUltimo());
			}
			if (listaAtual->retiraDaPosicao(valor) == ERROPOSICAOLAN)
				printf("Se voc� chegou aqui o progamador � um burro!");
			else
				printf("Lancamento removido com sucesso!\n");
			sair = true;
			break;
		case 's':
			printf(
					"Voc� saiu do menu de remo��o.");
			sair = true;
			break;
		default:
			printf("Op��o inv�lida");
		}
	}
}

void lancarTran() {
	string nome = "";
	double valor;
	string input = "";

	printf("Entre com o nome do lan�amento:\n");
	getline(cin, nome);
	while (true) {

		printf("Entre com o valor do lan�amento:\n");
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> valor)
			if (valor > 0)
				break;

		printf("N�mero inv�lido... Entre com um"
				" n�mero v�lido, real, maior ou igual a 0 !\n");

	}
   /*
   ATENCAO: Voce tem que garantir que o char * recebido do string nome
   tem que ser tratado no construtor do lan�amento para ocupar o menor
   espa�o em memoria possivel. Isso vale 1 ponto na nota do trabalho!
   */
	Lancamento lan = Lancamento((char *)nome.c_str(), valor);
	if (listaAtual->adiciona(lan) == ERROLISTACHEIA) {
		printf("Imposs�vel adicionar nova transa��o! Erro de lista cheia!");

	} else
		printf("Lancamento adicionado com sucesso!");
	}

void mostraSaldo() {
	double tCredito = 0;
	double tDebito = 0;

	for (int i = 0; i <= listaCredito.verUltimo(); i++)
		tCredito += listaCredito.verTrasacao(i).valor();
	for (int i = 0; i <= listaDebito.verUltimo(); i++)
		tDebito += listaDebito.verTrasacao(i).valor();

	printf("\nTotal (Cr�ditos - D�bitos): \n     %.2f", tCredito - tDebito);
}
int main() {
    
	bool sair = false;

	while (!sair) {
     

		printf("\n Menu:\n"
				"(c) Seleciona Lista de Cr�ditos\n"
				"(d) Seleciona Lista de D�bitos\n"
				"(l) Lan�ar Transa��o\n"
				"(t) Listar Transa��es\n"
				"(r) Remover Transa��es\n"
				"(s) Mostar Saldo (total cr�ditos - total de d�bitos)\n"
				"(q) Sair do Programa\n"
				"\nLista atual: %s \n%s", listaAtualTexto.c_str(),
				mensagem.c_str());

		opcao = getchar();
		getchar(); 
		switch (opcao) {
		case 'c':
			mensagem = "";
			listaAtualTexto = "Cr�ditos";
			listaAtual = &listaCredito;
			break;
		case 'd':
			mensagem = "";
			listaAtualTexto = "D�bitos";
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
			mensagem = "\nOp��o inv�lida selecione uma"
					" das op��es listadas acima!";
		} 
	}

}

