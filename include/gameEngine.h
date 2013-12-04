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
	static int getNumberIAUnits();
	static int getNumberUserUnits();

private:
	void sleep(unsigned int);

	graphicEngine* graphics;
	intelEngine* ia;
	int gameState;
	static float volumen;
	static vector<battleIA*> IAUnits;
	static vector<Unidades*> UserUnits;

};



#endif