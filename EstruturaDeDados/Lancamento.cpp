#include "stdafx.h"
#include "Lancamento.h"
#include <cstring>

Lancamento::Lancamento(void)
{
}

Lancamento::~Lancamento(void)
{
}

Lancamento::Lancamento(std::string nomeLancamento,double valorLancamento)
{
	nome = new char[nomeLancamento.length()];
	strcpy(nome, nomeLancamento.c_str());
	valor = valorLancamento;
}

std::string Lancamento::Nome()
{
	return nome;
}

double Lancamento::Valor()
{
	return valor;
}