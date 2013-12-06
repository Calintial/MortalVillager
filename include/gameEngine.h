#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "graphicEngine.h"
#include "intelEngine.h"
#include "battleIA.h"
#include "IDibujable.h"
#include "Unidades.h"
#include <iostream>
#include <time.h>
using namespace std;


#define MAIN 0
#define INGAME 1
#define PAUSE 2
#define FINISH 3

class graphicEngine;
class intelEngine;
class battleIA;

class gameEngine {

public:
	gameEngine();
	~gameEngine();
	void run();
	void updatePlayer();
	static void setVolume(float);
	static float getVolume();

	static void setSpeed(int);
	static int getSpeed();
	static IDibujable* addIAUnit(int,int);
	static IDibujable* addUserUnit(int,int);

private:
	void sleep(unsigned int);

	graphicEngine* graphics;
	intelEngine* ia;
	int gameState;
	static float volumen;

	static int game_speed;
	vector<IDibujable*> IAUnits;
	vector<IDibujable*> UserUnits;

	/*Añadir unidades dinamicamente*/
	static vector<battleIA*> Add_IAUnits;
	static vector<Unidades*> Add_UserUnits;
	
	void addNewUnits();


};



#endif