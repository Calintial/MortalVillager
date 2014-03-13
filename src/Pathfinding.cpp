#include "Pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
#include <limits.h>

Pathfinding::Pathfinding(shared_ptr<mapa2D> _mapa):mapa(_mapa){}

Pathfinding::~Pathfinding(){}

void preprocesar(){
	grafo.clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
}

void clear(){
	grafo.clear();
}

Camino* calcularCamino(position2di,position2di){
	cout<<"TODO: COPIAR DE PATHFINDING VIEJO"
}

void createRegions(){
	// guardar las regiones en una matriz de objetos Region. Todo lo demás es básicamente lo mismo que en el viejo
	cout<<"Creando Regiones"<<endl;
	int finalX,finalY;
	for (int i = 0; i < width; i+=tamRegion)
	{
		for (int j = 0; j < height; j+=tamRegion)
		{
			finalX = i+tamRegion-1;
			finalY = j+tamRegion-1;
			if (finalY > height)
			{
				finalY = height - 1;
			}

			if (finalX > width)
			{
				finalX = width -1;
			}
			
			regiones[i][j].inicio.X = i;
			regiones[i][j].inicio.Y = j;
			regiones[i][j].final.X = finalX;
			regiones[i][j].final.Y = finalY;
			regiones[i][j].descriptor = vertice;
		}
	}
	cout<<"Regiones creadas"<<endl;
}
void analyzeRegions(){
	// Poner un nodo en el grafo para cada lado del enlace. Camino de peso 1 entre los dos (new Camino(origen).addNodo(destino))
}
void findInnerPaths(){
	// A* igual que en antiguo
}