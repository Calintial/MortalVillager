#include "Pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
#include <limits.h>

Pathfinding::Pathfinding(std::shared_ptr<mapa2D> _mapa):mapa(_mapa){}

Pathfinding::~Pathfinding(){}

void Pathfinding::preprocesar(){
	grafo.clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
}

void Pathfinding::clear(){
	grafo.clear();
}

Camino* Pathfinding::calcularCamino(position2di,position2di){
	cout<<"TODO: COPIAR DE PATHFINDING VIEJO"<<endl;
}

void Pathfinding::createRegions(){
	cout<<"Creando Regiones"<<endl;
	int finalX,finalY;
	for (int i = 0; i < HEIGHT; i+=tamRegion)
	{
		std::vector<Region> fila;
		for (int j = 0; j < WIDTH; j+=tamRegion)
		{
			finalX = i+tamRegion-1;
			finalY = j+tamRegion-1;
			if (finalY > HEIGHT)
			{
				finalY = HEIGHT - 1;
			}

			if (finalX > WIDTH)
			{
				finalX = WIDTH -1;
			}
			Region nueva(i,j,finalX,finalY);
			fila.push_back(nueva);
		}
		regiones.push_back(fila);
	}
	cout<<"Regiones creadas"<<endl;
}

void Pathfinding::analyzeRegions(){
	// Poner un nodo en el grafo para cada lado del enlace. Camino de peso 1 entre los dos (new Camino(origen).addNodo(destino))
	for (int i = 0; i < regiones.size(); i++)
	{
		std::vector<Region> fila = regiones.at(i);
		for (int j = 0; j < fila.size(); j++)
		{
			Region actual = fila[j];
			// izquierda
			if (j > 0)
			{
				Region regionIzquierda = fila[j-1];
				int iterador = actual.inicio.Y;

				int tamHueco = 0;
				int posHueco = -1;
				while(iterador <= actual.final.Y && iterador < HEIGHT)
				{
					if (mapa->getTile(iterador,actual.inicio.X)->isTransitable() && mapa->getTile(iterador,regionIzquierda.final.X)->isTransitable())
					{
						if (posHueco == -1)
						{
							posHueco = iterador;
						}
						tamHueco++;
					}else{
						if (tamHueco > 0)
						{
							/*if (tamHueco > 3)
							{
								Enlace enlace(position2di(actual.inicio.X,posHueco),position2di(regionIzquierda.final.X,posHueco));
								Enlace enlace2(position2di(actual.inicio.X,posHueco+tamHueco-1),position2di(regionIzquierda.final.X,posHueco+tamHueco-1));
								boost::add_edge(actual.descriptor,regionIzquierda.descriptor,enlace,grafo);
								boost::add_edge(actual.descriptor,regionIzquierda.descriptor,enlace2,grafo);
							}else{*/
								vertex_t origen = boost::add_vertex(grafo);
								grafo[origen].posicion = position2di(actual.inicio.X,posHueco + tamHueco/2);
								grafo[origen].descriptor = origen;
								actual.nodos.push_back(grafo[origen]);

								vertex_t destino = boost::add_vertex(grafo);
								grafo[destino].posicion = position2di(regionIzquierda.final.X,posHueco + tamHueco/2);
								grafo[destino].descriptor = destino;
								regionIzquierda.nodos.push_back(grafo[destino]);


								Camino enlace(grafo[origen].posicion);
								enlace.addNodo(grafo[destino].posicion);
								boost::add_edge(origen,destino,enlace,grafo);
							//}
							tamHueco = 0;
							posHueco = -1;
						}
						
					}
					iterador++;
				}
				if (tamHueco > 0)
				{
					vertex_t origen = boost::add_vertex(grafo);
					grafo[origen].posicion = position2di(actual.inicio.X,posHueco + tamHueco/2);
					grafo[origen].descriptor = origen;
					actual.nodos.push_back(grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].posicion = position2di(regionIzquierda.final.X,posHueco + tamHueco/2);
					grafo[destino].descriptor = destino;
					regionIzquierda.nodos.push_back(grafo[destino]);

					Camino enlace(grafo[destino].posicion);
					enlace.addNodo(grafo[origen].posicion);
					boost::add_edge(origen,destino,enlace,grafo);
					//cout<<"Nuevo enlace izquierda"<<endl;
				}

			}
			// arriba
			if (i > 0)
			{
				Region regionArriba = regiones[i-1][j];
				int iterador = actual.inicio.X;

				int tamHueco = 0;
				int posHueco = -1;
				while(iterador <= actual.final.X && iterador < WIDTH)
				{
					if (mapa->getTile(actual.inicio.Y,iterador)->isTransitable() && mapa->getTile(regionArriba.final.Y,iterador)->isTransitable())
					{
						if (posHueco == -1)
						{
							posHueco = iterador;
						}
						tamHueco++;
					}else{
						if (tamHueco > 0)
						{
							// la conexión es (actual.inicioX,posHueco + tamHueco/2)<===>(regionIzquierda->finalX,posHueco + tamHueco/2)
							vertex_t origen = boost::add_vertex(grafo);
							grafo[origen].posicion = position2di(posHueco+tamHueco/2,actual.inicio.Y);
							grafo[origen].descriptor = origen;
							actual.nodos.push_back(grafo[origen]);

							vertex_t destino = boost::add_vertex(grafo);
							grafo[destino].posicion = position2di(posHueco+tamHueco/2,regionArriba.final.Y);
							grafo[destino].descriptor = destino;
							regionArriba.nodos.push_back(grafo[destino]);

							Camino enlace(grafo[origen].posicion);
							enlace.addNodo(grafo[destino].posicion);
							boost::add_edge(origen,destino,enlace,grafo);
							//cout<<"Nuevo enlace arriba"<<endl;
							tamHueco = 0;
							posHueco = -1;
						}
						
					}
					iterador++;
				}
				if (tamHueco > 0)
				{
					vertex_t origen = boost::add_vertex(grafo);
					grafo[origen].posicion = position2di(posHueco+tamHueco/2,actual.inicio.Y);
					grafo[origen].descriptor = origen;
					actual.nodos.push_back(grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].posicion = position2di(posHueco+tamHueco/2,regionArriba.final.Y);
					grafo[destino].descriptor = destino;
					regionArriba.nodos.push_back(grafo[destino]);

					Camino enlace(grafo[origen].posicion);
					enlace.addNodo(grafo[destino].posicion);
					boost::add_edge(origen,destino,enlace,grafo);
					//cout<<"Nuevo enlace arriba"<<endl;
				}
			}
		}
	}
}
void Pathfinding::findInnerPaths(){
	// A* igual que en antiguo
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafo); vp.first != vp.second; ++vp.first)
	{
		Nodo nodo = *(&grafo[*vp.first]);
		Region regionActual = getCorrespondingRegion(nodo.posicion);
		for(Nodo destino:regionActual.nodos){
			Camino* c=Aestrella(nodo.posicion,destino.posicion,regionActual);
			if (c != NULL)
			{
				boost::add_edge(nodo.descriptor,destino.descriptor,*c,grafo);
			}
		}
	}
}

Camino* Pathfinding::Aestrella(position2di origen,position2di destino, Region regionLimite){
	std::vector<Nodo> listaInterior;
	std::vector<Nodo> listaFrontera;
	std::priority_queue<Nodo> queueFrontera;
	Nodo nuevo(origen,0,distancia(origen,destino),NULL);

	queueFrontera.push(nuevo);

	while(!queueFrontera.empty()){
		Nodo actual = queueFrontera.top();
		queueFrontera.pop();
		listaInterior.push_back(actual);

		if (actual == destino)
		{
			// deshacemos el camino y devolvemos
		}else{
			// creamos los hijos
			// if(!listaInterior.contains(hijo)){
			// 		nueva_g = actual.g + 1;
			// 		if (!listaFrontera.contains(hijo) || nueva_g < hijo.g){
			//			actualizar_hijo
			//			if(!listaFrontera.contains(hijo)){	queueFrontera.push(hijo); listaFrontera.push_back(hijo);}
			//		}
			// }
		}
	}
}

Region Pathfinding::getCorrespondingRegion(position2di posicion){
	int i = posicion.Y / tamRegion;
	int j = posicion.X / tamRegion;
	return regiones[i][j];
}

int Pathfinding::distancia(position2di origen,position2di destino){
	return abs((destino.X-origen.X)+abs(destino.Y-origen.Y));
}
