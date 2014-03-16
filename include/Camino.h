#ifndef CAMINO_H
#define CAMINO_H

#include <vector>
#include <iostream>
#include <irrlicht.h>

using namespace irr;
using namespace core;

class Camino{
public:
	Camino();
	Camino(position2di inicio);
	Camino(const Camino &c);
	~Camino();

	void addNodo(position2di nodo);
	int getPeso() const;
	std::vector<position2di> getCamino() const;
	position2di getInicio() const;
	position2di getFinal() const;
	void addCamino(const Camino&);

private:
	std::vector<position2di> posiciones;
	int peso;
};

#endif