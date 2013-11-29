#ifndef IA_ENGINE_H
#define IA_ENGINE_H

/*
	Clase para gestionar las distintas IAs
*/
#include <iostream>
#include <vector>
#include "battleIA.h"
#include "gameEngine.h"

using namespace std;

class battleIA;

class intelEngine {
public:
	intelEngine();
	intelEngine(battleIA**,Unidades**);
	~intelEngine();
	void updateBattleIA();
	/*intelEngine(const intelEngine&) {};
	intelEngine& operator=(const intelEngine&) {};*/

private:
	battleIA** ia_units;
	Unidades** user_units;
};

#endif