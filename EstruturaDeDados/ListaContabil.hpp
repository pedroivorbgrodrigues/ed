#pragma once
#include "EstruturaLinear.hpp"
template<class T>
class ListaContabil : public EstruturaLinear<T>
{
public:
	ListaContabil(void) : EstruturaLinear()
	{

	}
	~ListaContabil(void)
	{

	}

	T ObterLancamentoPelaPosicao(int i)
	{
		return m_dados[i];
	}

	int AdicionaNoInicio(T dado)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		m_topo++;
		int posicao = m_topo;
		while (posicao > 0)
		{
			m_dados[posicao] = m_dados[posicao-1];
			posicao--;
		}
		return 0;
	}

	T RetiraDoInicio()
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		int posicao = 0;
		T valor;
		m_topo--;
		valor = m_dados[0];
		while(posicao <= m_topo)
		{
			m_dados[posicao] = m_dados[posicao+1];
			posicao++;
		}
		return valor;
	}

	int AdicionaNaPosicao(T dado, int destino)
	{
		if(this->EstruturaCheia())
			throw std::overflow_error("Estrutura Cheia!");
		if (destino > m_topo +1 || destino < 0)
			throw std::invalid_argument("Posicao invalida");
		int posicao = m_topo;
		while(posicao > destino)
		{
			m_dados[posicao] = m_dados[posicao-1];
			posicao--;
		}
		m_dados[destino] = dado;
		return destino;
	}

	T RetiraDaPosicao(int fonte)
	{
		if (fonte > m_topo || fonte < 0)
			throw std::invalid_argument("Posicao invalida");
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		m_topo--;
		int posicao = fonte;
		T valor = m_dados[fonte];
		while (posicao <= m_topo)
		{
			m_dados[posicao] = m_dados[posicao+1];
			posicao++;
		}
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
		while(posicao <= m_topo && maior(dado, m_dados[posicao]))
		{
			posicao++;
		}
		return AdicionaNaPosicao(dado,posicao);
	}

	int Posicao(T dado)
	{
		int posicao = 0;
		while(posicao <= m_topo && dado != m_dados[posicao])
		{
			posicao++;
		}
		if (posicao > m_topo)
			return -1;
		return posicao;
	}

	T RetiraEspecifico(T dado)
	{
		if(this->EstruturaVazia())
			throw std::underflow_error("Estrutura Vazia!");
		int posicao = Posicao(dado);
		if (posicao < 0)
			throw std::invalid_argument("Posicao invalida");
		return RetiraDaPosicao(posicao);
	}

};

