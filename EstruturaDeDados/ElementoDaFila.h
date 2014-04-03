#pragma once
#include <iostream>

#define TAMANHO_CHAR 40

class ElementoDaFila
{
public:
	ElementoDaFila()
	{
	}

	ElementoDaFila(std::string s)
	{
		for (int i = 0; i < TAMANHO_CHAR && i < s.length(); i++)
		{
			m_vetorDeChar[i] = s.at(i);
		}
		if (s.length() < TAMANHO_CHAR)
		{
			m_vetorDeChar[s.length()] = '\0';
		}
		else m_vetorDeChar[39] = '\0';
		
	}
	~ElementoDaFila(void)
	{
	}
	

	friend std::ostream &operator<<(std::ostream &out, ElementoDaFila &ef)     //output
	{
		out<<ef.m_vetorDeChar<<"\n";
		return out;
	}

private:
	char m_vetorDeChar[TAMANHO_CHAR];

	
};