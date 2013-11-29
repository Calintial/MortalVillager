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
	int updateIA(Unidades**);
	void Pintar(IVideoDriver*);

private:
	int state;
	int* enemy_pos;

	int searching(Unidades**);
	int approach(Unidades**);
	int attack(Unidades**);
	int flee(Unidades**);
	int recovery();
	int* searchEnemy(Unidades**);

};


#endif