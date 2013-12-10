#ifndef BATTLE_IA_H
#define BATTLE_IA_H

#include <iostream>
#include "Unidades.h"
#include "gameEngine.h"


using namespace std;

enum{
	/*Estados de la IA*/
	SEARCHING = 0,
	APPROACH = 1,
	ATTACK = 2,
	FLEE = 3,
	RECOVERY = 4,
};



class battleIA : public Unidades
{

public:
	battleIA();
	battleIA(int,int);
	~battleIA();
	int updateIA(vector<IDibujable*>*);
	void Pintar(IVideoDriver*);
	int getState();

private:
	int state;
	position2di enemy_pos;

	int searching(vector<IDibujable*>*);
	int approach(vector<IDibujable*>*);
	int attack(vector<IDibujable*>*);
	int flee(vector<IDibujable*>*);
	int recovery(vector<IDibujable*>*);
	position2di searchEnemy(vector<IDibujable*>*);

};


#endif
