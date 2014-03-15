#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "graphicEngine.h"
#include "intelEngine.h"
#include "battleIA.h"
#include "IDibujable.h"
#include "Unidades.h"
#include "Arquero.h"
#include "ArqueroIA.h"
#include "Espadachin.h"
#include "EspadachinIA.h"
#include "Aldeano.h"
#include "AldeanoIA.h"
#include "Lancero.h"
#include "LanceroIA.h"
#include "state.h"
#include "edificio.h"
#include "CentroCiudad.h"
#include "Cuartel.h"
#include "Granja.h"
#include "Arqueria.h"
#include "Lanceria.h"
#include <iostream>
#include <time.h>
using namespace std;

/*
#define MAIN 0
#define INGAME 1
#define PAUSE 2
#define FINISH 3*/

class graphicEngine;
class intelEngine;
class battleIA;
class Current;

class gameEngine {

public:
	gameEngine();
	~gameEngine();
	void run();
	void updatePlayer();
	static void setVolume(float);
	static float getVolume();

	vector<IDibujable*> getIAUnits(){ return IAUnits; }
	vector<IDibujable*> getUserUnits(){ return UserUnits; }
	vector<IDibujable*> getBuildings(){ return buildings; }

	static void setSpeed(int);
	static int getSpeed();

	static IDibujable* addIAUnit(int,int,int);
	static IDibujable* addUserUnit(int,int,int);
	static IDibujable* addBuildings(int,int,int);

	void sleep(unsigned int);
	static Current stado;
	void addNewUnits();


private:

	graphicEngine* graphics;
	intelEngine* ia;
	int gameState;
	static float volumen;

	static int game_speed;
	vector<IDibujable*> IAUnits;
	vector<IDibujable*> UserUnits;
	vector<IDibujable*> buildings;

	/*Añadir unidades dinamicamente*/
	static vector<battleIA*> Add_IAUnits;
	static vector<Unidades*> Add_UserUnits;
	static vector<edificio*> Add_Buildings;
};



#endif
