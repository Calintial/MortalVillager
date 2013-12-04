#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "graphicEngine.h"
#include <iostream>
using namespace std;


#define MAIN 0
#define INGAME 1
#define PAUSE 2
#define FINISH 3

class graphicEngine;

class gameEngine {

public:
	gameEngine();
	~gameEngine();
	void run();
	static void setVolume(float);
	static float getVolume();

private:
	graphicEngine* graphics;
	int gameState;
	static float volumen;
};



#endif