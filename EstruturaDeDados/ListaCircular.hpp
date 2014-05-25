#ifndef LISTACIRCULAR_HPP_
#define LISTACIRCULAR_HPP_
#include <stdlib.h>
#include <stdexcept>
#include "tElemento.hpp"
#include "FilaEncadeada.hpp"

template<class T>
class ListaCircular: public FilaEncadeadaCircular<T> {
public:
	ListaCircular() {
		criaEstrutura();
	}
	~ListaCircular() {
		destroiEstrutura();
	}
	T* retiraDoInicio() {
		return retira();
	}
	int adicionaNoFim(T *dado) {
		return adiciona(dado);
	}
	T* retiraDoFim() {
		tElemento<T> *eliminar, *anterior;
		T* volta;
		if (this->tamanho == 1)
			throw std::underflow_error("Lista vazia!");
		tamanho--;
		eliminar = this->sentinela->getAnterior();
		anterior = eliminar->getAnterior();
		this->sentinela->setAnterior(anterior);
		anterior->setProximo(this->sentinela);
		volta = eliminar->getInfo();
		eliminar->setAnterior(NULL);
		eliminar->setProximo(NULL);
		eliminar->setInfo(NULL);
		delete (eliminar);
		return volta;
	}
	tElemento<T>* obterProximoDecrescente(int posicao) {
		tElemento<T> *proximo;
		proximo = this->sentinela;
		for (int i = 0; i < this->tamanho - posicao; i++)
			proximo = proximo->getAnterior();
		return proximo;
	}
	tElemento<T>* obterAnteriorCrescente(int posicao) {
		tElemento<T> *anterior;
		anterior = this->sentinela;
		for (int i = 0; i < posicao - 1; i++)
			anterior = anterior->getProximo();
		return anterior;
	}
	int adicionaNaPosicao(T *info, int posicao) {
		tElemento<T> *novo, *anterior, *proximo;
		if (posicao > (this->tamanho + 1))
			throw std::runtime_error("Posição inválida!");
		if (posicao == 1)
			return adicionaNoInicio(info);
		if (posicao == this->tamanho)
			return adicionaNoFim(info);
		novo = new tElemento<T>();
		if (novo == NULL)
			throw std::overflow_error("Lista cheia!");
		switch (posicao > this->tamanho / 2) {
		case true:
			proximo = obterProximoDecrescente(posicao);
			anterior = proximo->getAnterior();
			break;
		case false:
			anterior = obterAnteriorCrescente(posicao);
			proximo = anterior->getProximo();
			break;
		}
		novo->setProximo(proximo);
		novo->setAnterior(anterior);
		novo->setInfo(info);
		anterior->setProximo(novo);
		proximo->setAnterior(novo);
		this->tamanho = (this->tamanho + 1);
		return this->tamanho;
	}

	T* retiraDaPosicao(int posicao) {
		tElemento<T> *anterior, *proximo, *eliminar;
		T *volta;
		if (posicao > this->tamanho)
			throw std::runtime_error("Posição inválida!");
		if (posicao == 1)
			return retiraDoInicio();
		if (posicao == this->tamanho)
			return retiraDoFim();
		tamanho--;
		switch (posicao > this->tamanho / 2) 
		{
		case true:
			eliminar = obterProximoDecrescente(posicao);
			anterior = eliminar->getAnterior();
			proximo = eliminar->getProximo();
			break;
		case false:
			anterior = obterAnteriorCrescente(posicao);
			eliminar = anterior->getProximo();
			proximo = eliminar->getProximo();
			break;
		}
		anterior->setProximo(proximo);
		proximo->setAnterior(anterior);
		volta = eliminar->getInfo();
		eliminar->setAnterior(NULL);
		eliminar->setInfo(NULL);
		eliminar->setProximo(NULL);
		delete (eliminar);
		return volta;
	}
};
#endif
