/*
 * main.cpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#include "Aviao.hpp"
#include "ListaAviao.hpp"
#include <iostream>
#include "Simulador.hpp"

int main() {
    srand(time(0));
	Simulador s(60);
	s.executar();
	return 0;
}


