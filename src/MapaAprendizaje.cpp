#include "MapaAprendizaje.h"
#include "EspadachinRedes.h"
#include "CGenAlg.h"

// ================== MapaAprendizaje ===================== //

MapaAprendizaje::MapaAprendizaje(IrrlichtDevice* dev, int num):mapa2D(dev),m_NumUnidades(num){
	// cosas del constructor del mapa
	unidad_seleccionada = NULL;
	driver = MapaDevice->getVideoDriver();
	font = dev->getGUIEnvironment()->getFont("../media/fonthaettenschweiler.bmp");
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
					shared_ptr<IDibujable> Tile = vTiles[i][j];
						//Pinta
					if(Tile->getTextura())
						Tile->Pintar(driver, DrawPosition.X, DrawPosition.Y);
				}
			}

			for (int i = 0; i < m_vecUnidades.size(); ++i)
			{
				position2di pos = m_vecUnidades[i]->getPosition();
				DrawPosition = position2di(pos.X*TILE_WIDTH - CameraScroll.X, pos.Y * TILE_HEIGHT - CameraScroll.Y);
				m_vecUnidades[i]->Pintar(driver, DrawPosition.X, DrawPosition.Y);
			}

			for (int i = 0; i < m_vecEnemigos.size(); ++i)
			{
				position2di pos = m_vecEnemigos[i]->getPosition();
				DrawPosition = position2di(pos.X*TILE_WIDTH - CameraScroll.X, pos.Y * TILE_HEIGHT - CameraScroll.Y);
				m_vecEnemigos[i]->Pintar(driver, DrawPosition.X, DrawPosition.Y);
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
	vector<ObjetosCercanos> objCercanos =  ((CUnidadesAprendizaje*)unidad_seleccionada)->getVectorObjetos();
	core::stringw Vida="Vida: ";
	Vida+=unidad_seleccionada->getLife();
	core::stringw Ataque="Ataque: ";
	Ataque+= unidad_seleccionada->getAttackValue();
	core::stringw Posicion="Posicion: ";
	Posicion+= unidad_seleccionada->getPosition().X;
	Posicion+= ",";
	Posicion+= unidad_seleccionada->getPosition().Y;


	font->draw(Vida,
		core::rect<s32>(650,100,650,100),
		video::SColor(255,0,0,0));
	font->draw(Ataque,
		core::rect<s32>(750,100,750,100),
		video::SColor(255,0,0,0));
	font->draw(Posicion,
		core::rect<s32>(850,100,850,100),
		video::SColor(255,0,0,0));


	for(ObjetosCercanos objeto: objCercanos){
		position2di drawPos = position2di(objeto.posicion.X*TILE_WIDTH, objeto.posicion.Y * TILE_HEIGHT);
		//Pinta
		if (objeto.tipo == 1) // muro
		{
			driver->draw2DRectangle(video::SColor(255,0,255,0),core::rect<s32>(drawPos,drawPos + position2di(TILE_WIDTH,TILE_HEIGHT)));
		}else if (objeto.tipo == 3) // unidad?
		{
			driver->draw2DRectangle(video::SColor(255,0,255,255),core::rect<s32>(drawPos,drawPos + position2di(TILE_WIDTH,TILE_HEIGHT)));
		}else{// lo que sea...
			driver->draw2DRectangle(video::SColor(255,0,0,255),core::rect<s32>(drawPos,drawPos + position2di(TILE_WIDTH,TILE_HEIGHT)));
		}
	}
}

void MapaAprendizaje::setTile(position2di pos,shared_ptr<IDibujable> elem){
	setTile(pos.Y,pos.X,elem);
}
void MapaAprendizaje::setTile(int y,int x,shared_ptr<IDibujable> elem){
	vTiles[y][x] = elem;
}

vector<shared_ptr<CUnidadesAprendizaje>> MapaAprendizaje::getUnidadesAprendizaje() const{
	vector<shared_ptr<CUnidadesAprendizaje>> vecTotal = m_vecUnidades;
	vecTotal.reserve(vecTotal.size()*2);
	vecTotal.insert(vecTotal.end(), m_vecEnemigos.begin(), m_vecEnemigos.end());
	return vecTotal;
}

void MapaAprendizaje::generarMapa(){
	int j=0;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			/*setTile(i,j, shared_ptr<Suelo>(new Suelo(j,i)));
			std::dynamic_pointer_cast<Suelo>(getTile(i,j))->setIsometric(false);
			getTile(i,j)->aplicarTextura(driver);*/
			nuevoSuelo(j,i);

		}
	}

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		/*setTile(RandIntY,RandIntX,shared_ptr<Muro>(new Muro(RandIntX,RandIntY)));
		std::dynamic_pointer_cast<Muro>(getTile(RandIntY,RandIntX))->setIsometric(false);
		getTile(RandIntY,RandIntX)->aplicarTextura(driver);*/
		nuevoMuro(RandIntX,RandIntY);
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
	vTiles[y][x]=shared_ptr<Suelo>( new Suelo(x,y));
	std::dynamic_pointer_cast<Suelo>( vTiles[y][x])->setIsometric(false);
	vTiles[y][x]->aplicarTextura(driver);
}
void MapaAprendizaje::nuevoMuro(int x, int y){
	vTiles[y][x]= shared_ptr<Muro>(new Muro(x,y));
	std::dynamic_pointer_cast<Muro>( vTiles[y][x])->setIsometric(false);
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

void MapaBasicoDummy::reset(const vector<SGenome>& poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		shared_ptr<CUnidadesAprendizaje> unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();


		if (posicion.X != -1)
		{
			nuevoSuelo(posicion.X,posicion.Y);
		}
		

	}
	m_vecUnidades.clear();
	m_vecEnemigos.clear();
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
 		
		shared_ptr<CUnidadesAprendizajeDummy> unidadDummy=shared_ptr<CUnidadesAprendizajeDummy>(new CUnidadesAprendizajeDummy(posX,posY));
		unidadDummy->aplicarTextura(driver);
		shared_ptr<IDibujable> aux = vTiles[posY][posX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		shared_ptr<EspadachinRedes>  unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX + 2,posY + 2));
		unidad->aplicarTextura(driver);
		aux = vTiles[posY + 2][posX + 2];
		aux->setVinculado(unidad.get());
		//vTiles[posY + 2][posX + 2]=unidad;
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

void MapaBasicoMuroYUnidad::reset(const vector<SGenome>& poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		shared_ptr<CUnidadesAprendizaje> unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();

		shared_ptr<CUnidadesAprendizaje> enemigo = m_vecEnemigos[i];
		position2di posicionEnemigo = enemigo->getPosition();
		
		if(posicion.X != -1){
			nuevoSuelo(posicion.X,posicion.Y);	
		}
		if (posicionEnemigo.X != -1)
		{
			nuevoSuelo(posicionEnemigo.X,posicionEnemigo.Y);
		}
		

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
 		
		shared_ptr<EspadachinRedes> unidadDummy=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX,posY));
		unidadDummy->aplicarTextura(driver);
		shared_ptr<IDibujable> aux = vTiles[posY][posX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX + 2,posY + 2));
		unidad->aplicarTextura(driver);
		aux = vTiles[posY + 2][posX + 2];
		aux->setVinculado(unidad.get());
		//vTiles[posY + 2][posX + 2]=unidad;
		m_vecUnidades.push_back(unidad);
	}
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

void MapaCuadrado::reset(const vector<SGenome>&  poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		shared_ptr<CUnidadesAprendizaje> unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();


		if(posicion.X != -1){
			nuevoSuelo(posicion.X,posicion.Y);	
		}
		

	}
	m_vecUnidades.clear();
	generarUnidades();
	for (int i=0; i<m_NumUnidades; ++i)
	{	
		m_vecUnidades[i]->PutWeights(poblacion[i].vecWeights);
	}
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
	shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(0,0));
	unidad->aplicarTextura(driver);
	shared_ptr<IDibujable> aux = vTiles[0][0];
	//vTiles[0][0]=unidad;
	m_vecUnidades.push_back(unidad);
	numUnidadesLeft++;

	unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(finalMapaCuadradoUnidades,finalMapaCuadradoUnidades));
	unidad->aplicarTextura(driver);
	aux = vTiles[finalMapaCuadradoUnidades][finalMapaCuadradoUnidades];
	//vTiles[finalMapaCuadradoUnidades][finalMapaCuadradoUnidades]=unidad;
	m_vecUnidades.push_back(unidad);
	numUnidadesLeft++;

	int i=0;
		for(int j=1;j<=finalMapaCuadradoUnidades;j+=2){
			if ( j <= finalMapaCuadradoUnidades && numUnidadesLeft<m_NumUnidades)
			{	

				shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(j,i));
				unidad->aplicarTextura(driver);
				shared_ptr<IDibujable> aux = vTiles[i][j];
				//vTiles[i][j]=unidad;
				aux->setVinculado(unidad.get());
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;

				unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(i,j));
				unidad->aplicarTextura(driver);
				aux = vTiles[j][i];
				aux->setVinculado(unidad.get());
				//vTiles[j][i]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
			}
			

		}
	i=finalMapaCuadradoUnidades;
			for(int j=2;j<=finalMapaCuadradoUnidades;j+=2){
			if (j <= finalMapaCuadradoUnidades && numUnidadesLeft<m_NumUnidades)
			{	

				shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(j,i));
				unidad->aplicarTextura(driver);
				shared_ptr<IDibujable> aux = vTiles[i][j];
				aux->setVinculado(unidad.get());
				//vTiles[i][j]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
				unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(i,j));
				unidad->aplicarTextura(driver);
				aux = vTiles[j][i];
				aux->setVinculado(unidad.get());
				//vTiles[j][i]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
			}
			

		}
		//cout<<"num unidades: "<<m_vecUnidades.size()<<endl;
	
}

// ================== ~MapaCuadrado ===================== //
// ================== ~MapaCuatroUnidades ===================== //


MapaCuatroUnidades::MapaCuatroUnidades(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaCuatroUnidades::~MapaCuatroUnidades(){

}

void MapaCuatroUnidades::generarMapa(){
	int Tamanyo=12;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			nuevoSuelo(j,i);
			

		}
	}
for (int i=0;i<MAPSIZE;i+=Tamanyo){
		for(int j=0;j<MAPSIZE;j+=Tamanyo){
			if (i + Tamanyo < MAPSIZE && j+Tamanyo < MAPSIZE)
			{	
				for (int iteradorEsquina = 0; iteradorEsquina < Tamanyo; ++iteradorEsquina)
				{
					nuevoMuro(j, i + iteradorEsquina);
					nuevoMuro(j + iteradorEsquina, i);
				}

				nuevoMuro(j + 5,i + 6);
				nuevoMuro(j + 6,i + 6);
				nuevoMuro(j + 6,i + 5);
				nuevoMuro(j + 6,i + 7);
				nuevoMuro(j + 7,i + 6);
				
			}
			

		}
	}
	generarUnidades();
}

void MapaCuatroUnidades::reset(const vector<SGenome>& poblacion){
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		shared_ptr<CUnidadesAprendizaje> unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();

		if(posicion.X != -1){
			nuevoSuelo(posicion.X,posicion.Y);			
		}


	}
	m_vecUnidades.clear();

	generarUnidades();
	for (int i=0; i<m_NumUnidades; ++i)
	{	
		m_vecUnidades[i]->PutWeights(poblacion[i].vecWeights);

	}
}

void MapaCuatroUnidades::generarUnidades(){
	//creamos las unidades 
	int posX = 0;
	int posY = 0;
	int size = MAPSIZE / 6;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		posY = i / size * 6 + 1;
		posX = i % size * 6 + 1;
 		


		shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX + 2,posY + 2));
		unidad->aplicarTextura(driver);
		shared_ptr<IDibujable> aux = vTiles[posY + 2][posX + 2];
		aux->setVinculado(unidad.get());
		//vTiles[posY + 2][posX + 2]=unidad;
		m_vecUnidades.push_back(unidad);

	}

}
// ================== ~MapaCuatroUnidades ===================== //





















/*







TODO: PONER LAS UNIDADES COMO VINCULADAS EN EL MAPA, CAMBIAR TODAS LAS FUNCIONES DE OBJETOSCERCANOS, MOVIMIENTO, ATAQUE Y DEM´AS PARA TENER EN CUENTA LOS VINCULADOS, NO LAS CASILLAS
QUITAR TODOS LOS NEW SUELO CUANDO SE MUEVE Y DEJARLO EN SETPOSITION Y SI ESO SETVINCULADO





*/