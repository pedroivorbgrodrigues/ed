#ifndef TELEMENTO_HPP_
#define TELEMENTO_HPP_
/**
*@brief Respons�vel por conter e gerenciar os ponteiros para os pr�ximos e anteriores e para a informa��o em si de uma estrutura duplamente encadeada
*/
template<class T>
class tElemento {
private:
	tElemento<T> *proximo, *anterior;
	T *info;
public:
	tElemento() {
		proximo = NULL;
		anterior = NULL;
		info = NULL;
	}
	~tElemento() {
		
	}
	/**
	*  Respons�vel por definir o ponteiro para o elemento posterior a este na estrutura
	*/
	void setProximo(tElemento<T> *proximo) {
		this->proximo = proximo;
	}
	/**
	*  Retorna o ponteiro para o elemento posterior a este na estrutura
	*/
	tElemento<T>* getProximo() {
		return proximo;
	}
	/**
	*  Respons�vel por definir o ponteiro para o elemento anterior a este na estrutura
	*/
	void setAnterior(tElemento<T> *anterior) {
		this->anterior = anterior;
	}
	/**
	*  Retorna o ponteiro para o elemento anterior a este na estrutura
	*/
	tElemento<T>* getAnterior() {
		return anterior;
	}
	/**
	*  Respons�vel por definir o ponteiro para o as informa��es do elemento
	*/
	void setInfo(T *info) {
		this->info = info;
	}
	/**
	*  Retorna as informa��es do elemento
	*/
	T* getInfo() {
		return info;
	}
};
#endif
