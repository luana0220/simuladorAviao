/*
 * main.cpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#include "Aviao.hpp"
#include "ListaAviao.hpp"
#include <iostream>

int main() {
	ListaAviao pista1;
	Aviao aviao(10, 1, 20, true, 2);
	pista1.enfileirar(aviao);
	return 0;
}


