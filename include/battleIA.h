#ifndef BATTLE_IA_H
#define BATTLE_IA_H

#include <iostream>
#include <vector>
#include <memory>
#include "Unidades.h"
#include "stateIA.h"


using namespace std;

class CurrentIA;
class mapa2D;

class battleIA : public Unidades{

public:
	battleIA();
	battleIA(int,int);
	~battleIA();
	virtual void updateIA(std::shared_ptr<mapa2D> mapa);
	int getState();
	CurrentIA* stadoIA;
	shared_ptr<IDibujable> searchEnemy(std::shared_ptr<mapa2D> mapa);

	//Acciones de la IA
	virtual bool enemy_in_attack_range(position2di) = 0;
	virtual void Recovery() = 0;

private:
	int stateIA;

};


#endif
