/*
 * Aviao.cpp
 *
 *  Created on: 25 de jul. de 2025
 *      Author: luana
 */
#include "Aviao.hpp"

Aviao::Aviao (int comb, int id, int tempo, bool ehPouso) : combustivel(comb), ID(id), tempoEspera(tempo), ehPouso(ehPouso) {}

int Aviao::retornarID() {
	return ID;
}

bool Aviao::retornarPousoOuChegada() {
	return ehPouso;
}

int Aviao::retornarTempo() {
	return tempoEspera;
}

void Aviao::diminuirComb() {
	if(combustivel < 0 && ehPouso)
		combustivel--;
}

bool Aviao::ehEmergencia() {

}

