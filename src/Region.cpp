#include "Region.h"
#include "NodoRegional.h"

Region::Region(){

}

Region::Region(int _inicioX, int _inicioY, int _finalX, int _finalY):inicio(_inicioX,_inicioY),final(_finalX,_finalY){
	//enlaces = new std::vector<Enlace*>();
}

Region::~Region(){
	clear();
}
/*
void Region::add(Enlace* link){
	enlaces.push_back(link);
}*/
/*
void Region::remove(Enlace* link){
	if(enlaces.size() > 0){
		// elimina el elemento que coincide con link.
		enlaces.erase(std::remove(enlaces.begin(), enlaces.end(), link), enlaces.end());
	}
}*/

bool Region::isInside(int x, int y) const{
	return ((x >= inicio.X && x <= final.X) && (y >= inicio.Y && y <= final.Y));
}
bool Region::isInside(position2di pos) const{
	return (isInside(pos.X,pos.Y));
}
/*
std::vector<Region*> Region::getConnectedRegions(){
	std::vector<Region*> regiones;
	for (int i = 0; i < enlaces.size(); ++i)
	{
		regiones.push_back(enlaces[i]->getConnected(this));
	}
	return regiones;
}*/

position2di Region::getInicio() const{
	return inicio;
}

position2di Region::getFinal() const{
	return final;
}

void Region::clear(){
	for(NodoRegional* nodo: nodos){
		nodo->clear();
	}
	nodos.clear();
}

bool Region::operator==(const Region & reg) const{
	return inicio == reg.getInicio();
}
bool Region::operator!=(const Region & reg) const{
	return !operator==(reg);
}
