#pragma once
#include "EstruturaLinear.hpp"
template<class T>
class Fila : public EstruturaLinear<T>
{
public:
	Fila(void) : EstruturaLinear()
	{
	}
	~Fila(void)
	{

	}

	T RemoveDado()
	{
		T dadoTemp = m_dados[0];
		for(int i = 0; i < m_topo; i++)
		{
			m_dados[i] = m_dados[i+1];
		}
		m_topo--;
		return dadoTemp;
	}
};

