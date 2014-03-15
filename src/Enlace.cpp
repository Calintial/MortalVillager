#include "Region.h"

Enlace::Enlace(position2di _origen,position2di _destino)
	:origen(_origen),destino(_destino)
{}

Enlace::Enlace(const Enlace& copia){
	origen = copia.origen;
	destino = copia.destino;
	intracaminos_origen = copia.intracaminos_origen;
	intracaminos_destino = copia.intracaminos_destino;
}

Enlace::~Enlace(){}

std::vector<Camino> Enlace::getIntraCaminosOrigen(){
	return intracaminos_origen;
}

std::vector<Camino> Enlace::getIntraCaminosDestino(){
	return intracaminos_destino;
}

void Enlace::setIntraCaminosOrigen(const std::vector<Camino>& caminos){
	intracaminos_origen = caminos;
}

void Enlace::setIntraCaminosDestino(const std::vector<Camino>& caminos){
	intracaminos_destino = caminos;
}