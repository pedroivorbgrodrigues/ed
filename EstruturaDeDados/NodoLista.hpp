#pragma once
template<class T>
class NodoLista
{
public:
	NodoLista(T* elementoNodo)
	{
		elemento = elementoNodo;
	}

	NodoLista(T* elementoNodo,NodoLista* proximoNodo) : NodoLista(elementoNodo)
	{
		proximo = proximoNodo;
	}

	void setProximo(NodoLista* proximoNodo)
	{
		proximo = proximoNodo;
	}

	NodoLista* Proximo()
	{
		return proximo;
	}

	T* Elemento()
	{
		return elemento;
	}

	~NodoLista(void)
	{

	}
protected:
	NodoLista* proximo;
	T* elemento;
};

