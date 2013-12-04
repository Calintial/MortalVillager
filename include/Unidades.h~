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
	void setPosition(int,int);
	void updateIA();
	void Move(int,int);
	void Attack(int,int);
	int* getPosition();
	bool enemy_in_attack_range(int,int);
	int getLife();
	virtual void Pintar(IVideoDriver* driver);
	void Recovery();
	void updateUnit();

private:
	int life;
	int position[2];
	int last_clicked[2];
	int state;

};

#endif