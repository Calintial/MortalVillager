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
#endif