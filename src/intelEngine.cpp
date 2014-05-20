#include "intelEngine.h"


intelEngine::intelEngine()
{
	//dt = new DecisionTree(NULL);
}


intelEngine::intelEngine(vector<shared_ptr<IDibujable>>* units,vector<shared_ptr<IDibujable>>* Userunits, vector<shared_ptr<IDibujable>>* build, video::IVideoDriver* driver)
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

	vector<std::shared_ptr<IDibujable>>* ia_buildings = new vector<std::shared_ptr<IDibujable>>();

	for(std::shared_ptr<IDibujable> iBuild : *buildings)
	{
		std::shared_ptr<edificio> build = std::dynamic_pointer_cast<edificio>(iBuild);

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

		std::dynamic_pointer_cast<battleIA>(ia_units->at(i))->updateIA(mapa);
		//Lo vinculamos a su posible nueva posicion
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(ia_units->at(i));
		
	}
}
