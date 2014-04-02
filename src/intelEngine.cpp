#include "intelEngine.h"


intelEngine::intelEngine()
{
}

intelEngine::intelEngine(vector<IDibujable*>* units,vector<IDibujable*>* Userunits)
{
	ia_units = units;
	user_units = Userunits;
}

intelEngine::~intelEngine()
{
		//delete ia_units;
}

void intelEngine::updateBattleIA(std::shared_ptr<mapa2D> mapa)
{
	for(unsigned int i=0; i<ia_units->size(); i++)
	{
		//Lo devinculamos de su posicion anterior
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(NULL);
		((battleIA*)ia_units->at(i))->updateIA(mapa);
		//Lo vinculamos a su posible nueva posicion
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(ia_units->at(i));
		
	}
}
