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
#include <memory>
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

	vector<shared_ptr<IDibujable>>* getIAUnits(){ return &IAUnits; }
	vector<shared_ptr<IDibujable>>* getUserUnits(){ return &UserUnits; }
	vector<shared_ptr<IDibujable>>* getBuildings(){ return &buildings; }

	static void setSpeed(int);
	static int getSpeed();

	static shared_ptr<IDibujable> addIAUnit(int,int,int);
	static shared_ptr<IDibujable> addUserUnit(int,int,int);
	static shared_ptr<IDibujable> addBuildings(int,int,int);

	void sleep(unsigned int);
	static Current stado;
	void addNewUnits();

	static int recursos_jugador;
	static int recursos_ia;


private:
	graphicEngine* graphics;
	intelEngine* ia;
	int gameState;
	static float volumen;

	static int game_speed;
	vector<shared_ptr<IDibujable>> IAUnits;
	vector<shared_ptr<IDibujable>> UserUnits;
	vector<shared_ptr<IDibujable>> buildings;

	/*Añadir unidades dinamicamente*/
	static vector<shared_ptr<battleIA>> Add_IAUnits;
	static vector<shared_ptr<Unidades>> Add_UserUnits;
	static vector<shared_ptr<edificio>> Add_Buildings;
};



#endif
