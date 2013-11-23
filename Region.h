#ifndef REGION_H
#define REGION_H

#include <vector>
#include <iostream>
#include <algorithm>
//#include "Enlace.h"

class Region
{
public:
	Region();
	Region(int,int,int,int);
	~Region();
/*	void add(Enlace*);
	void remove(Enlace*);*/
	bool isInside(int x, int y);
//	std::vector<Region*> getConnectedRegions();


//private:
	int inicioX;
	int inicioY;

	int finalX;
	int finalY;

	//std::vector<Enlace*> enlaces;
};

#endif