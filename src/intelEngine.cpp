#include "intelEngine.h"


intelEngine::intelEngine()
{
	//dt = new DecisionTree(NULL);
}

intelEngine::intelEngine(vector<IDibujable*>* units,vector<IDibujable*>* Userunits, vector<IDibujable*>* build, video::IVideoDriver* driver)
{
	this->driver = driver;
	dt = new DecisionTree(driver);
	ia_units = units;
	user_units = Userunits;
	buildings = build;
}

intelEngine::~intelEngine()
{
		//delete ia_units;
}

void intelEngine::updateBattleIA(std::shared_ptr<mapa2D> mapa)
{
	int vidaCC = 100;

	vector<IDibujable*>* ia_buildings = new vector<IDibujable*>();

	for(IDibujable* iBuild : *buildings)
	{
		edificio* build = (edificio*) iBuild;

		if(!build->getDeUsuario())
		{
			ia_buildings->push_back(build);
		}
	}

	dt->doDecision(vidaCC,gameEngine::recursos_ia,ia_units,user_units,ia_buildings);

	for(unsigned int i=0; i<ia_units->size(); i++)
	{
		//Lo devinculamos de su posicion anterior
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(NULL);
		((battleIA*)ia_units->at(i))->updateIA(mapa);
		//Lo vinculamos a su posible nueva posicion
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(ia_units->at(i));
		
	}
}
