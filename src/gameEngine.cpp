#include "gameEngine.h"
#include "AldeanoDemo.h"

float gameEngine::volumen = 0.5;
int gameEngine::game_speed = 100;
Current gameEngine::stado;

vector<shared_ptr<battleIA>> gameEngine::Add_IAUnits;
vector<shared_ptr<Unidades>> gameEngine::Add_UserUnits;
vector<shared_ptr<edificio>> gameEngine::Add_Buildings;

int gameEngine::recursos_jugador = 1000;
int gameEngine::recursos_ia = 1000;

int gameEngine::granjas_usuario = 0;
int gameEngine::granjas_ia = 0;


gameEngine::gameEngine()
{
	gameState = 0;

	graphics = new graphicEngine();

	video::IVideoDriver* driver = graphics->getDriver();
	
	ia = new intelEngine(&IAUnits,&UserUnits,&buildings,driver);


}

gameEngine::~gameEngine()
{
	delete graphics;
	thread_resources.join();

}

void gameEngine::run()
{
 	thread_resources = std::thread(&gameEngine::scheduler, this, 10000);
	//Bucle principal del juego. Mientras el estado no cambia a FINISH el programa no termina.
	//En cada estado se llamará a los motores necesarios(IA,Graficos,etc...)
	while(!stado.sfinal())
	{
		stado.doSomething(this, graphics,ia,graphics->mapa);
	}
}

void gameEngine::setVolume(float vol)
{
	volumen = vol;
}

float gameEngine::getVolume()
{
	return volumen;
}

void gameEngine::updatePlayer()
{
	Unidades* uni_ptr;
	for(shared_ptr<IDibujable> u : UserUnits)
	{
		graphics->mapa->getTile(u->getPosition().X,u->getPosition().Y)->setVinculado(NULL);
		uni_ptr = (Unidades*)(u.get());
		uni_ptr->updateUnit();
		graphics->mapa->getTile(u->getPosition().X,u->getPosition().Y)->setVinculado(u);
	}
}

void gameEngine::sleep(unsigned int mseconds)
{
    clock_t goal = (mseconds*(CLOCKS_PER_SEC/1000)) + clock();
    while (goal > clock());
}

void gameEngine::setSpeed(int speed)
{
	game_speed = speed;
}

int gameEngine::getSpeed()
{
	return game_speed;
}

shared_ptr<IDibujable> gameEngine::addUserUnit(int x,int y, int tipo)
{
	shared_ptr<Unidades> new_unit;
	switch(tipo)
	{
		case 0: new_unit = shared_ptr<Unidades>(new Aldeano(x,y)); break;
		case 1: new_unit = shared_ptr<Unidades>(new Espadachin(x,y)); break;
		case 2: new_unit = shared_ptr<Unidades>(new Lancero(x,y)); break;
		case 3: new_unit = shared_ptr<Unidades>(new Arquero(x,y)); break;
		
	}
	
	Add_UserUnits.push_back(new_unit);

	return new_unit;
}


shared_ptr<IDibujable> gameEngine::addIAUnit(int x,int y,int tipo)
{	
	shared_ptr<battleIA> new_unit;
	switch(tipo)
	{
		case 0: new_unit = shared_ptr<battleIA>(new AldeanoIA(x,y)); break;
		case 1: new_unit = shared_ptr<battleIA>(new EspadachinIA(x,y)); break;
		case 2: new_unit = shared_ptr<battleIA>(new LanceroIA(x,y)); break;
		case 3: new_unit = shared_ptr<battleIA>(new ArqueroIA(x,y)); break;
		case 4: new_unit = shared_ptr<battleIA>(new AldeanoDemo(position2di(25,150),position2di(175,150))); break;
	}
	
	Add_IAUnits.push_back(new_unit);
	return new_unit;
}


shared_ptr<IDibujable> gameEngine::addBuildings(int x,int y, int tipo,bool usuario)
{
	shared_ptr<edificio> new_build;
	switch(tipo)
	{
		case 0: new_build = shared_ptr<edificio>(new CentroCiudad(x,y,usuario)); break;
		case 1: new_build = shared_ptr<edificio>(new Granja(x,y,usuario)); 
				if(usuario)
					granjas_usuario++;
				else 
					granjas_ia++; 
				break;
		case 2: new_build = shared_ptr<edificio>(new Cuartel(x,y,usuario)); break;
		case 3: new_build = shared_ptr<edificio>(new Arqueria(x,y,usuario)); break;
		case 4: new_build = shared_ptr<edificio>(new Lanceria(x,y,usuario)); break;		
	}

	Add_Buildings.push_back(new_build);
	return new_build;
}

void gameEngine::addNewUnits()
{
	if(graphics->mapa.get() !=NULL)
	{
		for(shared_ptr<battleIA> ia : Add_IAUnits)
		{
			ia->setPathfinding(graphics->mapa->getPathfinding());
			graphics->mapa->AnyadirObjeto(ia);
			IAUnits.push_back(ia);
		}
		Add_IAUnits.clear();
		for(shared_ptr<Unidades> unit : Add_UserUnits)
		{
			unit->setPathfinding(graphics->mapa->getPathfinding());
			graphics->mapa->AnyadirObjeto(unit);
			UserUnits.push_back(unit);
		}
		Add_UserUnits.clear();
		for(shared_ptr<edificio> build : Add_Buildings)
		{
			build->setPathfinding(graphics->mapa->getPathfinding());
			buildings.push_back(build);
		}
		Add_Buildings.clear();
	}
}

void gameEngine::deleteUnits()
{
	for(int i = 0; i<IAUnits.size();i++)
	{
		shared_ptr<battleIA> ia = std::dynamic_pointer_cast<battleIA>(IAUnits.at(i));

		if(ia->getEliminar())
			IAUnits.erase(IAUnits.begin() + i);

	}

	for(int i = 0; i<UserUnits.size();i++)
	{
		shared_ptr<Unidades> unit = std::dynamic_pointer_cast<Unidades>(UserUnits.at(i));

		if(unit->getEliminar())
		{
			UserUnits.erase(UserUnits.begin() + i);
						
			vector<int>* seleccionados = graphics->mapa->getUserSelected();
			for(int j=0; j<seleccionados->size(); j++)
			{
				if(seleccionados->at(j) == i)
					seleccionados->erase(seleccionados->begin() + j);
			}
		}

	}

	

}

void gameEngine::scheduler (int variables) 
{

  while (!stado.sfinal()){
  	if(stado.is_ingame())
  	{
		recursos_jugador+=10 * (granjas_usuario+1);
		recursos_ia+=10  * (granjas_ia+1);
		cout<<recursos_jugador<<endl;
	    sleep (variables);
  	}

  }
}

long gameEngine::clockMS(clock_t ticks)
{
	return (ticks*1000)/CLOCKS_PER_SEC;
}
