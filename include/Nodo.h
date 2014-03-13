#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <irrlicht.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
using namespace irr::core;

class Nodo
{
public:
	Nodo(position2di _pos,int _g,Nodo *_padre);
	Nodo(position2di _pos,int _g,int _h,Nodo *_padre);
	Nodo(const Nodo&);
	~Nodo();

	bool operator<(const Nodo& nodo) const;

	position2di posicion;
	int g;
    int h;
    int f;
    Nodo* padre;	
};
#endif