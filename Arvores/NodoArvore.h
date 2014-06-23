#pragma once

enum DIRECAO
{
	// Indica que a subárvore esquerda tem maior altura,
	// Que devemos caminhar para a esquerda na pesquisa
	// ou que queremos acessar a Subárvore da esquerda.
	ESQUERDA  = 0,

	// Indica que a subárvore direita tem maior altura,
	// Que devemos caminhar para a direita na pesquisa
	// ou que queremos acessar a Subárvore da direita.
	DIREITA = 1,

	// Indica que as subárvore tem alturas iguais.
	// Não é válida nos outros contextos.
	IGUAL = 2,
};

template <class TipoChave,class TipoValor>
class NodoArvore
{
public:
	NodoArvore(){}
	NodoArvore(const TipoChave& chave, const TipoValor& value)
	{
		this->chave   = chave;
		this->info = value;
		this->subArvore[ESQUERDA]  = nullptr;
		this->subArvore[DIREITA] = nullptr;
		this->fatorBalanceamento = IGUAL;
	}

	~NodoArvore()
	{
		delete this->subArvore[ESQUERDA];
		delete this->subArvore[DIREITA];
	}


	unsigned short fatorBalanceamento;
	NodoArvore* subArvore[2];
	NodoArvore* pai;
	TipoChave chave;
	TipoValor info;
	bool cor;
};