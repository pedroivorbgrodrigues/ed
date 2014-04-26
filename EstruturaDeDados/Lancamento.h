#pragma once
#include <string>
#include <iostream>
#include <iomanip> 
class Lancamento
{
public:
	Lancamento();
	Lancamento(std::string nomeLancamento,double valorLancamento);
	~Lancamento(void);

	std::string Nome();
	double Valor();

	friend std::ostream &operator<<(std::ostream &out, Lancamento ef)     //output
	{
		out<<ef.nome<<" " << std::fixed << std::setprecision(2) << ef.valor << "\n";
		return out;
	}

	//sobreescrever os operadores de maior, e de igual para usar os metodos de adicionar em ordem e remover especifico

private:
	char* nome;
	double valor;
};

