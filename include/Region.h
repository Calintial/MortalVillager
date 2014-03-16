#ifndef REGION_H
#define REGION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <irrlicht.h>
#include "Nodo.h"
using namespace irr;
using namespace core;

class Region
{
public:
	Region();
	Region(int,int,int,int);
	~Region();
/*	void add(Enlace*);
	void remove(Enlace*);*/
	bool isInside(int x, int y);
	bool isInside(position2di);
//	std::vector<Region*> getConnectedRegions();
	position2di getInicio();
	position2di getFinal();


//private:
	//int inicioX;
	//int inicioY;
	position2di inicio;
	position2di final;

	//int finalX;
	//int finalY;

	//vertex_t descriptor;

	std::vector<NodoRegional*> nodos;
};

#endif