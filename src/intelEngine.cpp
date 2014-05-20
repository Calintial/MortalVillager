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

	/*
	 * CONFORME ESTA AHORA --> El hace una decision y la hace, y la battle ia actua cuando hay alguien cerca,
	 * PERO --> no manda a nadie a Atacar nunca, o a Defender la base 
	 * 
	 * MIENTRAS ESTE EN ATACAR --> Mando a num_soldados/2 a atacar (se puede poner variable en cada unidad para saber cuantos ya estan atacando)
	 * MIENTRAS ESTE EN DEFENDER --> Mando a todos a las coodenadas del centro ciudad (habria que mandar solo a los que no esten)
	 *
	*/

	for(unsigned int i=0; i<ia_units->size(); i++)
	{
		//Lo devinculamos de su posicion anterior
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(NULL);
		((battleIA*)ia_units->at(i))->updateIA(mapa);
		//Lo vinculamos a su posible nueva posicion
		mapa->getTile(ia_units->at(i)->getPosition().X,ia_units->at(i)->getPosition().Y)->setVinculado(ia_units->at(i));
		
	}
}
