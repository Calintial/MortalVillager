
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
			while(iterador <= actual->final.Y && iterador < height)
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
						//cout<<"Nuevo enlace izquierda"<<endl;
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
				//cout<<"Nuevo enlace izquierda"<<endl;
			}
			if (actual->inicio.Y == 0)
			{
				//cout<<"Salgo de {"<<actual->inicio.X<<",0}"<<endl;
			}
		}

		// upper edge
		if (actual->inicio.Y > 0)
		{
			Region* regionArriba = getCorrespondingRegion(actual->inicio.X,actual->inicio.Y-1);
			int iterador = actual->inicio.X;

			int tamHueco = 0;
			int posHueco = -1;
			while(iterador <= actual->final.X && iterador < width)
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
						//cout<<"Nuevo enlace arriba"<<endl;
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
				//cout<<"Nuevo enlace arriba"<<endl;
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
			Enlace* enlaceI = &grafoRegiones[*i];
			position2di puntoI;
			bool origen;
			if(regionActual->isInside(enlaceI->getOrigen().X,enlaceI->getOrigen().Y)){
				puntoI = enlaceI->getOrigen();
				origen = true;
			}else{
				puntoI = enlaceI->getDestino();
				origen = false;
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
					Camino c;
					c=A(puntoI,puntoJ,regionActual);
					caminos.push_back(c);
					// calculo el camino entre puntoI y puntoJ
					////cout<<"TODO: Calculo el camino entre {"<<puntoI.X<<","<<puntoI.Y<<"} y {"<<puntoJ.X<<","<<puntoJ.Y<<"}"<<endl;
				}
				//caminos.push_back(nuevo);
				// para cada enlace, hacemos push_back a enlaceI->intracaminos con el camino entre enlaceI y enlaceJ
			}
			if (origen)
			{
				enlaceI->setIntraCaminosOrigen(caminos);
			}else{
				enlaceI->setIntraCaminosDestino(caminos);
			}
			
			//cout<<"Soy el enlaceI entre {"<<enlaceI->getOrigen().X<<","<<enlaceI->getOrigen().Y<<"} y {"<<enlaceI->getDestino().X<<","<<enlaceI->getDestino().Y<<"}"<<endl;
		}
		//cout<<"Siguiente vértice"<<endl;
		//break;
	}
	position2di posPersonaje;
	posPersonaje.X=0;
	posPersonaje.Y=0;
	position2di posPersonajeFinal;
	posPersonajeFinal.X=10;
	posPersonajeFinal.Y=10;
	//caminosPersonajeRegion(posPersonaje,posPersonajeFinal);
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
	return new Camino(caminosPersonajeRegion(origen,destino));
	
}

void pathfinding::run(){
	grafoRegiones.clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
}
Camino pathfinding::A(position2di origen,position2di destino,Region* regionActual){
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
		//	//cout<<nuevo->origen.X<<" "<<nuevo->origen.Y<<endl;
			Nodo * nuevopuntero=nuevo;
			Camino camino=Camino();
			camino.addNodo(position2di(nuevo->g,-1));
			while(nuevopuntero!=NULL){
				camino.addNodo(nuevopuntero->origen);
				nuevopuntero=nuevopuntero->p;
			}
			return camino;

		}
		else{
			for(Nodo hijo: hijos(nuevo,regionActual)){
				hijo.g=nuevo->g+1;
				hijo.h=abs((destino.X-hijo.origen.X)+abs(destino.Y-hijo.origen.Y));
				hijo.f=hijo.g+hijo.h;
				hijo.p=nuevo;
				index = estaEnlistaInterior(listaInterior,hijo);
				if (index == -1)
				{
					int otroindex=estaEnlistaFrontera(listaFrontera,hijo);
					if(otroindex==-1){

						listaFrontera.push_back(hijo);
					}
					else{
						if(hijo.g<listaFrontera.at(otroindex).g){
							listaFrontera.at(otroindex).g=hijo.g;
							listaFrontera.at(otroindex).h=hijo.h;
							listaFrontera.at(otroindex).f=hijo.f;
							listaFrontera.at(otroindex).p=hijo.p;
		
						}
					}
				}else{
					if(hijo.g<listaInterior.at(index).g){
						listaInterior.at(index).g=hijo.g;
						listaInterior.at(index).h=hijo.h;
						listaInterior.at(index).f=hijo.f;
						listaInterior.at(index).p=hijo.p;
	
					}
				}
			}
		}
	}
return Camino(origen);
}
Camino pathfinding::ARegiones( position2di origen,position2di destino,Region* regionInicio,Region* regionFinal,std::vector<Camino> inicioCaminos,std::vector<Camino> finalCaminos){
	for(Camino caminosss:finalCaminos){
		//cout<<caminosss.getCamino()[1].X <<" "<<caminosss.getCamino()[1].Y<<endl;

	}

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
		if(regionFinal->isInside(nuevo->origen.X,nuevo->origen.Y)){
			Camino c;
			for(Camino camino: finalCaminos){
				cout<<camino.getCamino()[1].X <<" "<<camino.getCamino()[1].Y<<"y origen"<<nuevo->origen.X<<" "<<nuevo->origen.Y<<endl;
				if(camino.getCamino()[1]==nuevo->origen){					
					
						for(int i=camino.getCamino().size()-1; i>=1;i--){
							c.addNodo(camino.getCamino()[i]);
							cout<<camino.getCamino()[i].X<<" ,"<<camino.getCamino()[i].Y<<endl;
						}
						while(nuevo->p!=NULL && nuevo->p->p != NULL){
							//c.addNodo(nuevo->origen);
							std::vector<position2di> caminopos=getCaminodoEnlace(nuevo->origen,nuevo->p->origen);
							c.posiciones.insert(c.posiciones.end(), caminopos.begin(), caminopos.end());							
							nuevo=nuevo->p;
						}
						if (nuevo->p != NULL)
						{
							for(Camino objetoCamino :inicioCaminos){
								std::vector<position2di> caminoInicial = objetoCamino.getCamino();
								if(caminoInicial.at(caminoInicial.size()-1)==nuevo->origen || caminoInicial.at(1)==nuevo->origen){
									c.posiciones.insert(c.posiciones.end(), caminoInicial.begin(), caminoInicial.end());
								}
							}
						}
					return c;
				}
				
			}

		}
		else{
			for(Nodo hijo: hijosRegion(nuevo,origen,destino,regionInicio,regionFinal,inicioCaminos, finalCaminos)){
				index = estaEnlistaInterior(listaInterior,hijo);
				if (index == -1)
				{
					int otroindex=estaEnlistaFrontera(listaFrontera,hijo);
					if(otroindex==-1){

						listaFrontera.push_back(hijo);
					}
					else{
						if(hijo.g<listaFrontera.at(otroindex).g){
							listaFrontera.at(otroindex).g=hijo.g;
							listaFrontera.at(otroindex).h=hijo.h;
							listaFrontera.at(otroindex).f=hijo.f;
							listaFrontera.at(otroindex).p=hijo.p;
		
						}
					}
				}else{
					if(hijo.g<listaInterior.at(index).g){
						listaInterior.at(index).g=hijo.g;
						listaInterior.at(index).h=hijo.h;
						listaInterior.at(index).f=hijo.f;
						listaInterior.at(index).p=hijo.p;
	
					}
				}
			}
		}
	}
	return Camino(origen);
}
std::vector<position2di> pathfinding::getCaminodoEnlace(position2di inicio, position2di fin){
	Enlace * e=getEnlacePorPositionEnlace(inicio);
	std::vector<position2di> nuevo_v;

	if (inicio == e->getOrigen() && fin == e->getDestino()){
		nuevo_v.push_back(fin);
		return nuevo_v;
	}else if(inicio == e->getDestino() && fin == e->getOrigen()){
		nuevo_v.push_back(fin);
		return nuevo_v;
	}else{
		for(Camino i:e->getIntraCaminosOrigen()){
			std::vector<position2di> c = i.getCamino();
			if(c.at(c.size()-1)==fin || c.at(1)==fin){
				nuevo_v.insert(nuevo_v.end(), c.begin(), c.end());
				return nuevo_v;
			}
		}
		for(Camino i:e->getIntraCaminosDestino()){
			std::vector<position2di> c = i.getCamino();
			if(c.at(c.size()-1)==fin  || c.at(1)==fin){
				nuevo_v.insert(nuevo_v.end(), c.begin(), c.end());
				return nuevo_v;
			}
		}
	}
	cerr<<"######## ERROR!! #########"<<endl;
	return nuevo_v;
}
Enlace* pathfinding::getEnlacePorPositionEnlace(position2di pos){
		std::vector<Enlace*> vectorEnlace= getEnlaces();
	for(Enlace* enlace:vectorEnlace){
		if(enlace->getOrigen()==pos){
			return enlace;
		}
		if(enlace->getDestino()==pos){
			return enlace;
		}

	}


}
Camino pathfinding::caminosPersonajeRegion(const position2di& personajePosicion,const position2di& finalPosicion){
	std::vector<Enlace*> enlacesVector;
	std::vector<Camino> caminos;
	std::vector<Camino> caminosFinal;
	Camino c;
		Region* regionInicio = getCorrespondingRegion(personajePosicion.X,personajePosicion.Y);
		Region* regionFinal = getCorrespondingRegion(finalPosicion.X,finalPosicion.Y);
		if(regionInicio==regionFinal){
			return A(personajePosicion,finalPosicion,regionInicio);
		}
		enlacesVector=getEnlaces(regionInicio);
		for(Enlace* enlace:enlacesVector){
			
			position2di puntoI;
			if(regionInicio->isInside(enlace->getOrigen().X,enlace->getOrigen().Y)){
				puntoI = enlace->getOrigen();
			}else{
				puntoI = enlace->getDestino();
			}
			c=A(personajePosicion,puntoI,regionInicio);
			caminos.push_back(c);	

	}
	//cout<<"final"<<endl;
		
		enlacesVector.clear();
		enlacesVector=getEnlaces(regionFinal);
		for(Enlace* enlace:enlacesVector){
			
			position2di puntoI;
			if(regionFinal->isInside(enlace->getOrigen().X,enlace->getOrigen().Y)){
				puntoI = enlace->getOrigen();
			}else{
				puntoI = enlace->getDestino();
			}
			c=A(finalPosicion,puntoI,regionFinal);
			caminosFinal.push_back(c);	

	}
	if (caminos.size()== 0 || caminosFinal.size()==0)
	{
		return Camino(personajePosicion);
	}else{
		return ARegiones(personajePosicion,finalPosicion,regionInicio,regionFinal,caminos,caminosFinal);
	}
}



int pathfinding::estaEnlistaFrontera(std::vector<Nodo> listaFrontera,Nodo o){

	for(int i=0;i<listaFrontera.size();i++){
		if(listaFrontera.at(i).origen==o.origen)
			return i;
	}
	return -1;
}

int pathfinding::estaEnlistaInterior(std::vector<Nodo> listaInterior,Nodo o){

	for(int i=0;i<listaInterior.size();i++){
		if(listaInterior.at(i).origen==o.origen)
			return i;
	}
	return -1;
}

position2di pathfinding::getEnlacePorPosition(position2di pos){
	std::vector<Enlace*> vectorEnlace= getEnlaces();
	for(Enlace* enlace:vectorEnlace){
		if(enlace->getOrigen()==pos){
			return enlace->getDestino();
		}
		if(enlace->getDestino()==pos){
			return enlace->getOrigen();
		}

	}


}
std::vector<Nodo> pathfinding::hijosRegion(Nodo* n,position2di origen,position2di destino,Region * regionInicio,Region * regionFinal,std::vector<Camino> inicioCaminos,std::vector<Camino> finalCaminos){
	std::vector<Nodo> nuevoshijos;
	Nodo nuevo;
	position2di nueva_pos;
	nuevo.p=n;
	Region* regionActual=getCorrespondingRegion(n->origen.X,n->origen.Y);
	if(n->origen==origen){
		for(Camino c: inicioCaminos){
			
			nueva_pos.X=c.getCamino().at(1).X;
			nueva_pos.Y=c.getCamino().at(1).Y;
			nuevo.origen=nueva_pos;
			nuevo.g=c.getCamino().at(0).X;
			nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
			nuevo.f=nuevo.g+nuevo.h;
			nuevoshijos.push_back(nuevo);
		}
	}
	/*else if(regionActual==regionFinal){
		for(Camino c: finalCaminos){
			

			nueva_pos.X=c.getCamino().at(1).X;
			nueva_pos.Y=c.getCamino().at(1).Y;
			nuevo.origen=nueva_pos;
			nuevo.g=c.getCamino().at(0).X;
			nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
			nuevo.f=nuevo.g+nuevo.h;
			nuevoshijos.push_back(nuevo);
		}
	}*/
	else{
		std::vector<Enlace*> enlacesVector= getEnlaces(regionActual);
		for(Enlace* enlace:enlacesVector){
			if(regionActual->isInside(enlace->getOrigen().X,enlace->getOrigen().Y)){
				
				nueva_pos.X=enlace->getOrigen().X;
				nueva_pos.Y=enlace->getOrigen().Y;
				nuevo.origen=nueva_pos;
				nuevo.g=abs((enlace->getOrigen().X-n->origen.X)+abs(enlace->getOrigen().Y-n->origen.Y))+n->g;
				nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
				nuevo.f=nuevo.g+nuevo.h;
				nuevoshijos.push_back(nuevo);
			}
			else{
				nueva_pos.X=enlace->getDestino().X;
				nueva_pos.Y=enlace->getDestino().Y;
				nuevo.origen=nueva_pos;destino;
				nuevo.g=abs((enlace->getDestino().X-n->origen.X)+abs(enlace->getDestino().Y-n->origen.Y))+n->g;
				nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
				nuevo.f=nuevo.g+nuevo.h;
				nuevoshijos.push_back(nuevo);
			}
		}
		position2di posnodo=getEnlacePorPosition(n->origen);
			nueva_pos.X=posnodo.X;
			nueva_pos.Y=posnodo.Y;
			nuevo.origen=nueva_pos;
			nuevo.g=n->g+1;
			nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
			nuevo.f=nuevo.g+nuevo.h;
			nuevoshijos.push_back(nuevo);

	}
	return nuevoshijos;
}
std::vector<Nodo> pathfinding::hijos(Nodo* n,Region * regionActual){
	std::vector<Nodo> nuevoshijos;
	Nodo nuevo;
	position2di nueva_pos;
	nuevo.p=n;
	if(regionActual->isInside(n->origen.X,n->origen.Y+1) && mapa->getTile(n->origen.Y+1,n->origen.X)->isTransitable()){ // getTile está del revés, hay que verlo en mapa2d.cpp
		nueva_pos.X=n->origen.X;
		nueva_pos.Y=n->origen.Y+1;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X+1,n->origen.Y) && mapa->getTile(n->origen.Y,n->origen.X+1)->isTransitable()){
		nueva_pos.X=n->origen.X+1;
		nueva_pos.Y=n->origen.Y;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X-1,n->origen.Y) && mapa->getTile(n->origen.Y,n->origen.X-1)->isTransitable()){
		nueva_pos.X=n->origen.X-1;
		nueva_pos.Y=n->origen.Y;
		nuevo.origen=nueva_pos;
		nuevoshijos.push_back(nuevo);
	}
	if(regionActual->isInside(n->origen.X,n->origen.Y-1) && mapa->getTile(n->origen.Y-1,n->origen.X)->isTransitable()){
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
