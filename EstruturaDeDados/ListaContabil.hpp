#pragma once
#include "EstruturaLinear.hpp"
template<class T>
class ListaContabil : public EstruturaLinear<T>
{
public:
	ListaContabil(void) : EstruturaLinear<T>()
	{

	}
	~ListaContabil(void)
	{

	}

	T ObterDadoPelaPosicao(int i)
	{
		return this->m_dados[i];
	}

	int AdicionaNoInicio(T dado)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		this->m_topo++;
		DeslocarTodosParaDireita(0);
		this->m_dados[0] = dado;
		return 0;
	}

	T RetiraDoInicio()
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		int posicao = 0;
		T valor;
		this->m_topo--;
		valor = this->m_dados[0];
		DeslocarTodosParaEsquerda(0);
		return valor;
	}

	int AdicionaNaPosicao(T dado, int destino)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		if (destino > this->m_topo +1 || destino < 0)
			throw std::invalid_argument("Posicao invalida");
		this->m_topo++;
		DeslocarTodosParaDireita(destino);
		this->m_dados[destino] = dado;
		return destino;
	}

	/*
	int AdicionaEmOrdem(T dado)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		int posicao = 0;
		while(posicao <= this->m_topo && dado > this->m_dados[posicao])
		{
			posicao++;
		}
		return AdicionaNaPosicao(dado,posicao);

	}
	*/

	T RetiraDaPosicao(int fonte)
	{
		if (fonte > this->m_topo || fonte < 0)
			throw std::invalid_argument("Posicao invalida");
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		this->m_topo--;
		T valor = this->m_dados[fonte];
		DeslocarTodosParaEsquerda(fonte);
		return valor;
	}

	bool maior(T dado1, T dado2)
	{
		return dado1 > dado2;
	}

	int AdicionaEmOrdem(T dado)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		int posicao = 0;
		while(posicao <= this->m_topo && maior(dado,this-> m_dados[posicao]))
		{
			posicao++;
		}
		return AdicionaNaPosicao(dado,posicao);
	}

	int Posicao(T dado)
	{
		int posicao = 0;
		while(posicao <= this->m_topo && dado != this->m_dados[posicao])
		{
			posicao++;
		}
		if (posicao > this->m_topo)
			return -1;
		return posicao;
	}

	T RetiraEspecifico(T dado)
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		int posicao = Posicao(dado);
		if (posicao < 0)
			throw std::invalid_argument("Elemento inexistente!");
		return RetiraDaPosicao(posicao);
	}

	private:
		void DeslocarTodosParaEsquerda(int inicio)
		{
			int posicao = inicio;
			while (posicao <= this->m_topo)
			{
				this->m_dados[posicao] = this->m_dados[posicao+1];
				posicao++;
			}
		}

		void DeslocarTodosParaDireita(int inicio)
		{
			int posicao = this->m_topo;
			while(posicao > inicio)
			{
				this->m_dados[posicao] = this->m_dados[posicao-1];
				posicao--;
			}
		}

};

