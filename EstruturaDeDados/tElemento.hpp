#ifndef TELEMENTO_HPP_
#define TELEMENTO_HPP_
/**
*@brief Responsável por conter e gerenciar os ponteiros para os próximos e anteriores e para a informação em si de uma estrutura duplamente encadeada
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
	*  Responsável por definir o ponteiro para o elemento posterior a este na estrutura
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
	*  Responsável por definir o ponteiro para o elemento anterior a este na estrutura
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
	*  Responsável por definir o ponteiro para o as informações do elemento
	*/
	void setInfo(T *info) {
		this->info = info;
	}
	/**
	*  Retorna as informações do elemento
	*/
	T* getInfo() {
		return info;
	}
};
#endif
