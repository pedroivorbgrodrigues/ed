#ifndef EXCECOES_H_
#define EXCECOES_H_

#include <exception>

using namespace std;

class ExcecaoListaVazia: public exception {
public:
	ExcecaoListaVazia() {
	}
	virtual const char* what() const throw () {
		return ("Exceção Lista Vazia!");
	}
};

// Voce pode declarar classes para outras exceções neste arquivo!


#endif /* EXCECOES_H_ */
