#ifndef TELEMENTO_HPP_
#define TELEMENTO_HPP_

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
	void setProximo(tElemento<T> *proximo) {
		this->proximo = proximo;
	}
	tElemento<T>* getProximo() {
		return proximo;
	}
	void setAnterior(tElemento<T> *anterior) {
		this->anterior = anterior;
	}
	tElemento<T>* getAnterior() {
		return anterior;
	}
	void setInfo(T *info) {
		this->info = info;
	}
	T* getInfo() {
		return info;
	}
};
#endif
