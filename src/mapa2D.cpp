#include "mapa2D.h"
#include "graphicEngine.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;


mapa2D::mapa2D(IrrlichtDevice * IrrDevice, vector<IDibujable*>* IAunits, vector<IDibujable*>* Userunits, vector<IDibujable*>* b, bool suelo)
{
	ia_units = IAunits;
	user_units = Userunits;
	buildings = b;

	MapaDevice = IrrDevice;

    env = IrrDevice->getGUIEnvironment();
    env->clear();

    //Get the Scene Manager from the MapaDevice.
    smgr = IrrDevice->getSceneManager();

    //Get the Video Driver from the MapaDevice.
    driver = IrrDevice->getVideoDriver();
    
	file = IrrDevice->getFileSystem();
	WorkingDirectory = file->getWorkingDirectory() + "/";
	
	skin = env->getSkin();

	Init();   
    
    //GenerarMapa();
    
    InicializarGraficosUnidades();

    AllocateMap(suelo);

	Sel_Pulsado = false;

	drawVision = false;
	drawAttackVision = false;

	ia_selected = -1;
	pathFinding=new Pathfinding(shared_ptr<mapa2D>(this));
	// Esto es bastante sucio, pero bueno...
	for(IDibujable* unidad: *IAunits){
		unidad->setPathfinding(pathFinding);
	}
	for(IDibujable* unidad: *Userunits){
		unidad->setPathfinding(pathFinding);
	}
	for(IDibujable* unidad: *b){
		unidad->setPathfinding(pathFinding);
	}
	sombra_edificio = false;
	
	user_selvector = new vector<int>();
	pathFinding->preprocesar();
	
	recol_gradosel=0;
	recol_Rango=1;
	recol_RangoAux=0;
	recol_Grados = vector<int>(16);
	reasignarVectorRecolocacion(recol_RangoAux,recol_Rango);
}


mapa2D::~mapa2D()
{
   sombra_edificio = false;
   delete pathFinding;
   free();
}

void mapa2D::Init()
{
	ViewSize.Width = 26;//size.Width/TILE_WIDTH;
    ViewSize.Height = 20;//size.Height/TILE_HEIGHT;
    CameraScroll.X = 0;
    CameraScroll.Y = 0;
}

bool mapa2D::free()
{
	if(vTiles) 
    {
		for(int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				delete vTiles[i][j];
			}			
		}
	}
    
    return true;
}

vector<Unidades*>* mapa2D::OnEventMapa(const SEvent& event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		position2di pos_grid = getTileCoordinates(event.MouseInput.X,event.MouseInput.Y);

		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
				cout<<"Boton izquierdo, pulsado en:"<<pos_grid.X+CameraScroll.X << "," << pos_grid.Y+CameraScroll.Y <<endl; 
				Sel_Pulsado = true;
				Sel_Inicio = MapaDevice->getCursorControl()->getPosition();
				Sel_Fin = MapaDevice->getCursorControl()->getPosition();
				break;	
			
			case EMIE_LMOUSE_LEFT_UP:
				cout<<"Boton izquierdo, soltado en:"<< MapaDevice->getCursorControl()->getPosition().X/TILE_WIDTH << "," << MapaDevice->getCursorControl()->getPosition().Y/TILE_HEIGHT <<endl;
				Sel_Pulsado=false;
				
				user_selvector = new vector<int>();
				user_selvector = UserSelected();
				
				//deseleccionar a todos
				for(int i=0; i<user_units->size(); i++)
				{
					cout << "Deselecciono users" << endl;
					((Unidades*)user_units->at(i))->TexturaSeleccionada(driver,false);
					((Unidades*)user_units->at(i))->SetSelect(false);
				}
				for(int i=0; i<ia_units->size(); i++)
				{
					cout << "Deselecciono ia" << endl;
					((Unidades*)ia_units->at(i))->TexturaSeleccionada(driver,false);
					((Unidades*)ia_units->at(i))->SetSelect(false);
				}
				
				if(user_selvector->size() >= 1)
				{	
					vector<Unidades*>* usuarios_Seleccionados = new vector<Unidades*>();
					usuarios_Seleccionados->clear();
					
					cout << "CANTIDAD DE SELECCIONADOS:" << user_selvector->size() << endl;
					for(int i=0; i<user_selvector->size(); i++)
					{
						((Unidades*)user_units->at(user_selvector->at(i)))->TexturaSeleccionada(driver,true);
						((Unidades*)user_units->at(user_selvector->at(i)))->SetSelect(true);
						usuarios_Seleccionados->push_back((Unidades*)user_units->at(user_selvector->at(i)));
					}
										
					return usuarios_Seleccionados;
				}
				else
				{
					cout << "IA search" << endl;
					ia_selvector = new vector<int>();
					ia_selvector = IASelected();
					
					if(ia_selvector->size() >= 1)
					{
						vector<Unidades*>* ia_Seleccionados = new vector<Unidades*>();
						ia_Seleccionados->clear();
					
						cout << "CANTIDAD DE IA SELECCIONADOS:" << ia_selvector->size() << endl;
						
						for(int i=0; i<ia_selvector->size(); i++)
						{
							((battleIA*)ia_units->at(ia_selvector->at(i)))->TexturaSeleccionada(driver,true);
							((battleIA*)ia_units->at(ia_selvector->at(i)))->SetSelect(true);
							ia_Seleccionados->push_back((Unidades*)ia_units->at(ia_selvector->at(i)));
						}
										
						return ia_Seleccionados;
					}
					else
					{
						if(user_selvector->size() > 1)
						{
							for(int i=0; i<user_selvector->size(); i++)
							{
								((Unidades*)user_units->at(user_selvector->at(i)))->TexturaSeleccionada(driver,false);
								((Unidades*)user_units->at(ia_selvector->at(i)))->SetSelect(false);
							}
						}
						if(ia_selvector->size() > 1)
						{
							for(int i=0; i<ia_selvector->size(); i++)
							{
								((battleIA*)ia_units->at(ia_selvector->at(i)))->TexturaSeleccionada(driver,false);
								((battleIA*)ia_units->at(ia_selvector->at(i)))->SetSelect(false);
							}
						}
					}
				}
				
				
				break;
				
			case EMIE_MOUSE_MOVED:
				//cout << "Raton like to move it move it" << endl;
				if(Sel_Pulsado==true)
				{
					Sel_Fin = MapaDevice->getCursorControl()->getPosition();
				}
				break;
			
			case EMIE_RMOUSE_PRESSED_DOWN:
					//MIRAR COMO HACER MOVER TODOS
					if(user_selvector->size() >= 1)
					{
						cout<<"Boton derecho, pulsado en:"<<pos_grid.X+CameraScroll.X << "," << pos_grid.Y+CameraScroll.Y <<endl;
						for(int i=0; i<user_selvector->size(); i++)
						{
							//FALTARIAN CASOS DE FIN DE MUNDO
							//Lo suyo para que no falle seria, buscar una posicion mas cercana que fuera (Cutre o algoritmo de hoja) 
								//lugar transitable --> Mirar en el vector del mapa (edificios deberia estar en mapa)
								//no hay otro personaje --> Dar vuelta a todo el vector de unidades user
								
								cout << "POSICION INICIAL " << pos_grid.X+CameraScroll.X << "," << pos_grid.Y+CameraScroll.Y << endl;

								Unidades* unidad = ((Unidades*)user_units->at(user_selvector->at(i)));
								position2di posnueva=position2di(pos_grid.X+CameraScroll.X,pos_grid.Y+CameraScroll.Y);
								
								if(pos_grid.X+CameraScroll.X>=0 && pos_grid.Y+CameraScroll.Y>=0 && pos_grid.X+CameraScroll.X<WIDTH && pos_grid.Y+CameraScroll.Y<HEIGHT)
								{
									int index = IASelected(posnueva);
									if (index != -1)
									{
										// esto hace que se fusionen las unidades sobre la unidad objetivo >_<
										unidad->Move((Unidades*)ia_units->at(index));
									}else{
										unidad->Move(posnueva.X,posnueva.Y);
									}
								}
						}
						recol_gradosel=0;
						recol_Rango=1;
						recol_RangoAux=0;
						reasignarVectorRecolocacion(recol_RangoAux,recol_Rango);
					}
					break;
			default:;
		}
	}
	return NULL;
}


void mapa2D::AllocateMap(bool suelo)
{
	if(suelo)
	{
		for(int i = 0; i < WIDTH; i++) 
		{
			for(int j=0; j < HEIGHT; j++) 
			{
				vTiles[i][j] = new Suelo(i,j);
				vTiles[i][j]->aplicarTextura(driver);
			}		
		}
		
	}
	else
	{
		int k=0;
		//srand(time(0));
		std::string mapatext = "";
		
		ifstream myfile ("../media/mapa.txt");
		if (myfile.is_open())
		{
			getline (myfile,mapatext);
			myfile.close();
		}
		
		for(int i = 0; i < WIDTH; i++) 
		{
			for(int j=0; j < HEIGHT; j++) 
			{
				if(mapatext[k]=='0')
				{
					vTiles[i][j] = new Suelo(i,j);
				}
				else
				{
					vTiles[i][j] = new Muro(i,j);
				}
				vTiles[i][j]->aplicarTextura(driver);
				k++;
			}
		}
		
		//Añadimos 2 IAS por defecto
		(gameEngine::addIAUnit(0,0,0))->aplicarTextura(driver);
		(gameEngine::addIAUnit(28,20,3))->aplicarTextura(driver);
		(gameEngine::addUserUnit(24,12,3))->aplicarTextura(driver);
		(gameEngine::addUserUnit(30,15,3))->aplicarTextura(driver);
		(gameEngine::addUserUnit(40,20,3))->aplicarTextura(driver);
		(gameEngine::addUserUnit(34,17,3))->aplicarTextura(driver);
		/*addIAUnit(0,0,0)->aplicarTextura(driver);
		addIAUnit(10,10,0)->aplicarTextura(driver);
		addUserUnit(24,12,0)->aplicarTextura(driver);
		addUserUnit(30,15,0)->aplicarTextura(driver);
		addUserUnit(40,20,0)->aplicarTextura(driver);
		addUserUnit(34,17,0)->aplicarTextura(driver);*/
	}
}


//Suelo==0, Montaña=1, Bosque=2, CC=3, ALDEANO=4
void mapa2D::GenerarMapa()
{
	bool gen=true;
    int c=10;
    srand(time(0));
    std::string mapatext = "";

	for(int i = 0; i < WIDTH; i++) 
    {
		for(int j=0; j < HEIGHT; j++) 
		{
			int r=rand()%c;
			if(r==1){
				if(gen)
					gen=false;
				else 
					gen=true;
			}
			if(gen)
			{
				c=10;
				if(vTiles[i][j]==NULL)
				{
					vTiles[i][j] =new Suelo(i,j);
					mapatext+="0";
					if(rand()%c!=1)
						vTiles[i+1][j] = new Suelo(i,j);
				}
				else if(vTiles[i][j]->getTipo()==1)
				{
					gen=false;
					c=3;
					mapatext+="1";
				}
				else
				{
					mapatext+="0";
				}
			}
			else if(gen==false)
			{
				c=3;
				if(vTiles[i][j]==NULL)
				{
					vTiles[i][j] =new Muro(i,j);
					mapatext+="1";
					if(rand()%c!=1)
						vTiles[i+1][j] = new Muro(i,j);
				}
				else if(vTiles[i][j]->getTipo()==0)
				{
					mapatext+="0";
					gen=true;
					c=10;
				}
				else
				{
					mapatext+="1";
				}
			}
		}
	}
			std::ofstream file("../media/mapa.txt", std::ios_base::binary);
			std::string fileString;

			file << mapatext;
}

void mapa2D::GuardarMapa(){
	std::string mapatext = "";
	for(int i = 0; i < WIDTH; i++) 
    {
		for(int j=0; j < HEIGHT; j++) 
		{
			if (vTiles[i][j]->isTransitable())
			{
				mapatext+="0";
			}else{
				mapatext+="1";
			}
		}

	}

	std::ofstream file("../media/mapa.txt");
	if (file.is_open())
	{
		file<< mapatext;
		file.close();
	}
}

IDibujable* mapa2D::getTile(int y, int x){
	if (x >= WIDTH || y >= HEIGHT)
	{
		return NULL;
	}
	return vTiles[x][y];
}

IDibujable* mapa2D::getTile(position2di pos){
	if (pos.X >= WIDTH || pos.Y >= HEIGHT)
	{
		return NULL;
	}
	return vTiles[pos.X][pos.Y];
}

void mapa2D::setTile(int x, int y, IDibujable* contenido){
	vTiles[x][y] = contenido;
}

void mapa2D::SetCameraScroll(const position2di &TPosition) 
{
        CameraScroll = TPosition;
        if(CameraScroll.X < 0)
                CameraScroll.X = 0;
        if(CameraScroll.Y < 0)
                CameraScroll.Y = 0;
        if(CameraScroll.X >= WIDTH - 0)
                CameraScroll.X = WIDTH - 0;
        if(CameraScroll.Y >= HEIGHT - 0)
                CameraScroll.Y = HEIGHT - 0;
}

void mapa2D::Pintar()
{
	if (MapaDevice->run())
    {        
        if(driver)
        {
			position2di GridPosition, DrawPosition;
			
						
		    for(int i = 0; i < WIDTH; i++)
		    {
				for(int j = 0; j < HEIGHT; j++)
				{
					// Obtenermos coordenadas actuales cuadricula
		            //DrawPosition = position2di(((i - ViewSize.Width / 2) * TILE_WIDTH + 400)- CameraScroll.X, ((j - ViewSize.Height / 2) * TILE_HEIGHT + 300))- CameraScroll.Y;
					DrawPosition = getIsoFromTile(i - CameraScroll.X, j - CameraScroll.Y);
					// position2di((i*TILE_WIDTH) - CameraScroll.X, (j*TILE_HEIGHT) - CameraScroll.Y);
					// Validar coordenada
						IDibujable *Tile = vTiles[i][j];
						//Pinta
						if(Tile->getTextura())
							Tile->Pintar(driver, DrawPosition.X, DrawPosition.Y);
						//Pintando cosas vinculadas (de momento solo IAs)
						/*if(Tile->getVinculado()!=NULL)
						{
							DrawPosition = getDrawPosition(Tile->getVinculado()->getPosition());
							DrawPosition = twoDToIso(DrawPosition.X, DrawPosition.Y);
							Tile->getVinculado()->Pintar(driver,DrawPosition.X, DrawPosition.Y);
						}*/
				}
			}

			DrawIAUnits();
			DrawUserUnits();
			DrawBuildings();
			
			if(sombra_edificio)
				DrawBuildingShadow();

			env->drawAll();
			
			//Pintar seleccion
			if(Sel_Pulsado==true)
			{	
				//rect<s32>(top_left, bottom_right)
				if(Sel_Inicio.X > Sel_Fin.X && Sel_Inicio.Y > Sel_Fin.X)
				{
					//cout << "CASO ARRIBA IZQUIERDA: "<< Sel_Inicio.X << "," << Sel_Inicio.Y << " a " << Sel_Fin.X << "," << Sel_Fin.Y << endl;
					driver->draw2DRectangle(video::SColor(100,255,255,255),
					core::rect<s32>(Sel_Fin.X, Sel_Fin.Y, Sel_Inicio.X, Sel_Inicio.Y));
				}
				else if(Sel_Inicio.X < Sel_Fin.X && Sel_Inicio.Y < Sel_Fin.Y)
				{
					//cout << "CASO ABAJO DERECHA: "<< Sel_Inicio.X << "," << Sel_Inicio.Y << " a " << Sel_Fin.X << "," << Sel_Fin.Y << endl;
					driver->draw2DRectangle(video::SColor(100,255,255,255),
					core::rect<s32>(Sel_Inicio.X, Sel_Inicio.Y, Sel_Fin.X, Sel_Fin.Y));		
				}
				else if(Sel_Inicio.X > Sel_Fin.X && Sel_Inicio.Y < Sel_Fin.Y)
				{
					//cout << "CASO ABAJO IZQUIERDA: "<< Sel_Inicio.X << "," << Sel_Inicio.Y << " a " << Sel_Fin.X << "," << Sel_Fin.Y << endl;
					driver->draw2DRectangle(video::SColor(100,255,255,255),
					core::rect<s32>(Sel_Fin.X, Sel_Inicio.Y, Sel_Inicio.X, Sel_Fin.Y));		
				}
				else
				{
					//cout << "CASO ARRIBA DERECHA: " << Sel_Inicio.X << "," << Sel_Inicio.Y << " a " << Sel_Fin.X << "," << Sel_Fin.Y << endl;			
					driver->draw2DRectangle(video::SColor(100,255,255,255),
					core::rect<s32>(Sel_Inicio.X, Sel_Fin.Y, Sel_Fin.X, Sel_Inicio.Y));		
				}
			}      	
        }
    }
    else
    {
    	gameEngine::stado.finish();
    }
}

//Pinta alrededor de una posicion
void mapa2D::PintarTile(const ITexture *TTexture, int TPositionX, int TPositionY)
{
	driver->draw2DImage(TTexture, position2di(TPositionX, TPositionY), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

vector<IDibujable*>* mapa2D::getIa_units(){
	return ia_units;
}
vector<IDibujable*>* mapa2D::getUser_units(){
	return user_units;
}



vector<IDibujable*>* mapa2D::getBuildings(){
	return buildings;
}
void mapa2D::DrawBuildings()
{
	position2di DrawPosition;

	int n_build = buildings->size();	
	for(int i=0; i<n_build; i++)
	{
		DrawPosition = getDrawPosition(buildings->at(i)->getPosition());
		DrawPosition = twoDToIso(DrawPosition.X, DrawPosition.Y);
		buildings->at(i)->Pintar(driver,DrawPosition.X  - 25, DrawPosition.Y);
	}
}

void mapa2D::DrawBuildingShadow()
{
	
	position2di aux_tile = getTileCoordinates(shadowPosition.X,shadowPosition.Y);
	//cout<<"Dibujar sombra en en:"<<aux_tile.X << "," << aux_tile.Y <<endl;
	
	position2di aux;
	ITexture* shadow_texture = NULL;

	switch(tipo_edificio)
	{
		case 0: shadow_texture = driver->getTexture("../media/Texturas/building/city_center_shadow.png"); break;
		case 1: shadow_texture = driver->getTexture("../media/Texturas/building/farm_shadow.png"); break;
		case 2: shadow_texture = driver->getTexture("../media/Texturas/building/barracks_shadow.png"); break;
		case 3: shadow_texture = driver->getTexture("../media/Texturas/building/archer_building_shadow.png"); break;
		case 4: shadow_texture = driver->getTexture("../media/Texturas/building/spear_build_shadow.png"); break;
	}

	ITexture* shadow_texture2;
	//position2di colocar = aux_tile + GetCameraScroll(); colocar.X = colocar.X - 1;
	if((aux_tile.X != -1 && aux_tile.Y != -1) && puede_colocar(aux_tile + GetCameraScroll()))
		shadow_texture2 = driver->getTexture("../media/Texturas/building/shadow.png");
	else
		shadow_texture2 = driver->getTexture("../media/Texturas/building/shadow_incorrect.png");

	for(int i = aux_tile.X ; i< aux_tile.X + 5; i++)
	{
		for(int j = aux_tile.Y ; j< aux_tile.Y + 5; j++)
		{
			aux = getIsoFromTile(i,j);
			PintarTile(shadow_texture2, aux.X, aux.Y);
		}
	}	
	

	aux = getIsoFromTile(aux_tile.X,aux_tile.Y);
	if(shadow_texture != NULL)
		PintarTile(shadow_texture, aux.X - 25 , aux.Y);


	
}

void mapa2D::DrawIAUnits()
{
	position2di DrawPosition;

	int n_ia = ia_units->size();	
	for(int i=0; i<n_ia; i++)
	{
		DrawPosition = getDrawPosition(ia_units->at(i)->getPosition());
		DrawPosition = twoDToIso(DrawPosition.X, DrawPosition.Y);
		ia_units->at(i)->Pintar(driver,DrawPosition.X, DrawPosition.Y);
	}
}

void mapa2D::DrawUserUnits()
{
	int n_user = user_units->size();
	position2di DrawPosition;
	for(int i=0; i<n_user; i++)
	{
		DrawPosition = getDrawPosition(user_units->at(i)->getPosition());
		DrawPosition = twoDToIso(DrawPosition.X, DrawPosition.Y);
		user_units->at(i)->Pintar(driver, DrawPosition.X, DrawPosition.Y);
	}

}

position2di mapa2D::getDrawPosition(position2di pos){
	int newposX = pos.X - CameraScroll.X;
	int newposY = pos.Y - CameraScroll.Y;
	return position2di(newposX*TILE_WIDTH,newposY*TILE_HEIGHT);

}

void mapa2D::InicializarGraficosUnidades()
{
	int n_ia = ia_units->size();
	int n_units = user_units->size();

	for(int i=0; i<n_ia; i++)
		ia_units->at(i)->aplicarTextura(driver);

	for(int i=0; i<n_units; i++)
		user_units->at(i)->aplicarTextura(driver);
}

int mapa2D::IASelected(position2di coord)
{
	int n_ia = ia_units->size();

	for(int i=0; i<n_ia; i++)
	{
		if(ia_units->at(i)->getPosition().X == coord.X && ia_units->at(i)->getPosition().Y == coord.Y)
		{
			return i;
		}
	}
	return -1;
}

vector<int>* mapa2D::IASelected()
{
	int n_ia = ia_units->size();

	vector<int>* Sel_IA = new vector<int>();

	position2di IsoSel_Inicio = getTileCoordinates(Sel_Inicio.X,Sel_Inicio.Y)+CameraScroll;
	position2di IsoSel_Fin = getTileCoordinates(Sel_Fin.X,Sel_Fin.Y)+CameraScroll;

	cout << "INICIOISO: " << IsoSel_Inicio.X << "," << IsoSel_Inicio.Y << endl;
	cout << "FINISO: " << IsoSel_Fin.X << "," << IsoSel_Fin.Y << endl;

	for(int i=0; i<n_ia; i++)
	{
		if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y < IsoSel_Fin.Y)
		{
			cout << "pos ia1" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;			
			
			if( ia_units->at(i)->getPosition().X >= IsoSel_Inicio.X &&
				ia_units->at(i)->getPosition().Y >= IsoSel_Inicio.Y &&
				ia_units->at(i)->getPosition().X <= IsoSel_Fin.X &&
				ia_units->at(i)->getPosition().Y <= IsoSel_Fin.Y)
			{
				Sel_IA->push_back(i);
				cout << "1)Pos IA encontrada:" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			}
		}
		else if(IsoSel_Inicio.X > IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos ia2" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			if( ia_units->at(i)->getPosition().X <= IsoSel_Inicio.X &&
				ia_units->at(i)->getPosition().Y <= IsoSel_Inicio.Y &&
				ia_units->at(i)->getPosition().X >= IsoSel_Fin.X &&
				ia_units->at(i)->getPosition().Y >= IsoSel_Fin.Y)
			{
				Sel_IA->push_back(i);
				cout << "2)Pos IA encontrada:" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			}
		}
		else if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos ia3" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			if( ia_units->at(i)->getPosition().X >= IsoSel_Inicio.X &&
				ia_units->at(i)->getPosition().X <= IsoSel_Fin.X &&
				ia_units->at(i)->getPosition().Y <= IsoSel_Inicio.Y &&
				ia_units->at(i)->getPosition().Y >= IsoSel_Fin.Y)
			{
				Sel_IA->push_back(i);
				cout << "3)Pos IA encontrada:" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			}
		}
		else if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos ia4" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			if( ia_units->at(i)->getPosition().X <= IsoSel_Inicio.X &&
				ia_units->at(i)->getPosition().X >= IsoSel_Fin.X &&
				ia_units->at(i)->getPosition().Y >= IsoSel_Inicio.Y &&
				ia_units->at(i)->getPosition().Y <= IsoSel_Fin.Y)
			{
				Sel_IA->push_back(i);
				cout << "4)Pos IA encontrada:" << ia_units->at(i)->getPosition().X << "," << ia_units->at(i)->getPosition().Y << endl;
			}
		}
	}
	
	return Sel_IA;
}


vector<int>* mapa2D::UserSelected()
{
	int n_units = user_units->size();

	vector<int>* Sel_User = new vector<int>();

	position2di IsoSel_Inicio = getTileCoordinates(Sel_Inicio.X,Sel_Inicio.Y)+CameraScroll;
	position2di IsoSel_Fin = getTileCoordinates(Sel_Fin.X,Sel_Fin.Y)+CameraScroll;

	cout << "INICIOISO: " << IsoSel_Inicio.X << "," << IsoSel_Inicio.Y << endl;
	cout << "FINISO: " << IsoSel_Fin.X << "," << IsoSel_Fin.Y << endl;

	for(int i=0; i<n_units; i++)
	{
		if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y < IsoSel_Fin.Y)
		{
			cout << "pos user1 " << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
				
			if( user_units->at(i)->getPosition().X >= IsoSel_Inicio.X &&
				user_units->at(i)->getPosition().Y >= IsoSel_Inicio.Y &&
				user_units->at(i)->getPosition().X <= IsoSel_Fin.X &&
				user_units->at(i)->getPosition().Y <= IsoSel_Fin.Y)
			{
				Sel_User->push_back(i);
				cout << "1)Pos USER encontrada:" << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			}
		}
		else if(IsoSel_Inicio.X > IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos user2 " << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			
			cout << user_units->at(i)->getPosition().X << "<=" << IsoSel_Inicio.X << endl;
			cout << user_units->at(i)->getPosition().Y << "<=" << IsoSel_Inicio.Y << endl;
			cout << user_units->at(i)->getPosition().X << ">=" << IsoSel_Fin.X << endl;
			cout << user_units->at(i)->getPosition().Y << ">=" << IsoSel_Fin.Y << endl;
			
			if( user_units->at(i)->getPosition().X <= IsoSel_Inicio.X &&
				user_units->at(i)->getPosition().Y <= IsoSel_Inicio.Y &&
				user_units->at(i)->getPosition().X >= IsoSel_Fin.X &&
				user_units->at(i)->getPosition().Y >= IsoSel_Fin.Y)
			{
				Sel_User->push_back(i);
				cout << "2)Pos USER encontrada:" << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			}
			else
			{
				cout << "NOP2" << endl;
			}
		}
		else if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos user3 " << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			if( user_units->at(i)->getPosition().X >= IsoSel_Inicio.X &&
				user_units->at(i)->getPosition().X <= IsoSel_Fin.X &&
				user_units->at(i)->getPosition().Y <= IsoSel_Inicio.Y &&
				user_units->at(i)->getPosition().Y >= IsoSel_Fin.Y)
			{
				Sel_User->push_back(i);
				cout << "3)Pos USER encontrada:" << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			}
		}
		else if(IsoSel_Inicio.X < IsoSel_Fin.X && IsoSel_Inicio.Y > IsoSel_Fin.Y)
		{
			cout << "pos user4 " << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			if( user_units->at(i)->getPosition().X <= IsoSel_Inicio.X &&
				user_units->at(i)->getPosition().X >= IsoSel_Fin.X &&
				user_units->at(i)->getPosition().Y >= IsoSel_Inicio.Y &&
				user_units->at(i)->getPosition().Y <= IsoSel_Fin.Y)
			{
				Sel_User->push_back(i);
				cout << "4)Pos USER encontrada:" << user_units->at(i)->getPosition().X << "," << user_units->at(i)->getPosition().Y << endl;
			}
		}
	}
	
	return Sel_User;
}


int mapa2D::UserSelected(position2di coord)
{
	int n_units = user_units->size();

	for(int i=0; i<n_units; i++)
	{
		if(user_units->at(i)->getPosition().X == coord.X && user_units->at(i)->getPosition().Y == coord.Y)
		{
			return i;
		}
	}
	return -1;
}

int mapa2D::getIASelected()
{
	if(ia_selvector != NULL)
		if(ia_selvector->size() >= 1)
			return ia_selvector->at(0);
	return -1;
}

vector<int>* mapa2D::getUserSelected()
{
	return user_selvector;
}
Pathfinding* mapa2D::getPathfinding(){
	return pathFinding;
}

position2di mapa2D::twoDToIso(int x, int y)
{
	position2di pos;
	pos.X = x - y;
	pos.Y = (x + y) / 2;
	return pos;
}

//Le doy una coordenada y me dice en que tile esta
position2di mapa2D::getTileCoordinates(int x, int y)
{
	position2di pos;
	float ymouse=((2*y-x)/2);
	float xmouse=(x+ymouse);
	pos.Y=round(ymouse/TILE_WIDTH);
	pos.X=round(xmouse/TILE_WIDTH)-1;
	return pos;
}

position2di mapa2D::getIsoFromTile(int tilex, int tiley)
{
	return twoDToIso(tilex * TILE_WIDTH, tiley * TILE_HEIGHT);
}

void mapa2D::setSombra(bool s)
{
	sombra_edificio = s;
}

bool mapa2D::getSombra()
{
	return sombra_edificio;
}

void mapa2D::setSombraCoords(position2di pos)
{
	shadowPosition = pos;
}

position2di mapa2D::getSombraCoords()
{
	return shadowPosition;
}

void mapa2D::setTipoEdificio(int tipo)
{
	tipo_edificio = tipo;
}

int mapa2D::getTipoEdificio()
{
	return tipo_edificio;
}

bool mapa2D::puede_colocarUnidad(position2di pos)
{
	if(!getTile(pos.Y,pos.X)->isTransitable())
	{
		return false;
	}
			
	for(int i=0; i<ia_units->size(); i++)
	{
		if(ia_units->at(i)->getPosition() == pos)
		{
			return false;
		}
	}

	for(int i=0; i<user_units->size(); i++)
	{
		if(user_units->at(i)->getPosition() == pos)
		{
			return false;
		}
	}
	// for(int i=0; i<buildings->size(); i++)
	// {
	// 	if(collide(buildings->at(i)->getPosition(),4,4,pos,4,4))
	// 	{
	// 		return false;
	// 	}
	// }

	return true;
}

bool mapa2D::puede_colocar(position2di pos)
{

	for(int x = pos.X; x < pos.X + 5; x++)
	{
		for(int y = pos.Y; y < pos.Y + 5; y++)
		{
			if(getTile(y,x)->getTipo() == 1)
			{
				return false;
			}
			

			for(int i=0; i<ia_units->size(); i++)
			{
				if(ia_units->at(i)->getPosition().X == x && ia_units->at(i)->getPosition().Y == y)
				{
					return false;
				}
			}

			for(int i=0; i<user_units->size(); i++)
			{
				if(user_units->at(i)->getPosition().X == x && user_units->at(i)->getPosition().Y == y)
				{
					return false;
				}
			}
		}
	}

	for(int i=0; i<buildings->size(); i++)
	{
		/*cout<<buildings->at(i)->getPosition().X<<","<<buildings->at(i)->getPosition().Y<<":"<<"Edificio"<<endl;
		cout<<pos.X<<","<<pos.Y<<":"<<"Sombra"<<endl;*/
		if(collide(buildings->at(i)->getPosition(),5,5,pos,5,5))
		{
			//cout<<pos.X<<","<<pos.Y<<":"<<"Hay un edificio"<<endl;
			return false;
		}
	}

	return true;
}

position2di mapa2D::posicionDisponible(position2di pos)
{
	bool vacio = true;
	position2di posbuena;

	if(puede_colocarUnidad(pos)){
		posbuena = pos;
		vacio = false;
	}

	
	while(vacio)
	{
		if(recol_gradosel == 16*recol_Rango)
		{
			recol_gradosel=0;
			recol_Rango++;
			recol_RangoAux=recol_Rango-1;
			reasignarVectorRecolocacion(recol_RangoAux,recol_Rango);
		}
		else if(recol_gradosel%16 == 0)
		{
			reasignarVectorRecolocacion(recol_RangoAux,recol_Rango);
			recol_RangoAux--;
		}
		posbuena = pos;
		posbuena.X += recol_Grados[recol_gradosel];
		posbuena.Y += recol_Grados[recol_gradosel+1];
		
		recol_gradosel += 2;
		if(posbuena.X>=0 && posbuena.Y>=0 && posbuena.X<WIDTH && posbuena.Y<HEIGHT)
		{
			cout << "Posicion a PROBAR " << posbuena.X << "," << posbuena.Y << endl;
			if(puede_colocarUnidad(posbuena))
			{
				vacio = false;
			}
		}
	}
	
	cout << "NUEVA POSICION " << posbuena.X << "," << posbuena.Y << endl;
	return posbuena;
}



void mapa2D::reasignarVectorRecolocacion(int q, int w)
{
	/// WTF!? Medina te mato ¬¬
	//
	recol_Grados[0] = -q;
	recol_Grados[1] = w;
	//
	recol_Grados[2] = q;
	recol_Grados[3] = -w;
	//
	recol_Grados[4] = w-q;
	recol_Grados[5] = w;
	//
	recol_Grados[6] = w;
	recol_Grados[7] = q;
	//
	recol_Grados[8] = w;
	recol_Grados[9] = -w+q;
	//
	recol_Grados[10] = -w+q;
	recol_Grados[11] = -w;
	//
	recol_Grados[12] = -w;
	recol_Grados[13] = q;
	//
	recol_Grados[14] = -w;
	recol_Grados[15] = w-q;
}


bool mapa2D::collide(position2di obj1, int w_obj1, int h_obj1, position2di obj2, int w_obj2, int h_obj2)
{
    if ( (obj1.X < obj2.X + w_obj2) && (obj2.X < obj1.X + w_obj1) && (obj1.Y < obj2.Y + h_obj2))
    {
        return obj2.Y < obj1.Y + h_obj1;
    }
     
    return false;
}

void mapa2D::colocarEdificio(position2di pos_colocar){
	IDibujable* edificio = NULL;

	switch(getTipoEdificio())
	{
		case 0: edificio = gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,0); break;
		case 1: if(gameEngine::recursos_jugador >= 400)
				{
					edificio = gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,1);
					gameEngine::recursos_jugador = gameEngine::recursos_jugador - 400;
				} break;
		case 2: if(gameEngine::recursos_jugador >= 600)
				{
					edificio = gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,2);
					gameEngine::recursos_jugador = gameEngine::recursos_jugador - 600;
				} break;
		case 3: if(gameEngine::recursos_jugador >= 600)
				{
					edificio = gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,3);
					gameEngine::recursos_jugador = gameEngine::recursos_jugador - 600;
				} break;
		case 4: if(gameEngine::recursos_jugador >= 600)
				{
					edificio = gameEngine::addBuildings(pos_colocar.X,pos_colocar.Y,4);
					gameEngine::recursos_jugador = gameEngine::recursos_jugador - 600;
				} break;
	}

	if(edificio){
		edificio->aplicarTextura(driver);
		// vinculamos el edificio a todo el suelo que ocupa
		ITexture* tex = edificio->getTextura();
		int i,j;
		for (i = 0; i < tex->getSize().Width/TILE_WIDTH; ++i)
		{
			for (j = 0; j < tex->getSize().Height/TILE_HEIGHT; ++j){

				getTile(pos_colocar.Y + j,pos_colocar.X + i)->setVinculado(edificio);
			}
		}
		position2di down_right(pos_colocar.X + i,pos_colocar.Y + j);
		pathFinding->actualizarRegiones(pos_colocar,down_right);

	}
}


void mapa2D::AnyadirObjeto(IDibujable* obj)
{
	cout << obj->getPosition().X << endl;
	cout << obj->getPosition().Y << endl;
	vTiles[obj->getPosition().X][obj->getPosition().Y]->setVinculado(obj);
}
