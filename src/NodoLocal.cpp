#include "NodoLocal.h"
#include "Region.h"
#include "mapa2D.h"
using namespace irr::core;

NodoLocal::NodoLocal(position2di _pos,int _g,int _h,Nodo*_padre,Region* _region,std::shared_ptr<mapa2D> _mapa):Nodo(_pos,_g,_h,_padre){
	regionActual = _region;
	mapa = _mapa;
}

NodoLocal::NodoLocal():Nodo(),regionActual(NULL){}

NodoLocal::NodoLocal(const NodoLocal& copia):Nodo(copia){
	this->regionActual = copia.getRegion();
}

NodoLocal::~NodoLocal(){}

Region* NodoLocal::getRegion() const{
	return regionActual;
}

std::vector<Nodo*> NodoLocal::getHijos(){
	std::vector<Nodo*> hijos;
	position2di nueva_pos;

	nueva_pos.X=posicion.X;
	nueva_pos.Y=posicion.Y+1;
	auto tile = mapa->getTile(nueva_pos);
	if (regionActual->isInside(nueva_pos) && tile && tile->isTransitable())
	{
		NodoLocal* nuevo(new NodoLocal(nueva_pos,g+1,0,this,regionActual,mapa));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X+1;
	nueva_pos.Y=posicion.Y;
	tile = mapa->getTile(nueva_pos);
	if (regionActual->isInside(nueva_pos) && tile && tile->isTransitable())
	{
		NodoLocal* nuevo(new NodoLocal(nueva_pos,g+1,0,this,regionActual,mapa));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X-1;
	nueva_pos.Y=posicion.Y;
	tile = mapa->getTile(nueva_pos);
	if (regionActual->isInside(nueva_pos) && tile && tile->isTransitable())
	{
		NodoLocal* nuevo(new NodoLocal(nueva_pos,g+1,0,this,regionActual,mapa));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X;
	nueva_pos.Y=posicion.Y-1;
	tile = mapa->getTile(nueva_pos);
	if (regionActual->isInside(nueva_pos) && tile && tile->isTransitable())
	{
		NodoLocal* nuevo(new NodoLocal(nueva_pos,g+1,0,this,regionActual,mapa));
		hijos.push_back(nuevo);
	}
	
	return hijos;
}
Camino* NodoLocal::getCaminoDesdePadre(){
	if (padre != NULL)
	{
		Camino* c = new Camino(padre->getPosicion());
		c->addNodo(posicion);
		return c;
	}else{
		return NULL;
	}
	
}