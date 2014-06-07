#ifndef FILAENCADEADA_HPP_
#define FILAENCADEADA_HPP_
#include <stdlib.h>
#include <stdexcept>
#include "tElemento.hpp"
#define ERROLISTACHEIA -1
#define ERROLISTAVAZIA -2
#define ERROPOSICAO -3

/**
*@brief  Implementação da estrutura de dado fila encadeada circular
*/

template<class T>
class FilaEncadeadaCircular {
protected:
	tElemento<T> *sentinela;
	int tamanho;
public:
	FilaEncadeadaCircular() {
		criaEstrutura();
	}
	~FilaEncadeadaCircular() {
		destroiEstrutura();
	}
	/**
	*  Inicialização da estrutura
	*/
	void criaEstrutura() 
	{
			this->tamanho = 1;
			this->sentinela = new tElemento<T>();
			this->sentinela->setProximo(sentinela);
			this->sentinela->setAnterior(sentinela);
	}

	/**
	*  Retorna se a estrutura encontra-se vazia
	*/
	bool estruturaVazia() {
		if (this->tamanho == 1)
			return true;
		return false;
	}

	/**
	*  Adiciona um novo elemento no final da estrutura
	*/
	int adiciona(T *dado) {
		tElemento<T> *novo, *anterior;
		novo = new tElemento<T>();
		if (novo == NULL)
			throw std::overflow_error("Lista cheia!");
		anterior = this->sentinela->getAnterior();
		novo->setProximo(sentinela);
		this->sentinela->setAnterior(novo);
		novo->setAnterior(anterior);
		anterior->setProximo(novo);
		novo->setInfo(dado);
		this->tamanho = (this->tamanho + 1);
		return this->tamanho;
	}

	/**
	*  Remove o primeiro elemento adiciona na estrutura
	*/
	T* retira() {
		tElemento<T> *eliminar, *proximo;
		T* volta;
		if (this->tamanho == 1)
			throw std::underflow_error("Lista vazia!");
		tamanho--;
		eliminar = this->sentinela->getProximo();
		proximo = eliminar->getProximo();
		this->sentinela->setProximo(proximo);
		proximo->setAnterior(this->sentinela);
		eliminar->setAnterior(NULL);
		eliminar->setProximo(NULL);
		volta = eliminar->getInfo();
		eliminar->setInfo(NULL);
		return volta;
	}

	/**
	*  Adiciona um novo elemento no início da estrutura
	*/
	int adicionaNoInicio(T *dado) {
		tElemento<T> *novo, *proximo;
		novo = new tElemento<T>();
		if (novo == NULL)
			throw std::overflow_error("Lista cheia!");
		proximo = this->sentinela->getProximo();
		novo->setProximo(proximo);
		proximo->setAnterior(novo);
		novo->setAnterior(this->sentinela);
		this->sentinela->setProximo(novo);
		novo->setInfo(dado);
		this->tamanho = this->tamanho + 1;
		return this->tamanho;
	}

	/**
	*  Retorna o elemento no topo da estrutura
	*/
	T obterTopo() {
		return this->sentinela->getAnterior()->getInfo();
	}

	/**
	*  Retorna o tamanho da estrutura
	*/
	int obterTamanho() {
		return this->tamanho-1;
	}

	/**
	*  Reinicializa a estrutura
	*/
	void destroiEstrutura() {
		/*
		tElemento<T> *atual, *anterior;
		atual = this->sentinela;
		while (atual != NULL) {
			anterior = atual;
			atual = atual->getProximo();
			delete (anterior->getInfo());
			delete (anterior);
		}
		this->tamanho = 0;
		*/
	}
};
#endif
