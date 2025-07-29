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
	Aviao a1(20, 2, 25, true);
	Aviao a3(15, 3, 55, true);
	Aviao a2(5, 5, 0, true);

	std::cout << a1;
	std::cout << a2;
	std::cout << a3;

	if(a1 < a2) {
		std::cout << "Avião 1"<< a1 << "tem menos combustível";
	} else
		std::cout << "Avião 2"<< a2 << " tem menos combustivel";

	return 0;
}


