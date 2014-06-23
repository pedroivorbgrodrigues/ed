#pragma once
#include "NodoArvore.h"
#include <string>
#include <vector>
#include <utility>
#include <windows.h> 


typedef NodoArvore<int, std::string> VNodo;
class Arvore
{
public:
	Arvore()
	{
		this->m_raiz = NULL;
		this->qtdadeDeElementosNaArvore = 0;
		QueryPerformanceFrequency(&frequency);
	}
	~Arvore()
	{
		this->Limpar();
	}
	virtual VNodo * inserir(VNodo *&raizAtual, std::string nomeInformado, int cepInformado)=0;
	virtual VNodo * remover(VNodo *&raizAtual, int cepInformado)=0;
	void IniciarContagemDeTempo()
	{
		QueryPerformanceCounter(&t1);
	}
	void FinalizarContagemDeTempo()
	{
		double tempoInsercao;
		QueryPerformanceCounter(&t2);
		tempoInsercao = (t2.QuadPart - t1.QuadPart) * 1000000.0 / frequency.QuadPart;
		temposOperacoes.push_back(std::make_pair<int,double>(qtdadeDeElementosNaArvore,tempoInsercao));
	}

	void emOrdemRec(VNodo *r,VNodo* emOrd,int& pos)
	{
		if(r != NULL)
		{
			emOrdemRec(r->subArvore[ESQUERDA],emOrd,pos);		
			emOrd[pos++] = *r;
			emOrdemRec(r->subArvore[DIREITA],emOrd,pos);
		}	
	}
	virtual VNodo * emOrdem(VNodo *raizAtual)
	{
		VNodo* emOrd = new VNodo[this->qtdadeDeElementosNaArvore];
		int posInicial = 0;
		emOrdemRec(this->m_raiz,emOrd,posInicial);
		return emOrd;
	}

	void posOrdemRec(VNodo *r,VNodo* posOrd,int& pos)
	{
		if(r != NULL)
		{
			posOrdemRec(r->subArvore[ESQUERDA],posOrd,pos);		
			posOrdemRec(r->subArvore[DIREITA],posOrd,pos);
			posOrd[pos++] = *r;
		}	
	}

	virtual VNodo * posOrdem(VNodo *raizAtual)
	{
		VNodo* posOrd = new VNodo[this->qtdadeDeElementosNaArvore];
		int posInicial = 0;
		posOrdemRec(this->m_raiz,posOrd,posInicial);
		return posOrd;
	}

	void preOrdemRec(VNodo *r,VNodo* preOrd,int& pos)
	{
		if(r != NULL)
		{
			preOrd[pos++] = *r;
			preOrdemRec(r->subArvore[ESQUERDA],preOrd,pos);		
			preOrdemRec(r->subArvore[DIREITA],preOrd,pos);
		}	
	}

	virtual VNodo * preOrdem(VNodo *raizAtual)
	{
		VNodo* preOrd = new VNodo[this->qtdadeDeElementosNaArvore];
		//VNodo** preOrd = new VNodo*[this->qtdadeDeElementosNaArvore];
		//seria dessa maneira, com as devidas altera��es de assinatura do metodo recursivo e da interface de arvore
		int posInicial = 0;
		preOrdemRec(this->m_raiz,preOrd,posInicial);
		return preOrd;
	}

	virtual std::vector<std::pair<int,double>>* obterTemposArvore()
	{
		return &temposOperacoes;
	}
	virtual void Limpar()
	{
		delete m_raiz;
		this->m_raiz = NULL;
		temposOperacoes.clear();
	}
	VNodo* m_raiz;
	int qtdadeDeElementosNaArvore;
	std::vector<std::pair<int,double>> temposOperacoes;
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
 };
/*
Observa��o sobre os 3 m�todos que retorn�o um array de nodos:
Como a quantidade de nodos � definida em tempo de exceu��o para respeitar a assinatura definida no moodle,
criamos um construtor padr�o para a classe VNodo para que o array possa ser inicializado dinamicamente.
A outra alternativa seria um ponteiro para um array de nodos, oq n�o alteraria a modelagem natural da classe VNodo(sem construtor padr�o no caso)
Deixamos o c�digo comentado

Observa��o sobre a mudan�a da assinatura dos metodos inserir e remover: 
VNodo *&raizAtual
caso n�o se passe um ponteiro para ponteiro ao se anular a raiz a referencia n�o seria atualizada.

Observa��o sobre a contagem de tempo:
Utilizamos a biblioteca de contagem de tempo do windows devido a problemas de precis�o usando a ctime, e a nossa IDE n�o ter suporte a biblioteca chrono.
*/