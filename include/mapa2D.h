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
#include "pathfinding.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

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


class mapa2D {

public:
	enum EventType {
			EVENT_NONE,
			EVENT_GRANJA,
			EVENT_COUNT
	};


	mapa2D(IrrlichtDevice * IrrDevice,vector<IDibujable*>*,vector<IDibujable*>*,vector<IDibujable*>*,bool);
	~mapa2D();
	//mapa2D(const mapa2D&) {};
	//mapa2D& operator=(const mapa2D&) {};

	bool free();
	
	void GenerarMapa();

	IDibujable* getTile(int x, int y);
	void setTile(int x, int y, IDibujable* contenido);

	//VISTAS
	void SetCameraScroll(const position2di &TPosition);
	const position2di &GetCameraScroll() const { return CameraScroll; }
    const dimension2di &GetViewSize() const { return ViewSize; }
    
    //Graficos
    void Pintar();
    void PintarTile(const ITexture *TTexture, int TPositionX, int TPositionY);
	position2di getDrawPosition(position2di pos);
	
	//Eventos
	Unidades* OnEventMapa(const SEvent& event);
	
	// Collision
	//bool PuedoMover(const position2di &TPosition);
	
	//Manejo de objetos
	//void Update(u32 TDeltaTime);
	vector<IDibujable*>* getIa_units();
	vector<IDibujable*>* getUser_units();
	int getIASelected();
	int getUserSelected();
	pathfinding* getPathfinding();

	dimension2di ViewSize;

	void InicializarGraficosUnidades();

private:
	IrrlichtDevice * MapaDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	IFileSystem *file;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	int gameState;
	stringc MapaText;
	pathfinding *pathFinding;
	void Init();
	void AllocateMap(bool suelo);
	//void LoadEvents(STile *Tile, int i, int j);

	IDibujable* vTiles[WIDTH][HEIGHT];
	vector<IDibujable*>* ia_units;
	vector<IDibujable*>* user_units;
	vector<IDibujable*>* buildings;

	//Vista
	//int ViewWidth,ViewHeight;
	
	position2di CameraScroll;
	
	//Texturas
	stringc WorkingDirectory;
	
	//Eventos
	//array<IndexedEventStruct> IndexedEvents;
	
	bool drawVision;
	bool drawAttackVision;
	int ia_selected;
	int user_selected;

	//Objetos

	void DrawIAUnits();
	void DrawUserUnits();
	void DrawBuildings();
	int IASelected(position2di);
	int UserSelected(position2di);
};

#endif
