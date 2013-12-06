/*
	Clase para gestionar lel mapa
*/
#ifndef MAPA_H
#define MAPA_H

#include <irrlicht.h>
#include "gameEngine.h"
#include "IDibujable.h"
#include "suelo.h"
#include "edificio.h"
#include "Unidades.h"
#include "DebugMenu.h"


#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace irr;
using namespace video;
using namespace std;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;

const int TILE_WIDTH	= 32;
const int TILE_HEIGHT = 32;
#define WIDTH 250
#define HEIGHT 250


// estructura que guarda la imagen y información de un tile por cada
// textura que cargemos
/*struct STile
{
	//STile(): textura(NULL), EventType(0), EventData(0){}
	STile(): objeto(NULL), EventType(0), EventData(0){}
	//ITexture * textura;
	int EventType;
	int EventData;
	IDibujable * objeto; 
	//unsigned short ancho;
	//unsigned short alto;
	//unsigned short columnas;
};*/


/*struct IndexedEventStruct {
	IndexedEventStruct(const STile *TTile, const position2di &TPosition) : Tile(TTile), Position(TPosition) { }
	const STile *Tile;
	position2di Position;
};*/

class mapa2D : public IEventReceiver
{
public:
	enum EventType {
			EVENT_NONE,
			EVENT_GRANJA,
			EVENT_COUNT
	};


	mapa2D(IrrlichtDevice * IrrDevice,vector<IDibujable*>*,vector<IDibujable*>*);
	~mapa2D();
	//mapa2D(const mapa2D&) {};
	//mapa2D& operator=(const mapa2D&) {};

	bool free();
	
	void GenerarMapa();

	IDibujable* getTile(int x, int y);

	//VISTAS
	void SetCameraScroll(const position2di &TPosition);
	const position2di &GetCameraScroll() const { return CameraScroll; }
    const dimension2di &GetViewSize() const { return ViewSize; }
    
    //Graficos
    int Pintar();
    void PintarTile(const ITexture *TTexture, int TPositionX, int TPositionY);
    bool GridToScreen(const position2di &TGridPosition, position2di &TScreenPosition) const;
	void ScreenToGrid(const position2di &TScreenPosition, position2di &TGridPosition) const;
	
	//Eventos
	virtual bool OnEvent(const SEvent& event);
	//IndexedEventStruct *GetIndexedEvent(int TEventType, int TEventData);
	
	// Collision
	//bool PuedoMover(const position2di &TPosition);
	
	//Manejo de objetos
	//void Update(u32 TDeltaTime);

	int getIASelected();
	int getUserSelected();
private:
	IrrlichtDevice * MapaDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	IFileSystem *file;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	int gameState;
	stringc MapaText;

	void Init();
	void AllocateMap();
	//void LoadEvents(STile *Tile, int i, int j);

	IDibujable* vTiles[WIDTH][HEIGHT];
	vector<IDibujable*>* ia_units;
	vector<IDibujable*>* user_units;
	
	//Vista
	//int ViewWidth,ViewHeight;
	dimension2di ViewSize;
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
	void InicializarGraficosUnidades();
	int IASelected(position2di);
	int UserSelected(position2di);
};

#endif
