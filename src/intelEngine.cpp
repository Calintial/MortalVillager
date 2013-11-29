#include "intelEngine.h"


intelEngine::intelEngine()
{
}

intelEngine::intelEngine(battleIA** units,Unidades** Userunits)
{
	ia_units = units;
	user_units = Userunits;
}

intelEngine::~intelEngine()
{
	int n_iaUnits = gameEngine::getNumberIAUnits();
	for(int i=0; i<n_iaUnits; i++)
	{
		delete ia_units[i];
	}
}

void intelEngine::updateBattleIA()
{
	int n_iaUnits = gameEngine::getNumberIAUnits();

	for(int i=0; i<n_iaUnits; i++)
	{
		ia_units[i]->updateIA(user_units);
	}
}