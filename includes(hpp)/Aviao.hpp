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

	Aviao();
	Aviao (int comb, int id, int tempo, bool ehPouso);
	void decrementarCombAviao();


	void aumentarTempoDeEspera();



	friend std::ostream& operator<<(std::ostream &os, const Aviao &a);
	friend bool operator<(const Aviao &a1, const Aviao &a2);
	friend bool operator>(const Aviao &a1, const Aviao &a2);

	void imprimirAviao(const Aviao &a);
	//friend

};





#endif /* INCLUDES_HPP__AVIAO_HPP_ */
