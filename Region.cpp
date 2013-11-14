#include "Region.h"

Region::Region(int _inicioX, int _inicioY, int _finalX, int _finalY):inicioX(_inicioX),inicioY(_inicioY),finalX(_finalX),finalY(_finalY){
	//enlaces = new std::vector<Enlace*>();
}

Region::~Region(){
	int tam = enlaces.size();
	for (int i = 0; i < tam; ++i)
	{
		delete enlaces[i];
	}
	enlaces.clear();
}

void Region::add(Enlace* link){
	enlaces.push_back(link);
}

void Region::remove(Enlace* link){
	if(enlaces.size() > 0){
		// elimina el elemento que coincide con link.
		enlaces.erase(std::remove(enlaces.begin(), enlaces.end(), link), enlaces.end());
	}
}

bool Region::isInside(int x, int y){
	return ((x >= inicioX && x <= finalX) && (y >= inicioY && y <= finalY));
}

std::vector<Region*> Region::getConnectedRegions(){
	std::vector<Region*> regiones;
	for (int i = 0; i < enlaces.size(); ++i)
	{
		regiones.push_back(enlaces[i]->getConnected(this));
	}
	return regiones;
}