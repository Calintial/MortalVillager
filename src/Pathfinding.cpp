#include "Pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
#include "Camino.h"
#include <limits.h>
#include "NodoLocal.h"
#include "NodoRegional.h"

struct find_caminoInicio_by_pos {
    find_caminoInicio_by_pos(position2di _pos) : pos(_pos) {}
    bool operator()(Camino comp) {
        return comp.getInicio() == pos;
    }
private:
    position2di pos;
};

struct find_caminoFinal_by_pos {
    find_caminoFinal_by_pos(position2di _pos) : pos(_pos) {}
    bool operator()(Camino comp) {
        return comp.getFinal() == pos;
    }
private:
    position2di pos;
};

struct find_by_pos {
    find_by_pos(position2di _pos) : pos(_pos) {}
    bool operator()(Nodo* comp) {
        return *comp == pos;
    }
private:
    position2di pos;
};

struct find_by_nodo {
    find_by_nodo(Nodo* _nodo) : nodo(_nodo) {}
    bool operator()(Nodo* comp) {
        return *comp == *nodo;
    }
private:
    Nodo* nodo;
};

void printSet(std::vector<Nodo*> set,std::string nombre){
	cout<<endl<<"PRINTING: "<<nombre<<"{"<<endl;
	for(auto it = set.begin(); it != set.end(); ++it){
		position2di pos= (*it)->getPosicion();
		cout<<"["<<pos.X<<","<<pos.Y<<"]"<<endl;
	}
	cout<<"}"<<endl<<endl;
}


Pathfinding::Pathfinding(std::shared_ptr<mapa2D> _mapa):mapa(_mapa){}

Pathfinding::~Pathfinding(){
	clear();
}

void Pathfinding::preprocesar(){
	grafo.clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
}

void Pathfinding::clear(){
	regiones.clear();
	grafo.clear();
}

Camino* Pathfinding::calcularCamino(position2di posicionPersonaje,position2di posicionFinal){
	std::vector<Camino> caminosInicio;
	std::vector<Camino> caminosFinal;
	Region* regionInicio = getCorrespondingRegion(posicionPersonaje);
	Region* regionFinal = getCorrespondingRegion(posicionFinal);
	if (regionInicio == regionFinal)
	{
		Camino* c = ALocal(posicionPersonaje,posicionFinal,regionInicio);
		if (c != NULL)
		{
			cout<<"CAMINO: <"<<c<<">"<<endl;
		 	return c;
		}
		cout<<"CAMINO es NULL"<<endl;
		 // si no ha encontrado camino local, probamos con el externo
	}

	for(auto enlace: regionInicio->nodos){
		Camino* c = ALocal(posicionPersonaje,enlace->getPosicion(),regionInicio);
		if (c != NULL)
		{
			caminosInicio.push_back(*c);
			delete c;
		}
	}

	for(auto enlace: regionFinal->nodos){
		Camino* c = ALocal(enlace->getPosicion(),posicionFinal,regionFinal);
		if (c != NULL)
		{
			caminosFinal.push_back(*c);
			delete c;
		}
	}

	if (caminosInicio.empty() || caminosFinal.empty())
	{
		cout<<"NO HA ENCONTRADO CAMINO ni local ni entre personaje y final de region"<<endl;
		return NULL;
	}else{
		Camino* c = ARegiones(posicionPersonaje,posicionFinal,regionInicio,regionFinal,caminosInicio,caminosFinal);
		if (c != NULL)
		{
			return c;
		}else{
			cout<<"Camino no encontrado"<<endl;
		}
	}

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

std::vector<Camino> Pathfinding::getIntraCaminos(){
	std::vector<Camino> caminos;
	std::pair<edge_iter, edge_iter> es;
	for (es = edges(grafo); es.first != es.second; ++es.first) {
		Camino* c = &grafo[*es.first];
		if (c->getPeso() > 0)
		{
			caminos.push_back(*c);
		}
	}
	return caminos;
}

void Pathfinding::createRegions(){
	cout<<"Creando Regiones"<<endl;
	int finalX,finalY;
	for (int i = 0; i < HEIGHT; i+=tamRegion)
	{
		std::vector<Region*> fila;
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
			Region* nueva = new Region(j,i,finalX,finalY);
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
		std::vector<Region*> fila = regiones.at(i);
		for (int j = 0; j < fila.size(); j++)
		{
			Region* actual = fila[j];
			// izquierda
			if (j > 0)
			{
				Region* regionIzquierda = fila[j-1];
				int iterador = actual->inicio.Y;

				int tamHueco = 0;
				int posHueco = -1;
				while(iterador <= actual->final.Y && iterador < HEIGHT)
				{
					if (mapa->getTile(iterador,actual->inicio.X)->isTransitable() && mapa->getTile(iterador,regionIzquierda->final.X)->isTransitable())
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
								Enlace enlace(position2di(actual->inicio.X,posHueco),position2di(regionIzquierda->final.X,posHueco));
								Enlace enlace2(position2di(actual->inicio.X,posHueco+tamHueco-1),position2di(regionIzquierda->final.X,posHueco+tamHueco-1));
								boost::add_edge(actual->getVertexDescriptor(),regionIzquierda->getVertexDescriptor(),enlace,grafo);
								boost::add_edge(actual->getVertexDescriptor(),regionIzquierda->getVertexDescriptor(),enlace2,grafo);
							}else{*/
								vertex_t origen = boost::add_vertex(grafo);
								grafo[origen].init(position2di(actual->inicio.X,posHueco + tamHueco/2),origen,&grafo);
								actual->nodos.push_back(&grafo[origen]);

								vertex_t destino = boost::add_vertex(grafo);
								grafo[destino].init(position2di(regionIzquierda->final.X,posHueco + tamHueco/2),destino,&grafo);
								regionIzquierda->nodos.push_back(&grafo[destino]);


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
					grafo[origen].init(position2di(actual->inicio.X,posHueco + tamHueco/2),origen,&grafo);
					actual->nodos.push_back(&grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].init(position2di(regionIzquierda->final.X,posHueco + tamHueco/2),destino,&grafo);
					regionIzquierda->nodos.push_back(&grafo[destino]);

					Camino enlace(grafo[destino].getPosicion());
					enlace.addNodo(grafo[origen].getPosicion());
					boost::add_edge(origen,destino,enlace,grafo);
					//cout<<"Nuevo enlace izquierda"<<endl;
				}

			}
			// arriba
			if (i > 0)
			{
				Region* regionArriba = regiones[i-1][j];
				int iterador = actual->inicio.X;

				int tamHueco = 0;
				int posHueco = -1;
				while(iterador <= actual->final.X && iterador < WIDTH)
				{
					if (mapa->getTile(actual->inicio.Y,iterador)->isTransitable() && mapa->getTile(regionArriba->final.Y,iterador)->isTransitable())
					{
						if (posHueco == -1)
						{
							posHueco = iterador;
						}
						tamHueco++;
					}else{
						if (tamHueco > 0)
						{
							// la conexión es (actual->inicioX,posHueco + tamHueco/2)<===>(regionIzquierda->finalX,posHueco + tamHueco/2)
							vertex_t origen = boost::add_vertex(grafo);
							grafo[origen].init(position2di(posHueco+tamHueco/2,actual->inicio.Y),origen,&grafo);
							actual->nodos.push_back(&grafo[origen]);

							vertex_t destino = boost::add_vertex(grafo);
							grafo[destino].init(position2di(posHueco+tamHueco/2,regionArriba->final.Y),destino,&grafo);
							regionArriba->nodos.push_back(&grafo[destino]);

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
					grafo[origen].init(position2di(posHueco+tamHueco/2,actual->inicio.Y), origen,&grafo);
					actual->nodos.push_back(&grafo[origen]);

					vertex_t destino = boost::add_vertex(grafo);
					grafo[destino].init(position2di(posHueco+tamHueco/2,regionArriba->final.Y),destino,&grafo);
					regionArriba->nodos.push_back(&grafo[destino]);

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
	for (int i = 0; i < regiones.size(); i++)
	{
		std::vector<Region*> fila = regiones.at(i);
		for (int j = 0; j < fila.size(); j++)
		{
			Region* regionActual = fila[j];
			cout<<"Region: {["<<regionActual->inicio.X<<","<<regionActual->inicio.Y<<"] - ["<<regionActual->final.X<<","<<regionActual->final.Y<<"]}"<<endl;
			for (int i = 0; i < regionActual->nodos.size(); ++i)
			{
				NodoRegional* nodo = regionActual->nodos[i];
				for (int j = 0; j < regionActual->nodos.size(); ++j)
				{
					if (i != j)
					{
						NodoRegional* destino = regionActual->nodos[j];
						auto edge = boost::edge(nodo->getVertexDescriptor(),destino->getVertexDescriptor(),grafo);
						if (!edge.second)
						{
							Camino* c=ALocal(nodo->getPosicion(),destino->getPosicion(),regionActual);
							if (c != NULL)
							{
								boost::add_edge(nodo->getVertexDescriptor(),destino->getVertexDescriptor(),*c,grafo);
							}
						}
					}
				}
			}
		}
	}

}

Camino* Pathfinding::Aestrella(Nodo* origen,position2di destino){
	//cout<<endl<<endl<<"A*"<<endl<<"ORIGEN: ["<<origen.X<<","<<origen.Y<<"]"<<endl<<"DESTINO: ["<<destino.X<<","<<destino.Y<<"]"<<endl;
	Camino* camino = NULL;
	std::vector<Nodo*> listaFrontera;
	std::vector<Nodo*> listaInterior;

	listaFrontera.push_back(origen);

	//printSet(listaFrontera,"listaFrontera");
	while(!listaFrontera.empty() && camino == NULL){

		//cout<<"lower_bound"<<endl;
		Nodo* actual = listaFrontera.at(0);
		//printSet(listaFrontera,"listaFrontera");
		//printSet(listaInterior,"listaInterior");
		//cout<<"insert ["<<actual->getPosicion().X<<","<<actual->getPosicion().Y<<"]"<<endl;
		listaInterior.push_back(actual);
		//printSet(listaFrontera,"listaFrontera");
		//printSet(listaInterior,"listaInterior");
		//cout<<"erase"<<endl;
		listaFrontera.erase(listaFrontera.begin());
		//printSet(listaFrontera,"listaFrontera");
		//printSet(listaInterior,"listaInterior");
		
		//cout<<"Nodo: ["<<actual->getPosicion().X<<","<<actual->getPosicion().Y<<"]"<<endl;
		
		if (*actual == destino)
		{
			//cout<<"Camino encontrado"<<endl;
			camino = deshacerCamino(actual);
		}else{
			auto hijos = actual->getHijos();
			//cout<<"Hijos generados: <"<<hijos.size()<<">"<<endl;
			for(Nodo* hijo:hijos){				
				if(std::find_if(listaInterior.begin(), listaInterior.end(), find_by_nodo(hijo)) == listaInterior.end()){
					//cout<<"Hijo ["<<hijo->getPosicion().X<<","<<hijo->getPosicion().Y<<"] NO contenido en LISTA INTERIOR"<<endl;
					int nueva_g = actual->getG() + 1;
					auto iteratorHijo = std::find_if(listaFrontera.begin(), listaFrontera.end(), find_by_nodo(hijo));
					bool contiene = iteratorHijo != listaFrontera.end();
					if (contiene)
					{
						//cout<<"Hijo ["<<hijo->getPosicion().X<<","<<hijo->getPosicion().Y<<"] contenido en LISTA FRONTERA"<<endl;
						if (nueva_g < (*iteratorHijo)->getG())
						{
							//cout<<"Hijo ["<<hijo->getPosicion().X<<","<<hijo->getPosicion().Y<<"] mejora la G anterior"<<endl;
							listaFrontera.erase(iteratorHijo);
							hijo->update(nueva_g,distancia(hijo->getPosicion(),destino),actual);
							insertarOrdenado(listaFrontera,hijo);

						}
				
					}else{
						//cout<<"Hijo ["<<hijo->getPosicion().X<<","<<hijo->getPosicion().Y<<"] añadido a LISTA FRONTERA"<<endl;
						hijo->update(hijo->getG(),distancia(hijo->getPosicion(),destino),hijo->getPadre());
						insertarOrdenado(listaFrontera,hijo);
						
					}
				}else{
					//cout<<"Hijo ["<<hijo->getPosicion().X<<","<<hijo->getPosicion().Y<<"] contenido en LISTA INTERIOR"<<endl;
				}
			}
			//cout<<"Hijos generados"<<endl;
			//printSet(listaFrontera,"listaFrontera");
			//printSet(listaInterior,"listaInterior");
		}
	}
	
	if (camino != NULL)
	{
		// borrar los nodos
	}else{
		//cout<<"Camino NO encontrado"<<endl;
	}
	return camino;
}

Camino* Pathfinding::ALocal(position2di origen,position2di destino,Region* regionActual){
	Nodo* nodoOrigen = new NodoLocal(origen,0,distancia(origen,destino),NULL,regionActual,mapa);

	return Aestrella(nodoOrigen,destino);

}

Camino* Pathfinding::ARegiones(position2di origen, position2di destino, Region* regionInicio, Region* regionFinal, std::vector<Camino> caminosInicio, std::vector<Camino> caminosFinal){
	std::vector<Nodo*> listaFrontera;
	std::vector<Nodo*> listaDestino;

	vertex_t descriptorOrigen = boost::add_vertex(grafo);
	grafo[descriptorOrigen].init(origen,descriptorOrigen,&grafo);
	grafo[descriptorOrigen].update(0,distancia(origen,destino),NULL);

	vertex_t descriptorDestino = boost::add_vertex(grafo);
	grafo[descriptorDestino].init(destino,descriptorDestino,&grafo);
	grafo[descriptorDestino].update(0,0,NULL);

	for (Camino camino: caminosInicio)
	{
		auto iterNodo = std::find_if(regionInicio->nodos.begin(),regionInicio->nodos.end(),find_by_pos(camino.getFinal()));
		boost::add_edge(descriptorOrigen,(*iterNodo)->getVertexDescriptor(),camino,grafo);
	}
	for (Camino camino: caminosFinal)
	{
		auto iterNodo = std::find_if(regionFinal->nodos.begin(),regionFinal->nodos.end(),find_by_pos(camino.getInicio()));
		boost::add_edge(descriptorDestino,(*iterNodo)->getVertexDescriptor(),camino,grafo);
	}

	Camino* c = Aestrella(&grafo[descriptorOrigen],destino);

	boost::clear_vertex(descriptorOrigen,grafo);
	boost::clear_vertex(descriptorDestino,grafo);
	boost::remove_vertex(descriptorOrigen,grafo);
	boost::remove_vertex(descriptorDestino,grafo);
	return c;
}


Region* Pathfinding::getCorrespondingRegion(position2di posicion){
	int i = posicion.Y / tamRegion;
	int j = posicion.X / tamRegion;
	return regiones[i][j];
}

int Pathfinding::distancia(position2di origen,position2di destino){
	return abs((destino.X-origen.X)+abs(destino.Y-origen.Y));
}

Camino* Pathfinding::deshacerCamino(Nodo* nodo){
	// todo, aquí tendrá que sacar el camino completo que haya en el grafo
	if (nodo->getPadre())
	{
		Camino* c = deshacerCamino(nodo->getPadre());
		Camino* caminoDesdePadre = nodo->getCaminoDesdePadre();
		if (caminoDesdePadre != NULL)
		{
			c->addCamino(*caminoDesdePadre);
		}
		return c;
	}else{
		return new Camino(nodo->getPosicion());
	}
}

void Pathfinding::insertarOrdenado(std::vector<Nodo*>& lista, Nodo* nodo){
	bool insertado = false;
	for (std::vector<Nodo*>::iterator it = lista.begin(); it != lista.end(); ++it)
	{
		if ((*it)->getF() > nodo->getF())
		{
			lista.insert(it,nodo);
			insertado = true;
			break;
		}
	}
	if (!insertado)
	{
		lista.push_back(nodo);
	}
}