#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
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
	Pathfinding(std::shared_ptr<mapa2D>);
	~Pathfinding();

	void preprocesar();
	void clear();
	Camino* calcularCamino(position2di,position2di);
	std::vector<std::vector<Region*>> getRegiones(){return regiones;}
	std::vector<position2di> getEnlaces();
	std::vector<Camino> getIntraCaminos();

private:
	void createRegions();
	void analyzeRegions();
	void findInnerPaths();
	Camino* Aestrella(position2di,position2di,Region*);

	Region* getCorrespondingRegion(position2di);
	int distancia(position2di,position2di);
	Camino* deshacerCamino(Nodo*);

	const int tamRegion = 5;
	std::shared_ptr<mapa2D> mapa;
	Graph grafo;
	std::vector<std::vector<Region*> > regiones;
};