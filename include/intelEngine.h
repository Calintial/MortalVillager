#ifndef IA_ENGINE_H
#define IA_ENGINE_H

/*
	Clase para gestionar las distintas IAs
*/
#include <iostream>
#include <vector>
#include "battleIA.h"
#include "gameEngine.h"
#include "IDibujable.h"
#include "DecisionTree.h"

using namespace std;

class DecisionTree;

class intelEngine {
public:
	intelEngine();

	intelEngine(vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,vector<shared_ptr<IDibujable>>*,video::IVideoDriver*);
	~intelEngine();
	void updateBattleIA(std::shared_ptr<mapa2D> mapa);
	/*intelEngine(const intelEngine&) {};
	intelEngine& operator=(const intelEngine&) {};*/

private:
	vector<shared_ptr<IDibujable>>* ia_units;
	vector<shared_ptr<IDibujable>>* user_units;
	vector<shared_ptr<IDibujable>>* buildings;
	DecisionTree* dt;
	video::IVideoDriver* driver;

};

#endif
