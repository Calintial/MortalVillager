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

	ia_selected = 0;
	user_selected = 0;
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
	ViewSize.Width = 26;
    ViewSize.Height = 20;
    CameraScroll.X = 0;
    CameraScroll.Y = 0;
}

bool mapa2D::free()
{
	if(vTiles) 
    {
		for(int i = 0; i < WIDTH; i++)
			delete[] vTiles[i];
		delete[] vTiles;

	}
    
    return true;
}

Unidades * mapa2D::OnEventMapa(const SEvent& event)
{
	cout<<"mimimi"<<endl;
	Unidades* unidad;
	
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
			case EMIE_LMOUSE_PRESSED_DOWN:
							position2di pos_grid;
							cout<<"Evento X:"<< event.MouseInput.X << "," << event.MouseInput.Y << endl;
							cout<<"ViewWidth:"<< ViewSize.Width << endl;
							cout<<"ViewHeight:"<< ViewSize.Height << endl;
							pos_grid.X = (event.MouseInput.X+(TILE_WIDTH/2)) / TILE_WIDTH;
							pos_grid.Y = (event.MouseInput.Y+(TILE_HEIGHT/2)) / TILE_HEIGHT;
							cout<<"Posicion final:"<<pos_grid.X << "," << pos_grid.Y <<endl; 


							int pos_vector = IASelected(pos_grid);
							if(pos_vector != -1)
							{
								ia_selected = pos_vector;
								return (Unidades*)ia_units->at(ia_selected);
								//DebugMenu::setUnitSelected(ia_selected);

							}
							else
							{
								pos_vector = UserSelected(pos_grid);
								cout << "pos_vector" << pos_vector << endl;
								if(pos_vector != -1)
								{

									user_selected = pos_vector;
									cout<<"usuario seleccionado: "<<user_selected<<endl;
									return (Unidades*)user_units->at(user_selected);
								}
								else
								{

									((Unidades*)user_units->at(user_selected))->Move(pos_grid.X,pos_grid.Y);

								}
							}
							break;
		}
	}
	else if(event.GUIEvent.EventType == EGET_CHECKBOX_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch(id)
		{
			case CB_VISION_RANGE: drawVision = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
			case CB_ATTACK_RANGE: drawAttackVision = ((IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
								  break;
		}
		
	}
	else if(event.GUIEvent.EventType == EGET_SCROLL_BAR_CHANGED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		switch(id)
		{
			case SCROLL_SPEED: s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                 			   gameEngine::setSpeed(pos);
							   break;
		}
	}

	else if(event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		s32 id = event.GUIEvent.Caller->getID();

		IGUISpinBox* spbox_X = (IGUISpinBox*) env->getRootGUIElement()->getElementFromId(SPBOX_COORDX);
		IGUISpinBox* spbox_Y = (IGUISpinBox*) env->getRootGUIElement()->getElementFromId(SPBOX_COORDY);

		switch(id)
		{
			case BUTTON_ADD_IA: gameEngine::addIAUnit((int)spbox_X->getValue(),(int)spbox_Y->getValue()); break;
			case BUTTON_ADD_UNIT: break;
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
			vTiles[i][j]->Pintar(driver);
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
        if(MapaDevice->isWindowActive() && driver)
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
						IDibujable *Tile = vTiles[GridPosition.X][GridPosition.Y];
						//Pinta
						if(Tile->getTextura())
							PintarTile(Tile->getTextura(), DrawPosition.X, DrawPosition.Y);
					//}
				}
			}

			DrawIAUnits();
			DrawUserUnits();
			
			env->drawAll();
			      	
        }
    }
}

//Pinta alrededor de una posicion
void mapa2D::PintarTile(const ITexture *TTexture, int TPositionX, int TPositionY)
{
	driver->draw2DImage(TTexture, position2di(TPositionX - (TTexture->getSize().Width >> 1), TPositionY - (TTexture->getSize().Height >> 1)), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
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
	int newposX = 0;
	int newposY = 0;
	for(int i=0; i<n_ia; i++)
	{
		position2di pos = ia_units->at(i)->getPosition();
		newposX = pos.X - CameraScroll.X;
		newposY = pos.Y - CameraScroll.Y;
		if(newposX> 0 && newposY > 0)
		{
			DrawPosition = position2di(newposX*TILE_WIDTH,newposY*TILE_HEIGHT);
			PintarTile(ia_units->at(i)->getTextura(), DrawPosition.X, DrawPosition.Y);
			
			int v_range = ((Unidades*)ia_units->at(i))->getVisionRange();
			int a_range = ((Unidades*)ia_units->at(i))->getAttackRange();
			/*Pintar vision de la unidad*/
			if(drawVision)
			{
				for(int x = newposX - v_range; x <= newposX + v_range; x++)
				{
					for(int y = newposY - v_range; y <= newposY + v_range; y++)
					{
						if(x < ViewSize.Width && y < ViewSize.Height)
						{
							ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_distance.png");
							DrawPosition = position2di(x*TILE_WIDTH,y*TILE_HEIGHT);
							PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);					
						}

					}
				}
			}

			/*Pintar rango de ataque de la unidad*/
			if(drawAttackVision)
			{
				for(int x = newposX - a_range; x <= newposX + a_range; x++)
				{
					for(int y = newposY - a_range; y <= newposY + a_range; y++)
					{
						if(x < ViewSize.Width && y < ViewSize.Height)
						{
							ITexture* vision_texture = driver->getTexture("../media/Texturas/units/vision_attack.png");
							DrawPosition = position2di(x*TILE_WIDTH,y*TILE_HEIGHT);
							PintarTile(vision_texture, DrawPosition.X, DrawPosition.Y);						
						}

					}
				}
			}
		}
	}
}

void mapa2D::DrawUserUnits()
{
	int n_user = user_units->size();
	int newposX = 0;
	int newposY = 0;
	position2di DrawPosition;
	for(int i=0; i<n_user; i++)
	{
		position2di pos = user_units->at(i)->getPosition();
		newposX = pos.X - CameraScroll.X;
		newposY = pos.Y - CameraScroll.Y;
		if(newposX> 0 && newposY > 0)
		{
			DrawPosition = position2di(newposX*TILE_WIDTH,newposY*TILE_HEIGHT);
			PintarTile(user_units->at(i)->getTextura(), DrawPosition.X, DrawPosition.Y);
		}
	}

}

void mapa2D::InicializarGraficosUnidades()
{
	int n_ia = ia_units->size();
	int n_units = user_units->size();

	for(int i=0; i<n_ia; i++)
		ia_units->at(i)->Pintar(driver);

	for(int i=0; i<n_units; i++)
		user_units->at(i)->Pintar(driver);
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