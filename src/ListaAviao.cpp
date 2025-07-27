/*
 * ListaAviao.cpp
 *
 *  Created on: 25 de jul. de 2025
 *      Author: luana
 */
#include "ListaAviao.hpp"
#include<iostream>
#include <stdexcept>

ListaAviao::ListaAviao() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

void ListaAviao::enfileirar(const Aviao& dado) {
	NoDeAviao * aviao = new NoDeAviao(dado);
	if (estaVazia()) {
		primeiro = aviao;
		ultimo = aviao;
	} else {
	ultimo->proximo = aviao;
	ultimo = aviao;
	}
	tamanho++;
	std::cout << "Aviao inserido!" << std::endl;
}

ListaAviao::~ListaAviao() {
	ListaAviao * deletar;
	while (primeiro != nullptr) {
		deletar = primeiro;
		primeiro = primeiro->proximo;
		delete deletar;
	}
	ultimo = nullptr;
	tamanho = 0;

}

bool ListaAviao::estaVazia() {
	return primeiro == nullptr;
}

Aviao * ListaAviao::desenfileirar() {
	if (estaVazia()) {
		throw std::runtime_error("Pista Vazia");
	}

	Aviao * AviaoQuePousou = primeiro;
	NoDeAviao * temp = primeiro;
	primeiro = primeiro->proximo;
	delete temp;
	tamanho--;
	return AviaoQuePousou;
}

int ListaAviao::size() {
	return tamanho;
}

NoDeAviao * ListaAviao::primeiroFila() {
	return primeiro;
}

Aviao ListaAviao::desenfileirarAviaoEmergencia() {
	//if(no == primeiro) {
		//desenfileirar();
	//	return aviaoDeletado;
	//}

	NoDeAviao * anterior = nullptr;
	NoDeAviao * NoAtual = primeiro;

	NoDeAviao * noMenor = primeiro;
	NoDeAviao * anteriorMenor = nullptr;
	while(NoAtual != nullptr) {

		if (NoAtual->dado < noMenor->dado) {
			noMenor = NoAtual;
			anteriorMenor = anterior;
		}
		anterior = NoAtual;
		NoAtual = NoAtual->proximo;

	}
	/*anterior = NoAtual;
	NoAtual = NoAtual->proximo;
	anterior->proximo = NoAtual->proximo;*/

	Aviao aviaoDeletado = noMenor->dado;
	if(noMenor == primeiro) {
		desenfileirar();
	} else {
		anteriorMenor->proximo = noMenor->proximo;
		if(noMenor == ultimo) {
			ultimo = anteriorMenor;
		}
		delete noMenor;
		tamanho--;
	}
	return aviaoDeletado;

}

void ListaAviao::decrementarComb() {
	NoDeAviao * NoAtual = primeiro;
	while(NoAtual != nullptr) {
		if(NoAtual->dado.ehPouso) {
			NoAtual->dado.diminuirComb();
		}
		NoAtual = NoAtual->proximo;
	}
}
