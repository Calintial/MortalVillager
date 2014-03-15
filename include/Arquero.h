#ifndef ARQUERO_H
#define ARQUERO_H

#include <iostream>
#include "IDibujable.h"
#include "Unidades.h"

class Arquero : public Unidades{

public:
	Arquero();
	Arquero(int,int);
	~Arquero();

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
	int vision_range;
	int attack_range;
};

#endif