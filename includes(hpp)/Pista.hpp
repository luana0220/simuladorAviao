/*
 * Pista.hpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__PISTA_HPP_
#define INCLUDES_HPP__PISTA_HPP_

#include "ListaAviao.hpp"
#include "Aviao.hpp"

class Pista {
private:
	int num; // 1, 2 ou 3
	bool estaSendoUsada; //usada para saber se a pista está sofrendo alguma ação
	Aviao  aviaoNaPista;

public:
	Pista(int num);
	bool estaOcupada() const;
	void pousarAviao(Aviao& aviao);
	void decolarAviao(Aviao& aviao);
	void atualizarEstado();

};



#endif /* INCLUDES_HPP__PISTA_HPP_ */
