#include "Nodo.h"

Nodo(position2di _pos,int _g,int _h,Nodo *_padre){
	this->posicion = _pos;
	this->g=_g;
	this->h=_h;
	this->f=_g + _h;
	this->padre=_padre;
}

Nodo::Nodo(const Nodo& copia){
	this->g=copia.g;
	this->h=copia.h;
	this->f=copia.f;
	this->posicion=copia.posicion;
	this->p=copia.p;
}

Nodo::~Nodo(){
	
}

bool Nodo::operator <(const Nodo& nodo) const
{
    if(g < nodo.g)
        return true;
    else
        return false;
}