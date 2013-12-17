
#include "pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
pathfinding::pathfinding(mapa2D* _mapa):width(WIDTH),height(HEIGHT),mapa(_mapa){}

pathfinding::~pathfinding(){}

void pathfinding::createRegions(){
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
			//regiones.push_back();
			vertex_t vertice = boost::add_vertex(grafoRegiones);
			grafoRegiones[vertice].inicio.X = i;
			grafoRegiones[vertice].inicio.Y = j;
			grafoRegiones[vertice].final.X = finalX;
			grafoRegiones[vertice].final.Y = finalY;
			grafoRegiones[vertice].descriptor = vertice;
		}
	}
}

void pathfinding::analyzeRegions(){
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first){
		Region* actual = &grafoRegiones[*vp.first];
		// para cada región solo hay que mirar izquierda y arriba
		// left edge
		if (actual->inicio.X > 0)
		{
			if (actual->inicio.Y == 0)
			{
				cout<<"Estoy en {"<<actual->inicio.X<<",0}"<<endl;
			}
			Region* regionIzquierda = getCorrespondingRegion(actual->inicio.X-1,actual->inicio.Y);
			int iterador = actual->inicio.Y;

			int tamHueco = 0;
			int posHueco = -1;
			while(iterador < actual->final.Y && iterador < height)
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
						// la conexión es (actual->inicioX,posHueco + tamHueco/2)<===>(regionIzquierda->finalX,posHueco + tamHueco/2)
						Enlace enlace(position2di(actual->inicio.X,posHueco),position2di(regionIzquierda->final.X,posHueco));
						boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace,grafoRegiones);
						cout<<"Nuevo enlace izquierda"<<endl;
						tamHueco = 0;
						posHueco = -1;
					}
					
				}
				iterador++;
			}
			if (tamHueco > 0)
			{
				Enlace enlace(position2di(actual->inicio.X,posHueco),position2di(regionIzquierda->final.X,posHueco));
				boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace,grafoRegiones);
				cout<<"Nuevo enlace izquierda"<<endl;
			}
			if (actual->inicio.Y == 0)
			{
				cout<<"Salgo de {"<<actual->inicio.X<<",0}"<<endl;
			}
		}

		// upper edge
		if (actual->inicio.Y > 0)
		{
			Region* regionArriba = getCorrespondingRegion(actual->inicio.X,actual->inicio.Y-1);
			int iterador = actual->inicio.X;

			int tamHueco = 0;
			int posHueco = -1;
			while(iterador < actual->final.X && iterador < width)
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
						Enlace enlace(position2di(posHueco,actual->inicio.Y),position2di(posHueco,regionArriba->final.Y));
						boost::add_edge(actual->descriptor,regionArriba->descriptor,enlace,grafoRegiones);
						cout<<"Nuevo enlace arriba"<<endl;
						tamHueco = 0;
						posHueco = -1;
					}
					
				}
				iterador++;
			}
			if (tamHueco > 0)
			{
				Enlace enlace(position2di(posHueco,actual->inicio.Y),position2di(posHueco,regionArriba->final.Y));
				boost::add_edge(actual->descriptor,regionArriba->descriptor,enlace,grafoRegiones);
				cout<<"Nuevo enlace arriba"<<endl;
			}
		}

	}
}

void pathfinding::findInnerPaths(){
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first)
	{
		Region* regionActual = &grafoRegiones[*vp.first];

		auto edges = boost::in_edges(*vp.first,grafoRegiones);
		for(auto i = edges.first; i != edges.second; ++i){
			Enlace enlaceI = grafoRegiones[*i];
			position2di puntoI;
			if(regionActual->isInside(enlaceI.getOrigen().X,enlaceI.getOrigen().Y)){
				puntoI = enlaceI.getOrigen();
			}else{
				puntoI = enlaceI.getDestino();
			}
			std::vector<Camino> caminos;
			for(auto j = edges.first; j != edges.second; ++j){
				Enlace enlaceJ = grafoRegiones[*j];
				position2di puntoJ;
				if(regionActual->isInside(enlaceJ.getOrigen().X,enlaceJ.getOrigen().Y)){
					puntoJ = enlaceJ.getOrigen();
				}else{
					puntoJ = enlaceJ.getDestino();
				}
				Camino nuevo(puntoI);
				// el camino con el propio nodo es vacío (nuevo camino y ya está)
				if (j != i)
				{

					pathfinding::A(caminos,puntoI,puntoJ,regionActual);
					// calculo el camino entre puntoI y puntoJ
					cout<<"TODO: Calculo el camino entre {"<<puntoI.X<<","<<puntoI.Y<<"} y {"<<puntoJ.X<<","<<puntoJ.Y<<"}"<<endl;
				}
				caminos.push_back(nuevo);
				// para cada enlace, hacemos push_back a enlaceI.intracaminos con el camino entre enlaceI y enlaceJ
			}
			enlaceI.setIntraCaminos(caminos);
			cout<<"Soy el enlaceI entre {"<<enlaceI.getOrigen().X<<","<<enlaceI.getOrigen().Y<<"} y {"<<enlaceI.getDestino().X<<","<<enlaceI.getDestino().Y<<"}"<<endl;
		}
		cout<<"Siguiente vértice"<<endl;
	}
}

std::vector<Region*> pathfinding::getRegiones(){
	std::vector<Region*> regiones;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first)
	{
		regiones.push_back(&grafoRegiones[*vp.first]);
	}
	return regiones;
}

std::vector<Enlace*> pathfinding::getEnlaces(){
	std::vector<Enlace*> enlaces;
	std::pair<edge_iter, edge_iter> es;
	for (es = edges(grafoRegiones); es.first != es.second; ++es.first) {
		enlaces.push_back(&grafoRegiones[*es.first]);
	}
	return enlaces;
}

std::vector<Enlace*> pathfinding::getEnlaces(Region* region){
	std::vector<Enlace*> enlaces;
	auto edges = boost::in_edges(region->descriptor,grafoRegiones);
	for(auto i = edges.first; i != edges.second; ++i){
		enlaces.push_back(&grafoRegiones[*i]);
	}
	return enlaces;
}

Region* pathfinding::getCorrespondingRegion(int x, int y){
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first)
	{
		if(grafoRegiones[*vp.first].isInside(x,y)){
			return &grafoRegiones[*vp.first];
		}
	}
	return NULL;
}

Camino* pathfinding::calcularCamino(position2di origen, position2di destino){
	
}

void pathfinding::run(){
	grafoRegiones.clear();
	createRegions();
	analyzeRegions();
	//findInnerPaths();
}
void pathfinding::A(std::vector<Camino> caminos,position2di origen,position2di destino,Region* regionActual){
	std::vector<Nodo> listaInterior;
	std::vector<Nodo> listaFrontera;
	std::priority_queue<Nodo> queueFrontera;
	int mejor=0;
	int index=0;
	Nodo nuevo;
	Nodo nodoantiguo;
	nuevo.origen=origen;
	listaFrontera.push_back(nuevo);
	queueFrontera.push(nuevo);
	while(listaFrontera.size()>0){
		mejor=menorF(listaFrontera);
		listaFrontera.erase(listaFrontera.begin()+mejor);
		nuevo=listaFrontera.at(mejor);
		listaInterior.push_back(nuevo);
		if(nuevo.origen==destino){
			Camino nuevocamino;
			nuevocamino.addNodoCamino(nuevo);
			caminos.push_back(nuevocamino);
			//construir camino
		}
		else{
			for(Nodo o: hijos(& nuevo,regionActual)){
				o.g=nuevo.g+1;
				o.h=abs((destino.X-o.origen.X)+abs(destino.Y-o.origen.Y));
				o.f=o.g+o.h;
				index=estaEnlistaFrontera(listaFrontera,o);
				if(index!=-1){

					listaFrontera.push_back(o);
				}
				else{
					if(o.g<listaFrontera.at(index).g){
						listaFrontera.at(index).g=o.g;
						listaFrontera.at(index).h=o.h;
						listaFrontera.at(index).f=o.f;
						listaFrontera.at(index).p=o.p;
	
					}

				}
			}
		}
	}

}
int pathfinding::estaEnlistaFrontera(std::vector<Nodo> listaFrontera,Nodo o){

	for(int i=0;i<listaFrontera.size();i++){
		if(listaFrontera.at(i).origen==o.origen)
			return i;
	}
	return -1;
}
std::vector<Nodo> pathfinding::hijos(Nodo* n,Region * regionActual){
	std::vector<Nodo> nuevoshijos;
	Nodo nuevo;
	position2di nueva_pos;
	nuevo.p=n;
	if(regionActual->isInside(n->origen.X,n->origen.Y+1)){
		nueva_pos.X=n->origen.X;
		nueva_pos.Y=n->origen.Y+1;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X+1,n->origen.Y+1)){
		nueva_pos.X=n->origen.X+1;
		nueva_pos.Y=n->origen.Y+1;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X-1,n->origen.Y)){
		nueva_pos.X=n->origen.X-1;
		nueva_pos.Y=n->origen.Y;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X,n->origen.Y-1)){
		nueva_pos.X=n->origen.X;
		nueva_pos.Y=n->origen.Y-1;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	return nuevoshijos;
}
int pathfinding::menorF(std::vector<Nodo> listaFrontera){

	int f=0;
	int iter=0;
	for(int i=0;i<listaFrontera.size();i++){
		if(f<listaFrontera.at(i).f){
			f=listaFrontera.at(i).f;
			iter=i;
		}
	}
	return iter;
}
/*
int main(){
	pathfinding p;
	p.run();
	return 0;
}
*/
