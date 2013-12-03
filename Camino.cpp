#include "Camino.h"

Camino::Camino(position2di inicio){
	camino.push_back(inicio);
	peso = 0;
}

Camino::~Camino(){

}

void Camino::addNodo(position2di nodo){
	camino.push_back(nodo);
	peso++;
}

int Camino::getPeso(){
	return peso;
}

std::vector<position2di> Camino::getCamino(){
	return camino;
}