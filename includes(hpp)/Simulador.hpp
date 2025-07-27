/*
 * Simulador.hpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#ifndef INCLUDES_HPP__SIMULADOR_HPP_
#define INCLUDES_HPP__SIMULADOR_HPP_

#include "Aviao.hpp"
#include <cstdlib>
#include <ctime>
#include "ListaAviao.hpp"
#include "Pista.hpp"

const int TEMPO = 60;

class Simulador {
private:
	int tempoAtual;
	int IDAviao;

	Pista pista1, pista2, pista3;

	//Filas de aterrisagem(2 para pista 1, e duas para pista2)
	ListaAviao *filaAterrissagem1A, *filaAterrissagem1B, *filaAterrissagem2A, *filaAterrissagem2B;
	ListaAviao *filaDecolagem1, *filaDecolagem2, *filaDecolagem3;

	void criarAvioes();
	void decrementarComb();
	void usarPista();
	void aumentarTempoDeEspera();
	void simulacaoUnidadesDeTempo();
	ListaAviao* verificarMenorFilaAterr(ListaAviao * filaAterrissagem1A, ListaAviao *filaAterrissagem1B,ListaAviao *filaAterrissagem2A, ListaAviao *filaAterrissagem2B);
	ListaAviao* menorFilaDec(ListaAviao *lista1, ListaAviao *lista2, ListaAviao *lista3);
	void verificarEmergencias();
	Simulador();
	void executar();


};




#endif /* INCLUDES_HPP__SIMULADOR_HPP_ */
