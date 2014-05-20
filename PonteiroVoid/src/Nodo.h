#ifndef NODO_H_
#define NODO_H_
#include <iostream>
#include <fstream>
using namespace std;
template<class T>
class Nodo {//Elemento
public:
	Nodo *proximo;
	T *info;
	Nodo();
	virtual ~Nodo();
	friend ostream& operator<<(ostream& stream, Nodo &n){
//		cout << "nodo: ";
		return stream << *n.info;
	};
};

template<class T>
Nodo<T>::Nodo() {
}

template<class T>
Nodo<T>::~Nodo() {
	delete info;
}
#endif /* NODO_H_ */
