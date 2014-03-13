#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <irrlicht.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
using namespace irr::core;

class Nodo;
class Camino;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Nodo,Camino > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class Nodo
{
public:
	Nodo(position2di _pos,int _g,int _h,Nodo *_padre);
	Nodo();
	Nodo(const Nodo&);
	~Nodo();

	bool operator<(const Nodo& nodo) const;
	bool operator==(const Nodo& nodo) const;

	position2di posicion;
	int g;
    int h;
    int f;
    Nodo* padre;
    vertex_t descriptor;
};
#endif



