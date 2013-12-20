#ifndef BATTLE_IA_H
#define BATTLE_IA_H

#include <iostream>
#include "Unidades.h"
#include "gameEngine.h"
#include "stateIA.h"


using namespace std;

enum{
	/*Estados de la IA*/
	SEARCHING = 0,
	APPROACH = 1,
	ATTACK = 2,
	FLEE = 3,
	RECOVERY = 4,
};

class CurrentIA;

class battleIA : public Unidades
{

public:
	battleIA();
	battleIA(int,int);
	~battleIA();
	void updateIA(vector<IDibujable*>*);
	virtual void Pintar(IVideoDriver*,int,int);
	void TexturaSeleccionada(IVideoDriver*,bool);
	virtual void aplicarTextura(IVideoDriver* driver);
	int getState();
	static CurrentIA stadoIA;
	position2di enemy_pos;
	position2di searchEnemy(vector<IDibujable*>*);

private:
	int state;
	

	int searching(vector<IDibujable*>*);
	int approach(vector<IDibujable*>*);
	int attack(vector<IDibujable*>*);
	int flee(vector<IDibujable*>*);
	int recovery(vector<IDibujable*>*);
};


#endif
