#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <array>
#include "Nodo.h"
#include "Camino.h"
#include "Region.h"

class mapa2D;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Nodo,Camino > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::edge_iterator edge_iter;

class Pathfinding
{
public:
	Pathfinding(shared_ptr<mapa2D>);
	~Pathfinding();

	void preprocesar();
	void clear();
	Camino* calcularCamino(position2di,position2di);
	//std::vector<Region*> getRegiones();
	//std::vector<Enlace*> getEnlaces();
private:
	void createRegions();
	void analyzeRegions();
	void findInnerPaths();
	Camino* Aestrella(position2di,position2di);

	const int tamRegion = 5;
	shared_ptr<mapa2D> mapa;
	Graph grafo;
	std::array<std::array<Region,HEIGHT/tamRegion>, WIDTH/tamRegion> regiones;
};