/*
 * Aviao.hpp
 *
 *  Created on: 25 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__AVIAO_HPP_
#define INCLUDES_HPP__AVIAO_HPP_

#include <iostream>

class Aviao {

private:
	int combustivel;
	int ID;
	int tempoEspera;
	bool ehPouso;
public:
	Aviao (int comb, int id, int tempo, bool ehPouso);
	~Aviao();

	int retornarID();
	bool retornarPousoOuChegada();
	void diminuirComb();
	int retornarTempo();
	bool ehEmergencia();

};



#endif /* INCLUDES_HPP__AVIAO_HPP_ */
