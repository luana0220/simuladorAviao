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

	ListaAviao lista;
	int tempo = 60;
	Aviao a(20, 5, 2, true);
	Aviao a2(2, 6, 45, true);
		try {
		Simulador simulador(60);
		simulador.executar();

		lista.enfileirar(a);
		lista.enfileirar(a2);
		std::cout << lista.noComMaisTempoDeEspera();
		std::cout << lista.noComMaisEmergencia();
		lista.imprimirAvioes();

		std::cout << lista.desenfileirarAviaoPosicao(lista.noComMaisEmergencia());
		lista.decrementarComb();
		lista.imprimirAvioes();
		} catch (const std::exception &e){
			std::cerr << "Erro: " << e.what() << std::endl;
		}
	return 0;
}


