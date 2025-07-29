/*
 * Simulador.cpp
 *
 *  Created on: 26 de jul. de 2025
 *      Author: luana
 */

#include "Simulador.hpp"
#include <ctime>
#include <cstdlib>
#include "ListaAviao.hpp"
#include "Pista.hpp"
#include<vector>
#include "Aviao.hpp"

Simulador::Simulador(const int TEMPO_SIMULACAO) : tempoAtual(0), IDAviao(1), pista1(1), pista2(2), pista3(3), pousosDeEmergencia(0),  pousosNormais(0), totalDePousos(0), totalPousosEmergencias(0){}

ListaAviao& Simulador::verificarMenorFilaAterr() {
	ListaAviao& menorFila = filaAterrissagem1A;
	if(menorFila.size() > filaAterrissagem1B.size()) {
		menorFila = filaAterrissagem1B;
	}
	if (menorFila.size() > filaAterrissagem2A.size()) {
		menorFila = filaAterrissagem2A;
	}
	if (menorFila.size() > filaAterrissagem2B.size()) {
		menorFila = filaAterrissagem2B;
	}

	return menorFila;
}

ListaAviao& Simulador::menorFilaDec() {
	ListaAviao& menor = filaDecolagem1;
	if (filaDecolagem2.size() < menor.size()) {
		menor = filaDecolagem2;
	} else if (filaDecolagem3.size() < menor.size()) {
		menor = filaDecolagem3;
	}
	return menor;
}

void Simulador::criarAvioes() {
	int avioesParaDecolar = rand() % 4;
	int avioesParaPousar = rand() % 4;
	int IDaviaoImp = IDAviao;
	int IDaviaoPar = IDAviao + 1;

	for (int i = 0; i <  avioesParaPousar; i++){
		int combustivel = rand() % 21;
		ListaAviao& filaParaEnfileirar = verificarMenorFilaAterr();
		filaParaEnfileirar.enfileirar(Aviao(combustivel,IDaviaoImp, tempoAtual,  true));
		IDaviaoImp += 2;
	}

	for (int i = 0; i < avioesParaDecolar; i++) {
		ListaAviao& fila = menorFilaDec();
		fila.enfileirar(Aviao(0, IDaviaoPar, tempoAtual,  false));
		IDaviaoPar += 2;
	}

}

void Simulador::decrementarComb() {
	ListaAviao*  listaDeFilasDePouso [] = {&filaAterrissagem1A, &filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B};

	for(int i = 0; i < 4;i++) {
		listaDeFilasDePouso[i]->decrementarComb();
	}
}

void Simulador::aumentarTempoDeEspera() {
	ListaAviao*  listaDeFilas [] = {&filaAterrissagem1A, &filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B, &filaDecolagem1, &filaDecolagem2, &filaDecolagem3};
	for(int i = 0; i < 6; i ++) {
			listaDeFilas[i]->aumentarTempoEspera();
	}
}

void Simulador::desocuparPistas() {
	Pista * everyPistas[] = {&pista1, &pista2, &pista3};
	for(int i = 0; i < 2;i++){
		everyPistas[i]->atualizarEstado();
	}
}

void Simulador::pousandoEmergencias() {
	ListaAviao * listaDeFilasDePouso [] = {&filaAterrissagem1A, &filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B};
	for(int i = 0 ;i < 4 && pousosDeEmergencia < 3; i++) {
		if(listaDeFilasDePouso[i]->temEmergencia()) {
			Aviao a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(listaDeFilasDePouso[i]->noComMaisEmergencia());
			 if(!pista3.estaOcupada()) {
				 pista3.pousarAviao(a);
				 pousosDeEmergencia++;
			 } else if(!pista1.estaOcupada()){
				 pista1.pousarAviao(a);
				 pousosDeEmergencia++;
			 } else if(!pista2.estaOcupada()) {
				 pista2.pousarAviao(a);
				 pousosDeEmergencia++;
			 }
		}
	}
}


void Simulador::pousosRegulares() {
	pousosNormais = 0;
	ListaAviao * listaDeFilasDePouso [] = {&filaAterrissagem1A, &filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B};
	for(int i = 0 ;i < 4 && pousosNormais <= 3; i++) {
		Aviao a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(listaDeFilasDePouso[i]->noComMaisTempoDeEspera());
		if(i == 0 || i == 1) {
			if(!pista1.estaOcupada()) {
			pista1.pousarAviao(a);
			pousosNormais++;
			}
		} else if(i == 2 || i == 3) {
			if(!pista2.estaOcupada()) {
				pista2.pousarAviao(a);
				pousosNormais++;
			}
		}
	}
	totalPousosEmergencias += pousosDeEmergencia;
	totalDePousos += pousosNormais + pousosDeEmergencia;
}



void Simulador::simulacaoUnidadesDeTempo() {
	criarAvioes();
	decrementarComb();
	pousandoEmergencias();
}
