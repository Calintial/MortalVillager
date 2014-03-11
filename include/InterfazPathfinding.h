#ifndef INTERFAZ_PF_H
#define INTERFAZ_PF_H

#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include <string>
#include <vector>
#include "graphicEngine.h"
#include "mapa2D.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

enum{
	CB_REGIONES = 0,
	CB_ENLACES = 1,
	CB_CAMINOS_INTERNOS = 2,
	CB_CAMINO_FINAL = 3,
	BUTTON_NEXT = 4,
	BUTTON_CLEAR = 5
};

enum Estado{
	ESTADO_PINTAR,
	ESTADO_CAMINO
};

class InterfazPathfinding
{
private:
	IrrlichtDevice * device;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUIFont* font;

	shared_ptr<mapa2D> mapa;
	Camino* caminoFinal;

	bool drawRegiones, drawEnlaces, drawCaminosInternos, drawCaminoFinal;
	Estado estado;

	ITexture *enlaces_textura;
	ITexture *caminos_internos_textura;
	ITexture *caminos_textura;
public:
	InterfazPathfinding(IrrlichtDevice * IrrDevice,shared_ptr<mapa2D>);
	~InterfazPathfinding();

	void Draw();
	void DrawRegiones();
	void DrawEnlacesYCaminos();
	void DrawCaminoFinal();
	void init();
	bool OnEvent(const SEvent& event);
	void DrawIsometricRectangle(position2di ini, position2di fin,video::SColor color);
	void DrawIsometricRectangleFilled(position2di ini, position2di fin,ITexture * textura);
	position2di origen,destino;
};

#endif