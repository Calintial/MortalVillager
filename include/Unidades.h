#ifndef UNIDADES_H
#define UNIDADES_H

#include <iostream>
#include "IDibujable.h"

using namespace std;

enum{
	/*Estados de la IA*/
	NOTHING = 0,
	MOVE = 1,
	ATTACKING = 2
};


class Unidades : public IDibujable{
public:
	Unidades();
	Unidades(int,int);
	~Unidades();
	void updateIA();
	void Move(int,int);
	void Attack(position2di);
	bool enemy_in_attack_range(position2di);
	int getLife();
	virtual void Pintar(IVideoDriver* driver);
	void PintarSeleccionada(IVideoDriver* driver);
	void Recovery();
	void updateUnit();
	int getVisionRange();
	int getAttackRange();

private:
	int life;
	position2di last_clicked;
	int state;
	int vision_range;
	int attack_range;

};

#endif
