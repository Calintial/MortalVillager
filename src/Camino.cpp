#include "Camino.h"

Camino::Camino(position2di inicio){
	posiciones.push_back(inicio);
	peso = 0;
}

Camino::Camino(){
	peso = -1;
}

Camino::Camino(const Camino &c){
	posiciones=c.posiciones;	
	peso=c.peso;
}

Camino::~Camino(){

}

void Camino::addNodo(position2di nodo){
	posiciones.push_back(nodo);
	if (posiciones.size() == 1){
		peso = 0;
	}else{
		peso++;
	}
}

int Camino::getPeso(){
	return peso;
}

std::vector<position2di> Camino::getCamino(){
	return posiciones;
}

position2di Camino::getInicio(){
	return posiciones[0];
}
position2di Camino::getFinal(){
	return posiciones[posiciones.size()-1];		
}
