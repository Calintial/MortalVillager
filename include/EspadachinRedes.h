#ifndef ESPADACHINREDES_H
#define ESPADACHINREDES_H
#include "CUnidadesAprendizaje.h"


class EspadachinRedes : public CUnidadesAprendizaje{
	public:
		EspadachinRedes(int x,int y);
		int getVisionRange(){return vision_range;};
		int getAttackRange(){return attack_range;};
		int getAttackValue(){return attack_value;};
		int getType(){return getTipo();}; // esto... creo que no es asi >_<
	private:

		int attack_value;
		int vision_range;
		int attack_range;
};

class CUnidadesAprendizajeDummy :  public EspadachinRedes{
public:
	CUnidadesAprendizajeDummy(int x, int y):EspadachinRedes(x,y){}
	void updateIA(std::shared_ptr<mapa2D> mapa){
		this->calcular8Objetos(mapa);
	}
};
#endif