#include "mapa2D.h"
#include <string>
#include <iostream>
#include <vector>

using namespace irr;
using namespace video;
using namespace std;
using namespace core;


mapa2D::mapa2D()
{
	IFileSystem *irrFile;
	WorkingDirectory = irrFile->getWorkingDirectory() + "/";

	Init();   
    
    AllocateMap();
    
    LoadTextures();
    
    //LoadEvents();
}

mapa2D::~mapa2D()
{
   free();
}

void mapa2D::Init()
{
	vTiles = NULL;
	Width = 250;
	Height = 250;
	ViewSize.Width = 25;
    ViewSize.Height = 19;
    CameraScroll.X = 2;
    CameraScroll.Y = 2;
}

bool mapa2D::free()
{
    //dealloc the vector
    //vTiles.clear();
	if(vTiles) 
    {
		for(int i = 0; i < Width; i++)
			delete[] vTiles[i];
		delete[] vTiles;

        vTiles = NULL;
	}
    IndexedEvents.clear();
    
    return true;
}

void mapa2D::AllocateMap()
{
        if(vTiles)
                return;

        vTiles = new STile*[Width];
        for(int i = 0; i < Width; i++) {
                vTiles[i] = new STile[Height];
        }

        // Delete textures
        for(u32 i = 0; i < Texturas.size(); i++)
                irrDriver->removeTexture(Texturas[i]);
        Texturas.clear();
}

void mapa2D::LoadTextures()
{
	//Carga Texturas
	int TexCount = 0;
	File.read(reinterpret_cast<char *>(&TexCount), sizeof(TexCount));
    Texturas.clear();
        
	stringc TextureFile;
	char tex[256];
	
	for(int i = 0; i < TexCount; i++)
	{
		File.get(tex, 2147483647, 0);
		File.get();
        TextureFile = tex;
                
        if(TextureFile == "none")
			Texturas.push_back(NULL);
		else
			Texturas.push_back(irrDriver->getTexture(WorkingDirectory + "Texturas/map/" + TextureFile));
	}
        
        STile *Tile;
        for(int i = 0; i < Width; i++)
        {
                for(int j = 0; j < Height; j++)
                {
					Tile = &vTiles[i][j];
					Tile->textura = Texturas[0];
				}
		}
}

void mapa2D::LoadEvents(STile *Tile,int i, int j)
{
	IndexedEvents.push_back(IndexedEventStruct(Tile, position2di(i, j)));
}


void mapa2D::SetCameraScroll(const position2di &TPosition) {

        CameraScroll = TPosition;
        if(CameraScroll.X < 2)
                CameraScroll.X = 2;
        if(CameraScroll.Y < 2)
                CameraScroll.Y = 2;
        if(CameraScroll.X >= Width - 2)
                CameraScroll.X = Width - 2;
        if(CameraScroll.Y >= Height - 2)
                CameraScroll.Y = Height - 2;
}

void mapa2D::Render()
{
	position2di GridPosition, DrawPosition;
    for(int i = 0; i < ViewSize.Width; i++)
    {
		for(int j = 0; j < ViewSize.Height; j++)
		{
			// Obtenermos coordenadas actuales cuadricula
            GridPosition.X = i + CameraScroll.X - ViewSize.Width / 2;
            GridPosition.Y = j + CameraScroll.Y - ViewSize.Height / 2;
            DrawPosition = position2di((i - ViewSize.Width / 2) * TILE_WIDTH + 400, (j - ViewSize.Height / 2) * TILE_HEIGHT + 300);

			// Validar coordenada
			if(GridPosition.X >= 0 && GridPosition.X < Width && GridPosition.Y >= 0 && GridPosition.Y < Height) {
				STile *Tile = &vTiles[GridPosition.X][GridPosition.Y];
				//Pinta
				if(Tile->textura)
					Pintar(Tile->textura, DrawPosition.X, DrawPosition.Y);
			}
		}
	}
}

//Pinta alrededor de una posicion
void mapa2D::Pintar(const ITexture *TTexture, int TPositionX, int TPositionY)
{
                irrDriver->draw2DImage(TTexture, position2di(TPositionX - (TTexture->getSize().Width >> 1), TPositionY - (TTexture->getSize().Height >> 1)), rect<s32>(0, 0, TTexture->getSize().Width, TTexture->getSize().Height), 0, SColor((u32)((1.0f - 0.0f) * 255), 255, 255, 255), true);
}

// Posicion de la cuadricula del mapa a una coordenada de la pantalla
bool mapa2D::GridToScreen(const position2di &TGridPosition, position2di &TScreenPosition) const 
{
        position2di CenterDelta(TGridPosition.X - CameraScroll.X, TGridPosition.Y - CameraScroll.Y);

        TScreenPosition.X = CenterDelta.X * TILE_WIDTH + 400;
        TScreenPosition.Y = CenterDelta.Y * TILE_HEIGHT + 300;

        // Para saber si esta en la pantalla
        if(abs(CenterDelta.X) > ViewSize.Width/2 || abs(CenterDelta.Y) > ViewSize.Height/2)
                return false;

        return true;
}

// Convierte una coordenada de la pantalla en una posicion de la cuadricula del mapa
void mapa2D::ScreenToGrid(const position2di &TScreenPosition, position2di &TGridPosition) const {
        TGridPosition.X = GetCameraScroll().X + TScreenPosition.X / TILE_WIDTH - GetViewSize().Width / 2;
        TGridPosition.Y = GetCameraScroll().Y + TScreenPosition.Y / TILE_HEIGHT - GetViewSize().Height / 2;
}


IndexedEventStruct *mapa2D::GetIndexedEvent(int TEventType, int TEventData) {

        for(u32 i = 0; i < IndexedEvents.size(); i++) {
                IndexedEventStruct *IndexedEvent = &IndexedEvents[i];
                if(IndexedEvent->Tile->EventType == TEventType && IndexedEvent->Tile->EventData == TEventData) {
                        return IndexedEvent;
                }
        }

        return NULL;
}



