
#include "pathfinding.h"
#include <boost/graph/graphviz.hpp>
#include <queue>
#include "mapa2D.h"
#include <limits.h>
pathfinding::pathfinding(shared_ptr<mapa2D> _mapa):width(WIDTH),height(HEIGHT),mapa(_mapa){}

pathfinding::~pathfinding(){}

void pathfinding::createRegions(){
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
			//regiones.push_back();
			vertex_t vertice = boost::add_vertex(grafoRegiones);
			grafoRegiones[vertice].inicio.X = i;
			grafoRegiones[vertice].inicio.Y = j;
			grafoRegiones[vertice].final.X = finalX;
			grafoRegiones[vertice].final.Y = finalY;
			grafoRegiones[vertice].descriptor = vertice;
		}
	}
	cout<<"Regiones creadas"<<endl;
}

void pathfinding::analyzeRegions(){
	cout<<"Analizando Regiones"<<endl;
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
						/*if (tamHueco > 3)
						{
							Enlace enlace(position2di(actual->inicio.X,posHueco),position2di(regionIzquierda->final.X,posHueco));
							Enlace enlace2(position2di(actual->inicio.X,posHueco+tamHueco-1),position2di(regionIzquierda->final.X,posHueco+tamHueco-1));
							boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace,grafoRegiones);
							boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace2,grafoRegiones);
						}else{*/
							Enlace enlace(position2di(actual->inicio.X,posHueco + tamHueco/2),position2di(regionIzquierda->final.X,posHueco + tamHueco/2));
							boost::add_edge(actual->descriptor,regionIzquierda->descriptor,enlace,grafoRegiones);	
						//}
						tamHueco = 0;
						posHueco = -1;
					}
					
				}
				iterador++;
			}
			if (tamHueco > 0)
			{
				Enlace enlace(position2di(actual->inicio.X,posHueco + tamHueco/2),position2di(regionIzquierda->final.X,posHueco + tamHueco/2));
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
						Enlace enlace(position2di(posHueco+tamHueco/2,actual->inicio.Y),position2di(posHueco+tamHueco/2,regionArriba->final.Y));
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
				Enlace enlace(position2di(posHueco+tamHueco/2,actual->inicio.Y),position2di(posHueco+tamHueco/2,regionArriba->final.Y));
				boost::add_edge(actual->descriptor,regionArriba->descriptor,enlace,grafoRegiones);
				//cout<<"Nuevo enlace arriba"<<endl;
			}
		}

	}
	cout<<"Regiones Analizadas"<<endl;
}

void pathfinding::findInnerPaths(){
	cout<<"Buscando caminos internos"<<endl;
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
				/*if (j != i)
				{*/
					Camino* c=A(puntoI,puntoJ,regionActual);
					if (c != NULL)
					{
						caminos.push_back(*c);
					}
					// calculo el camino entre puntoI y puntoJ
					////cout<<"TODO: Calculo el camino entre {"<<puntoI.X<<","<<puntoI.Y<<"} y {"<<puntoJ.X<<","<<puntoJ.Y<<"}"<<endl;
				//}
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
	cout<<"caminos internos buscados"<<endl;
}

std::vector<Region*> pathfinding::getRegiones(){
	cout<<"getRegiones"<<endl;
	std::vector<Region*> regiones;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first)
	{
		regiones.push_back(&grafoRegiones[*vp.first]);
	}
	cout<<"getRegiones terminado"<<endl;
	return regiones;
}

std::vector<Enlace*> pathfinding::getEnlaces(){
	cout<<"getEnlaces"<<endl;
	std::vector<Enlace*> enlaces;
	std::pair<edge_iter, edge_iter> es;
	for (es = edges(grafoRegiones); es.first != es.second; ++es.first) {
		enlaces.push_back(&grafoRegiones[*es.first]);
	}
	cout<<"getEnlaces terminado"<<endl;
	return enlaces;
}

std::vector<Enlace*> pathfinding::getEnlaces(Region* region){
	cout<<"getEnlaces(region)"<<endl;
	std::vector<Enlace*> enlaces;
	auto edges = boost::in_edges(region->descriptor,grafoRegiones);
	for(auto i = edges.first; i != edges.second; ++i){
		enlaces.push_back(&grafoRegiones[*i]);
	}
	cout<<"getEnlaces(region) terminado"<<endl;
	return enlaces;
}

Region* pathfinding::getCorrespondingRegion(int x, int y){
	cout<<"getCorrespondingRegion"<<endl;
	std::pair<vertex_iter, vertex_iter> vp;
	for (vp = vertices(grafoRegiones); vp.first != vp.second; ++vp.first)
	{
		if(grafoRegiones[*vp.first].isInside(x,y)){
			cout<<"Region encontrada"<<endl;
			return &grafoRegiones[*vp.first];
		}
	}
	cerr<<"####### ERROR: getCorrespondingRegion NO ENCONTRADA #########"<<endl;
	return NULL;
}

Camino* pathfinding::calcularCamino(position2di origen, position2di destino){
	cout<<"calculando camino desde ["<<origen.X<<","<<origen.Y<<"] hasta ["<<destino.X<<","<<destino.Y<<"]"<<endl;
	return caminosPersonajeRegion(origen,destino);
	
}

void pathfinding::run(){
	cout<<"run"<<endl;
	grafoRegiones.clear();
	createRegions();
	analyzeRegions();
	findInnerPaths();
	cout<<"run terminado"<<endl;
}
Camino* pathfinding::A(position2di origen,position2di destino,Region* regionActual){
	cout<<"A* local"<<endl;
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
		cout<<listaFrontera.size()<<endl;
		mejor=menorF(listaFrontera);
		nuevo=new Nodo(listaFrontera.at(mejor));
		listaFrontera.erase(listaFrontera.begin()+mejor);		
		listaInterior.push_back(*nuevo);
		if(nuevo->origen==destino){
		//	//cout<<nuevo->origen.X<<" "<<nuevo->origen.Y<<endl;
			Nodo * nuevopuntero=nuevo;
			Camino* camino=new Camino();
			camino->addNodo(position2di(nuevo->g,-1));
			while(nuevopuntero!=NULL){
				camino->addNodo(nuevopuntero->origen);
				nuevopuntero=nuevopuntero->p;
			}
			cout<<"CAMINO LOCAL ENCONTRADO"<<endl;
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
						// TODO: igual no va bien g,h y f -> f se calcula a partir de los otros, y g es nodo.g+1,no?
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
	cerr<<"###### CAMINO LOCAL NO ENCONTRADO ########"<<endl;
	return NULL;
}
Camino* pathfinding::ARegiones( position2di origen,position2di destino,Region* regionInicio,Region* regionFinal,std::vector<Camino> inicioCaminos,std::vector<Camino> finalCaminos){
	cout<<"A* Regiones"<<endl;
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
			Camino* c = new Camino();
			for(Camino camino: finalCaminos){
				cout<<camino.getCamino()[1].X <<" "<<camino.getCamino()[1].Y<<"y origen"<<nuevo->origen.X<<" "<<nuevo->origen.Y<<endl;
				if(camino.getCamino()[1]==nuevo->origen){					
					
						for(int i=camino.getCamino().size()-1; i>=1;i--){
							c->addNodo(camino.getCamino()[i]);
							cout<<camino.getCamino()[i].X<<" ,"<<camino.getCamino()[i].Y<<endl;
						}
						while(nuevo->p!=NULL && nuevo->p->p != NULL){
							//c->addNodo(nuevo->origen);
							std::vector<position2di> caminopos=getCaminodoEnlace(nuevo->origen,nuevo->p->origen);
							c->posiciones.insert(c->posiciones.end(), caminopos.begin(), caminopos.end());							
							nuevo=nuevo->p;
						}
						if (nuevo->p != NULL)
						{
							for(Camino objetoCamino :inicioCaminos){
								std::vector<position2di> caminoInicial = objetoCamino.getCamino();
								if(caminoInicial.at(caminoInicial.size()-1)==nuevo->origen || caminoInicial.at(1)==nuevo->origen){
									c->posiciones.insert(c->posiciones.end(), caminoInicial.begin(), caminoInicial.end());
								}
							}
						}
						cout<<"CAMINO REGIONES ENCONTRADO"<<endl;
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
	cerr<<"###### CAMINO REGIONES NO ENCONTRADO ########"<<endl;
	return NULL;
}
std::vector<position2di> pathfinding::getCaminodoEnlace(position2di inicio, position2di fin){
	cout<<"getCaminodoEnlace"<<endl;
	Enlace * e=getEnlacePorPositionEnlace(inicio);
	std::vector<position2di> nuevo_v;

	if (inicio == e->getOrigen() && fin == e->getDestino()){
		nuevo_v.push_back(fin);
		cout<<"getCaminodoEnlace encontrado camino inicio=origen && fin = dest"<<endl;
		return nuevo_v;
	}else if(inicio == e->getDestino() && fin == e->getOrigen()){
		nuevo_v.push_back(fin);
		cout<<"getCaminodoEnlace encontrado camino inicio=dest && fin = origen"<<endl;
		return nuevo_v;
	}else{
		for(Camino i:e->getIntraCaminosOrigen()){
			std::vector<position2di> c = i.getCamino();
			if(c.at(c.size()-1)==fin || c.at(1)==fin){
				nuevo_v.insert(nuevo_v.end(), c.begin(), c.end());
				cout<<"getCaminodoEnlace encontrado camino Origen"<<endl;
				return nuevo_v;
			}
		}
		cerr<<"No he encontrado intra caminos Origen entre <"<<inicio.X<<","<<inicio.Y<<"> y <"<<fin.X<<","<<fin.Y<<">. Mirando intracaminos destino"<<endl;
		for(Camino i:e->getIntraCaminosDestino()){
			std::vector<position2di> c = i.getCamino();
			if(c.at(c.size()-1)==fin  || c.at(1)==fin){
				nuevo_v.insert(nuevo_v.end(), c.begin(), c.end());
				cout<<"getCaminodoEnlace encontrado camino Destino"<<endl;
				return nuevo_v;
			}
		}
	}
	cerr<<"######## ERROR!! Camino inexistente entre "<<inicio.X<<","<<inicio.Y<<" y "<<fin.X<<","<<fin.Y<<" #########"<<endl;
	return nuevo_v;
}
Enlace* pathfinding::getEnlacePorPositionEnlace(position2di pos){
	cout<<"getEnlacePorPositionEnlace"<<endl;
		std::vector<Enlace*> vectorEnlace= getEnlaces();
	for(Enlace* enlace:vectorEnlace){
		if(enlace->getOrigen()==pos){
			return enlace;
		}
		if(enlace->getDestino()==pos){
			return enlace;
		}

	}
	cerr<<"########## ERROR: getEnlacePorPosition NO HA ENCONTRADO ENLACE #########"<<endl;
}
Camino* pathfinding::caminosPersonajeRegion(const position2di& personajePosicion,const position2di& finalPosicion){
	cout<<"caminosPersonajeRegion"<<endl;
	std::vector<Enlace*> enlacesVector;
	std::vector<Camino> caminos;
	std::vector<Camino> caminosFinal;
	Camino* c;
		Region* regionInicio = getCorrespondingRegion(personajePosicion.X,personajePosicion.Y);
		Region* regionFinal = getCorrespondingRegion(finalPosicion.X,finalPosicion.Y);
		if(regionInicio==regionFinal){
			Camino* c = A(personajePosicion,finalPosicion,regionInicio);
			if (c != NULL)
			{
				cout<<"CAMINO: <"<<c<<">"<<endl;
			 	return c;
			}
			cout<<"CAMINO es NULL"<<endl;
			 // si no ha encontrado camino local, probamos con el externo
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
			if (c != NULL)
			{
				caminos.push_back(*c);
			}

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
			if (c != NULL)
			{
				caminosFinal.push_back(*c);	
			}
			

	}
	if (caminos.size()== 0 || caminosFinal.size()==0)
	{
		cout<<"caminosPersonajeRegion NO HA ENCONTRADO CAMINO"<<endl;
		return NULL;
	}else{
		cout<<"Calculando ARegiones"<<endl;
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
	cout<<"hijosRegion"<<endl;
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
			std::vector<Camino> caminosEnlace;
			if(regionActual->isInside(enlace->getOrigen().X,enlace->getOrigen().Y)){
				caminosEnlace = enlace->getIntraCaminosOrigen();
				// comprobar que hay camino entre n y enlace->getOrigen()
				for(Camino camino:caminosEnlace){
					std::vector<position2di> posiciones = camino.getCamino();
					if ((posiciones[1] == n->origen && posiciones[posiciones.size()-1] == enlace->getOrigen()) || (posiciones[posiciones.size()-1] == n->origen && posiciones[1] == enlace->getOrigen()))
					{
						nueva_pos.X=enlace->getOrigen().X;
						nueva_pos.Y=enlace->getOrigen().Y;
						nuevo.origen=nueva_pos;
						nuevo.g=abs((enlace->getOrigen().X-n->origen.X)+abs(enlace->getOrigen().Y-n->origen.Y))+n->g;
						nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
						nuevo.f=nuevo.g+nuevo.h;
						nuevoshijos.push_back(nuevo);
						break;
					}
				}
				
			}
			else{
				caminosEnlace = enlace->getIntraCaminosDestino();
				// comprobar que hay camino entre n y enlace->getOrigen()
				for(Camino camino:caminosEnlace){
					std::vector<position2di> posiciones = camino.getCamino();
					if ((posiciones[1] == n->origen && posiciones[posiciones.size()-1] == enlace->getDestino()) || (posiciones[posiciones.size()-1] == n->origen && posiciones[1] == enlace->getDestino()))
					{
						nueva_pos.X=enlace->getDestino().X;
						nueva_pos.Y=enlace->getDestino().Y;
						nuevo.origen=nueva_pos;destino;
						nuevo.g=abs((enlace->getDestino().X-n->origen.X)+abs(enlace->getDestino().Y-n->origen.Y))+n->g;
						nuevo.h=abs((destino.X-nuevo.origen.X)+abs(destino.Y-nuevo.origen.Y));
						nuevo.f=nuevo.g+nuevo.h;
						nuevoshijos.push_back(nuevo);
						break;
					}
				}
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
	cerr<<"Hijos generados (["<<regionActual->getInicio().X<<","<<regionActual->getInicio().Y<<"] - ["<<regionActual->getFinal().X<<","<<regionActual->getFinal().Y<<"])"<<endl<<"{"<<endl;
	for(Nodo hijo:nuevoshijos){
		cerr<<"["<<hijo.origen.X<<","<<hijo.origen.Y<<"]"<<endl;
	}
	cerr<<"}"<<endl;
	cout<<"hijosRegion terminado"<<endl;
	return nuevoshijos;
}
std::vector<Nodo> pathfinding::hijos(Nodo* n,Region * regionActual){
	cout<<"hijos"<<endl;
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
	cout<<"hijos terminado"<<endl;
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
void pathfinding::clear(){
	grafoRegiones.clear();
}
