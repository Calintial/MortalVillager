#ifndef ALDEANO_H
#define ALDEANO_H

#include <iostream>
#include "IDibujable.h"
#include "Unidades.h"

class Aldeano : public Unidades{

public:
	Aldeano();
	Aldeano(int,int);
	~Aldeano();

	//Metodos de acción
	bool enemy_in_attack_range(position2di);
	void Recovery();

	//Getters
	virtual int getVisionRange();
	virtual int getAttackRange();
	virtual int getAttackValue();
	virtual int getType();

	//Metodos de dibujado
	virtual void Pintar(IVideoDriver* driver,int,int);
	virtual void TexturaSeleccionada(IVideoDriver* driver,bool);
	void aplicarTextura(IVideoDriver* driver);
	

private:
	int sprite_Width;
	int sprite_Height;
	int current_sprite;
	int attack_value;
	int vision_range;
	int attack_range;
	ITexture *TTexture;
};

#endif
