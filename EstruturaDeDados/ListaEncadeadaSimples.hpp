#pragma once
#include <exception>
#include <string>
#include <stdio.h>
#include "NodoLista.hpp"

template<class T>
class ListaEncadeadaSimples
{
public:
	ListaEncadeadaSimples(void)
	{
		InicializaEstrutura();
	}
	~ListaEncadeadaSimples(void)
	{

	}

	void InicializaEstrutura()
	{
		tamanho = -1;
	}

	void LimpaEstrutura()
	{
		tamanho = -1;
		NodoLista<T>* antigoInicial = nodoInicial;
		nodoInicial = nullptr;
		delete antigoInicial;
	}

	bool EstruturaVazia()
	{
		return tamanho == -1;
	}

	NodoLista<T>* UltimoElemento()
	{
		NodoLista<T>* iterator = nodoInicial;
		while(!iterator&&!(iterator->Proximo()))//diferente de null
		{
			iterator = iterator->Proximo();
		}
		return iterator;
	}

	int AdicionaDado(T* dado)
	{
		NodoLista<T>* novo = new NodoLista<T>(dado);
		if(EstruturaVazia())
			nodoInicial = novo;
		else
		{
			NodoLista<T>* ultimo = UltimoElemento();
			ultimo->setProximo(novo);
		}
		tamanho++;		
		return tamanho;
	}

	virtual T* RemoveDado()
	{
		if(EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		tamanho--;
		return RetiraDaPosicao(tamanho);
	}

	T* ObterTopo()
	{
		if(EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		return UltimoElemento()->Elemento();
	}

	int ObterIndiceTopo()
	{
		return tamanho;
	}

	void ImprimirVetor()
	{
		if(EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		/*
		for (int i = 0; i <= tamanho; i++)
		{
			printf("%i %i\n", i, m_dados[i]);
		}
		*/
	}

	T* ObterDadoPelaPosicao(int i)
	{
		NodoLista<T>* iterator = nodoInicial;
		int indiceAtual = 0;
		while(!iterator&&!(iterator->Proximo()) && indiceAtual < i)//diferente de null
		{
			iterator = iterator->Proximo();
		}
		return iterator->Elemento();
	}

	NodoLista<T>* ObterNodoAnteriorAPosicao(int i)
	{
		NodoLista<T>* iterator = nodoInicial;
		int indiceAtual = 0;
		while(!iterator&&!(iterator->Proximo()) && indiceAtual < i-1)//diferente de null
		{
			iterator = iterator->Proximo();
		}
		return iterator;
	}

	int AdicionaNoInicio(T* dado)
	{
		tamanho++;
		NodoLista<T>* novo = new NodoLista<T>(dado,nodoInicial);
		nodoInicial = novo;
		return tamanho;
	}

	T RetiraDoInicio()
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		NodoLista<T>* antigoInicial = nodoInicial;
		nodoInicial = nodoInicial->Proximo();
		antigoInicial->setProximo(null);
		return antigoInicial->Elemento();
	}

	int AdicionaNaPosicao(T* dado, int destino)
	{
		if (destino > tamanho+1)
			throw std::invalid_argument("Posicao invalida");
		tamanho++;
		
		NodoLista<T>* anteriorAoDestino = ObterNodoAnteriorAPosicao(destino);
		NodoLista<T>* novo = new NodoLista<T>(dado,anteriorAoDestino->Proximo());
		anteriorAoDestino->setProximo(novo);
		return tamanho;
	}

	T* RetiraDaPosicao(int fonte)
	{
		if (fonte > tamanho || fonte < 0)
			throw std::invalid_argument("Posicao invalida");
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		tamanho--;
		NodoLista<T>* anteriorAoDestino = ObterNodoAnteriorAPosicao(fonte);
		NodoLista<T>* nodoARetirar = anteriorAoDestino->Proximo();
		anteriorAoDestino->setProximo(anteriorAoDestino->Proximo()->Proximo());
		nodoARetirar->setProximo(nullptr);
		return nodoARetirar->Elemento();
	}

	bool maior(T* dado1, T* dado2)
	{
		return *dado1 > *dado2;
	}

	bool igual(T* dado1, T* dado2)
	{
		return *dado1 == *dado2;
	}

	int AdicionaEmOrdem(T* dado)
	{
		NodoLista<T>* iterator = nodoInicial;
		NodoLista<T>* anterior = iterator;
		int indiceAtual = 0;
		while(!iterator&&!(iterator->Proximo()) && maior(dado,iterator->Elemento()))//diferente de null
		{
			anterior = iterator;
			iterator = iterator->Proximo();
		}	
		NodoLista<T>* novo = new NodoLista<T>(dado,iterator->Proximo());
		anteriorAoDestino->setProximo(novo);
		return tamanho;
	}


	T RetiraEspecifico(T* dado)
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");

		NodoLista<T>* iterator = nodoInicial;
		NodoLista<T>* anterior = iterator;
		while(!iterator && !(iterator->Proximo()) && !igual(dado,iterator->Elemento()))//diferente de null
		{
			anterior = iterator;
			iterator = iterator->Proximo();
		}
		if (iterator->Proximo() && !igual(dado,iterator->Elemento()))
			throw std::invalid_argument("Elemento inexistente!");
		NodoLista<T>* nodoARetirar = anterior->Proximo();
		anteriorAoDestino->setProximo(anterior->Proximo()->Proximo());
		nodoARetirar->setProximo(null);
	}

protected:
	int tamanho;
	NodoLista<T>* nodoInicial;

};

#pragma once
