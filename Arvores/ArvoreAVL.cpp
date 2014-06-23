#include "ArvoreAVL.h"
#include <fstream>
#include <iostream>

inline DIRECAO ArvoreAVL::oposto(DIRECAO dir)
{
	return (dir == DIREITA) ? ESQUERDA : DIREITA;
}

void ArvoreAVL::rotacionarUmaVez(VNodo*& nodo, DIRECAO dir)
{
	int oposto = this->oposto(dir);

	VNodo* child = nodo->subArvore[dir];
	nodo->subArvore[dir] = child->subArvore[oposto];
	child->subArvore[oposto] = nodo;

	nodo = child;
}

void ArvoreAVL::rotacionarDuasVezes(VNodo*& nodo, DIRECAO dir)
{
	int oposto = this->oposto(dir);

	VNodo* child = nodo->subArvore[dir]->subArvore[oposto];
	nodo->subArvore[dir]->subArvore[oposto] = child->subArvore[dir];
	child->subArvore[dir] = nodo->subArvore[dir];
	nodo->subArvore[dir] = child;
	child = nodo->subArvore[dir];
	nodo->subArvore[dir] = child->subArvore[oposto];
	child->subArvore[oposto] = nodo;

	nodo = child;
}

void ArvoreAVL::atualizarBalanceamento(VNodo* nodo, DIRECAO dir)
{
	int oposto = this->oposto(dir);

	int bal = nodo->subArvore[dir]->subArvore[oposto]->fatorBalanceamento;

	if (bal == dir)
	{
		nodo->fatorBalanceamento = IGUAL;
		nodo->subArvore[dir]->fatorBalanceamento = oposto;
	}
	else if (bal == oposto)
	{
		nodo->fatorBalanceamento = dir;
		nodo->subArvore[dir]->fatorBalanceamento = IGUAL;
	}
	else
		nodo->fatorBalanceamento = nodo->subArvore[dir]->fatorBalanceamento = IGUAL;

	nodo->subArvore[dir]->subArvore[oposto]->fatorBalanceamento = IGUAL;
}

void ArvoreAVL::rebalancearInsercao(VNodo*& nodo, DIRECAO dir, bool& alturaFoiAlterada)
{
	int oposto = this->oposto(dir);

	if (nodo->fatorBalanceamento == dir)
	{                        
		if (nodo->subArvore[dir]->fatorBalanceamento == dir)
		{
			nodo->subArvore[dir]->fatorBalanceamento = 2;
			nodo->fatorBalanceamento = IGUAL;
			rotacionarUmaVez(nodo, dir);
		}
		else
		{   

			atualizarBalanceamento(nodo, dir);
			rotacionarDuasVezes(nodo, dir);
		}

		alturaFoiAlterada = false;
	}
	else if (nodo->fatorBalanceamento == oposto)
	{
		nodo->fatorBalanceamento = 2;
		alturaFoiAlterada = false;
	}
	else
	{
		nodo->fatorBalanceamento = dir;
	}
}

void ArvoreAVL::rebalancearRemovocao(VNodo*& nodo, DIRECAO dir,bool& alturaFoiAlterada)
{
	DIRECAO oposto = this->oposto(dir);

	if (nodo->fatorBalanceamento == dir)
		nodo->fatorBalanceamento = IGUAL;
	else if (nodo->fatorBalanceamento == oposto)
	{
		if (nodo->subArvore[oposto]->fatorBalanceamento == oposto)
		{
			nodo->subArvore[oposto]->fatorBalanceamento = IGUAL;
			nodo->fatorBalanceamento = IGUAL;
			rotacionarUmaVez(nodo, oposto);
		}
		else if (nodo->subArvore[oposto]->fatorBalanceamento == IGUAL)
		{
			nodo->subArvore[oposto]->fatorBalanceamento = dir;
			rotacionarUmaVez(nodo, oposto);
		}
		else
		{
			atualizarBalanceamento(nodo, oposto);
			rotacionarDuasVezes(nodo, oposto);
		}

		alturaFoiAlterada = false;
	}
	else
	{
		nodo->fatorBalanceamento = oposto;
		alturaFoiAlterada = false;
	}
}



VNodo* ArvoreAVL::inserir(VNodo*& raiz,std::string valor, int chave)
{
	IniciarContagemDeTempo();
	VNodo* inserido;
	bool alturaFoiAlterada = false;
	inserido = this->insert(chave, valor, raiz, alturaFoiAlterada);
	qtdadeDeElementosNaArvore++;
	FinalizarContagemDeTempo();	
	return inserido;
}


VNodo* ArvoreAVL::insert(int chave, const std::string& valor,VNodo*& nodo, bool& alturaFoiAlterada)
{
	VNodo* inserido;
	if (nodo == NULL)
	{
		nodo = new VNodo(chave, valor);
		alturaFoiAlterada = true;
		inserido = nodo;
	}
	else if (nodo->chave == chave)
	{
		return nodo;
	}
	else
	{
		DIRECAO dir = (chave > nodo->chave) ? DIREITA : ESQUERDA;

		alturaFoiAlterada = false;
		inserido = insert(chave, valor, nodo->subArvore[dir], alturaFoiAlterada);

		if (alturaFoiAlterada)
		{
			this->rebalancearInsercao(nodo, dir, alturaFoiAlterada);
		}		
	}
	return inserido;
}

VNodo* ArvoreAVL::remover(VNodo*& raiz,int chave)
{
	VNodo* removido;
	bool alturaFoiAlterada = false; // para passagem por referência
	removido = this->remove(chave, raiz, alturaFoiAlterada);
	double tempoRemocao = 0;
	qtdadeDeElementosNaArvore--;
	temposOperacoes.push_back(std::make_pair<int,double>(qtdadeDeElementosNaArvore,tempoRemocao));
	return removido;
}

VNodo* ArvoreAVL::remove(int chave, VNodo*& nodo,bool& alturaFoiAlterada)
{
	VNodo* removido;
	if (nodo == NULL)
	{
		alturaFoiAlterada = false;
		return NULL;//throw
	}
	else if (chave == nodo->chave)
	{
		removido =  new VNodo(nodo->chave,nodo->info);

		if (nodo->subArvore[ESQUERDA] != NULL && nodo->subArvore[DIREITA] != NULL )
		{      
			VNodo* substituto = nodo->subArvore[ESQUERDA];

			while (substituto->subArvore[DIREITA] != NULL)
				substituto = substituto->subArvore[DIREITA];

			nodo->chave   = substituto->chave;
			nodo->info    = substituto->info;
			
			remove(nodo->chave, nodo->subArvore[ESQUERDA], alturaFoiAlterada);

			if (alturaFoiAlterada)
				rebalancearRemovocao(nodo, ESQUERDA, alturaFoiAlterada);
		}
		else
		{
			VNodo* temp = nodo;
			DIRECAO dir = (nodo->subArvore[ESQUERDA] == NULL) ? DIREITA : ESQUERDA;

			nodo = nodo->subArvore[dir];

			temp->subArvore[ESQUERDA]  = NULL;
			temp->subArvore[DIREITA] = NULL;
			delete temp;

			alturaFoiAlterada = true;
		}

		return removido;
	}
	else
	{
		DIRECAO dir = (chave > nodo->chave) ? DIREITA : ESQUERDA;

		if (nodo->subArvore[dir] != NULL)
			removido = this->remove(chave, nodo->subArvore[dir], alturaFoiAlterada);
		else
		{
			alturaFoiAlterada = false;
			return NULL;
		}

		if (alturaFoiAlterada)
			this->rebalancearRemovocao(nodo, dir, alturaFoiAlterada);

		return removido;
	}
}