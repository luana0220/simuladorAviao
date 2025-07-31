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
#include<iostream>
#include "Aviao.hpp"

Simulador::Simulador(int TEMPO_SIMULACAO) :
TEMPO_SIMULACAO(TEMPO_SIMULACAO),
		tempoAtual(0), IDAviaoPar(2), IDAviaoImp(1), pista1(1), pista2(2), pista3(3), pousosDeEmergencia(
				0), pousosNormais(0), totalDePousos(0), totalPousosEmergencias(
				0), numDecolagens(0), somaDosTemposDeEsperaDecolagem(0), somaDosTemposPousos(
				0) {}


ListaAviao* Simulador::verificarMenorFilaAterr() {
	ListaAviao *menorFila = &filaAterrissagem1A;
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

ListaAviao* Simulador::menorFilaDec() {
	ListaAviao *menor = &filaDecolagem1;
	if (filaDecolagem2.size() < menor->size()) {
		menor = &filaDecolagem2;
	}
	if (filaDecolagem3.size() < menor->size()) {
		menor = &filaDecolagem3;
	}
	return menor;
}

void Simulador::criarAvioes() {
	int avioesParaDecolar = rand() % 4;
	int avioesParaPousar = rand() % 4;

	for (int i = 0; i < avioesParaPousar; i++) {
		int combustivel = 1 + rand() % 20;
		ListaAviao &filaParaEnfileirar = *verificarMenorFilaAterr();
		filaParaEnfileirar.enfileirar(Aviao(combustivel, IDAviaoImp, tempoAtual, true));

		IDAviaoImp += 2;
	}

	for (int i = 0; i < avioesParaDecolar; i++) {
		ListaAviao &fila = *menorFilaDec();
		fila.enfileirar(Aviao(0, IDAviaoPar, tempoAtual, false));
		IDAviaoPar += 2;
	}
	std::cout << "[T" << tempoAtual << "] Fila 1A: " << filaAterrissagem1A.size()
	          << ", 1B: " << filaAterrissagem1B.size()
	          << ", 2A: " << filaAterrissagem2A.size()
	          << ", 2B: " << filaAterrissagem2B.size()
	          << ", Dec1: " << filaDecolagem1.size()
	          << ", Dec2: " << filaDecolagem2.size()
	          << ", Dec3: " << filaDecolagem3.size() << std::endl;

}

void Simulador::decrementarComb() {
	ListaAviao *listaDeFilasDePouso[] = { &filaAterrissagem1A,
			&filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B };

	for (int i = 0; i < 4; i++) {
		if(!listaDeFilasDePouso[i]->estaVazia()) {
		listaDeFilasDePouso[i]->decrementarComb();
		}
	}
}

void Simulador::aumentarTempoDeEspera() {
	ListaAviao *listaDeFilas[] = { &filaAterrissagem1A, &filaAterrissagem1B,
			&filaAterrissagem2A, &filaAterrissagem2B, &filaDecolagem1,
			&filaDecolagem2, &filaDecolagem3 };
	for (int i = 0; i < 7; i++) {
		if(!listaDeFilas[i]->estaVazia()) {
		listaDeFilas[i]->aumentarTempoEspera();
		}
	}
}

void Simulador::desocuparPistas() {
	Pista *everyPistas[] = { &pista1, &pista2, &pista3 };
	for (int i = 0; i < 2; i++) {
		everyPistas[i]->atualizarEstado();
	}
}

void Simulador::pousandoEmergencias() {
	ListaAviao *listaDeFilasDePouso[] = { &filaAterrissagem1A,
			&filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B };
	Aviao a;
	for (int i = 0; i < 4 && pousosDeEmergencia < 3; i++) {
		if(!listaDeFilasDePouso[i]->estaVazia()) {
		if (listaDeFilasDePouso[i]->temEmergencia()) {

			if (!pista3.estaOcupada()) {
				a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(
						listaDeFilasDePouso[i]->noComMaisEmergencia());
				pista3.pousarAviao(a);
				pousosDeEmergencia++;
			} else if (!pista1.estaOcupada()) {
				a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(
						listaDeFilasDePouso[i]->noComMaisEmergencia());
				pista1.pousarAviao(a);
				pousosDeEmergencia++;
			} else if (!pista2.estaOcupada()) {
				a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(
						listaDeFilasDePouso[i]->noComMaisEmergencia());
				pista2.pousarAviao(a);
				pousosDeEmergencia++;
			}
		}
		}
	}
}

void Simulador::pousosRegulares() {
	ListaAviao *listaDeFilasDePouso[] = { &filaAterrissagem1A,
			&filaAterrissagem1B, &filaAterrissagem2A, &filaAterrissagem2B };
	Aviao a;
	for (int i = 0; i < 4 && pousosNormais <= 3; i++) {

		if (i == 0 || i == 1) {
			if (!pista1.estaOcupada()) {
				if (!listaDeFilasDePouso[i]->estaVazia()) {
					a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(listaDeFilasDePouso[i]->noComMaisTempoDeEspera());
					pista1.pousarAviao(a);
					pousosNormais++;
					somaDosTemposPousos += a.tempoEspera;
				}
			}
		} else if (i == 2 || i == 3) {
			if (!pista2.estaOcupada()) {
				if(!listaDeFilasDePouso[i]->estaVazia()) {
				a = listaDeFilasDePouso[i]->desenfileirarAviaoPosicao(
						listaDeFilasDePouso[i]->noComMaisTempoDeEspera());
				pista2.pousarAviao(a);
				pousosNormais++;
				somaDosTemposPousos += a.tempoEspera;
				}
			}
		}
		totalPousosEmergencias += pousosDeEmergencia;
		totalDePousos += pousosNormais + pousosDeEmergencia;
	}
}

void Simulador::decolandoAvioes() {
	ListaAviao *listaDeFilasDecolagem[] = { &filaDecolagem1, &filaDecolagem2,
			&filaDecolagem3 };
	for (int i = 0; i < 3; i++) {
		if (!pista1.estaOcupada() || !pista2.estaOcupada()
				|| !pista3.estaOcupada()) {
			if (!listaDeFilasDecolagem[i]->estaVazia()) {
				Aviao a = listaDeFilasDecolagem[i]->desenfileirarAviaoPosicao(
						listaDeFilasDecolagem[i]->noComMaisTempoDeEspera());
				if (!pista1.estaOcupada()) {
					pista1.decolarAviao(a);

				} else if (!pista2.estaOcupada()) {
					pista2.decolarAviao(a);
				} else if (!pista3.estaOcupada()) {
					pista3.decolarAviao(a);

				}
				numDecolagens++;
				somaDosTemposDeEsperaDecolagem += a.tempoEspera;
			}
		}
	}
}

void Simulador::imprimirFilasDePouso() {
	ListaAviao *filas[] = { &filaAterrissagem1A, &filaAterrissagem1B,
			&filaAterrissagem2A, &filaAterrissagem2B };
	for (int i = 0; i < 4; i++) {
		if (filas[i]->estaVazia()) {
			std::cout << "Fila de aterrissagem " << i + 1 << std::endl;
			filas[i]->imprimirAvioes();
		}
	}
}

void Simulador::imprimirFilaDecolagem() {
	ListaAviao *filas[] = { &filaDecolagem1, &filaDecolagem2, &filaDecolagem3 };
	for (int i = 0; i < 3; i++) {
		std::cout << "Fila de decolagem " << i + 1 << std::endl;
		if(!filas[i]->estaVazia()) {
		filas[i]->imprimirAvioes();
		}
	}
}

float Simulador::mediaTempoDeEsperaDecolagem() {
	float media = (somaDosTemposDeEsperaDecolagem / numDecolagens);
	return media;
}

float Simulador::mediaTempoPousos() {
	float media = (somaDosTemposPousos / (totalDePousos));
	return media;
}

void Simulador::imprimirInfoAcada10un() {
	imprimirFilasDePouso();
	imprimirFilaDecolagem();
	std::cout << "A média do tempo de espera para decolagem é: "
			<< mediaTempoDeEsperaDecolagem() << std::endl;
	std::cout << "A média do tempo de espera para aterrissagem é: "
			<< mediaTempoPousos() << std::endl;
	std::cout
			<< "Quantidade de aeronaves que pousaram em situação de emergência: "
			<< pousosDeEmergencia << std::endl;

}

void Simulador::simulacaoUnidadesDeTempo() {
	criarAvioes();
	decrementarComb();
	aumentarTempoDeEspera();
	pousandoEmergencias();
	pousosRegulares();
	decolandoAvioes();
	desocuparPistas();
}

void Simulador::executar() {
	while (tempoAtual != TEMPO_SIMULACAO) {
		simulacaoUnidadesDeTempo();
		tempoAtual++;
		if (tempoAtual % 10 == 0) {
			imprimirInfoAcada10un();
		}
	}
}
