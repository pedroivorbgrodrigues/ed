#pragma once
#include <stdlib.h>
#include "Virtual.h"
#define VERMELHO true
#define PRETO false
#define LESQUERDA true
#define LDIREITA false
class ArvoreRB : public Arvore
{
	public:
		ArvoreRB(){}
		~ArvoreRB(){}
		
		VNodo* inserir(VNodo *&raizAtual, std::string nomeInformado, int cepInformado) 
		{
			IniciarContagemDeTempo();
			VNodo *novo, *atual, *pai, *avo;
			novo = new VNodo(cepInformado,nomeInformado);
			if (raizAtual == NULL) 
			{
				novo->cor = PRETO;
				raizAtual = novo;
			} 
			else 
			{
				this->insercao(raizAtual, novo);
			}
			
			atual = novo;
			
			while (atual != m_raiz && !atual->pai) 
			{
				pai = atual->pai;
				avo = pai->pai;
				if (avo->subArvore[ESQUERDA] == pai) 
					this->passoCE_Esq(atual, pai, avo);
				else 
					this->passoCE_Dir(atual, pai, avo);
			}
			m_raiz->cor = PRETO;
			qtdadeDeElementosNaArvore++;
			FinalizarContagemDeTempo();
			return novo;
		}

		VNodo* remover(VNodo *&raizAtual, int cepInformado)
		{
			if (raizAtual != NULL)
				return this->delecao(m_raiz, cepInformado);
			return NULL;
		}
private:
	void insercao(VNodo *nodoBase, VNodo *novo) 
	{
		if (novo->chave < nodoBase->chave) 
		{
			VNodo *esq = nodoBase->subArvore[ESQUERDA];
			if (esq == NULL) 
			{
				novo->subArvore[DIREITA]= esq;
				novo->subArvore[ESQUERDA]= esq;
				novo->pai = nodoBase;
				nodoBase->subArvore[ESQUERDA] = novo;
			} else 
			{
				this->insercao(esq, novo);
			}
		} 
		else 
		{
			VNodo *dir = nodoBase->subArvore[DIREITA];
			if (dir == NULL) 
			{
				novo->subArvore[DIREITA]= dir;
				novo->subArvore[ESQUERDA]= dir;
				novo->pai = nodoBase;
				nodoBase->subArvore[DIREITA] = novo;
			} 
			else 
			{
				this->insercao(dir, novo);
			}
		}
	}

	VNodo* minimo(VNodo *nodo) 
	{
		VNodo *retorno = nodo;
		while (retorno->subArvore[ESQUERDA] != NULL)
			retorno = retorno->subArvore[ESQUERDA];
		return retorno;
	}

	VNodo* delecao(VNodo *nodo, int chave) 
	{
		VNodo *aux, *filho;
		if (chave < nodo->chave) 
		{
			nodo->subArvore[ESQUERDA] = this->delecao(nodo->subArvore[ESQUERDA], chave);
			return nodo;
		} 
		else 
		{
			if (chave > nodo->chave) 
			{
				nodo->subArvore[DIREITA] = this->delecao(nodo->subArvore[DIREITA], chave);
				return nodo;
			} 
			else 
			{
				if (nodo->subArvore[DIREITA] != NULL && nodo->subArvore[ESQUERDA] != NULL) 
				{
					aux = this->minimo(nodo->subArvore[DIREITA]);
					nodo->chave =aux->chave;
					nodo->subArvore[DIREITA] = delecao(nodo->subArvore[DIREITA], nodo->chave) ;
					return nodo;
				} 
				else 
				{
					aux = nodo;
					if (nodo->subArvore[DIREITA] != NULL) 
					{
						filho = nodo->subArvore[DIREITA];
						return filho;
					} 
					else 
					{
						if (nodo->subArvore[ESQUERDA] != NULL) 
						{
							filho = nodo->subArvore[ESQUERDA];
							return filho;
						} 
						else 
						{
							nodo->subArvore[DIREITA] = NULL;
							nodo->subArvore[ESQUERDA] = NULL;
							delete (nodo);
							return NULL;
						}
					}
				}
			}
		}
		return NULL;
	}

	void rodaEsq(VNodo *roda) 
	{
		VNodo *aux, *pai;
		bool lado = LDIREITA;
		pai = roda->pai;
		if (!roda->pai)
		{
			if (pai->subArvore[ESQUERDA] == roda)
			{
				lado = LESQUERDA;
			}
			else lado = LDIREITA;
		}
		
		aux = roda->subArvore[DIREITA];
		aux->pai = pai;
		roda->subArvore[DIREITA] = aux->subArvore[ESQUERDA];
		if (roda->subArvore[DIREITA] != NULL)
		{
			roda->subArvore[DIREITA]->pai = roda;
			aux->subArvore[ESQUERDA] = roda;
			aux->subArvore[ESQUERDA]->pai = aux;
		}
		if (lado)
			pai->subArvore[ESQUERDA] = aux;
		else
		{
			if (!roda->pai)
				pai->subArvore[DIREITA] = aux;
		}
	}

	void rodaDir(VNodo *roda) 
	{
		VNodo *aux, *pai;
		bool lado;
		pai = roda->pai;
		if (pai->subArvore[ESQUERDA] == roda)
			lado = LESQUERDA;
		else
			lado = LDIREITA;
		aux = roda->subArvore[ESQUERDA];
		aux->pai = pai;
		
		if (aux->subArvore[DIREITA] != NULL)
		{
			roda->subArvore[ESQUERDA] = aux->subArvore[DIREITA];
			roda->subArvore[ESQUERDA]->pai = roda;
			
		}
		//dentrou ou fora do if?
		aux->subArvore[DIREITA] = roda;
		aux->subArvore[DIREITA]->pai = aux;
		
		if (lado)
			pai->subArvore[ESQUERDA] = aux;
		else
			pai->subArvore[DIREITA] = aux;
	}
	void passoCE_Esq(VNodo *atual, VNodo *pai, VNodo *avo) 
	{
		VNodo *tio;
		tio = avo->subArvore[DIREITA];
		if (tio->cor) 
		{
			pai->cor = PRETO;
			avo->cor = VERMELHO;
			tio->cor = PRETO;
			atual = avo;
		} 
		else 
		{
			if (pai->subArvore[DIREITA] == atual) 
			{
				this->rodaEsq(pai);
				atual = atual->subArvore[ESQUERDA];
			}
			pai->cor = PRETO;
			avo->cor = VERMELHO;
			this->rodaDir(avo);
		}
	}

	void passoCE_Dir(VNodo *atual, VNodo *pai, VNodo *avo) 
	{
		VNodo *tio;
		tio = avo->subArvore[ESQUERDA];
		if (tio == NULL) 
		{
			pai->cor = PRETO;
			avo->cor = VERMELHO;
			atual = avo;
		} 
		else 
		{
			if (pai->subArvore[ESQUERDA] == atual) 
			{
				this->rodaDir(pai);
				atual = atual->subArvore[DIREITA];
			}
			pai->cor = PRETO;
			avo->cor = VERMELHO;
			this->rodaEsq(avo);
		}
	}
};
