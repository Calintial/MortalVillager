#ifndef BATTLE_IA_H
#define BATTLE_IA_H

#include <iostream>
#include <vector>
#include "Unidades.h"
#include "stateIA.h"


using namespace std;

class CurrentIA;

class battleIA : public Unidades{

public:
	battleIA();
	battleIA(int,int);
	~battleIA();
	void updateIA(vector<IDibujable*>*);
	/*virtual void Pintar(IVideoDriver*,int,int);
	virtual void TexturaSeleccionada(IVideoDriver*,bool);
	virtual void aplicarTextura(IVideoDriver* driver);*/
	int getState();
	CurrentIA* stadoIA;
	position2di enemy_pos;
	position2di searchEnemy(vector<IDibujable*>*);

	//Acciones de la IA
	virtual bool enemy_in_attack_range(position2di) = 0;
	virtual void Attack(position2di) = 0;
	virtual void Recovery() = 0;

private:
	int state;

	int searching(vector<IDibujable*>*);
	int approach(vector<IDibujable*>*);
	int attack(vector<IDibujable*>*);
	int flee(vector<IDibujable*>*);
	int recovery(vector<IDibujable*>*);
};


#endif
