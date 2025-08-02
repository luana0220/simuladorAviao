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
}

ListaAviao::~ListaAviao() {
	NoDeAviao * deletar;
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

int ListaAviao::size() {
	return tamanho;
}

NoDeAviao * ListaAviao::primeiroFila() {
	if(estaVazia()) {
		throw std::runtime_error("Fila Vazia");
	}
	return primeiro;
}

void ListaAviao::desenfileirarAviaoPosicao(NoDeAviao * no) {
	if(no == nullptr) {
		throw std::invalid_argument("Nó inválido!");
	}
	if(no == primeiro) {
		return desenfileirarInicio();
	}

	NoDeAviao * anterior = nullptr;
	NoDeAviao * NoAtual = primeiro;
	while (NoAtual != no) {
		anterior = NoAtual;
		NoAtual = NoAtual->proximo;
	}

	if (anterior == nullptr) {
		primeiro = NoAtual->proximo;
	} else {
		anterior->proximo = NoAtual->proximo;
	}

	delete NoAtual;
	tamanho--;
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
		noAtual = noAtual->proximo;
	}
}

void ListaAviao::aumentarTempoEspera() {
	NoDeAviao *noAtual = primeiro;
	while (noAtual != nullptr) {
		noAtual->dado.aumentarTempoDeEspera();
		noAtual = noAtual->proximo;
	}
}

NoDeAviao * ListaAviao::noComMaisTempoDeEspera() {
	NoDeAviao *NoAtual = primeiro;
	NoDeAviao *noMaior = primeiro;

	while(NoAtual != nullptr) {
		if (NoAtual->dado > noMaior->dado) {
			noMaior = NoAtual;
		}
		NoAtual = NoAtual->proximo;
	}
	return noMaior;
}

void ListaAviao::imprimirAvioes() {
	NoDeAviao * temp = primeiro;
	while(temp != nullptr) {
		temp->dado.imprimirAviao(temp->dado);
		temp = temp->proximo;
	}
}

void ListaAviao::desenfileirarInicio() {
	if(estaVazia()) {
		throw std::runtime_error("Fila Vazia");
	}
	NoDeAviao * temp = primeiro;
	primeiro = primeiro->proximo;

	delete temp;
	tamanho--;
}
