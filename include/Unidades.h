#ifndef UNIDADES_H
#define UNIDADES_H

#include <iostream>
#include "IDibujable.h"
#include "Camino.h"

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
	int Attack(shared_ptr<Unidades>);
	void PierdoVida(int);
	int TrianguloArmas(shared_ptr<Unidades>);
	
	void Move(int,int);
	void Move(Camino*);
	void Move(shared_ptr<Unidades>);
	void updateUnit();
	int getState();
	bool getSelect(){return select;};
	void SetSelect(bool sel){select=sel;};
	int getLife(){return life;};
	void setLife(int l){life=l;};
	
	//Getters virtuales
	virtual int getVisionRange() = 0;
	virtual int getAttackRange() = 0;
	virtual int getAttackValue() = 0;
	virtual int getType() = 0;

	//Pintado
	virtual void TexturaSeleccionada(IVideoDriver* driver,bool) = 0;
	
protected:
	position2di last_clicked;
	Camino* camino;
	shared_ptr<Unidades> objetivo;
	position2di posicionObjetivo;
	int pesoComprobacion;
	int state;
	bool select;
	int life;
};

#endif
