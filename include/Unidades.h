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
	//void updateIA();
	//Metodos de movimiento y actualización de la unidad
	void Move(int,int);
	void updateUnit();

	//Getters virtuales
	virtual int getLife() = 0;
	virtual int getVisionRange() = 0;
	virtual int getAttackRange() = 0;

	//Pintado
	virtual void TexturaSeleccionada(IVideoDriver* driver,bool) = 0;
	
private:
	position2di last_clicked;
	int state;

};

#endif
