/*
	Clase para gestionar lel mapa
*/
#ifndef MAPA_APRENDIZAJE_H
#define MAPA_APRENDIZAJE_H

#include <irrlicht.h>
#include "mapa2D.h"

using namespace irr;
using namespace video;
using namespace std;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;

class MapaAprendizaje : public mapa2D
{
public:
	MapaAprendizaje(IrrlichtDevice* dev);
	virtual ~MapaAprendizaje();

	void Pintar();
	void PintarInformacionUnidad();
	
	void setTile(position2di,IDibujable*);
	void setTile(int y,int x,IDibujable*);

	virtual void generarMapa() = 0;
	
protected:
	Unidades* unidad_seleccionada;
};

class MapaBasicoDummy : public MapaAprendizaje
{
public:
	MapaBasicoDummy(IrrlichtDevice* dev);
	~MapaBasicoDummy();

	void generarMapa();
};

#endif