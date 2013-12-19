#ifndef ENLACE_H
#define ENLACE_H

#include <stdexcept> 
#include <iostream>
#include <irrlicht.h>
#include "Camino.h"

using namespace irr::core;

class Enlace
{
public:
	Enlace(position2di,position2di);
	Enlace(const Enlace&);
	~Enlace();

	position2di getOrigen() const {return origen;}
	position2di getDestino() const {return destino;}

	std::vector<Camino> getIntraCaminosOrigen();
	std::vector<Camino> getIntraCaminosDestino();
	void setIntraCaminosOrigen(const std::vector<Camino>& caminos);
	void setIntraCaminosDestino(const std::vector<Camino>& caminos);

private:
	position2di origen;
	position2di destino;

	std::vector<Camino> intracaminos_origen;
	std::vector<Camino> intracaminos_destino;

};
#endif