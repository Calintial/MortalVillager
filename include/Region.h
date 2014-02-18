#ifndef REGION_H
#define REGION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <irrlicht.h>
#include "Enlace.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
class Region;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Region,Enlace > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

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
	position2di getInicio();
	position2di getFinal();


//private:
	//int inicioX;
	//int inicioY;
	position2di inicio;
	position2di final;

	//int finalX;
	//int finalY;

	vertex_t descriptor;

	//std::vector<Enlace*> enlaces;
};

#endif