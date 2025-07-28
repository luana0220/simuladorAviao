/*
 * Pista.cpp
 *
 *  Created on: 27 de jul. de 2025
 *      Author: luana
 */

#include "Pista.hpp"

Pista::Pista (int num) {
	this->estaSendoUsada = estaSendoUsada;
	this->num = num;
	this->aviaoNaPista = nullptr;
}

void Pista::pousarAviao(Aviao& aviao) {
	estaSendoUsada = true;
	aviaoNaPista = aviao;
	std::cout << "Avião " << aviao << " pousando na pista " << num << std::endl;
}

void Pista::decolarAviao(Aviao&  aviao) {
	estaSendoUsada = true;
	aviaoNaPista = aviao;
	std::cout << "Avião " << aviao << " pousando na pista " << num << std::endl;
}

void Pista::atualizarEstado() {
	estaSendoUsada = false;
	aviaoNaPista = nullptr;
}

bool Pista::estaOcupada() const {
	return estaSendoUsada == true;
}


