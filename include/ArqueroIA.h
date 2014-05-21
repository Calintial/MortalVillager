#ifndef ARQUEROIA_H
#define ARQUEROIA_H

#include <iostream>
#include "IDibujable.h"
#include "battleIA.h"

class ArqueroIA : public battleIA{

public:
	ArqueroIA();
	ArqueroIA(int,int);
	~ArqueroIA();

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

	void nextSprite();

	

private:
	int sprite_Width;
	int sprite_Height;
	int current_sprite;
	int delay_sprite;
	int attack_value;
	int vision_range;
	int attack_range;
	ITexture *TTexture;
};

#endif
