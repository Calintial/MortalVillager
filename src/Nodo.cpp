#include "Nodo.h"
#include "Region.h"
#include "mapa2D.h"
using namespace irr::core;

Nodo::Nodo(position2di _pos,int _g,int _h,std::shared_ptr<Nodo>_padre){
        this->posicion = _pos;
        this->g=_g;
        this->h=_h;
        this->f=_g + _h;
        this->padre=_padre;
}

Nodo::Nodo(){
	this->posicion = position2di(-1,-1);
	this->g=9999;
	this->h=9999;
	this->f=9999;
	this->padre=NULL;
}

Nodo::Nodo(const Nodo& copia){
	this->g=copia.g;
	this->h=copia.h;
	this->f=copia.f;
	this->posicion=copia.posicion;
	this->padre=copia.padre;
	this->descriptor = copia.descriptor;
}

Nodo::~Nodo(){
	
}

void Nodo::init(position2di _pos,vertex_t _desc){
	posicion = _pos;
	descriptor = _desc;
}

void Nodo::update(int _g,int _h,std::shared_ptr<Nodo> _padre){
	this->g=_g;
    this->h=_h;
    this->f=_g + _h;
    this->padre=_padre;
}

std::vector<std::shared_ptr<Nodo>> Nodo::getHijos(std::shared_ptr<mapa2D> mapa,Region regionActual,Graph grafo){
	// Pongo los dos parámetros por si acaso, para el local solo necesito la región, para el otro necesito el grafo
	std::vector<std::shared_ptr<Nodo>> hijos;
	position2di nueva_pos;

	nueva_pos.X=posicion.X;
	nueva_pos.Y=posicion.Y+1;
	if (regionActual.isInside(nueva_pos) && mapa->getTile(posicion.Y+1,posicion.X)->isTransitable())
	{
		std::shared_ptr<Nodo> nuevo(new Nodo(nueva_pos,g+1,0,std::shared_ptr<Nodo>(this)));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X+1;
	nueva_pos.Y=posicion.Y;
	if (regionActual.isInside(nueva_pos) && mapa->getTile(posicion.Y+1,posicion.X)->isTransitable())
	{
		std::shared_ptr<Nodo> nuevo(new Nodo(nueva_pos,g+1,0,std::shared_ptr<Nodo>(this)));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X-1;
	nueva_pos.Y=posicion.Y;
	if (regionActual.isInside(nueva_pos) && mapa->getTile(posicion.Y+1,posicion.X)->isTransitable())
	{
		std::shared_ptr<Nodo> nuevo(new Nodo(nueva_pos,g+1,0,std::shared_ptr<Nodo>(this)));
		hijos.push_back(nuevo);
	}

	nueva_pos.X=posicion.X;
	nueva_pos.Y=posicion.Y-1;
	if (regionActual.isInside(nueva_pos) && mapa->getTile(posicion.Y+1,posicion.X)->isTransitable())
	{
		std::shared_ptr<Nodo> nuevo(new Nodo(nueva_pos,g+1,0,std::shared_ptr<Nodo>(this)));
		hijos.push_back(nuevo);
	}
	
	return hijos;
}

bool Nodo::operator <(const Nodo& nodo) const
{
    if(f < nodo.f)
        return true;
    else
        return false;
}

bool Nodo::operator==(const Nodo& nodo) const
{
    return posicion == nodo.posicion;
}

bool Nodo::operator==(const position2di& pos) const{
	return posicion == pos;
}
