#include "gameEngine.h"
#include "AldeanoDemo.h"

float gameEngine::volumen = 0.5;
int gameEngine::game_speed = 100;
Current gameEngine::stado;

vector<battleIA*> gameEngine::Add_IAUnits;
vector<Unidades*> gameEngine::Add_UserUnits;
vector<edificio*> gameEngine::Add_Buildings;

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
	for(IDibujable* u : UserUnits)
	{
		graphics->mapa->getTile(u->getPosition().X,u->getPosition().Y)->setVinculado(NULL);
		((Unidades*)u)->updateUnit();
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

IDibujable* gameEngine::addUserUnit(int x,int y, int tipo)
{
	Unidades* new_unit;
	switch(tipo)
	{
		case 0: new_unit = new Aldeano(x,y); break;
		case 1: new_unit = new Espadachin(x,y); break;
		case 2: new_unit = new Lancero(x,y); break;
		case 3: new_unit = new Arquero(x,y); break;
		
	}
	
	Add_UserUnits.push_back(new_unit);
	return new_unit;
}


IDibujable* gameEngine::addIAUnit(int x,int y,int tipo)
{	
	battleIA* new_unit;
	switch(tipo)
	{
		case 0: new_unit = new AldeanoIA(x,y); break;
		case 1: new_unit = new EspadachinIA(x,y); break;
		case 2: new_unit = new LanceroIA(x,y); break;
		case 3: new_unit = new ArqueroIA(x,y); break;
		case 4: new_unit = new AldeanoDemo(position2di(25,150),position2di(175,150)); break;
	}
	
	Add_IAUnits.push_back(new_unit);
	return new_unit;
}


IDibujable* gameEngine::addBuildings(int x,int y, int tipo, bool usuario)
{
	edificio* new_build;
	switch(tipo)
	{
		case 0: new_build = new CentroCiudad(x,y,usuario); break;
		case 1: new_build = new Granja(x,y,usuario); if(usuario) granjas_usuario++; else granjas_ia++; break;
		case 2: new_build = new Cuartel(x,y,usuario); break;
		case 3: new_build = new Arqueria(x,y,usuario); break;
		case 4: new_build = new Lanceria(x,y,usuario); break;
		
	}

	Add_Buildings.push_back(new_build);
	return new_build;
}

void gameEngine::addNewUnits()
{
	if(graphics->mapa.get() !=NULL)
	{
		for(battleIA* ia : Add_IAUnits)
		{
			ia->setPathfinding(graphics->mapa->getPathfinding());
			graphics->mapa->AnyadirObjeto(ia);
			IAUnits.push_back(ia);
		}
		Add_IAUnits.clear();
		for(Unidades* unit : Add_UserUnits)
		{
			unit->setPathfinding(graphics->mapa->getPathfinding());
			graphics->mapa->AnyadirObjeto(unit);
			UserUnits.push_back(unit);
		}
		Add_UserUnits.clear();
		for(edificio* build : Add_Buildings)
		{
			build->setPathfinding(graphics->mapa->getPathfinding());
			buildings.push_back(build);
		}
		Add_Buildings.clear();
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