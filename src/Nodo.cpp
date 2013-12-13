#include "Nodo.h"

Nodo::Nodo(int _g,int _h,int _f,position2di _or,Nodo *_nodo)
{
	this->g=_g;
	this->h=_h;
	this->f=_f;
	this->origen=_or;
	this->p=_nodo;
}

Nodo::Nodo(const Nodo& copia){
	this->g=copia.g;
	this->h=copia.h;
	this->f=copia.f;
	this->origen=copia.origen;
	this->p=copia.p;
}

Nodo::~Nodo(){
	delete this->p;
}
Nodo::Nodo(){
	this->g=0;
	this->h=0;
	this->f=0;
	this->origen.X=0;
	this->origen.Y=0;
	this->p=NULL;
	
}
bool Nodo::operator <(const Nodo& nodo) const
{
    if(g < nodo.g)
        return false;
    else
        return true;
}