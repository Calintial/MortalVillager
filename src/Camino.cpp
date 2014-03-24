#include "Camino.h"

Camino::Camino(position2di _inicio){
	//posiciones.push_back(_inicio);
	peso = 0;
	inicio = _inicio;
}

Camino::Camino():inicio(position2di(-1,-1)){
	peso = -1;
}

Camino::Camino(const Camino &c){
	posiciones=c.getCamino();
	peso=c.getPeso();
	inicio=c.getInicio();
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

int Camino::getPeso() const{
	return peso;
}

std::vector<position2di> Camino::getCamino() const{
	return posiciones;
}

position2di Camino::getInicio() const{
	//return posiciones[0];
	return inicio;
}
position2di Camino::getFinal() const{
	return posiciones[posiciones.size()-1];		
}

void Camino::addCamino(const Camino& nuevoCamino){
	for(position2di casilla: nuevoCamino.getCamino()){
		addNodo(casilla);
	}
}

position2di Camino::darPaso(){
	position2di paso = *posiciones.begin();
	posiciones.erase(posiciones.begin());
	peso--;
	inicio = paso;
	return paso;
}
