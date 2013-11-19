#ifndef UNIDADES_H
#define UNIDADES_H

#include <iostream>

using namespace std;


class Unidades {
public:
	Unidades();
	~Unidades();
	void updateIA();
	int* searchEnemy();
	void Move(int,int);
	void Attack(int,int);
	int* getPosition();
	bool enemy_in_attack_range(int,int);
	int getLife();

private:
	int life;
	int position[2];
};

#endif