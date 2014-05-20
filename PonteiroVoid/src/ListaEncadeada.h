#ifndef LISTAENCADEADA_H_
#define LISTAENCADEADA_H_
#include "Nodo.h"
#include "Excecoes.h"
#include <iostream>
#include <fstream>
using namespace std;
template<class T>
class ListaEncadeada {
	Nodo<T> *cabeca;
	int tamanho;
public:
	ListaEncadeada();
	virtual ~ListaEncadeada();
	int adiciona(T*);
	T* retira();
	void imprimir();
	bool listaVazia();
	friend ostream& operator<<(ostream& stream, const ListaEncadeada &l){
		Nodo<T>* auxiliar = l.cabeca;
		for (int i = 1; i <= l.tamanho; i++) {
			printf("Dado[%d] = ", i);
			cout << *auxiliar << endl;;
			auxiliar = auxiliar->proximo;
		}
		return stream;
	};
};

template<class T>
ListaEncadeada<T>::ListaEncadeada() {
	tamanho = 0;
	cabeca = 0;
}

template<class T>
ListaEncadeada<T>::~ListaEncadeada() {
	Nodo<T>* atual = cabeca;
	while( atual != 0 ) {
	    Nodo<T>* proximo = atual->proximo;
	    delete atual;
	    atual = proximo;
	}
	cabeca = 0;
}
template<class T>
int ListaEncadeada<T>::adiciona(T *dado) {
	Nodo<T> *novo = new Nodo<T>();
	novo->proximo = cabeca;
	novo->info = dado;
	cabeca = novo;
	tamanho++;
	return tamanho;

}
template<class T>
T* ListaEncadeada<T>::retira() {
	Nodo<T> *saiu;
	T *retorno;
	if (listaVazia())
		throw ExcecaoListaVazia();

	saiu = cabeca;
	retorno = saiu->info;
	cabeca = saiu->proximo;
	tamanho--;
	delete (saiu);
	return retorno;
}

template<class T>
void ListaEncadeada<T>::imprimir() {

}

template<class T>
bool ListaEncadeada<T>::listaVazia(){
	return tamanho == 0;
};

#endif /* LISTAENCADEADA_H_ */
