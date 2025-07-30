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

	const int tempo = 60;
		Simulador simulador(tempo);
		simulador.executar();

		try {

		} catch (const std::exception &e){
			std::cerr << "Erro: " << e.what() << std::endl;
		}
	return 0;
}


