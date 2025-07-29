/*
 * Pista.cpp
 *
 *  Created on: 27 de jul. de 2025
 *      Author: luana
 */

#include "Pista.hpp"

Pista::Pista (int num) : num(num), estaSendoUsada(false), aviaoNaPista() {}
void Pista::pousarAviao(Aviao& aviao) {
	estaSendoUsada = true;
	aviaoNaPista = aviao;
	std::cout << "Avião " << aviao << " pousando na pista " << num << std::endl;
}

void Pista::decolarAviao(Aviao&  aviao) {
	estaSendoUsada = true;
	aviaoNaPista = aviao;
	std::cout << "Avião:  " << aviao << "  pousando na pista " << num << std::endl;
}

void Pista::atualizarEstado() {
	estaSendoUsada = false;
}

bool Pista::estaOcupada() const {
	return estaSendoUsada == true;
}


