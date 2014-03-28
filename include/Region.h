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
	bool isInside(int x, int y) const;
	bool isInside(position2di) const;
//	std::vector<Region*> getConnectedRegions();
	position2di getInicio() const;
	position2di getFinal() const;
	void clear();
	bool operator==(const Region & ) const;
	bool operator!=(const Region & ) const;


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