#include "Region.h"

Enlace::Enlace(position2di _origen,position2di _destino)
	:origen(_origen),destino(_destino)
{}

Enlace::Enlace(const Enlace& copia){
	origen = copia.origen;
	destino = copia.destino;
	intracaminos = copia.intracaminos;
}

Enlace::~Enlace(){}

std::vector<Camino> Enlace::getIntraCaminos(){
	return intracaminos;
}

void Enlace::setIntraCaminos(const std::vector<Camino>& caminos){
	intracaminos = caminos;
}