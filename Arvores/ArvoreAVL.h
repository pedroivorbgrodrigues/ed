#pragma once
#include "Virtual.h"

class ArvoreAVL : public Arvore
{
public:
	ArvoreAVL(void){};
	~ArvoreAVL(void){};
	VNodo* inserir(VNodo *&raizAtual, std::string nomeInformado, int cepInformado);
	VNodo* remover(VNodo *&raizAtual, int cepInformado);
private:
	void rotacionarDuasVezes(VNodo*& nodo, DIRECAO dir);
	void rotacionarUmaVez (VNodo*& nodo, DIRECAO dir);

	void atualizarBalanceamento  (VNodo* arvore,  DIRECAO dir);
	void rebalancearInsercao(VNodo*& arvore, DIRECAO dir,bool& alturaFoiAlterada);
	void rebalancearRemovocao(VNodo*& arvore, DIRECAO dir,bool& alturaFoiAlterada);

	VNodo* insert(int key, const std::string& value, VNodo*& nodo, bool& alturaFoiAlterada);
	VNodo* remove(int key, VNodo*& nodo, bool& alturaFoiAlterada);

	inline DIRECAO oposto(DIRECAO dir);
	
};

