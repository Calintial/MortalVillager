#ifndef UNIDADES_H
#define UNIDADES_H

#include <iostream>
#include "IDibujable.h"
#include "Camino.h"
#include "edificio.h"
#include "CentroCiudad.h"

using namespace std;

enum{
	/*Estados de la IA*/
	NOTHING = 0,
	MOVE = 1,
	ATTACKING = 2,
	DEAD = 3
};

const int MAX_DELAY = 3;

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
	void Move(shared_ptr<edificio>);
	void updateUnit();
	int getState();
	void setState(int s){state = s;};
	bool getSelect(){return select;};
	void SetSelect(bool sel){select=sel;};
	int getLife(){return life;};
	void setLife(int l){life=l;};
	Camino* getCamino(){return camino;};

	bool getEliminar(){return eliminar_unidad;};
	void setEliminar(bool eliminar){eliminar_unidad = eliminar;};
	
	//Getters virtuales
	virtual int getVisionRange() = 0;
	virtual int getAttackRange() = 0;
	virtual int getAttackValue() = 0;
	virtual int getType() = 0;

	//Pintado
	virtual void TexturaSeleccionada(IVideoDriver* driver,bool) = 0;

	virtual bool enemy_in_attack_range(position2di) = 0;
	virtual bool enemy_in_vision_range(position2di) = 0;
	bool CC_in_range(position2di);
	
protected:
	position2di last_clicked;
	Camino* camino;
	shared_ptr<Unidades> objetivo;
	shared_ptr<edificio> CC_Objetivo;
	position2di posicionObjetivo;
	int pesoComprobacion;
	int state;
	bool select;
	int life;
	bool eliminar_unidad;
};

#endif
