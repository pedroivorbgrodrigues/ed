#include <iostream>
#include <time.h>
#include <string.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctime>
using namespace std;
//# Concatenar todos os ceps em um
// cat df.cep sc.cep sp.cep > todos.cep

//# Gerar dados para gnuplot
// ./a.out > dados.dat

//# GnuPlot
// gnuplot
// plot "dados.dat"

// Listar todos os nomes em ordem?
long diferencaDeTempo(timeval inicio, timeval fim) {
	long diferenca, segundos, usegundos;

	segundos = fim.tv_sec - inicio.tv_sec;
	usegundos = fim.tv_usec - inicio.tv_usec;

	diferenca = segundos * 1000000 + usegundos;
	return diferenca;
}

timeval tempo() {
	timeval tempo;
	gettimeofday(&tempo, NULL);
	return tempo;
}

class Cep {
	char nome[200];
	int cep;
};

int main(int argc, char *argv[]) {
	timeval inicio, fim;
	char linha[200], *nome;
	int cep, numero = 0;
	long dif;
//	ifstream arquivo("todos.cep");
	ifstream arquivo(argv[1]);

	while (!arquivo.eof()) {
		bool teste = arquivo.eof();
		inicio = tempo();
		arquivo.getline(linha, 200);
		numero = numero + 1;
		nome = strtok(linha, "|");
		if (linha[0] != 0){
			cep = atoi(strtok(linha, "|"));
		}
		//insere na árvore
		fim = tempo();
		cout << numero << " " << diferencaDeTempo(inicio, fim) << endl;
	}

	return 0;
}
