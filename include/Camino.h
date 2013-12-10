#ifndef CAMINO_H
#define CAMINO_H

#include <vector>
#include <iostream>
#include <irrlicht.h>


using namespace irr;
using namespace core;

class Camino{
public:
	Camino(position2di inicio);
	~Camino();
	void addNodo(position2di nodo);
	int getPeso();
	std::vector<position2di> getCamino();

private:
	std::vector<position2di> camino;
	int peso;
};

#endif