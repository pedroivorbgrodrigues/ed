#include "stdafx.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <exception>
#include <string.h>
#include "ListaContabil.hpp"

struct  WrapperChar
{
	char * palavra;


	bool operator > (const WrapperChar& comparar)
	{
		int resultado = strcmp(palavra,comparar.palavra);
		return resultado  > 0;
	}

	bool operator != (const WrapperChar& comparar)
	{
		return !strcmp(palavra,comparar.palavra) == 0;
	}
};


void except(std::exception*);
void imprimeMenu();
void imprimirLista(ListaContabil<WrapperChar>*);
WrapperChar lerString();
int lerInt();

int main() {
    
    ListaContabil<WrapperChar> lP;
    int op = 10;

    while (op!=0) {
        imprimeMenu();
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                try
                {
                    lP.AdicionaDado(lerString());
                }
				catch(std::exception& exc)
                {
                    except(&exc);
                }
                break;
            case 2:
                try
                {
                    lP.AdicionaNoInicio(lerString());
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            case 3:
                try
                {
                    lP.AdicionaNaPosicao(lerString(),lerInt());
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            
            case 4:
                try
                {
                    lP.AdicionaEmOrdem(lerString());
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            case 5:
                try
                {
                    WrapperChar aux = lP.RemoveDado();
                    printf("%s foi retirado da lista.\n\n",aux.palavra);
                    delete(aux.palavra);
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            case 6:
                try
                {
                    WrapperChar aux = lP.RetiraDoInicio();
                    printf("%s foi retirado da lista.\n\n",aux.palavra);
                    delete(aux.palavra);
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            case 7:
                try
                {
                    WrapperChar aux = lP.RetiraDaPosicao(lerInt());
                    printf("%s foi retirado da lista.\n\n",aux.palavra);
                    delete(aux.palavra);
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
             case 8:
                try
                {
                    WrapperChar aux = lP.RetiraEspecifico(lerString());
                    printf("%s foi retirado da lista.\n\n",aux.palavra);
                    delete(aux.palavra);
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
             case 9:
                try
                {
                    imprimirLista(&lP);
                }
				catch(std::exception& exc)
				{
					except(&exc);
				}
                break;
            case 0:
               printf("Hasta La Vista Baby!\n");
            	break;
            default:
                printf("Sinto muito, opção inválida.\n");
                break;
        }
    }
    return 0;
}

void imprimeMenu()
{
    printf("Menu:\n\n");
    
    printf("1: Adicionar\n");
    printf("2: Adicionar no início\n");
    printf("3: Adicionar na posição\n");
    printf("4: Adicionar em ordem\n");
    printf("5: Retirar\n");
    printf("6: Retirar do início\n");
    printf("7: Retirar da posição\n");
    printf("8: Retirar específico\n");
    printf("9: Imprimir Lista\n");
    printf("0: Sair\n");
    printf("\n");
}

void except(std::exception* exc)
{
	printf(exc->what());
		/*
    switch(exc)
    {
        case -1:
                printf("Lista vazia!\n");
                break;
        case -2:
                printf("A lista está cheia!\n");
                break;
        case -3:
                printf("Posição invalida!\n");   
                break;
        case -4:
                printf("Elemento inexistente!\n");
                break;
        default:
                break;
                
    }
	*/
    printf("\n");
}

WrapperChar lerString()
{
    char buffer[10000];
	WrapperChar wc;
    char *point;
    setbuf(stdin, NULL);
    printf("Digite a String a ser armazenada\n");
    scanf("%[^\n]s",buffer); //Ler strings com espaços
    setbuf(stdin, NULL);
	int tamanho = std::strlen(buffer);
	point = new char[tamanho];
	strcpy(point, buffer);
    printf("\n");
	wc.palavra = point;
    return wc;
}

int lerInt()
{
    int aux;
    printf("Digite a posição:\n");
    scanf("%i", &aux);
    printf("\n");
    return aux;
}

void imprimirLista(ListaContabil<WrapperChar> *p)
{
    printf("Imprimindo lista:\n\n");
       
    if(p->EstruturaVazia())
        printf("Lista vazia!\n");
    
    for(int i = 0; i < p->ObterIndiceTopo()+1; i++)
    {
        printf("%d",i);
        printf("> %s",p->ObterDadoPelaPosicao(i).palavra);
        printf("\n");
    }
    printf("\n");
}