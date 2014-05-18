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

class CUnidadesAprendizaje;
class SGenome;

class MapaAprendizaje : public mapa2D
{
public:
	MapaAprendizaje(IrrlichtDevice* dev,int);
	virtual ~MapaAprendizaje();

	void Pintar();
	void PintarInformacionUnidad();
	
	void setTile(position2di,IDibujable*);
	void setTile(int y,int x,IDibujable*);
	IDibujable* getTile(int y,int x){return vTiles[y][x];};
	IDibujable* getTile(position2di pos){return getTile(pos.Y,pos.X);};
	void setUnidadSeleccionada(Unidades* unit){unidad_seleccionada = unit;}

	vector<CUnidadesAprendizaje*> getUnidadesAprendizaje() const {return m_vecUnidades;}

	virtual void generarMapa() = 0;
	virtual void reset(const vector<SGenome> &) = 0;
	
protected:
	void nuevoSuelo(int,int);
	void nuevoMuro(int,int);

	Unidades* unidad_seleccionada;
	vector<CUnidadesAprendizaje*> m_vecUnidades;
	int m_NumUnidades;
private:
	IGUIFont* font;
};

class MapaBasicoDummy : public MapaAprendizaje
{
public:
	MapaBasicoDummy(IrrlichtDevice* dev,int);
	~MapaBasicoDummy();

	void generarMapa();
	void reset(const vector<SGenome> &);
private:
	void generarUnidades();
};

class MapaBasicoMuroYUnidad : public MapaAprendizaje
{
public:
	MapaBasicoMuroYUnidad(IrrlichtDevice* dev,int);
	~MapaBasicoMuroYUnidad();

	void generarMapa();
	void reset(const vector<SGenome> &);
private:
	void generarUnidades();

	vector<CUnidadesAprendizaje*> m_vecEnemigos;
};
class MapaCuatroUnidades: public MapaAprendizaje
{
public:
	MapaCuatroUnidades(IrrlichtDevice* dev,int);
	~MapaCuatroUnidades();
	void generarSuelos(int inicio,int fin);
	void generarMapa();
		void reset(const vector<SGenome> &);
private:
	void generarUnidades();
};
class MapaCuadrado: public MapaAprendizaje
{
public:
	MapaCuadrado(IrrlichtDevice* dev,int);
	~MapaCuadrado();
	void generarSuelos(int inicio,int fin);
	void generarMapa();
		void reset(const vector<SGenome> &);
private:
	void generarUnidades();
};
#endif