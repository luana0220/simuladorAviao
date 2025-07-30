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
	return primeiro;
}

Aviao ListaAviao::desenfileirarAviaoPosicao(NoDeAviao * no) {
	if(no == nullptr) {
		throw std::invalid_argument("Nó inválido!");
	}
	if(estaVazia()) {
			throw std::runtime_error("Fila Vazia!!1");
		}

	NoDeAviao * anterior = nullptr;
	NoDeAviao * NoAtual = primeiro;
	while (NoAtual != no) {
		anterior = NoAtual;
		NoAtual = NoAtual->proximo;
	}
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
	if(estaVazia()) {
			throw std::runtime_error("Fila Vazia!!2");
		}
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

	if(estaVazia()) {
				throw std::runtime_error("Fila Vazia!!0");
		}
	NoDeAviao *NoAtual = primeiro;

	NoDeAviao *noMenor = primeiro;

	while (NoAtual != nullptr) {
		if(NoAtual->dado.ehPouso) {
			if (NoAtual->dado < noMenor->dado) {
				noMenor = NoAtual;
			}
		}
		NoAtual = NoAtual->proximo;
	}
	return noMenor;
}

void ListaAviao::decrementarComb() {
	if(estaVazia()) {
			throw std::runtime_error("Fila Vazia!!3");
	}
	NoDeAviao *noAtual = primeiro;
	while (noAtual != nullptr) {
		if(noAtual->dado.ehPouso) {
		noAtual->dado.decrementarCombAviao();
		}
		noAtual = noAtual->proximo;
	}
}

void ListaAviao::aumentarTempoEspera() {
	if(estaVazia()) {
			throw std::runtime_error("Fila Vazia!!4");
		}
	NoDeAviao *noAtual = primeiro;
	while (noAtual != nullptr) {
		noAtual->dado.aumentarTempoDeEspera();
		noAtual = noAtual->proximo;
	}
}

NoDeAviao* ListaAviao::noComMaisTempoDeEspera() {
	if (estaVazia()) {
		throw std::runtime_error("Fila Vazia!!5");
	}
	NoDeAviao *NoAtual = primeiro;
	NoDeAviao *noMaior = primeiro;

	while (NoAtual != nullptr) {
		if (NoAtual->dado > noMaior->dado) {
			noMaior = NoAtual;
		}
		NoAtual = NoAtual->proximo;
	}

	return noMaior;
}

void ListaAviao::imprimirAvioes() {
	if(estaVazia()) {
		throw std::runtime_error("Fila Vazia!!6");
	}
	NoDeAviao * temp = primeiro;
	while(temp != nullptr) {
	   temp->dado.imprimirAviao(temp->dado);
	   temp = temp->proximo;
	}
}
