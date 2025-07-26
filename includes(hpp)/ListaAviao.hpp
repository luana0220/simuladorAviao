/*
 * ListaAviao.hpp
 *
 *  Created on: 25 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__LISTAAVIAO_HPP_
#define INCLUDES_HPP__LISTAAVIAO_HPP_
#include "Aviao.hpp"

struct NoDeAviao {
	Aviao dado;
	NoDeAviao * proximo;
	NoDeAviao(const Aviao aeronave) : dado(aeronave), proximo(nullptr) {}
};

class ListaAviao {
private:
	NoDeAviao * primeiro;
	NoDeAviao * ultimo;
	int tamanho;
public:
	ListaAviao();
	~ListaAviao();

	void enfileirar(const Aviao& dado);
	Aviao desenfileirar();

};



#endif /* INCLUDES_HPP__LISTAAVIAO_HPP_ */
