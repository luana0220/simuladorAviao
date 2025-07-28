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



class Simulador {
private:
	int tempoAtual;
	int IDAviao;
	const int TEMPO_SIMULACAO = 60;
	Pista pista1, pista2, pista3;
	int pousosDeEmergencia;
	int totalDePousos;
	int pousosNormais;
	int totalPousosEmergencias;

	//Filas de aterrisagem(2 para pista 1, e duas para pista2)
	ListaAviao filaAterrissagem1A, filaAterrissagem1B, filaAterrissagem2A, filaAterrissagem2B;
	ListaAviao filaDecolagem1, filaDecolagem2, filaDecolagem3;

	void criarAvioes();
	void decrementarComb();
	void usarPista();
	void aumentarTempoDeEspera();
	void simulacaoUnidadesDeTempo();
	ListaAviao* verificarMenorFilaAterr();
	ListaAviao* menorFilaDec();
	void verificarEmergencias();
	Simulador(const int TEMPO_SIMULACAO);
	void executar();
	void pousandoEmergencias();
	void pousosRegulares();
	void desocuparPistas();
};




#endif /* INCLUDES_HPP__SIMULADOR_HPP_ */
