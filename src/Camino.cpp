#include "Camino.h"

Camino::Camino(position2di inicio){
	posiciones.push_back(inicio);
	peso = 0;
}

Camino::Camino(const Camino &c){
	posiciones=c.posiciones;	
	peso=c.peso;
}

Camino::~Camino(){

}

void Camino::addNodo(position2di nodo){
	posiciones.push_back(nodo);
	peso++;
}

int Camino::getPeso(){
	return peso;
}

std::vector<position2di> Camino::getCamino(){
	return posiciones;
}

