/*
Ponteiros void
Random
Leitura de arquivos
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "ListaEncadeada.h"
using namespace std;

class Cliente{
public:
	bool cheque;
	int itens;
	int total;
	Cliente(bool c, int i, int t){
		cheque = c;
		itens = i;
		total = t;
	}
};

class Caixa{
	char nome[80];
	int desempenho;
	int salario;
	float faturamentoTotal;
	float faturamentoMedio;
	//ListaEncadeada<Cliente> clientes;//Aqui é pra ser usada uma fila!
public:
	Caixa(char *n, int d, int s){
		strncpy(nome,n,80);
		desempenho = d;
		salario = s;
	}
};

class Evento{
public:
	int tempo;
	int tipo;
	void *objeto;
	Evento(int t, void* o, int tipo){
		tempo = t;
		objeto = o;
		this->tipo = tipo;
	}
	int valor(){
		return tempo;
	}
};

int main() {
	char nomeMercado[100], *sub, nomeCaixa[80];
	int tempoDeSimulacao, tempoMedioClients, nCaixas, eficiencia, salario, tempoDecorrido, tEvento;
	char linha[200];
	bool comentarios = true;
	Cliente *cliente;
	Caixa *caixa;
	Evento *evento;
	ListaEncadeada<Caixa> caixas;
	ListaEncadeada<Evento> eventos;

	ifstream arquivo("naocompre.dat");

	while (comentarios){
		arquivo.getline(linha,200);
		if (linha[0]=='#'){
//			cout << linha << endl;
		} else {
			comentarios = false;
		}
	}
	strncpy(nomeMercado,linha,100);

	arquivo >> tempoDeSimulacao;
	arquivo >> tempoMedioClients;
	arquivo >> nCaixas;

	cout << "Nome do Supermercado: " << nomeMercado << endl;
	cout << "Tempo de Simulação: " << tempoDeSimulacao << " horas" << endl;
	cout << "Tempo médio de chegada de clientes: " << tempoMedioClients << " segundos" << endl;
	cout << "Número de caixas: " << nCaixas << endl;

	arquivo.getline(linha,200);

	for (int i = 0; i < nCaixas; i++){
		arquivo.getline(linha,200);
		sub = strtok(linha, " ");
		strncpy(nomeCaixa,sub,80);
		sub = strtok(NULL, " ");
		eficiencia = atoi(sub);
		sub = strtok(NULL, " ");
		salario = atoi(sub);
		caixa = new Caixa(nomeCaixa,eficiencia,salario);
		caixas.adiciona(caixa);
	}

	tempoDecorrido = 0;

	srand((unsigned)time(NULL));

	tEvento  = int((double(rand())/RAND_MAX)*tempoMedioClients) + tempoMedioClients/2;

	int compras = int((double(rand())/RAND_MAX)*99) + 2;
	//mais numeros aleatorios para os preços dos produtos, só é necessário o total
	//gera e soma em um total

	eventos.adiciona(new Evento(tEvento,new Cliente(false,compras,987),1));
	evento = eventos.retira();
	tempoDecorrido = evento->tempo;
	while (tempoDecorrido <= tempoDeSimulacao*1200){ // multiplica por 1200 pois é em horas
		if (evento->tipo == 1){
			cliente = (Cliente*) evento->objeto;
			cout << cliente->cheque << "|" << cliente->itens << "|"<< cliente->total << endl;
			// se evento de chegada de cliente, cria outro evento de chegada e adiciona na fila de acordo com as regras
			// se não houver nenhum cliente na fila, já calcula o tempo de saída do cliente que acabou de entrar
		} else {
			caixa = (Caixa*) evento->objeto;
			// se evento de saida em um caixa, calcula o faturamento e tals e já calcula a próxima saida do caixa, se tiver cliente na fila
		}
		if (!eventos.listaVazia()){
		evento = eventos.retira();
		tempoDecorrido = evento->tempo;
		} else {
			tempoDecorrido = tempoDeSimulacao*1200 + 1;
		}


	}

	return 0;
}
