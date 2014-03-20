#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include "boost/graph/labeled_graph.hpp"
using namespace irr::core;

class NodoRegional;
class Camino;
class mapa2D;
class Region;
typedef boost::labeled_graph<
    boost::adjacency_list<boost::listS, boost::listS, boost::undirectedS, NodoRegional,Camino >,
    std::string
> Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class Nodo
{
public:

	Nodo(position2di _pos,int _g,int _h,Nodo* _padre);
	Nodo();
	Nodo(const Nodo&);
	virtual ~Nodo();

	static int distancia(position2di,position2di);
	int distancia(position2di destino);

	position2di getPosicion() const;
	int getG() const;
	int getH() const;
	int getF() const;
	Nodo* getPadre() const;

	void init(position2di _pos);
	void update(int _g,int _h,Nodo* _padre);
	virtual std::vector<Nodo*> getHijos(position2di destino) = 0;
	virtual Camino* getCaminoDesdePadre() = 0;

	bool operator<(const Nodo& nodo) const;
	bool operator==(const Nodo& nodo) const;
	bool operator==(const position2di& pos) const;

	std::string toString() const;

protected:
	

	position2di posicion;
	int g;
    int h;
    int f;
    Nodo* padre;
};
#endif



