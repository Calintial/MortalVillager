#ifndef REGION_H
#define REGION_H

#include <vector>
#include <iostream>
#include <algorithm>
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


//private:
	int inicioX;
	int inicioY;

	int finalX;
	int finalY;

	vertex_t descriptor;

	//std::vector<Enlace*> enlaces;
};

#endif