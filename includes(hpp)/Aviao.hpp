/*
 * Aviao.hpp
 *
 *  Created on: 25 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__AVIAO_HPP_
#define INCLUDES_HPP__AVIAO_HPP_

#include <iostream>
#include <string>

struct Aviao {


	int combustivel;
	int ID;
	int tempoEspera;
	bool ehPouso;

	Aviao (int comb, int id, int tempo, bool ehPouso) : combustivel(comb), ID(id), tempoEspera(tempo), ehPouso(ehPouso) {}



};

std::ostream& operator<<(std::ostream& os, const Aviao& aviao) {
	if (aviao.ehPouso) {
		os << "Avião de Id " << aviao.ID << "pousou com " << aviao.combustivel << "un. combustível" << " e esperou "<< aviao.tempoEspera << std::endl;
	}
	return os;
}

bool operator < (const Aviao& aviao, Aviao aviao2) {
		return aviao.combustivel <= aviao2.combustivel;
}




#endif /* INCLUDES_HPP__AVIAO_HPP_ */
