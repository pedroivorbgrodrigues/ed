// Arvores.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <ctime>
#include "Virtual.h"
#include "ArvoreAVL.h"
#include "ArvoreRB.hpp"
#include <sstream>
#include <algorithm>
#include <ctype.h>

ArvoreAVL* avl;
ArvoreRB* redblack;
Arvore* atual;
const std::string nomeArquivoAVL = "avl.dat";
const std::string nomeArquivoRedBlack = "redblack.dat";
const std::string gnuplotPath = "C:\\gnuplot\\bin\\";
const std::string nomeImagemGrafico = "comparacaoArvores.png";
std::string selecionada()
{
	if (atual == avl)
		return "AVL";
	else return "Red Black";
}

void imprimeMenu()
{
	std::cout << "\nArvores:\n";
	std::cout << "Arvore "<< selecionada() <<" selecionada\n\n";

	std::cout <<"1: Selecionar arvore\n";
	std::cout <<"2: Carregar dados do arquivo\n";
	std::cout <<"3: Inserir\n";
	std::cout <<"4: Remover\n";
	std::cout <<"5: Limpar arvore\n";
	std::cout <<"6: Imprimir em pre ordem\n";
	std::cout <<"7: Imprimir em ordem\n";
	std::cout <<"8: Imprimir em pos ordem\n";
	std::cout <<"9: Imprimir grafico\n";
	std::cout <<"0: Acesso aos vetores de preOrdem,emOrdem e posOrdem definidos pela interface\n";
	std::cout <<"-1: Sair\n";
	std::cout <<"\n";
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		item.erase(remove_if(item.begin(), item.end(), isspace), item.end());
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::vector<std::pair<std::string,int>> lerArquivo(std::string caminhoParaArquivo)
{
	std::string linha;
	std::ifstream arquivo(caminhoParaArquivo);
	std::vector<std::pair<std::string,int>> linhasArquivo;
	if (arquivo.is_open())
	{
		while (!arquivo.eof())
		{
			getline(arquivo,linha);
			std::vector<std::string> parString = split(linha,'|');
			linhasArquivo.push_back(std::make_pair<std::string,int>(parString.at(0),atoi(parString.at(1).c_str())));
		}
		arquivo.close();
	}
	else
		std::cout << "\nERRO :Problema ao acessar o arquivo, ou arquivo nao existe\n";
	return linhasArquivo;
}

void AdiconarElementosDoArquivoNoArvoreAtual()
{
	std::string nomeArquivo;
	std::cout << "Entre com o nome do arquivo de dados:\n";
	std::cin >> nomeArquivo;
	std::vector<std::pair<std::string,int>> dadosAdicionar = lerArquivo(nomeArquivo);
	if (dadosAdicionar.size()>0)
	{
		for (int i=0;i<dadosAdicionar.size();i++)
			atual->inserir(atual->m_raiz,dadosAdicionar.at(i).first,dadosAdicionar.at(i).second);
		std::cout << "\nElementos adicionas com sucesso!\n";
	}
	else
		std::cout << "\nERRO: Nenhum elemento encontrado no arquivo!\n";
	
}

void InserirElementoNaArvoreAtual()
{
	std::string nomeElemento;
	std::cout << "Entre com o identificador(nome) do cep:\n";
	std::cin >> nomeElemento;
	double valorElemento;
	std::cout << "Entre com o cep:\n";
	std::cin >> valorElemento;
	VNodo* inserido = atual->inserir(atual->m_raiz,nomeElemento,valorElemento);
	printf("CEP: %d - %s  inserido com sucesso!\n", inserido->chave,inserido->info.c_str());
}

void RemoverElementoDaArvoreAtual()
{
	double valorElemento;
	std::cout << "Entre com o cep a ser removido:\n";
	std::cin >> valorElemento;
	VNodo* removido = atual->remover(atual->m_raiz,valorElemento);
	if (removido==NULL)
		printf("CEP nao encontrado na arvore\n");
	else
		printf("CEP: %d - %s  removido com sucesso!\n", removido->chave,removido->info.c_str());

}

std::string converterParaDouble(double ds)
{
	std::ostringstream doubleString;
	doubleString << ds;
	return doubleString.str();
}

void criarArquivo(std::vector<std::pair<int,double>>* tempos,std::string nomeArquivo)
{
	FILE * pFile;
	pFile = fopen (nomeArquivo.c_str(),"w");
	for (int i = 0;i< tempos->size();i++)
	{
		fprintf (pFile, "%d %f.4\n",tempos->at(i).first,tempos->at(i).second);
	}
	fclose (pFile);
}

bool GerarArquivoParaGrafico()
{
	std::vector<std::pair<int,double>>* temposAVL = avl->obterTemposArvore();
	std::vector<std::pair<int,double>>* temposRedBlack = redblack->obterTemposArvore();
	criarArquivo(temposAVL,nomeArquivoAVL);
	criarArquivo(temposRedBlack,nomeArquivoRedBlack);
	return (temposAVL->size()>0 || temposRedBlack->size() > 0) ? true : false;
}

void ImprimirGrafico()
{
	std::ofstream file("file");
	file << "set term pngcairo\n";
	file << "set output '"<<nomeImagemGrafico<<"'\n";
	file << "set title \"Diferenca entre tempos de insercao da arvore\"\n";
	file << "set xlabel \"Quantidade de nodos na arvore\"\n";
	file << "set ylabel \"microsegundos\"\n";
	file << "plot \""<< nomeArquivoAVL <<"\" title 'avl' with lines, \\\n";
	file << "\""<<nomeArquivoRedBlack<<"\" title 'redblack' with lines\n";
	file << "set term windows\n";
	file << "replot\n";
	file.close();
	std::string comando = gnuplotPath+"gnuplot.exe -persist file";
	std::system(comando.c_str());
}

void GerarGrafico()
{
	if(GerarArquivoParaGrafico())
	{
		std::cout << "\nGerando grafico...Imagem "<<nomeImagemGrafico<<" gerada.\n";
		std::cout << "GNUPlot invocado! Digite exit para continuar com o programa.\n";
		ImprimirGrafico();
	}
	else
	{
		std::cout << "\nERRO: Nenhuma das arvores possue elementos\n";
		std::cout << "Adicione elementos antes de gerar o gráfico\n";
	}
}



void desenhaArvoreEmOrdem(VNodo *r) 
{
	if(r != NULL)
	{
		printf("<");
		desenhaArvoreEmOrdem(r->subArvore[ESQUERDA]);
		printf("%d ", r->chave);
		desenhaArvoreEmOrdem(r->subArvore[DIREITA]);
		printf(">");
	}
}

void desenhaArvorePreOrdem(VNodo *r) 
{
	if(r != NULL)
	{
		printf("<");
		printf("%d", r->chave);
		desenhaArvorePreOrdem(r->subArvore[ESQUERDA]);		
		desenhaArvorePreOrdem(r->subArvore[DIREITA]);
		printf(">");
	}
}

void desenhaArvorePosOrdem(VNodo *r) 
{
	if(r != NULL)
	{
		printf("<");
		desenhaArvorePosOrdem(r->subArvore[ESQUERDA]);
		desenhaArvorePosOrdem(r->subArvore[DIREITA]);
		printf("%d ", r->chave);
		printf(">");
	}
}

void SelecionarArvore()
{
	std::cout << "Digite 'a' para AVL e 'r' para Red Black\n";
	getchar();
	char opcao = getchar();
	switch (opcao) 
	{
		case 'a':
			atual = avl;
			break;
		case 'r':
			atual = redblack;
			break;
		default:
			atual = avl;
			break;
	}

}


int _tmain(int argc, _TCHAR* argv[])
{
	avl = new ArvoreAVL();
	redblack = new ArvoreRB();
	atual = avl;
	int op = 1;
	while (op!=-1) 
	{
		imprimeMenu();
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				SelecionarArvore();
				break;
			case 2:
				AdiconarElementosDoArquivoNoArvoreAtual();
				break;
			case 3:
				InserirElementoNaArvoreAtual();
				break;
			case 4:
				RemoverElementoDaArvoreAtual();
				break;
			case 5:
				atual->Limpar();
				std::cout << "Arvore limpa com sucesso!\n";
				break;
			case 6:
				desenhaArvorePreOrdem(atual->m_raiz);
				printf("\n");
				break;
			case 7:
				desenhaArvoreEmOrdem(atual->m_raiz);
				printf("\n");
				break;
			case 8:
				desenhaArvorePosOrdem(atual->m_raiz);
				printf("\n");
				break;
			case 9:
				GerarGrafico();				
				break;
			case 0:
				{
					VNodo* preOrd = atual->preOrdem(atual->m_raiz);
					VNodo* emOrd = atual->emOrdem(atual->m_raiz);
					VNodo* posOrd = atual->posOrdem(atual->m_raiz);
					printf("\nNo código é possivel utilizar os vetores para listar os elementos da arvore\n");
					printf("Porem por eles não representarem a estrutura não utilizamos esses vetores para imprimir.\n\n");
				}
				break;
			case -1:				
				std::cout << "Hasta La Vista Baby!\n";
				break;
			default:
				std::cout << "Opcao invalida!\n";
				break;
		}
	}
	return 0;
}

