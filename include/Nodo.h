#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
using namespace irr::core;

class NodoRegional;
class Camino;
class mapa2D;
class Region;
typedef boost::adjacency_list<boost::listS, boost::listS, boost::undirectedS, NodoRegional,Camino > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class Nodo
{
public:
	Nodo(position2di _pos,int _g,int _h,Nodo* _padre);
	Nodo();
	Nodo(const Nodo&);
	virtual ~Nodo();

	position2di getPosicion() const;
	int getG() const;
	int getH() const;
	int getF() const;
	Nodo* getPadre() const;

	void init(position2di _pos);
	void update(int _g,int _h,Nodo* _padre);
	virtual std::vector<Nodo*> getHijos() = 0;

	bool operator<(const Nodo& nodo) const;
	bool operator==(const Nodo& nodo) const;
	bool operator==(const position2di& pos) const;

protected:
	position2di posicion;
	int g;
    int h;
    int f;
    Nodo* padre;
};
#endif



