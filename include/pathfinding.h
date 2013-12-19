#pragma once 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>
#include "Nodo.h"
#include "Region.h"
#include "Enlace.h"
//#include "mapa2D.h"

using namespace std;
class mapa2D;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Region,Enlace > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::edge_iterator edge_iter;


class pathfinding
{
public:
	pathfinding(mapa2D*);
	~pathfinding();
	void run();
	void createRegions();
	void analyzeRegions();
	void findInnerPaths();
	std::vector<Region*> getRegiones();
	std::vector<Enlace*> getEnlaces();
	std::vector<position2di> getCaminodoEnlace(position2di inicio, position2di fin);
	Enlace* getEnlacePorPositionEnlace(position2di);
	position2di getEnlacePorPosition(position2di pos);
	std::vector<Enlace*> getEnlaces(Region*);
	Region* getCorrespondingRegion(int x, int y);

	Camino* calcularCamino(position2di,position2di);
	void A(std::vector<Camino> &caminos,position2di,position2di,Region *);
	int menorF(std::vector<Nodo> listaFrontera);
	std::vector<Nodo> hijos(Nodo* n,Region * regionActual);
	int estaEnlistaFrontera(std::vector<Nodo> listaFrontera,Nodo o);
	int estaEnlistaInterior(std::vector<Nodo> listaInterior,Nodo o);
	Camino caminosPersonajeRegion(const position2di&,const position2di&);
	Camino ARegiones(position2di origen,position2di destino,Region* regionActual,Region* regionFinal,std::vector<Camino> inicioCaminos,std::vector<Camino> finalCaminos);
	std::vector<Nodo> hijosRegion(Nodo* n,position2di origen,position2di destino,Region * regionInicio,Region * regionFinal,std::vector<Camino> inicioCaminos,std::vector<Camino> finalCaminos);
private:
	int width,height; 
	const int tamRegion = 10;
	mapa2D* mapa;
	Graph grafoRegiones;
};