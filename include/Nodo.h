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
	Nodo(position2di _pos,int _g,int _h,std::shared_ptr<Nodo> _padre);
	Nodo();
	Nodo(const Nodo&);
	~Nodo();

	position2di getPosicion(){return posicion;}
	int getG(){return g;}
	int getH(){return h;}
	int getF(){return f;}
	std::shared_ptr<Nodo> getPadre(){return padre;}
	vertex_t getVertexDescriptor(){return descriptor;}

	void init(position2di _pos,vertex_t _desc);
	void update(int _g,int _h,std::shared_ptr<Nodo> _padre);
	std::vector<std::shared_ptr<Nodo>> getHijos(std::shared_ptr<mapa2D>,Region,Graph);

	bool operator<(const Nodo& nodo) const;
	bool operator==(const Nodo& nodo) const;
	bool operator==(const position2di& pos) const;

private:
	position2di posicion;
	int g;
    int h;
    int f;
    std::shared_ptr<Nodo> padre;
    vertex_t descriptor;
};
#endif



