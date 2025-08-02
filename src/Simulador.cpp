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
#include <iostream>
#include "Aviao.hpp"

Simulador::Simulador(int tempo) : tempoAtual(0), IDAviaoPar(2), IDAviaoImp(1), TEMPO_SIMULACAO(tempo), pista1(1), pista2(2), pista3(3), totalPousos(0), totalDecolagens(0), pousosDeEmergencia(0), somaTempoDec(0), somaTempoPouso(0), pousosEmergenciaPorUn(0), pousosRegularesPorUn(0), decolagensUn(0) {}


ListaAviao * Simulador::verificarMenorFilaAterr() {
	ListaAviao * menorFila = &filaAterrissagem1A;
	if (menorFila->size() > filaAterrissagem1B.size()) {
		menorFila = &filaAterrissagem1B;
	}
	if (menorFila->size() > filaAterrissagem2A.size()) {
		menorFila = &filaAterrissagem2A;
	}
	if (menorFila->size() > filaAterrissagem2B.size()) {
		menorFila = &filaAterrissagem2B;
	}

	return menorFila;
}

ListaAviao * Simulador::menorFilaDec() {
	ListaAviao * menor = &filaDecolagem1;
	if (filaDecolagem2.size() < menor->size()) {
		menor = &filaDecolagem2;
	}
	if (filaDecolagem3.size() < menor->size()) {
		menor = &filaDecolagem3;
	}
	return menor;
}

void Simulador::criarAvioes() {
	std::cout << "CRIANDO AVIÕES..." << std::endl;
	std::cout << std::endl;
	int avioesParaDecolar = rand() % 4;
	int avioesParaPousar = rand() % 4;

	for (int i = 0; i < avioesParaPousar; i++) {
		int combustivel = 1 + rand() % 20;
		ListaAviao &filaParaEnfileirar = *verificarMenorFilaAterr();
		Aviao a(combustivel, IDAviaoImp, 0, true);
		filaParaEnfileirar.enfileirar(a);
		IDAviaoImp += 2;
		std::cout << "Avião:" << a << " inserido na fila de espera para pouso!" << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < avioesParaDecolar; i++) {
		ListaAviao &fila = *menorFilaDec();
		Aviao a(0, IDAviaoPar, 0, false);
		fila.enfileirar(a);
		IDAviaoPar += 2;
		std::cout << "Avião:" << a << " inserido na fila de espera para decolagem" << std::endl;
	}
	std::cout << std::endl;

}

void Simulador::decrementarComb() {
	std::cout << std::endl;
	std::cout << "DECREMENTANDO COMBUSTÍVEL..." << std::endl;
	ListaAviao *listaDeFilasDePouso[] = { &filaAterrissagem1A,
			&filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B };

	for (int i = 0; i < 4; i++) {
		listaDeFilasDePouso[i]->decrementarComb();
	}
}

void Simulador::aumentarTempoDeEspera() {
	std::cout << "INCREMENTANDO TEMPO DE ESPERA..." << std::endl;
	ListaAviao *listaDeFilas[] = { &filaAterrissagem1A, &filaAterrissagem1B,
			&filaAterrissagem2A, &filaAterrissagem2B, &filaDecolagem1,
			&filaDecolagem2, &filaDecolagem3 };
	for (int i = 0; i < 6; i++) {
		listaDeFilas[i]->aumentarTempoEspera();
	}
}

void Simulador::desocuparPistas() {
	std::cout << "DESOCUPANDO PISTAS..." << std::endl;
	Pista *everyPistas[] = { &pista1, &pista2, &pista3 };
	for (int i = 0; i < 2; i++) {
		everyPistas[i]->atualizarEstado();
	}
}

float Simulador::mediaTempoDeEsperaDecolagem() {
	if(totalDecolagens == 0) {
		return 0;
	}
	float media = somaTempoDec / totalDecolagens;
	return media;
}

float Simulador::mediaTempoPousos() {
	if(totalPousos == 0 || somaTempoPouso == 0){
		return 0;
	}
	float media = somaTempoPouso / totalPousos;
	return media;
}

void Simulador::imprimirFilasDePouso() {
	ListaAviao * filas[] = {&filaAterrissagem1A, &filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B};
	for(int i = 0; i < 4; i++) {
		std::cout << "Fila de aterrissagem " << i + 1 << std::endl;
		if(filas[i]->estaVazia()) {
			std::cout << "Fila Vazia!!"<< std::endl;
		} else {
		filas[i]->imprimirAvioes();
		std::cout << std::endl;
		std::cout << std::endl;
		}
	}
}

void Simulador::imprimirFilaDecolagem() {
	ListaAviao * filas[] = {&filaDecolagem1, &filaDecolagem2, &filaDecolagem3};
	for(int i = 0; i < 3; i++) {
		std::cout << "Fila de decolagem " << i + 1  << ": " << std::endl;
		if(filas[i]->estaVazia()) {
			std::cout << "Fila Vazia!!"<< std::endl;
		} else {
		filas[i]->imprimirAvioes();
		std::cout << std::endl;
		std::cout << std::endl;
		}
	}
}

void Simulador::imprimirInfoAcada10un() {
	std::cout << std::endl;
	std::cout << "-- Relatório das últimas 10 Un. --" << std::endl;
	imprimirFilasDePouso();
	imprimirFilaDecolagem();
	std::cout << std::endl;
	std::cout << "Tempo médio de espera para a decolagem: " << mediaTempoDeEsperaDecolagem() << " un. de tempo" << std::endl;
	std::cout << "Tempo médio de espera para a pouso: " << mediaTempoPousos() << " un. de tempo" << std::endl;
	std::cout << "Total de pousos de emergencia até " << tempoAtual + 1 << ": " << pousosDeEmergencia << std::endl;
}


void Simulador::simulacaoUnidadesDeTempo() {
	criarAvioes();
	decrementarComb();
	aumentarTempoDeEspera();
	pousandoEmergencias();
	if (!(pista1.estaOcupada() || pista2.estaOcupada())) {
		pousosRegulares();
	}

	if(!pista1.estaOcupada() || !pista2.estaOcupada() || !pista3.estaOcupada()) {
	decolandoAvioes();
	}
	desocuparPistas();
	std::cout << std::endl;
	std::cout << "-- Relatório de operações do tempo " << tempoAtual << " --" << std::endl;
	infoPorUn();

}

void Simulador::executar() {
	std::cout << " --- INÍCIO DA SIMULAÇÃO ---" << std::endl;
	while (tempoAtual <= TEMPO_SIMULACAO) {

		std::cout << "--- INÍCIO DA UNIDADE DE TEMPO " << tempoAtual  <<" ---" << std::endl;
		if (tempoAtual % 10 == 0) {
			imprimirInfoAcada10un();
		}

		std::cout << std::endl;
		simulacaoUnidadesDeTempo();
		std::cout << std::endl;
		std::cout << "--- FIM DA UNIDADE DE TEMPO " << tempoAtual << " ---" << std::endl;
		tempoAtual++;
	}
	imprimirInfoAcada10un();
	std::cout << " --- FIM DA SIMULAÇÃO --- " << std::endl;


}


void Simulador::pousandoEmergencias() {
	std::cout << "POUSANDO EMERGÊNCIAS..." << std::endl;
	ListaAviao *listas[] = { &filaAterrissagem1A, &filaAterrissagem1B,
			&filaAterrissagem2A, &filaAterrissagem2B };
	pousosEmergenciaPorUn = 0;
	int tentativas = 0;
	while (pousosEmergenciaPorUn < 3 && tentativas < 4) {

		bool aviaoPousou = false;
		NoDeAviao *noEmerg = nullptr;
		ListaAviao *filaDoNo = nullptr;
		for (int i = 0; i < 4; i++) {
			if (!listas[i]->estaVazia()) {
				if (listas[i]->temEmergencia()) {
					NoDeAviao *atual = listas[i]->noComMaisEmergencia();
					if (noEmerg == nullptr || atual->dado < noEmerg->dado) {
						noEmerg = atual;
						filaDoNo = listas[i];

					}
				}
			}
		}

		if (noEmerg != nullptr && filaDoNo != nullptr) {
			Aviao a = noEmerg->dado;
			if (!pista3.estaOcupada()) {
				filaDoNo->desenfileirarAviaoPosicao(noEmerg);
				pista3.pousarAviao(a);
				pousosEmergenciaPorUn++;
				aviaoPousou = true;
				break;
			}
			if (filaDoNo == &filaAterrissagem1A
					|| filaDoNo == &filaAterrissagem1B) {
				if (!pista1.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noEmerg);
					pista1.pousarAviao(a);
					pousosEmergenciaPorUn++;
					aviaoPousou = true;
					break;
				} else {
					std::cout << "ATENÇÃO: Pista 1 ocupada, aeronave " << a
							<< " aguardando...." << std::endl;
				}
			}

			if (filaDoNo == &filaAterrissagem2A
					|| filaDoNo == &filaAterrissagem2B) {
				if (!pista2.estaOcupada()) {

					pista2.pousarAviao(a);
					pousosEmergenciaPorUn++;
					 filaDoNo->desenfileirarAviaoPosicao(noEmerg);
					aviaoPousou = true;
					break;
				} else {
					std::cout << "ATENÇÃO: Pista 2 ocupada, aeronave " << a
							<< " aguardando...." << std::endl;
				}
			}
		}
		 if (!aviaoPousou) break;
			    tentativas++;

	}
	pousosDeEmergencia += pousosEmergenciaPorUn;


}

void Simulador::pousosRegulares() {
	std::cout << std::endl;
	std::cout << "POUSANDO AVIÕES REGULARES..." << std::endl;
	ListaAviao *listas[] = { &filaAterrissagem1A, &filaAterrissagem1B,
			&filaAterrissagem2A, &filaAterrissagem2B };
	NoDeAviao *noMaior = nullptr;
	ListaAviao *filaDoNo = nullptr;
	pousosRegularesPorUn = 0;
	for (int i = 0; i < 4; i++) {
		if (!listas[i]->estaVazia()) {
			NoDeAviao *atual = listas[i]->noComMaisTempoDeEspera();
			if (noMaior == nullptr || atual->dado > noMaior->dado) {
				noMaior = atual;
				filaDoNo = listas[i];
			}
		}

	}
	if (noMaior != nullptr && filaDoNo != nullptr) {

		Aviao a = noMaior->dado;
		if (!(pista1.estaOcupada() && pista2.estaOcupada())) {
			if (filaDoNo == &filaAterrissagem1A
					|| filaDoNo == &filaAterrissagem1B) {
				if (!pista1.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noMaior);
					pista1.pousarAviao(a);
					pousosRegularesPorUn++;
					somaTempoPouso += a.tempoEspera;
				}
			} else if (filaDoNo == &filaAterrissagem2A
					|| filaDoNo == &filaAterrissagem2B) {
				if (!pista2.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noMaior);
					pista2.pousarAviao(a);
					pousosRegularesPorUn++;
					somaTempoPouso += a.tempoEspera;
				}
			}
		}
	}

	totalPousos += pousosRegularesPorUn;

	std::cout << std::endl;
}

void Simulador::decolandoAvioes() {
	std::cout << "DECOLANDO AVIÕES..." << std::endl;
	ListaAviao *listas[] = { &filaDecolagem1, &filaDecolagem2, &filaDecolagem3 };
	decolagensUn = 0;
	NoDeAviao *noMaior = nullptr;
	ListaAviao *filaDoNo = nullptr;

	for (int i = 0; i < 3; i++) {
		if (!listas[i]->estaVazia()) {
			NoDeAviao *atual = listas[i]->noComMaisTempoDeEspera();
			if (noMaior == nullptr || atual->dado > noMaior->dado) {
				noMaior = atual;
				filaDoNo = listas[i];
			}
		}

	}
	if (noMaior != nullptr && filaDoNo != nullptr) {

			Aviao a = noMaior->dado;
			if (filaDoNo == &filaDecolagem1) {
				if (!pista1.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noMaior);
					pista1.decolarAviao(a);
					somaTempoDec += a.tempoEspera;
					decolagensUn++;

				}
			} else if (filaDoNo == &filaDecolagem2) {
				if (!pista2.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noMaior);
					pista2.decolarAviao(a);
				somaTempoDec += a.tempoEspera;
				decolagensUn++;

				}
			} else if (filaDoNo == &filaDecolagem3) {
				if (!pista3.estaOcupada()) {
					filaDoNo->desenfileirarAviaoPosicao(noMaior);
					pista3.decolarAviao(a);
				somaTempoDec += a.tempoEspera;
				decolagensUn++;
				}
			}

	}
	totalDecolagens += decolagensUn;


}

void Simulador::infoPorUn() {
	std::cout << std::endl;
	std::cout << "Pousos de emergencia por unidade: " << pousosEmergenciaPorUn << std::endl;
	std::cout << "Número de pousos regulares nessa unidade de tempo: " << pousosRegularesPorUn << std::endl;
	std::cout << "Número de decolagens nessa unidade de tempo: " << decolagensUn << std::endl;
}
