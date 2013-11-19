#ifndef BATTLE_IA_H
#define BATTLE_IA_H

#include <iostream>
#include "Unidades.h"


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
	~battleIA();
	int updateIA();

private:
	int state;
	int* enemy_pos;

	int searching();
	int approach();
	int attack();
	int flee();
	int recovery();

};


#endif