/*
 * Pista.hpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__PISTA_HPP_
#define INCLUDES_HPP__PISTA_HPP_

#include "ListaAviao.hpp"

struct Pista {
	int num; // 1, 2 ou 3
	ListaAviao prateleiras[2];
	ListaAviao *filaDec = nullptr;
	bool ehParaPouso;
	Pista(ListaAviao *fila1, ListaAviao *fila2, int num, bool ehParaPouso) :
			num(num), ehParaPouso(ehParaPouso) {
		prateleiras[0] = fila1;
		prateleiras[1] = fila2;
	}

	Pista(int num, bool pouso, ListaAviao *filaDec) : num(num), ehParaPouso(pouso), filaDec(filaDec) {
		prateleiras[0] = nullptr;
		prateleiras[1] = nullptr;
	}
};



#endif /* INCLUDES_HPP__PISTA_HPP_ */
