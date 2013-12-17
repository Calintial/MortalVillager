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
	/*int n_iaUnits = gameEngine::getNumberIAUnits();
	for(int i=0; i<n_iaUnits; i++)
	{*/
		delete ia_units;
	/*}*/
}

void intelEngine::updateBattleIA()
{
	for(unsigned int i=0; i<ia_units->size(); i++)
	{
		((battleIA*)ia_units->at(i))->updateIA(user_units);
	}
}