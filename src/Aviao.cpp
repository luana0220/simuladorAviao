/*
 * Aviao.cpp
 *
 *  Created on: 29 de jul. de 2025
 *      Author: luana
 */

#include "Aviao.hpp"

Aviao::Aviao() :
		combustivel(0), ID(0), tempoEspera(0), ehPouso(false) {
}

Aviao::Aviao(int comb, int id, int tempo, bool ehPouso) :
		combustivel(comb), ID(id), tempoEspera(tempo), ehPouso(ehPouso) {
}

void Aviao::decrementarCombAviao() {
	combustivel--;
}

void Aviao::aumentarTempoDeEspera() {
	tempoEspera++;
}

std::ostream& operator<<(std::ostream& os, const Aviao& a) {
	if(a.ehPouso) {
		os << "{ ID: " << a.ID << ", Combustível: " << a.combustivel
		   << " un. combustível,  Tempo de espera: " << a.tempoEspera << " un. de tempo }";
	} else {
		os << "{ ID: " << a.ID << ", Tempo de espera: " << a.tempoEspera << " un. de tempo }";
	}
	return os;
}

bool operator <(const Aviao &aviao, const Aviao &aviao2) {
	return aviao.combustivel < aviao2.combustivel;
}

bool operator >(const Aviao &a1, const Aviao &a2) {
	if( a1.tempoEspera > a2.tempoEspera) {
		return true;
	}
	return false;
}

void Aviao::imprimirAviao(const Aviao &a) {
		if(ehPouso) {
			std::cout << " [ ID: " << a.ID << " Combustivel: " << a.combustivel << " ]" << std::endl;
		} else
			std::cout << " [ ID: " << a.ID << " ]" << std::endl;
	}

