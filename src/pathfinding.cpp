
#include "pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
#include <limits.h>
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
			grafoRegiones[vertice].inicioX = i;
			grafoRegiones[vertice].inicioY = j;
			grafoRegiones[vertice].finalX = finalX;
			grafoRegiones[vertice].finalY = finalY;
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
		if (actual->inicioX > 0)
		{
			Region* regionIzquierda = getCorrespondingRegion(actual->inicioX-1,actual->inicioY);
			int iterador = actual->inicioY;

			int tamHueco = 0;
			int posHueco = -1;
			while(iterador < actual->finalY && iterador < height)
			{
				if (mapa->getTile(iterador,actual->inicioX)->isTransitable() && mapa->getTile(iterador,regionIzquierda->finalX)->isTransitable())
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
						Enlace enlace(position2di(actual->inicioX,posHueco),position2di(regionIzquierda->finalX,posHueco));
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
				Enlace enlace(position2di(actual->inicioX,posHueco),position2di(regionIzquierda->finalX,posHueco));
				boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace,grafoRegiones);
				cout<<"Nuevo enlace izquierda"<<endl;
			}
		}

		// upper edge
		if (actual->inicioY > 0)
		{
			Region* regionArriba = getCorrespondingRegion(actual->inicioX,actual->inicioY-1);
			int iterador = actual->inicioX;

			int tamHueco = 0;
			int posHueco = -1;
			while(iterador < actual->finalX && iterador < width)
			{
				if (mapa->getTile(actual->inicioY,iterador)->isTransitable() && mapa->getTile(regionArriba->finalY,iterador)->isTransitable())
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
						Enlace enlace(position2di(posHueco,actual->inicioY),position2di(posHueco,regionArriba->finalY));
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
				Enlace enlace(position2di(posHueco,actual->inicioY),position2di(posHueco,regionArriba->finalY));
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
				//Camino nuevo(puntoI);
				// el camino con el propio nodo es vacío (nuevo camino y ya está)
				if (j != i)
				{

					A(caminos,puntoI,puntoJ,regionActual);
					// calculo el camino entre puntoI y puntoJ
					//cout<<"TODO: Calculo el camino entre {"<<puntoI.X<<","<<puntoI.Y<<"} y {"<<puntoJ.X<<","<<puntoJ.Y<<"}"<<endl;
				}
				//caminos.push_back(nuevo);
				// para cada enlace, hacemos push_back a enlaceI.intracaminos con el camino entre enlaceI y enlaceJ
			}
			enlaceI.setIntraCaminos(caminos);
			//cout<<"Soy el enlaceI entre {"<<enlaceI.getOrigen().X<<","<<enlaceI.getOrigen().Y<<"} y {"<<enlaceI.getDestino().X<<","<<enlaceI.getDestino().Y<<"}"<<endl;
		}
		//cout<<"Siguiente vértice"<<endl;
	}
	position2di posPersonaje;
	posPersonaje.X=0;
	posPersonaje.Y=0;
	caminosPersonajeRegion(posPersonaje);
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
	createRegions();
	
	cout<<"He creado "<<num_vertices(grafoRegiones)<<" regiones"<<endl;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first){
		std::cout << "Reg"<<*vp.first<<"{"<<grafoRegiones[*vp.first].inicioX << ", " << grafoRegiones[*vp.first].inicioY <<"}"<< std::endl;
	}
	std::cout << std::endl;

	analyzeRegions();

	findInnerPaths();

}
void pathfinding::A(std::vector<Camino> &caminos,position2di origen,position2di destino,Region* regionActual){
	std::vector<Nodo> listaInterior;
	std::vector<Nodo> listaFrontera;
	std::priority_queue<Nodo> queueFrontera;
	int mejor=0;
	int index=0;
	Nodo *nuevo= new Nodo();
	Nodo nodoantiguo;
	nuevo->origen=origen;
	nuevo->h=abs((destino.X-nuevo->origen.X)+abs(destino.Y-nuevo->origen.Y));
	listaFrontera.push_back(*nuevo);
	queueFrontera.push(*nuevo);
	while(listaFrontera.size()>0){
		mejor=menorF(listaFrontera);
		nuevo=new Nodo(listaFrontera.at(mejor));
		listaFrontera.erase(listaFrontera.begin()+mejor);		
		listaInterior.push_back(*nuevo);
		if(nuevo->origen==destino){
			Nodo * nuevopuntero=nuevo;
			Camino camino=Camino();
			while(nuevopuntero->p!=NULL){
				camino.addNodo(nuevopuntero->origen);
				nuevopuntero=nuevopuntero->p;
			}
			caminos.push_back(camino);
			listaFrontera.clear();
		}
		else{
			for(Nodo hijo: hijos(nuevo,regionActual)){
				hijo.g=nuevo->g+1;
				hijo.h=abs((destino.X-hijo.origen.X)+abs(destino.Y-hijo.origen.Y));
				hijo.f=hijo.g+hijo.h;
				hijo.p=nuevo;
				index=estaEnlistaFrontera(listaFrontera,hijo);
				if(index==-1){

					listaFrontera.push_back(hijo);
				}
				else{
					if(hijo.g<listaFrontera.at(index).g){
						listaFrontera.at(index).g=hijo.g;
						listaFrontera.at(index).h=hijo.h;
						listaFrontera.at(index).f=hijo.f;
						listaFrontera.at(index).p=hijo.p;
	
					}

				}
			}
		}
	}

}
void pathfinding::caminosPersonajeRegion(position2di personajePosicion){
	std::pair<vertex_iter, vertex_iter> vp;
	std::vector<Camino> caminos;
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
			
			A(caminos,personajePosicion,puntoI,regionActual);	

		}
		break;
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
	if(regionActual->isInside(n->origen.X+1,n->origen.Y)){
		nueva_pos.X=n->origen.X+1;
		nueva_pos.Y=n->origen.Y;
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

	int f=INT_MAX;
	int iter=0;
	for(int i=0;i<listaFrontera.size();i++){
		if(f>listaFrontera.at(i).f){
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
