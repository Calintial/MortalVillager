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

std::vector<position2di> Pathfinding::getEnlaces(){
	std::vector<position2di> enlaces;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafo); vp.first != vp.second; ++vp.first)
	{
		enlaces.push_back((&grafo[*vp.first])->getPosicion());
	}
	return enlaces;
}

void Pathfinding::createRegions(){
	cout<<"Creando Regiones"<<endl;
	int finalX,finalY;
	for (int i = 0; i < HEIGHT; i+=tamRegion)
	{
		std::vector<Region> fila;
		for (int j = 0; j < WIDTH; j+=tamRegion)
		{
			finalX = j+tamRegion-1;
			finalY = i+tamRegion-1;
			if (finalY > HEIGHT)
			{
				finalY = HEIGHT - 1;
			}

			if (finalX > WIDTH)
			{
				finalX = WIDTH -1;
			}
			Region nueva(j,i,finalX,finalY);
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
								boost::add_edge(actual.getVertexDescriptor(),regionIzquierda.getVertexDescriptor(),enlace,grafo);
								boost::add_edge(actual.getVertexDescriptor(),regionIzquierda.getVertexDescriptor(),enlace2,grafo);
							}else{*/
								vertex_t origen = boost::add_vertex(grafo);
								grafo[origen].init(position2di(actual.inicio.X,posHueco + tamHueco/2),origen);
								actual.nodos.push_back(grafo[origen]);

								vertex_t destino = boost::add_vertex(grafo);
								grafo[destino].init(position2di(regionIzquierda.final.X,posHueco + tamHueco/2),destino);
								regionIzquierda.nodos.push_back(grafo[destino]);


								Camino enlace(grafo[origen].getPosicion());
								enlace.addNodo(grafo[destino].getPosicion());
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
					grafo[origen].init(position2di(actual.inicio.X,posHueco + tamHueco/2),origen);
					actual.nodos.push_back(grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].init(position2di(regionIzquierda.final.X,posHueco + tamHueco/2),destino);
					regionIzquierda.nodos.push_back(grafo[destino]);

					Camino enlace(grafo[destino].getPosicion());
					enlace.addNodo(grafo[origen].getPosicion());
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
							grafo[origen].init(position2di(posHueco+tamHueco/2,actual.inicio.Y),origen);
							actual.nodos.push_back(grafo[origen]);

							vertex_t destino = boost::add_vertex(grafo);
							grafo[destino].init(position2di(posHueco+tamHueco/2,regionArriba.final.Y),destino);
							regionArriba.nodos.push_back(grafo[destino]);

							Camino enlace(grafo[origen].getPosicion());
							enlace.addNodo(grafo[destino].getPosicion());
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
					grafo[origen].init(position2di(posHueco+tamHueco/2,actual.inicio.Y), origen);
					actual.nodos.push_back(grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].init(position2di(posHueco+tamHueco/2,regionArriba.final.Y),destino);
					regionArriba.nodos.push_back(grafo[destino]);

					Camino enlace(grafo[origen].getPosicion());
					enlace.addNodo(grafo[destino].getPosicion());
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
		Region regionActual = getCorrespondingRegion(nodo.getPosicion());
		for(Nodo destino:regionActual.nodos){
			Camino* c=Aestrella(nodo.getPosicion(),destino.getPosicion(),regionActual);
			if (c != NULL)
			{
				boost::add_edge(nodo.getVertexDescriptor(),destino.getVertexDescriptor(),*c,grafo);
			}
		}
	}
}

Camino* Pathfinding::Aestrella(position2di origen,position2di destino, Region regionLimite){
	Camino* camino = NULL;
	std::vector<std::shared_ptr<Nodo>> listaInterior;
	std::vector<std::shared_ptr<Nodo>> listaFrontera;
	std::priority_queue<std::shared_ptr<Nodo>> queueFrontera;
	std::shared_ptr<Nodo> nuevo(new Nodo(origen,0,distancia(origen,destino),NULL));

	queueFrontera.push(nuevo);

	while(!queueFrontera.empty() && camino == NULL){
		std::shared_ptr<Nodo> actual = queueFrontera.top();
		queueFrontera.pop();
		listaInterior.push_back(actual);

		if (*actual == destino)
		{
			return deshacerCamino(actual);
		}else{
			auto hijos = actual->getHijos(mapa,regionLimite,grafo);
			for(std::shared_ptr<Nodo> hijo:hijos){
				if(std::find(listaInterior.begin(), listaInterior.end(), hijo) == listaInterior.end()){
					int nueva_g = hijo->getG();
					auto iteratorHijo = std::find(listaFrontera.begin(), listaFrontera.end(), hijo);
					bool contiene = iteratorHijo != listaFrontera.end();
					if (contiene)
					{
						hijo = *iteratorHijo;
						if (nueva_g < hijo->getG())
						{
							hijo->update(nueva_g,distancia(hijo->getPosicion(),destino),actual);
						}
				
					}else{
						hijo->update(hijo->getG(),distancia(hijo->getPosicion(),destino),hijo->getPadre());
						queueFrontera.push(hijo);
						listaFrontera.push_back(hijo);
					}
				}
			}
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

Camino* Pathfinding::deshacerCamino(std::shared_ptr<Nodo> nodo){
	if (nodo->getPadre() != NULL)
	{
		Camino* c = deshacerCamino(nodo->getPadre());
		c->addNodo(nodo->getPosicion());
		return c;
	}else{
		return new Camino(nodo->getPosicion());
	}
}