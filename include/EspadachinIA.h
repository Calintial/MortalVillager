#ifndef ESPADACHINIA_H
#define ESPADACHINIA_H

#include <iostream>
#include "IDibujable.h"
#include "battleIA.h"

class EspadachinIA : public battleIA{

public:
	EspadachinIA();
	EspadachinIA(int,int);
	~EspadachinIA();

	//Metodos de acción
	void Attack(position2di);
	bool enemy_in_attack_range(position2di);
	void Recovery();

	//Getters
	virtual int getLife();
	virtual int getVisionRange();
	virtual int getAttackRange();

	//Metodos de dibujado
	virtual void Pintar(IVideoDriver* driver,int,int);
	virtual void TexturaSeleccionada(IVideoDriver* driver,bool);
	void aplicarTextura(IVideoDriver* driver);
	

private:
	int life;
	int attack_value;
	int vision_range;
	int attack_range;
};

#endif