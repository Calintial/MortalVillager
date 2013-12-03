#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>

#include "Region.h"
#include "Enlace.h"

using namespace std;

#define HEIGHT 20
#define WIDTH 20

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Region,Enlace > Graph;

//Some typedefs for simplicity
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;


class pathfinding
{
public:
	pathfinding();
	~pathfinding();
	void run();
	void createRegions();
	void analyzeRegions();
	void findInnerPaths();
	Region* getCorrespondingRegion(int x, int y);
	Camino* calcularCamino(position2di,position2di);

private:
	int width,height; 
	int tamRegion;
	int mapa[HEIGHT][WIDTH];
	Graph grafoRegiones;
};