#ifndef NODO_H
#define NODO_H


#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
using namespace irr::core;

class Nodo;
class Camino;
class mapa2D;
class Region;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Nodo,Camino > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class Nodo
{
public:
	Nodo(position2di _pos,int _g,int _h,Nodo* _padre);
	Nodo();
	Nodo(const Nodo&);
	~Nodo();

	position2di getPosicion();
	int getG();
	int getH();
	int getF();
	Nodo* getPadre();
	vertex_t getVertexDescriptor();

	void init(position2di _pos,vertex_t _desc);
	void update(int _g,int _h,Nodo* _padre);
	std::vector<Nodo*> getHijos(std::shared_ptr<mapa2D>,Region*);

	bool operator<(const Nodo& nodo) const;
	bool operator==(const Nodo& nodo) const;
	bool operator==(const position2di& pos) const;

private:
	position2di posicion;
	int g;
    int h;
    int f;
    Nodo* padre;
    vertex_t descriptor;
};
#endif



