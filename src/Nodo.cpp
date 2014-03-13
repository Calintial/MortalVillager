#include "Nodo.h"
using namespace irr::core;

Nodo::Nodo(position2di _pos,int _g,int _h,Nodo *_padre){
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