#include "MapaAprendizaje.h"
#include "EspadachinRedes.h"
#include "CGenAlg.h"

// ================== MapaAprendizaje ===================== //

MapaAprendizaje::MapaAprendizaje(IrrlichtDevice* dev, int num):mapa2D(dev),m_NumUnidades(num){
	// cosas del constructor del mapa
	unidad_seleccionada = NULL;
	driver = MapaDevice->getVideoDriver();
	//generarMapa();
}

MapaAprendizaje::~MapaAprendizaje(){

}

void MapaAprendizaje::Pintar()
{
	
	if (MapaDevice->run())
	{        
		if(driver)
		{
			position2di GridPosition, DrawPosition;
			

			for(int i = 0; i < MAPSIZE; i++)
			{
				for(int j = 0; j < MAPSIZE; j++)
				{
					// Obtenermos coordenadas actuales cuadricula
					DrawPosition = position2di(j*TILE_WIDTH - CameraScroll.X, i * TILE_HEIGHT - CameraScroll.Y);
					//DrawPosition = getIsoFromTile(i - CameraScroll.X, j - CameraScroll.Y);
					// position2di((i*TILE_WIDTH) - CameraScroll.X, (j*TILE_HEIGHT) - CameraScroll.Y);
					// Validar coordenada
					IDibujable *Tile = vTiles[i][j];
						//Pinta
					if(Tile->getTextura())
						Tile->Pintar(driver, DrawPosition.X, DrawPosition.Y);
				}
			}

			if(unidad_seleccionada != NULL && unidad_seleccionada->getTipo() == 3)
			{
				PintarInformacionUnidad();
			}else{
				unidad_seleccionada = NULL;
			}

			MapaDevice->getGUIEnvironment()->drawAll();

		}
	}
	else
	{
		gameEngine::stado.finish();
	}
}

void MapaAprendizaje::PintarInformacionUnidad(){
	// TODO -> hay que copiarlo de mapa2D.cpp
}

void MapaAprendizaje::setTile(position2di pos,IDibujable* elem){
	setTile(pos.Y,pos.X,elem);
}
void MapaAprendizaje::setTile(int y,int x,IDibujable* elem){
	vTiles[y][x] = elem;
}

void MapaAprendizaje::generarMapa(){
	int j=0;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			setTile(i,j, new Suelo(j,i));
			((Suelo*) getTile(i,j))->setIsometric(false);
			getTile(i,j)->aplicarTextura(driver);

		}
	}

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		setTile(RandIntY,RandIntX,new Muro(RandIntX,RandIntY));
		((Muro*) getTile(RandIntY,RandIntX))->setIsometric(false);
		getTile(RandIntY,RandIntX)->aplicarTextura(driver);
	}

	//creamos las unidades 
	/*
	j=1;
 	int k=1;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		k=i% MAPSIZE;
 		if(k==0){
 			j++;
 		}
		EspadachinRedes* unidad=new EspadachinRedes(j,k);
		unidad->aplicarTextura(driver);
		setTile(k,j,unidad);
		ia_units.push_back(unidad);
	}*/
}

void MapaAprendizaje::nuevoSuelo(int x, int y){
	vTiles[y][x]= new Suelo(x,y);
	((Suelo*) vTiles[y][x])->setIsometric(false);
	vTiles[y][x]->aplicarTextura(driver);
}
void MapaAprendizaje::nuevoMuro(int x, int y){
	vTiles[y][x]= new Muro(x,y);
	((Muro*) vTiles[y][x])->setIsometric(false);
	vTiles[y][x]->aplicarTextura(driver);
}


// ================== ~MapaAprendizaje ===================== //
// ================== MapaBasicoDummy ===================== //

MapaBasicoDummy::MapaBasicoDummy(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaBasicoDummy::~MapaBasicoDummy(){
	
}

void MapaBasicoDummy::generarMapa(){
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			nuevoSuelo(j,i);
			

		}
	}
	for (int i=0;i<MAPSIZE;i+=6){
		for(int j=0;j<MAPSIZE;j+=6){
			if (i + 6 < MAPSIZE && j+6 < MAPSIZE)
			{	
				for (int iteradorEsquina = 0; iteradorEsquina < 6; ++iteradorEsquina)
				{
					nuevoMuro(j, i + iteradorEsquina);
					nuevoMuro(j + iteradorEsquina, i);
				}
				
			}
			

		}
	}
	generarUnidades();
	
}

void MapaBasicoDummy::reset(vector<SGenome> poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		CUnidadesAprendizaje* unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();


		// aqui deberia borrar la unidad, pero peta >_<
		nuevoSuelo(posicion.X,posicion.Y);

	}
	m_vecUnidades.clear();
	generarUnidades();
	for (int i=0; i<m_NumUnidades; ++i)
	{	
		m_vecUnidades[i]->PutWeights(poblacion[i].vecWeights);
	}
}

void MapaBasicoDummy::generarUnidades(){
	//creamos las unidades 
	int posX = 0;
	int posY = 0;
	int size = MAPSIZE / 6;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		posY = i / size * 6 + 2;
		posX = i % size * 6 + 2;
 		
		EspadachinRedes* unidadDummy=new EspadachinRedes(posX,posY);
		unidadDummy->aplicarTextura(driver);
		IDibujable* aux = vTiles[posY][posX];
		delete aux;
		vTiles[posY][posX]=unidadDummy;
		

		EspadachinRedes* unidad=new EspadachinRedes(posX + 2,posY + 2);
		unidad->aplicarTextura(driver);
		aux = vTiles[posY + 2][posX + 2];
		delete aux;
		vTiles[posY + 2][posX + 2]=unidad;
		m_vecUnidades.push_back(unidad);
	}
}

// ================== ~MapaBasicoDummy ===================== //
// ================== MapaBasicoMuroYUnidad ===================== //
	
MapaBasicoMuroYUnidad::MapaBasicoMuroYUnidad(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaBasicoMuroYUnidad::~MapaBasicoMuroYUnidad(){

}

void MapaBasicoMuroYUnidad::generarMapa(){
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			nuevoSuelo(j,i);
			

		}
	}
	for (int i=0;i<MAPSIZE;i+=6){
		for(int j=0;j<MAPSIZE;j+=6){
			if (i + 6 < MAPSIZE && j+6 < MAPSIZE)
			{	
				for (int iteradorEsquina = 0; iteradorEsquina < 6; ++iteradorEsquina)
				{
					nuevoMuro(j, i + iteradorEsquina);
					nuevoMuro(j + iteradorEsquina, i);
				}

				nuevoMuro(j + 2,i + 3);
				nuevoMuro(j + 3,i + 3);
				nuevoMuro(j + 3,i + 2);
				nuevoMuro(j + 3,i + 4);
				nuevoMuro(j + 4,i + 3);
				
			}
			

		}
	}
	generarUnidades();
}

void MapaBasicoMuroYUnidad::reset(vector<SGenome> poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		CUnidadesAprendizaje* unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();

		CUnidadesAprendizaje* enemigo = m_vecEnemigos[i];
		position2di posicionEnemigo = enemigo->getPosition();
		// aqui deberia borrar la unidad, pero peta >_<
		nuevoSuelo(posicion.X,posicion.Y);
		nuevoSuelo(posicionEnemigo.X,posicionEnemigo.Y);

	}
	m_vecUnidades.clear();
	m_vecEnemigos.clear();
	generarUnidades();
	for (int i=0; i<m_NumUnidades; ++i)
	{	
		m_vecUnidades[i]->PutWeights(poblacion[i].vecWeights);
		m_vecEnemigos[i]->PutWeights(poblacion[0].vecWeights);
	}
}

void MapaBasicoMuroYUnidad::generarUnidades(){
	//creamos las unidades 
	int posX = 0;
	int posY = 0;
	int size = MAPSIZE / 6;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		posY = i / size * 6 + 2;
		posX = i % size * 6 + 2;
 		
		EspadachinRedes* unidadDummy=new EspadachinRedes(posX,posY);
		unidadDummy->aplicarTextura(driver);
		IDibujable* aux = vTiles[posY][posX];
		delete aux;
		vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		EspadachinRedes* unidad=new EspadachinRedes(posX + 2,posY + 2);
		unidad->aplicarTextura(driver);
		aux = vTiles[posY + 2][posX + 2];
		delete aux;
		vTiles[posY + 2][posX + 2]=unidad;
		m_vecUnidades.push_back(unidad);
	}
	m_vecUnidades.reserve(m_vecUnidades.size()*2);
	m_vecUnidades.insert(m_vecUnidades.end(), m_vecEnemigos.begin(), m_vecEnemigos.end());
}


// ================== ~MapaBasicoMuroYUnidad ===================== //
// ================== MapaCuadrado ===================== //

MapaCuadrado::MapaCuadrado(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaCuadrado::~MapaCuadrado(){
	
}

void MapaCuadrado::generarMapa(){
	int dimensionCuadrado=m_NumUnidades;
	int inicioRectanguloInterior=MAPSIZE/4;
	int finRectanguloInterior=(MAPSIZE/2)+inicioRectanguloInterior;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			nuevoSuelo(j,i);
			

		}
	}
	int inicioCuadrado=MAPSIZE/4;
	int finalCuadrado=(MAPSIZE/2)+inicioCuadrado-1;
	generarSuelos(inicioCuadrado,finalCuadrado);
	inicioCuadrado=MAPSIZE/8;
	finalCuadrado=MAPSIZE-inicioCuadrado-1;
	generarSuelos(inicioCuadrado,finalCuadrado);
	generarUnidades();
	
}

void MapaCuadrado::reset(){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		CUnidadesAprendizaje* unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();


		// aqui deberia borrar la unidad, pero peta >_<
		nuevoSuelo(posicion.X,posicion.Y);

	}
	m_vecUnidades.clear();
	generarUnidades();
}
void MapaCuadrado::generarSuelos(int inicio,int fin){




	int i=inicio;
	for(int j=inicio;j<=fin;j+=2){
		if ( j <= fin )
		{	
			nuevoMuro(i, j);
			nuevoMuro(j, i);
		}
			

	}
	i=fin;
	for(int j=inicio;j<=fin;j+=2){
		if (j <= fin)
		{	
			nuevoMuro(i, j);
			nuevoMuro(j, i);
		}
			

	}
}
void MapaCuadrado::generarUnidades(){
	int numUnidadesLeft=0;
	int finalMapaCuadradoUnidades=(m_NumUnidades/2)-1;
	EspadachinRedes* unidad=new EspadachinRedes(0,0);
	unidad->aplicarTextura(driver);
	IDibujable* aux = vTiles[0][0];
	delete aux;
	vTiles[0][0]=unidad;
	m_vecUnidades.push_back(unidad);
	numUnidadesLeft++;
	unidad=new EspadachinRedes(finalMapaCuadradoUnidades,finalMapaCuadradoUnidades);
	unidad->aplicarTextura(driver);
	aux = vTiles[finalMapaCuadradoUnidades][finalMapaCuadradoUnidades];
	delete aux;
	vTiles[finalMapaCuadradoUnidades][finalMapaCuadradoUnidades]=unidad;
	m_vecUnidades.push_back(unidad);
	numUnidadesLeft++;

	int i=0;
		for(int j=1;j<=finalMapaCuadradoUnidades;j+=2){
			if ( j <= finalMapaCuadradoUnidades && numUnidadesLeft<m_NumUnidades)
			{	

				EspadachinRedes* unidad=new EspadachinRedes(j,i);
				unidad->aplicarTextura(driver);
				IDibujable* aux = vTiles[i][j];
				delete aux;
				vTiles[i][j]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
				unidad=new EspadachinRedes(i,j);
				unidad->aplicarTextura(driver);
				aux = vTiles[j][i];
				delete aux;
				vTiles[j][i]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
			}
			

		}
	i=finalMapaCuadradoUnidades;
			for(int j=2;j<=finalMapaCuadradoUnidades;j+=2){
			if (j <= finalMapaCuadradoUnidades && numUnidadesLeft<m_NumUnidades)
			{	

				EspadachinRedes* unidad=new EspadachinRedes(j,i);
				unidad->aplicarTextura(driver);
				IDibujable* aux = vTiles[i][j];
				delete aux;
				vTiles[i][j]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
				unidad=new EspadachinRedes(i,j);
				unidad->aplicarTextura(driver);
				aux = vTiles[j][i];
				delete aux;
				vTiles[j][i]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
			}
			

		}
		cout<<"num unidades: "<<m_vecUnidades.size()<<endl;
	
}

// ================== ~MapaCuadrado ===================== //