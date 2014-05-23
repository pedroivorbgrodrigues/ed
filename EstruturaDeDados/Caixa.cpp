#include "stdafx.h"
#include "Caixa.h"
#include <string.h>

Caixa::Caixa(std::string identificador, int desempenho, int salario) {
	this->m_clientes = new FilaEncadeadaCircular<Cliente>();
	this->m_numeroDeClientesNaFila = 0;
	this->m_numeroDeClientesAtendidos = 0;
	this->m_tempoMedioDeEsperaDeUmClienteNaFila = 0;
	this->m_faturamentoTotal = 0;
	this->m_faturamentoMedio = 0;
	this->m_identificador = identificador;
	this->m_eficiencia = desempenho;
	this->m_salario = salario;
}
Caixa::~Caixa() {
}
void Caixa::recebeCliente(Cliente *novo, int tempoAtual) {
	this->m_clientes->adiciona(novo);
	this->m_numeroDeClientesNaFila += 1;
	int tempo = novo->getNProdutos();
	switch (m_eficiencia) {
	case EFICIENTE:
		if (novo->pagamentoCheque())
			tempo += 10;
		break;
	case MEDIO:
		tempo = tempo * 2;
		if (novo->pagamentoCheque())
			tempo += 25;
		break;
	case RUIM:
		tempo = tempo * 4;
		if (novo->pagamentoCheque())
			tempo += 60;
	}
	this->m_tempoMedioDeEsperaDeUmClienteNaFila += tempo;
	novo->setTempoSaida(
		tempo + this->m_tempoMedioDeEsperaDeUmClienteNaFila + tempoAtual);
}
int Caixa::atendeCliente(int tempoAtual) {
	this->m_tempoMedioDeEsperaDeUmClienteNaFila -= 1;
	//try{
	Cliente *proximo = m_clientes->retira();
	if (proximo->getTempoSaida() == tempoAtual) {
		this->m_faturamentoTotal += proximo->getValorTotalCompras();
		this->m_numeroDeClientesAtendidos += 1;
		this->m_numeroDeClientesNaFila -= 1;
		delete (proximo);
	} else {
		this->m_clientes->adicionaNoInicio(proximo);
	}
	return this->m_clientes->obterTamanho();
} //} catch(){}
}
int Caixa::getNroClientes() {
	return this->m_numeroDeClientesNaFila();
}
int Caixa::getNroClientesAtendidos() {
	return this->m_numeroDeClientesAtendidos;
}
int Caixa::getTempoEspera() {
	return this->m_tempoMedioDeEsperaDeUmClienteNaFila;
}
double Caixa::getFaturamento() {
	return this->m_faturamentoTotal;
}
double Caixa::getFaturamentoMedio() {
	return this->m_faturamentoMedio;
}
std::string Caixa::getIdentificador() {
	return this->m_identificador;
}
int Caixa::getDesempenho() {
	return this->m_eficiencia;
}
int Caixa::getNroProdutos() {
	int numero = 0;
	Cliente *atual;
	for (int i = 0; i < this->m_clientes->obterTamanho(); i++) {
		atual = this->m_clientes->retira();
		numero += atual->getNProdutos();
		this->m_clientes->adiciona(atual);
	}
	return numero;
}
