#pragma once

enum DIRECAO
{
	// Indica que a sub�rvore esquerda tem maior altura,
	// Que devemos caminhar para a esquerda na pesquisa
	// ou que queremos acessar a Sub�rvore da esquerda.
	ESQUERDA  = 0,

	// Indica que a sub�rvore direita tem maior altura,
	// Que devemos caminhar para a direita na pesquisa
	// ou que queremos acessar a Sub�rvore da direita.
	DIREITA = 1,

	// Indica que as sub�rvore tem alturas iguais.
	// N�o � v�lida nos outros contextos.
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