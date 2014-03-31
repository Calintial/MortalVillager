#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include "Nodo.h"
#include "NodoRegional.h"
#include "NodoLocal.h"
#include "Camino.h"
#include "Region.h"

class Unidades;
class mapa2D;

//Some typedefs for simplicity
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
	void actualizarRegiones(position2di up_left,position2di down_right);
	Camino* calcularCamino(position2di,position2di);
	Camino* calcularCamino(Unidades*);
	std::vector<std::vector<Region*>> getRegiones(){return regiones;}
	std::vector<position2di> getEnlaces();
	std::vector<Camino> getIntraCaminos();
	position2di posicionDisponible(position2di);

private:
	void createRegions();

	void analyzeRegions();
	void analyzeRegions(Region*);
	void analyzeRegionsReverse(Region*);
	void analyzeRegionsFully(Region*);
	void crearEnlace(position2di,position2di,Region*,Region*);

	void findInnerPaths();
	void findInnerPaths(Region*);

	Camino* Aestrella(Nodo*,position2di);
	Camino* ALocal(position2di,position2di,Region*);
	Camino* ARegiones(position2di,position2di,Region*,Region*,std::vector<Camino>,std::vector<Camino>);

	Region* getCorrespondingRegion(position2di);
	Camino* deshacerCamino(Nodo*);
	void insertarOrdenado(std::vector<Nodo*>&, Nodo*);

	bool addVertex(position2di posEnlace, std::string label);
	bool addVertex(position2di posEnlace, std::string label,Region* region);

	const int tamRegion = 20;
	std::shared_ptr<mapa2D> mapa;
	Graph grafo;
	std::vector<std::vector<Region*> > regiones;
};