#ifndef CAMINO_H
#define CAMINO_H

#include <vector>
#include <iostream>
#include <irrlicht.h>
#include "Nodo.h"

using namespace irr;
using namespace core;

class Camino{
public:
	Camino(position2di inicio);
	Camino();
	~Camino();
	void addNodo(position2di nodo);
	int getPeso();
	std::vector<position2di> getCamino();
	void addNodoCamino(Nodo _nodo);

private:
	std::vector<position2di> camino;
	Nodo caminoNodo;
	int peso;
};

#endif