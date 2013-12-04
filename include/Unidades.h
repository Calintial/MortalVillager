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
	void Attack(int,int);
	bool enemy_in_attack_range(int,int);
	int getLife();
	virtual void Pintar(IVideoDriver* driver);
	void Recovery();
	void updateUnit();

private:
	int life;
	position2di last_clicked;
	int state;

};

#endif
