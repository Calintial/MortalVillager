/*
	Clase para gestionar lel mapa
*/
#ifndef MAPA_H
#define MAPA_H

#include <irrlicht.h>
#include "gameEngine.h"

#include <string>
#include <vector>
#include <fstream>

using namespace irr;
using namespace video;
using namespace std;
using namespace io;
using namespace gui;
using namespace core;
using namespace scene;

const int TILE_WIDTH	= 32;
const int TILE_HEIGHT = 32;


// estructura que guarda la imagen y información de un tile por cada
// textura que cargemos
struct STile
{
	STile(): textura(NULL), EventType(0), EventData(0){}
	ITexture * textura;
	int EventType;
	int EventData;
	//unsigned short ancho;
	//unsigned short alto;
	//unsigned short columnas;
};


struct IndexedEventStruct {
	IndexedEventStruct(const STile *TTile, const position2di &TPosition) : Tile(TTile), Position(TPosition) { }
	const STile *Tile;
	position2di Position;
};

class mapa2D
{
public:
	enum EventType {
			EVENT_NONE,
			EVENT_GRANJA,
			EVENT_COUNT
	};


	mapa2D();
	~mapa2D();
	mapa2D(const mapa2D&) {};
	mapa2D& operator=(const mapa2D&) {};

	bool free();

	//VISTAS
	void SetCameraScroll(const position2di &TPosition);
	const position2di &GetCameraScroll() const { return CameraScroll; }
    const dimension2di &GetViewSize() const { return ViewSize; }
    
    //Graficos
    void Render();
    void Pintar(const ITexture *TTexture, int TPositionX, int TPositionY);
    bool GridToScreen(const position2di &TGridPosition, position2di &TScreenPosition) const;
	void ScreenToGrid(const position2di &TScreenPosition, position2di &TGridPosition) const;
	
	//Eventos
	IndexedEventStruct *GetIndexedEvent(int TEventType, int TEventData);
	
	// Collision
	//bool PuedoMover(const position2di &TPosition);
	
	//Manejo de objetos
	//void Update(u32 TDeltaTime);
private:
	IrrlichtDevice * MapaDevice;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	ITimer *timer;
	IFileSystem *file;
	gui::IGUIEnvironment* env;
	IGUISkin* skin;
	IGUIFont* font;
	video::ITexture* images;
	int gameState;

	void Init();
	void AllocateMap();
	void LoadTextures();
	void LoadEvents(STile *Tile, int i, int j);

	STile **vTiles;
	int Width, Height;
	
	//Vista
	//int ViewWidth,ViewHeight;
	dimension2di ViewSize;
	position2di CameraScroll;
	
	//Texturas
	array<ITexture *> Texturas;
	std::fstream File;
	stringc WorkingDirectory;
	IVideoDriver *irrDriver;
	
	//Eventos
	array<IndexedEventStruct> IndexedEvents;
	
	//Objetos
	
};

#endif
