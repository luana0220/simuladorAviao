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

Aviao ListaAviao::desenfileirarAviaoPosicao(NoDeAviao * no) {
	if(no == nullptr) {
		throw std::invalid_argument("Nó inválido!");
	}

	NoDeAviao * anterior = nullptr;
	NoDeAviao * NoAtual = primeiro;
	while (NoAtual != no) {
		anterior = NoAtual;
		NoAtual = NoAtual->proximo;
	}
	anterior = NoAtual;
	NoAtual = NoAtual->proximo;
	Aviao a = NoAtual->dado;
	if (anterior == nullptr) {
		primeiro = NoAtual->proximo;
	} else {
		anterior->proximo = NoAtual->proximo;
	}

	delete NoAtual;
	tamanho--;
	return a;
}


bool ListaAviao::temEmergencia() {
	NoDeAviao * noAtual = primeiro;
	while(noAtual != nullptr) {
		if(noAtual->dado.combustivel <= 0) {
			return true;
		} else {
			noAtual = noAtual->proximo;
		}
	}
	return false;
}

NoDeAviao * ListaAviao::noComMaisEmergencia() {

	NoDeAviao *NoAtual = primeiro;

	NoDeAviao *noMenor = primeiro;

	while (NoAtual != nullptr) {
			if (NoAtual->dado < noMenor->dado) {
				noMenor = NoAtual;
			}
		NoAtual = NoAtual->proximo;
	}
	return noMenor;
}

void ListaAviao::decrementarComb() {
	NoDeAviao *noAtual = primeiro;
	while (noAtual != nullptr) {
		noAtual->dado.decrementarCombAviao();
		noAtual = primeiro->proximo;
	}
}

void ListaAviao::aumentarTempoEspera() {
	NoDeAviao *noAtual = primeiro;
	while (noAtual != nullptr) {
		noAtual->dado.aumentarTempoDeEspera();
		noAtual = primeiro->proximo;
	}
}

NoDeAviao * ListaAviao::noComMaisTempoDeEspera() {
	NoDeAviao *NoAtual = primeiro;
	NoDeAviao *noMaior = primeiro;

	while(NoAtual != nullptr) {
		if (NoAtual->dado > noMaior->dado) {
			noMaior = NoAtual;
		}
		NoAtual = primeiro->proximo;
	}
	return noMaior;
}
