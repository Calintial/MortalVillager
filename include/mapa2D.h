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
	void GuardarMapa();

	IDibujable* getTile(int x, int y);
	IDibujable* getTile(position2di);
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
	
	//Manejo de objetos
	vector<IDibujable*>* getIa_units();
	vector<IDibujable*>* getUser_units();
	int getIASelected();
	int getUserSelected();
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


private:
	IrrlichtDevice * MapaDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	IFileSystem *file;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	int gameState;
	stringc MapaText;
	Pathfinding *pathFinding;
	void Init();
	void AllocateMap(bool suelo);

	IDibujable* vTiles[WIDTH][HEIGHT];
	vector<IDibujable*>* ia_units;
	vector<IDibujable*>* user_units;
	vector<IDibujable*>* buildings;
	
	position2di CameraScroll;


	position2di shadowPosition;

	bool Sel_Pulsado;
	position2di Sel_Inicio;
	position2di Sel_Fin;

	
	//Texturas
	stringc WorkingDirectory;
	
	bool drawVision;
	bool drawAttackVision;
	int ia_selected;
	int user_selected;

	bool sombra_edificio;
	int tipo_edificio;

	//Objetos

	void DrawIAUnits();
	void DrawUserUnits();
	void DrawBuildings();
	void DrawBuildingShadow();
	int IASelected(position2di);
	vector<int>* IASelected();
	int UserSelected(position2di);

};

#endif
