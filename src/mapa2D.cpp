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


mapa2D::mapa2D(IrrlichtDevice * IrrDevice, vector<IDibujable*>* IAunits, vector<IDibujable*>* Userunits)
{
	ia_units = IAunits;
	user_units = Userunits;

	MapaDevice = IrrDevice;

    env = IrrDevice->getGUIEnvironment();
    env->clear();

    //Get the Scene Manager from the MapaDevice.
    smgr = IrrDevice->getSceneManager();

    //Get the Video Driver from the MapaDevice.
    driver = IrrDevice->getVideoDriver();
    
	file = IrrDevice->getFileSystem();;
	WorkingDirectory = file->getWorkingDirectory() + "/";
	
	skin = env->getSkin();

	Init();   
    
    //GenerarMapa();
    
    InicializarGraficosUnidades();

    AllocateMap();


	drawVision = false;
	drawAttackVision = false;

	ia_selected = -1;
	user_selected = -1;
	pathFinding=new pathfinding(this);
}

mapa2D::~mapa2D()
{
	delete pathFinding;
   free();
}

void mapa2D::Init()
{
	//vTiles = NULL;
	auto size = driver->getScreenSize();
	ViewSize.Width = size.Width/TILE_WIDTH;
    ViewSize.Height = size.Height/TILE_HEIGHT;
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
		position2di pos_grid;
		int pos_vector = -1;
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
							
							cout<<"Evento X:"<< event.MouseInput.X << "," << event.MouseInput.Y << endl;
							cout<<"ViewWidth:"<< ViewSize.Width << endl;
							cout<<"ViewHeight:"<< ViewSize.Height << endl;
							pos_grid.X = event.MouseInput.X/TILE_WIDTH ;
							pos_grid.Y = event.MouseInput.Y/TILE_HEIGHT;
							cout<<"Posicion final:"<<pos_grid.X << "," << pos_grid.Y <<endl; 


							pos_vector = IASelected(pos_grid);
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
								cout << "pos_vector" << pos_vector << endl;
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

			case EMIE_RMOUSE_PRESSED_DOWN: if(user_selected != -1)
										   {
				   								//position2di pos_grid;
												cout<<"Evento X:"<< event.MouseInput.X << "," << event.MouseInput.Y << endl;
												cout<<"ViewWidth:"<< ViewSize.Width << endl;
												cout<<"ViewHeight:"<< ViewSize.Height << endl;
												pos_grid.X = event.MouseInput.X/TILE_WIDTH;
												pos_grid.Y = event.MouseInput.Y/TILE_HEIGHT;
												cout<<"Posicion final:"<<pos_grid.X << "," << pos_grid.Y <<endl; 
		   										((Unidades*)user_units->at(user_selected))->Move(pos_grid.X,pos_grid.Y);
										   }
										   break;
			default:;
		}
	}
	return NULL;
}


void mapa2D::AllocateMap()
{
	int k=0;
    srand(time(0));
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
					
			cout << mapatext.size() << endl;
			std::ofstream file("../media/mapa.txt", std::ios_base::binary);
			std::string fileString;

			file << mapatext;
}

IDibujable* mapa2D::getTile(int x, int y){
	return vTiles[y][x];
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
			
						
		    for(int i = 0; i < ViewSize.Width; i++)
		    {
				for(int j = 0; j < ViewSize.Height; j++)
				{
					// Obtenermos coordenadas actuales cuadricula
		            GridPosition.X = i + CameraScroll.X;
		            GridPosition.Y = j + CameraScroll.Y;
		            //DrawPosition = position2di((i - ViewSize.Width / 2) * TILE_WIDTH + 400, (j - ViewSize.Height / 2) * TILE_HEIGHT + 300);
					DrawPosition = position2di(i*TILE_WIDTH,j*TILE_HEIGHT);
					// Validar coordenada
					//if(GridPosition.X >= 0 && GridPosition.X < Width && GridPosition.Y >= 0 && GridPosition.Y < Height) {
						if(GridPosition.X == 0 && GridPosition.Y==1)
						{
							IDibujable *Tile = vTiles[GridPosition.X][GridPosition.Y];
							//cout << "0,1 --> " << Tile->getTipo() << endl;
							
						}
						IDibujable *Tile = vTiles[GridPosition.X][GridPosition.Y];
						//Pinta
						if(Tile->getTextura())
							Tile->Pintar(driver, DrawPosition.X, DrawPosition.Y);
					//}
				}
			}

			DrawIAUnits();
			DrawUserUnits();
			
			env->drawAll();
			      	
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

void mapa2D::DrawIAUnits()
{
	position2di DrawPosition;

	int n_ia = ia_units->size();	
	for(int i=0; i<n_ia; i++)
	{
		DrawPosition = getDrawPosition(ia_units->at(i)->getPosition());
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
pathfinding* mapa2D::getPathfinding(){
	return pathFinding;
}
