#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "graphicEngine.h"
#include "intelEngine.h"
#include "battleIA.h"
#include "IDibujable.h"
#include "Unidades.h"
#include "state.h"
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
	static void updatePlayer();
	static void setVolume(float);
	static float getVolume();

	static void setSpeed(int);
	static int getSpeed();
	static vector<IDibujable*> getIAUnits(){ return IAUnits; }
	static vector<IDibujable*> getUserUnits(){ return UserUnits; }
	static void addIAUnit(int,int);
	static void sleep(unsigned int);
	static void addNewUnits();

	static Current stado;
private:
	graphicEngine* graphics;
	intelEngine* ia;
	int gameState;
	static float volumen;

	static int game_speed;
	static vector<IDibujable*> IAUnits;
	static vector<IDibujable*> UserUnits;

	/*Añadir unidades dinamicamente*/
	static vector<battleIA*> Add_IAUnits;
	static vector<Unidades*> Add_UserUnits;
	static void addUserUnit(int,int);
};



#endif
