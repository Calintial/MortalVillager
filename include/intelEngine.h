#ifndef IA_ENGINE_H
#define IA_ENGINE_H

/*
	Clase para gestionar las distintas IAs
*/
#include <iostream>
#include <vector>
#include "battleIA.h"
using namespace std;

class intelEngine {
public:
	intelEngine();
	intelEngine(vector<battleIA*> units);
	~intelEngine();
	void updateBattleIA();
	/*intelEngine(const intelEngine&) {};
	intelEngine& operator=(const intelEngine&) {};*/

private:
	vector<battleIA*> ia_units;
	
};

#endif