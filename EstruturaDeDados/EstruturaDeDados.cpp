// EstruturaDeDados.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <exception>
#include <string>
#include <ctype.h>
#include "EstruturaLinear.hpp"
#include "ElementoDaFila.h"
#include "Fila.hpp"

#define TIPO_DADO 1

using namespace std;

void tratarEntradaChar(char* saida)
{
	string entrada;
	cin >> entrada;
	if (entrada.length()>0)
	{
		 strcpy(saida, entrada.c_str());
		 return;
	}
	else
		cout << std::endl << "Entrada invalida! Digite uma sequencia de ate 40 caracteres!" << std::endl;
	return tratarEntradaChar(saida);
}

int tratarEntradaNumero()
{
	string entrada;
	bool entradaValida = true;
	int retorno;
	cin >> entrada;
	for (int i =0 ; i < entrada.length(); i++ )
	{
		if (!isdigit(entrada[i]))
		{
			entradaValida = false;
			break;
		}
	}
	if (entradaValida)
	{
		retorno = atoi(entrada.c_str());
		return retorno;
	}
	cout << std::endl << "Entrada invalida! Digite um numero!" << std::endl;
	return tratarEntradaNumero();
	
}

std::string testeEstrutura(bool vouf)
{
	return vouf ? "esta " : "nao esta ";
}

template<class T>
void menuRecursivo(EstruturaLinear<T>* estutura)//char is 1, number is 2
{
	cout << "Pilhas:" << endl
		<< "Digite o numero da opção desejada:" << endl
		<< "1) Empilhar Elemento" << endl
		<< "2) Desempilhar Elemento" << endl
		<< "3) Limpar Pilha" << endl
		<< "4) Mostrar Pilha" << endl
		<< "5) Sair do programa" << endl;
	int opcao = tratarEntradaNumero();
	
	switch (opcao)
	{
		case 1:
			{
				cout << "Digite o elemento a ser empilhado:" << endl;
				T elemento;
#if (TIPO_DADO == 2)
				elemento = tratarEntradaNumero();
#else (TIPO_DADO == 1)
				char* c = new char[40];
				tratarEntradaChar(c);
				ElementoDaFila ef(c);
				elemento = ef;
#endif
				try
				{
					estutura->AdicionaDado(elemento);
					cout << "Valor empilhado corretamente." << endl;
				}
				catch (overflow_error& e)
				{
					cout << "Erro: pilha cheia." << endl;
				}
				cout << std::endl << std::endl;
				menuRecursivo(estutura);
				
			}	
		break;
		case 2:
			{
				cout << "Desempilhando um valor:" << endl;
				T elemento;
				try
				{
					elemento = estutura->RemoveDado();
					cout << "Valor desempilhado: " << elemento << endl;
				}
				catch (underflow_error& e)
				{
					cout << "Erro: pilha vazia." << endl;
				}

				cout << std::endl << std::endl;
				menuRecursivo(estutura);
			}
		break;
		case 3:
			{
				estutura->InicializaEstrutura();
				cout << "Pilha limpa." << endl;

				cout << std::endl << std::endl;
				menuRecursivo(estutura);
			}
			
		break;
		case 4:
			{
				try
				{
					cout << "Posição Valor" << endl;
					T vetor[MAXPILHA];
					estutura->CopiarVetor(vetor);
					int indiceTopo = estutura->ObterIndiceTopo();
					for (int i = 0; i <= indiceTopo; i++)
					{
						if (TIPO_DADO == 2)
							printf("%i %i\n", i, vetor[i]);
						else cout << i << "   " << vetor[i];
					}
					//estutura->ImprimirVetor();
				}
				catch (underflow_error& e)
				{
					cout << "Erro: pilha vazia." << endl;
				}
				cout << std::endl << std::endl;
				menuRecursivo(estutura);
			}
		break;
		case 5:
			break;
		default:
			cout << std::endl << "Entrada invalida, digite um numero entre 1 e 5!" << std::endl;
		break;
	}	
}
int _tmain(int argc, _TCHAR* argv[])
{
#if (TIPO_DADO == 2)
	EstruturaLinear<int> pilha;
	menuRecursivo(&pilha);
#else
	Fila<ElementoDaFila> fila;
	menuRecursivo(&fila);
#endif
	return 0;
}

