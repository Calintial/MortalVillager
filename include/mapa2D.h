/*
	Clase para gestionar lel mapa
*/
#ifndef MAPA_H
#define MAPA_H

#include <irrlicht.h>
#include "gameEngine.h"
#include "IDibujable.h"
#include "suelo.h"
#include "muro.h"
#include "edificio.h"
#include "Unidades.h"
#include "Pathfinding.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <math.h>

using namespace irr;
using namespace video;
using namespace std;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;

const int TILE_WIDTH	= 32;
const int TILE_HEIGHT = 32;

#define WIDTH 200
#define HEIGHT 200
#define MAPSIZE 200


class mapa2D {

public:
	enum EventType {
			EVENT_NONE,
			EVENT_GRANJA,
			EVENT_COUNT
	};


	mapa2D(IrrlichtDevice * IrrDevice,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,bool);
	virtual ~mapa2D();
	//mapa2D(const mapa2D&) {};
	//mapa2D& operator=(const mapa2D&) {};

	bool free();
	
	void GenerarMapa();
	void GuardarMapa();

	virtual shared_ptr<IDibujable> getTile(int x, int y);
	virtual shared_ptr<IDibujable> getTile(position2di);
	virtual void setTile(int x, int y, shared_ptr<IDibujable>contenido);
	virtual void setTile(position2di pos, shared_ptr<IDibujable>contenido){setTile(pos.Y,pos.X,contenido);}
	void AnyadirObjeto(shared_ptr<IDibujable>);

	//VISTAS
	void SetCameraScroll(const position2di &TPosition);
	const position2di &GetCameraScroll() const { return CameraScroll; }
    const dimension2di &GetViewSize() const { return ViewSize; }
    
    //Graficos
    virtual void Pintar();
    void PintarTile(const ITexture *TTexture, int TPositionX, int TPositionY);
	position2di getDrawPosition(position2di pos);
	
	//Eventos
	vector<shared_ptr<Unidades>>* OnEventMapa(const SEvent& event);
	
	//Manejo de objetos
	vector<shared_ptr<IDibujable>>* getIa_units();
	vector<shared_ptr<IDibujable>>* getUser_units();
	
	vector<shared_ptr<IDibujable>>* getBuildings();
	int getIASelected();
	vector<int>* getUserSelected();
	Pathfinding* getPathfinding();

	dimension2di ViewSize;

	void InicializarGraficosUnidades();

	static position2di isoTo2D(int x, int y);
	static position2di twoDToIso(int x, int y);
	static position2di getTileCoordinates(int x, int y);
	static position2di getIsoFromTile(int x, int y);

	void setSombra(bool s);
	bool getSombra();

	void setTipoEdificio(int tipo);
	int getTipoEdificio();

	void setSombraCoords(position2di pos);
	position2di getSombraCoords();
	bool puede_colocar(position2di pos);
	bool collide(position2di,int,int,position2di,int,int);
	void colocarEdificio(position2di);

	position2di posicionDisponible(position2di );

	
	shared_ptr<IDibujable> addIAUnit(int,int,int);
	shared_ptr<IDibujable> addUserUnit(int,int,int);

private:
	
	stringc MapaText;
	Pathfinding *pathFinding;
	void Init();
	void AllocateMap(bool suelo);

	
	
	


	position2di shadowPosition;

	bool Sel_Pulsado;
	position2di Sel_Inicio;
	position2di Sel_Fin;

	
	//Texturas
	stringc WorkingDirectory;
	
	bool drawVision;
	bool drawAttackVision;
	int ia_selected;
	int numuser_selected;

	bool sombra_edificio;
	int tipo_edificio;
	
	//Algoritmo de recolocacion
	int recol_Rango,recol_gradosel,recol_RangoAux;
	vector<int> recol_Grados;
	void reasignarVectorRecolocacion(int, int );
	
	bool puede_colocarUnidad(position2di );

	//Objetos

	void DrawIAUnits();
	void DrawUserUnits();
	void DrawBuildings();
	void DrawBuildingShadow();
	int IASelected(position2di);
	vector<int>* IASelected();
	int UserSelected(position2di);
	vector<int>* UserSelected();
	
	vector<int>* ia_selvector;
	vector<int>* user_selvector;

protected:
	mapa2D(IrrlichtDevice* dev);

	IrrlichtDevice * MapaDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	IFileSystem *file;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	int gameState;

	shared_ptr<IDibujable> vTiles[WIDTH][HEIGHT];
	vector<shared_ptr<IDibujable>>* ia_units;
	vector<shared_ptr<IDibujable>>* user_units;
	vector<shared_ptr<IDibujable>>* buildings;

	position2di CameraScroll;
};

#endif
