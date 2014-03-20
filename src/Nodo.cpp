#include "Nodo.h"
#include "Region.h"
#include "mapa2D.h"
using namespace irr::core;

Nodo::Nodo(position2di _pos,int _g,int _h,Nodo*_padre){
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
}

Nodo::~Nodo(){
	
}

position2di Nodo::getPosicion() const{return posicion;}
int Nodo::getG() const{return g;}
int Nodo::getH() const{return h;}
int Nodo::getF() const{return f;}
Nodo* Nodo::getPadre() const{return padre;}


void Nodo::init(position2di _pos){
	posicion = _pos;
}

void Nodo::update(int _g,int _h,Nodo* _padre){
	this->g=_g;
    this->h=_h;
    this->f=_g + _h;
    this->padre=_padre;
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

int Nodo::distancia(position2di origen, position2di destino){
	return abs((destino.X-origen.X)+abs(destino.Y-origen.Y));
}

int Nodo::distancia(position2di destino){
	return distancia(posicion,destino);
}

std::string Nodo::toString() const{
	return std::to_string(posicion.X) + "," + std::to_string(posicion.Y);
}