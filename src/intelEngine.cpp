#include "intelEngine.h"

intelEngine::intelEngine()
{
}

intelEngine::intelEngine(vector<battleIA*> units)
{
	ia_units = units;
}

intelEngine::~intelEngine()
{
	for(int i=0; i<ia_units.size(); i++)
	{
		delete ia_units[i];
	}
}

void intelEngine::updateBattleIA()
{
	for(int i=0; i<ia_units.size(); i++)
	{
		ia_units[i]->updateIA();
	}
}