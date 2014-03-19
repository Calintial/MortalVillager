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
	clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
}

void Pathfinding::clear(){
	regiones.clear();
	grafo.graph().clear();
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
			cout<<"Camino encontrado"<<endl;
		}else{
			cout<<"Camino no encontrado"<<endl;
		}
		return c;
	}
}

std::vector<position2di> Pathfinding::getEnlaces(){
	std::vector<position2di> enlaces;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafo); vp.first != vp.second; ++vp.first)
	{
		enlaces.push_back((&grafo.graph()[*vp.first])->getPosicion());
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

bool Pathfinding::addVertex(position2di posEnlace, std::string label){
	vertex_t vertex = grafo.vertex(label);
	if (vertex != NULL)
	{
		return false;
	}
	vertex_t origen = boost::add_vertex(label, grafo);
	grafo[label].init(posEnlace,origen,&grafo);
	return true;
}

bool Pathfinding::addVertex(position2di posEnlace, std::string label,Region* region){
	bool inserted = addVertex(posEnlace,label);
	if (inserted)
	{
		region->nodos.push_back(&grafo[label]);
	}
	return inserted;	
}

void Pathfinding::analyzeRegions(){
	cout<<"####### TODO: HACER QUE CUANDO YA HAYA UN NODO EN ESA POSICIÓN, NO SE CREE EL NODO, SE AÑADA EL ENLACE AL QUE YA HAY ######"<<endl;
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
								position2di posOrigen = position2di(actual->inicio.X,posHueco + tamHueco/2);
								std::string labelOrigen = std::to_string(posOrigen.X) + "," + std::to_string(posOrigen.Y);
								bool added_origen = addVertex(posOrigen,labelOrigen,actual);
								position2di posDestino = position2di(regionIzquierda->final.X,posHueco + tamHueco/2);
								std::string labelDestino = std::to_string(posDestino.X) + "," + std::to_string(posDestino.Y);
								bool added_destino = addVertex(posDestino,labelDestino,regionIzquierda);

								Camino enlace(grafo[labelOrigen].getPosicion());
								enlace.addNodo(grafo[labelDestino].getPosicion());
								boost::add_edge_by_label(labelOrigen,labelDestino,enlace,grafo);
							//}
							tamHueco = 0;
							posHueco = -1;
						}
						
					}
					iterador++;
				}
				if (tamHueco > 0)
				{
					position2di posOrigen = position2di(actual->inicio.X,posHueco + tamHueco/2);
					std::string labelOrigen = std::to_string(posOrigen.X) + "," + std::to_string(posOrigen.Y);
					bool added_origen = addVertex(posOrigen,labelOrigen,actual);
					position2di posDestino = position2di(regionIzquierda->final.X,posHueco + tamHueco/2);
					std::string labelDestino = std::to_string(posDestino.X) + "," + std::to_string(posDestino.Y);
					bool added_destino = addVertex(posDestino,labelDestino,regionIzquierda);

					Camino enlace(grafo[labelOrigen].getPosicion());
					enlace.addNodo(grafo[labelDestino].getPosicion());
					boost::add_edge_by_label(labelOrigen,labelDestino,enlace,grafo);
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
							position2di posOrigen = position2di(posHueco+tamHueco/2,actual->inicio.Y);
							std::string labelOrigen = std::to_string(posOrigen.X) + "," + std::to_string(posOrigen.Y);
							bool added_origen = addVertex(posOrigen,labelOrigen,actual);

							position2di posDestino = position2di(posHueco+tamHueco/2,regionArriba->final.Y);
							std::string labelDestino = std::to_string(posDestino.X) + "," + std::to_string(posDestino.Y);
							bool added_destino = addVertex(posDestino,labelDestino,regionArriba);

							Camino enlace(grafo[labelOrigen].getPosicion());
							enlace.addNodo(grafo[labelDestino].getPosicion());
							boost::add_edge_by_label(labelOrigen,labelDestino,enlace,grafo);
							
							//cout<<"Nuevo enlace arriba"<<endl;
							tamHueco = 0;
							posHueco = -1;
						}
						
					}
					iterador++;
				}
				if (tamHueco > 0)
				{
					position2di posOrigen = position2di(posHueco+tamHueco/2,actual->inicio.Y);
					std::string labelOrigen = std::to_string(posOrigen.X) + "," + std::to_string(posOrigen.Y);
					bool added_origen = addVertex(posOrigen,labelOrigen,actual);

					position2di posDestino = position2di(posHueco+tamHueco/2,regionArriba->final.Y);
					std::string labelDestino = std::to_string(posDestino.X) + "," + std::to_string(posDestino.Y);
					bool added_destino = addVertex(posDestino,labelDestino,regionArriba);

					Camino enlace(grafo[labelOrigen].getPosicion());
					enlace.addNodo(grafo[labelDestino].getPosicion());
					boost::add_edge_by_label(labelOrigen,labelDestino,enlace,grafo);
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
				Nodo* nuevoHijo = hijo;		
				if(std::find_if(listaInterior.begin(), listaInterior.end(), find_by_nodo(nuevoHijo)) == listaInterior.end()){
					//cout<<"Hijo ["<<nuevoHijo->getPosicion().X<<","<<nuevoHijo->getPosicion().Y<<"] NO contenido en LISTA INTERIOR"<<endl;
					int nueva_g = actual->getG() + 1;
					auto iteratorHijo = std::find_if(listaFrontera.begin(), listaFrontera.end(), find_by_nodo(nuevoHijo));
					bool contiene = iteratorHijo != listaFrontera.end();
					if (contiene)
					{
						//cout<<"Hijo ["<<nuevoHijo->getPosicion().X<<","<<nuevoHijo->getPosicion().Y<<"] contenido en LISTA FRONTERA"<<endl;
						if (nueva_g < (*iteratorHijo)->getG())
						{
							//cout<<"Hijo ["<<nuevoHijo->getPosicion().X<<","<<nuevoHijo->getPosicion().Y<<"] mejora la G anterior"<<endl;
							listaFrontera.erase(iteratorHijo);
							nuevoHijo->update(nueva_g,distancia(nuevoHijo->getPosicion(),destino),actual);
							insertarOrdenado(listaFrontera,nuevoHijo);

						}
				
					}else{
						//cout<<"Hijo ["<<nuevoHijo->getPosicion().X<<","<<nuevoHijo->getPosicion().Y<<"] añadido a LISTA FRONTERA"<<endl;
						nuevoHijo->update(nuevoHijo->getG(),distancia(nuevoHijo->getPosicion(),destino),actual);
						insertarOrdenado(listaFrontera,nuevoHijo);
						
					}
				}else{
					//cout<<"Hijo ["<<nuevoHijo->getPosicion().X<<","<<nuevoHijo->getPosicion().Y<<"] contenido en LISTA INTERIOR"<<endl;
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

	cout<<"Añadiendo nodo origen. num_vertices antes: <"<<boost::num_vertices(grafo)<<">"<<endl;
	std::string labelOrigen = std::to_string(origen.X) + "," + std::to_string(origen.Y);
	bool borrarOrigen = addVertex(origen,labelOrigen);

	cout<<"Añadiendo nodo destino. num_vertices antes: <"<<boost::num_vertices(grafo)<<">"<<endl;
	std::string labelDestino = std::to_string(destino.X) + "," + std::to_string(destino.Y);
	bool borrarDestino = addVertex(destino,labelDestino);

	grafo[labelOrigen].update(0,distancia(origen,destino),NULL);
	grafo[labelDestino].update(0,0,NULL);

	cout<<"Añadiendo edges origen. Num_edges antes: <"<<boost::num_edges(grafo)<<">"<<endl;

	std::vector<edge_t> edgesAdded;
	for (Camino camino: caminosInicio)
	{
		std::string findLabel = std::to_string(camino.getFinal().X) + "," + std::to_string(camino.getFinal().Y);
		//auto nodo = grafo[findLabel];
		auto edge = boost::add_edge_by_label(labelOrigen,findLabel,camino,grafo);
		if (edge.second)
		{
			edgesAdded.push_back(edge.first);
		}
	}
	cout<<"Añadidos edges origen. Añadiendo edges destino. Num_edges antes: <"<<boost::num_edges(grafo)<<">"<<endl;
	for (Camino camino: caminosFinal)
	{
		std::string findLabel = std::to_string(camino.getInicio().X) + "," + std::to_string(camino.getInicio().Y);
		//auto nodo = grafo[findLabel];
		auto edge = boost::add_edge_by_label(labelDestino,findLabel,camino,grafo);
		if (edge.second)
		{
			edgesAdded.push_back(edge.first);
		}
	}
	cout<<"Añadidos edges destino. Num_edges: <"<<boost::num_edges(grafo)<<">"<<endl;

	Camino* c = Aestrella(&grafo[labelOrigen],destino);

	cout<<"Borrando edges nuevos. Num_edges antes: <"<<boost::num_edges(grafo)<<">"<<endl;
	for(edge_t edge: edgesAdded){
		boost::remove_edge(edge,grafo);
	}
	cout<<"Borrados edges nuevos. Num_edges: <"<<boost::num_edges(grafo)<<">"<<endl;

	if (borrarOrigen)
	{
		cout<<"Borrando nodo origen. num_vertices antes: <"<<boost::num_vertices(grafo)<<">"<<endl;
		boost::clear_vertex_by_label(labelOrigen,grafo); // por si acaso, no debería hacer nada
		boost::remove_vertex(labelOrigen,grafo);
		cout<<"Borrado nodo origen. num_vertices: <"<<boost::num_vertices(grafo)<<">"<<endl;
	}


	if (borrarDestino)
	{
		cout<<"Borrando nodo destino. num_vertices antes: <"<<boost::num_vertices(grafo)<<">"<<endl;
		boost::clear_vertex_by_label(labelDestino,grafo); // por si acaso, no debería hacer nada
		boost::remove_vertex(labelDestino,grafo);
		cout<<"Borrado nodo destino. num_vertices: <"<<boost::num_vertices(grafo)<<">"<<endl;
	}
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