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

Simulador::Simulador() : tempoAtual(0), IDAviao(1){
	filaAterrissagem1A = new ListaAviao();
	filaAterrissagem1B = new ListaAviao();
	filaAterrissagem2A = new ListaAviao();
	filaAterrissagem2B = new ListaAviao();
	filaDecolagem1 = new ListaAviao();
	filaDecolagem2 = new ListaAviao();
	filaDecolagem3 = new ListaAviao();

	pista1 = new Pista(1, false,  filaDecolagem1);
	pista2 = new Pista(2, false, filaDecolagem2);
	pista3 = new Pista(3, false, filaDecolagem3);
}

ListaAviao* Simulador::verificarMenorFilaAterr(ListaAviao * filaAterrissagem1A, ListaAviao *filaAterrissagem1B,ListaAviao *filaAterrissagem2A, ListaAviao *filaAterrissagem2B) {
	ListaAviao * menorFila = filaAterrissagem1A;
	if(menorFila->size() > filaAterrissagem1B->size()) {
		menorFila = filaAterrissagem1B;
	} else if (menorFila->size() > filaAterrissagem2A->size()) {
		menorFila = filaAterrissagem2A;
	} else if (menorFila->size() > filaAterrissagem2B->size()) {
		menorFila = filaAterrissagem2B;
	}

	return menorFila;
}

ListaAviao* Simulador::menorFilaDec(ListaAviao *lista1, ListaAviao *lista2, ListaAviao *lista3) {
	ListaAviao* menor = lista1;
	if (lista2->size() < menor->size()) {
		menor = lista2;
	} else if (lista3->size() < menor->size()) {
		menor = lista3;
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
		ListaAviao * filaParaEnfileirar = verificarMenorFilaAterr(filaAterrissagem1A, filaAterrissagem1B, filaAterrissagem2A, filaAterrissagem2B);
		filaParaEnfileirar->enfileirar(Aviao(combustivel,IDaviaoImp, tempoAtual,  true, -1));
		IDaviaoImp += 2;
	}

	for (int i = 0; i < avioesParaDecolar; i++) {
		ListaAviao * fila = menorFilaDec(filaDecolagem1, filaDecolagem2, filaDecolagem3);
		fila->enfileirar(Aviao(0, IDaviaoPar, tempoAtual,  false, -1));
		IDaviaoPar += 2;
	}

}

void Simulador::verificarEmergencias() {
	int AvioesEmerg = 0;
	ListaAviao *TodasAsFilas[4];
	TodasAsFilas[0] = filaAterrissagem1A;
	TodasAsFilas[1] = filaAterrissagem1B;
	TodasAsFilas[2] = filaAterrissagem2A;
	TodasAsFilas[3] = filaAterrissagem2B;


	for(int i = 0; i < 4; i++) {
		TodasAsFilas[i]->desenfileirarAviaoEmergencia();
	}

	filaAterrissagem1A->desenfileirarAviaoEmergencia();
	filaAterrissagem1B->decrementarComb();
	filaAterrissagem2A->decrementarComb();
	filaAterrissagem2B->decrementarComb();
}

void Simulador::decrementarComb() {
	filaAterrissagem1A->decrementarComb();
	filaAterrissagem1B->decrementarComb();
	filaAterrissagem2A->decrementarComb();
	filaAterrissagem2B->decrementarComb();
}

void Simulador::simulacaoUnidadesDeTempo() {
	criarAvioes();
	decrementarComb();

}
