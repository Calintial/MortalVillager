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

	std::vector<Camino> getIntraCaminos();
	void setIntraCaminos(const std::vector<Camino>& caminos);

private:
	position2di origen;
	position2di destino;

	std::vector<Camino> intracaminos;

};
#endif