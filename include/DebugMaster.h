#ifndef DEBUG_MASTER_H
#define DEBUG_MASTER_H

#include <iostream>
#include <irrlicht.h>
#include <fmod.hpp>
#include <string>
#include <vector>
#include <memory>
#include "graphicEngine.h"
#include "mapa2D.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;


class mapa2D;

enum{
	COMBO_SUBARBOL = 0,
	BUTTON_SEE_SUBARBOL = 1/*,
	SCROLL_SPEED = 2*/
};

class DebugMaster : public IEventReceiver
{
private:
	IrrlichtDevice * DebugDevice;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	IGUIFont* font;
	/*Imagenes de estados del MEF*/
	video::ITexture* node_1;
	video::ITexture* node_2;
	video::ITexture* node_3;
	video::ITexture* node_4;
	video::ITexture* node_5;
	video::ITexture* node_6;
	video::ITexture* node_7;
	video::ITexture* node_8;
	video::ITexture* node_9;
	video::ITexture* node_10;
	video::ITexture* node_11;
	video::ITexture* node_12;
	video::ITexture* node_13;
	video::ITexture* node_14;
	video::ITexture* node_15;
	video::ITexture* node_16;
	video::ITexture* node_17;
	video::ITexture* node_18;
	video::ITexture* node_19;
	video::ITexture* node_20;
	video::ITexture* node_21;
	video::ITexture* node_22;
	video::ITexture* node_23;
	video::ITexture* node_24;
	video::ITexture* node_25;
	video::ITexture* node_26;
	video::ITexture* node_27;
	video::ITexture* node_28;
	video::ITexture* node_29;
	video::ITexture* node_30;
	video::ITexture* node_31;
	video::ITexture* node_32;
	video::ITexture* node_33;
	video::ITexture* node_34;
	video::ITexture* node_35;
	video::ITexture* node_36;
	video::ITexture* node_37;
	video::ITexture* node_38;
	video::ITexture* node_39;
	video::ITexture* node_40;
	video::ITexture* node_41;
	video::ITexture* node_42;
	video::ITexture* node_43;
	video::ITexture* node_44;
	video::ITexture* node_45;
	video::ITexture* node_46;
	video::ITexture* node_47;
	video::ITexture* node_48;
	video::ITexture* node_49;
	video::ITexture* node_50;
	video::ITexture* node_51;
	video::ITexture* node_52;
	video::ITexture* node_53;
	video::ITexture* node_54;
	video::ITexture* node_55;
	video::ITexture* node_56;
	video::ITexture* node_57;
	video::ITexture* node_58;
	video::ITexture* node_59;
	video::ITexture* node_60;
	video::ITexture* node_61;

	shared_ptr<mapa2D> mapa;

	bool drawVision;
	bool drawAttackVision;
	int subarbolElegido;

public:
	DebugMaster(IrrlichtDevice * IrrDevice,shared_ptr<mapa2D>);
	~DebugMaster();
	void initDebugMenu();
	void Draw(vector<int> caminoNodos);
	void DrawMEF(vector<int> caminoNodos);
	void DrawParameters();
	void DrawVisions();
	virtual bool OnEvent(const SEvent& event);
	void selectSubarbol(int seleccion){subarbolElegido = seleccion;}
};

#endif
