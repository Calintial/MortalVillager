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
	user_selected = -1;
	pathFinding=new Pathfinding(shared_ptr<mapa2D>(this));
	sombra_edificio = false;
}


mapa2D::~mapa2D()
{
   sombra_edificio = false;
   delete pathFinding;
   free();
}

void mapa2D::Init()
{
	//vTiles = NULL;
	//auto size = driver->getScreenSize();
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

		//delete[] vTiles;

	}
    
    return true;
}

Unidades* mapa2D::OnEventMapa(const SEvent& event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		position2di pos_grid = getTileCoordinates(event.MouseInput.X,event.MouseInput.Y);
		int pos_vector = -1;


		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
				cout<<"Boton izquierdo, pulsado en:"<<pos_grid.X+CameraScroll.X << "," << pos_grid.Y+CameraScroll.Y <<endl; 
				Sel_Pulsado = true;
				Sel_Inicio = MapaDevice->getCursorControl()->getPosition();
				Sel_Fin = MapaDevice->getCursorControl()->getPosition();
				
				pos_vector = IASelected(pos_grid+CameraScroll);
				if(pos_vector != -1)
				{
					if(ia_selected != -1)
					{
						((battleIA*)ia_units->at(ia_selected))->TexturaSeleccionada(driver,false);
						ia_selected = -1;
					}
					ia_selected = pos_vector;
					((battleIA*)ia_units->at(ia_selected))->TexturaSeleccionada(driver,true);

					return (Unidades*)ia_units->at(ia_selected);
				}
				else
				{
					pos_vector = UserSelected(pos_grid);
					if(pos_vector != -1)
					{
						if(user_selected != -1)
						{
							((Unidades*)user_units->at(user_selected))->TexturaSeleccionada(driver,false);
							user_selected = -1;
						}
						
						user_selected = pos_vector;
						cout<<"usuario seleccionado: "<<user_selected<<endl;
						((Unidades*)user_units->at(user_selected))->TexturaSeleccionada(driver,true);
						return (Unidades*)user_units->at(user_selected);
					}
					else
					{
						if(user_selected != -1)
						{
							((Unidades*)user_units->at(user_selected))->TexturaSeleccionada(driver,false);
							user_selected = -1;
						}
						if(ia_selected != -1)
						{
							((battleIA*)ia_units->at(ia_selected))->TexturaSeleccionada(driver,false);
							ia_selected = -1;
						}
					}
				}
				break;
			
			case EMIE_LMOUSE_LEFT_UP:
				cout<<"Boton izquierdo, soltado en:"<< MapaDevice->getCursorControl()->getPosition().X/TILE_WIDTH << "," << MapaDevice->getCursorControl()->getPosition().Y/TILE_HEIGHT <<endl;
				Sel_Pulsado=false;
				break;
				
			case EMIE_MOUSE_MOVED:
				//cout << "Raton like to move it move it" << endl;
				if(Sel_Pulsado==true)
				{
					Sel_Fin = MapaDevice->getCursorControl()->getPosition();
				}
				break;
			
			case EMIE_RMOUSE_PRESSED_DOWN: 
					if(user_selected != -1)
					{
						/*pos_grid.X = event.MouseInput.X/TILE_WIDTH;
						pos_grid.Y = event.MouseInput.Y/TILE_HEIGHT;*/
						cout<<"Boton derecho, pulsado en:"<<pos_grid.X+CameraScroll.X << "," << pos_grid.Y+CameraScroll.Y <<endl; 
		   				((Unidades*)user_units->at(user_selected))->Move(pos_grid.X+CameraScroll.X,pos_grid.Y+CameraScroll.Y);
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
				vTiles[i][j] = new Suelo(0,i,j);
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
					vTiles[i][j] = new Suelo(0,i,j);
				}
				else
				{
					vTiles[i][j] = new Muro(1,i,j);
				}
				vTiles[i][j]->aplicarTextura(driver);
				k++;
			}
		}
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
					vTiles[i][j] =new Suelo(0,i,j);
					mapatext+="0";
					if(rand()%c!=1)
						vTiles[i+1][j] = new Suelo(0,i,j);
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
					vTiles[i][j] =new Suelo(1,i,j);
					mapatext+="1";
					if(rand()%c!=1)
						vTiles[i+1][j] = new Suelo(1,i,j);
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

void mapa2D::DrawBuildings()
{
	position2di DrawPosition;

	int n_build = buildings->size();	
	for(int i=0; i<n_build; i++)
	{
		DrawPosition = getDrawPosition(buildings->at(i)->getPosition());
		DrawPosition = twoDToIso(DrawPosition.X, DrawPosition.Y);
		buildings->at(i)->Pintar(driver,DrawPosition.X, DrawPosition.Y);
	}
}

void mapa2D::DrawBuildingShadow()
{
	
	position2di aux_tile = getTileCoordinates(shadowPosition.X,shadowPosition.Y);
	//cout<<"Dibujar sombra en en:"<<aux_tile.X << "," << aux_tile.Y <<endl;
	
	position2di aux = getIsoFromTile(aux_tile.X,aux_tile.Y);
	ITexture* shadow_texture = NULL;

	switch(tipo_edificio)
	{
		case 0: shadow_texture = driver->getTexture("../media/Texturas/building/city_center_shadow.png"); break;
		case 1: shadow_texture = driver->getTexture("../media/Texturas/building/farm_shadow.png"); break;
		case 2: shadow_texture = driver->getTexture("../media/Texturas/building/barracks_shadow.png"); break;
		case 3: shadow_texture = driver->getTexture("../media/Texturas/building/archer_building_shadow.png"); break;
		case 4: shadow_texture = driver->getTexture("../media/Texturas/building/spear_build_shadow.png"); break;
	}

	if(shadow_texture != NULL)
		PintarTile(shadow_texture, aux.X, aux.Y);	
	
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
	return ia_selected;
}

int mapa2D::getUserSelected()
{
	return user_selected;
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

bool mapa2D::puede_colocar(position2di pos)
{
	for(int x = pos.X; x < pos.X + 4; x++)
	{
		for(int y = pos.Y; y < pos.Y + 3; y++)
		{
			cout<<x<<","<<y<<":"<<getTile(y,x)->getTipo()<<endl;
			if(getTile(y,x)->getTipo() == 1)
			{
				return false;
			}


			for(int i=0; i<ia_units->size(); i++)
			{
				if(ia_units->at(i)->getPosition().X == x && ia_units->at(i)->getPosition().Y == y)
				{
					cout<<x<<","<<y<<":"<<"Hay una unidad IA"<<endl;
					return false;
				}
			}

			for(int i=0; i<user_units->size(); i++)
			{
				if(user_units->at(i)->getPosition().X == x && user_units->at(i)->getPosition().Y == y)
				{
					cout<<x<<","<<y<<":"<<"Hay una unidad Usuario"<<endl;
					return false;
				}
			}

			for(int i=0; i<buildings->size(); i++)
			{
				if(buildings->at(i)->getPosition().X == x && buildings->at(i)->getPosition().Y == y)
				{
					cout<<x<<","<<y<<":"<<"Hay un edificio"<<endl;
					return false;
				}
			}
	
		}
	}

	return true;
}