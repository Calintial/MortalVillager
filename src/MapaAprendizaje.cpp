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
	CUnidadesAprendizaje* cunidad = (CUnidadesAprendizaje*)unidad_seleccionada;
	vector<ObjetosCercanos> objCercanos =  cunidad->getVectorObjetos();

	core::stringw Vida="Vida: ";
	Vida+=unidad_seleccionada->getLife();
	core::stringw Ataque="Fitness: ";
	Ataque+= cunidad->Fitness();
	core::stringw Posicion="Posicion: ";
	Posicion+= unidad_seleccionada->getPosition().X;
	Posicion+= ",";
	Posicion+= unidad_seleccionada->getPosition().Y;
	core::stringw  output=" Output: ";
	if (cunidad->output.size() > 0)
	{
		
		output+="X: ";
		output+=cunidad->output[0];
		output+="          ";
		output+="Y: ";
		output+=cunidad->output[1];
		output+="          ";
		output+="Atacar: ";
		output+=cunidad->output[2];
		output+="          ";
		output+="Izquierda: ";
		output+=cunidad->output[3];
		output+="          ";
		output+="Derecha: ";
		output+=cunidad->output[4];
		output+="          ";
		output+="Arriba: ";
		output+=cunidad->output[5];
		output+="          ";
		output+="Abajo: ";
		output+=cunidad->output[6];
		output+="          ";
		output+="Moverse: ";
		output+=cunidad->output[7];
		output+="          ";
	}
	
	
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
		driver->draw2DRectangle(video::SColor(255,255,255,255),core::rect<s32>(600,100,950,115));

	font->draw(Vida,
		core::rect<s32>(650,100,650,100),
		video::SColor(255,0,0,0));
	font->draw(Ataque,
		core::rect<s32>(750,100,750,100),
		video::SColor(255,0,0,0));
	font->draw(Posicion,
		core::rect<s32>(850,100,850,100),
		video::SColor(255,0,0,0));
	font->draw(output,
		core::rect<s32>(950,100,950,100),
		video::SColor(255,0,0,0));
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
	vTiles[y][x]->setDriver(driver);
}
void MapaAprendizaje::nuevoMuro(int x, int y){
	vTiles[y][x]= shared_ptr<Muro>(new Muro(x,y));
	std::dynamic_pointer_cast<Muro>( vTiles[y][x])->setIsometric(false);
	vTiles[y][x]->aplicarTextura(driver);
	vTiles[y][x]->setDriver(driver);
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
	unidad_seleccionada = NULL;
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
		unidadDummy->setDriver(driver);
		shared_ptr<IDibujable> aux = vTiles[posY][posX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		shared_ptr<EspadachinRedes>  unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX + 2,posY + 2));
		unidad->aplicarTextura(driver);
		unidad->setDriver(driver);
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
	unidad_seleccionada = NULL;
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
		unidadDummy->setDriver(driver);
		shared_ptr<IDibujable> aux = vTiles[posY][posX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX + 2,posY + 2));
		unidad->aplicarTextura(driver);
		unidad->setDriver(driver);
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
	unidad_seleccionada = NULL;
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
	unidad->setDriver(driver);
	shared_ptr<IDibujable> aux = vTiles[0][0];
	//vTiles[0][0]=unidad;
	m_vecUnidades.push_back(unidad);
	numUnidadesLeft++;

	unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(finalMapaCuadradoUnidades,finalMapaCuadradoUnidades));
	unidad->aplicarTextura(driver);
	unidad->setDriver(driver);
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
				unidad->setDriver(driver);
				shared_ptr<IDibujable> aux = vTiles[i][j];
				//vTiles[i][j]=unidad;
				aux->setVinculado(unidad.get());
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;

				unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(i,j));
				unidad->aplicarTextura(driver);
				unidad->setDriver(driver);
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
				unidad->setDriver(driver);
				shared_ptr<IDibujable> aux = vTiles[i][j];
				aux->setVinculado(unidad.get());
				//vTiles[i][j]=unidad;
				m_vecUnidades.push_back(unidad);
				numUnidadesLeft++;
				unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(i,j));
				unidad->aplicarTextura(driver);
				unidad->setDriver(driver);
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
	unidad_seleccionada = NULL;
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
		unidad->setDriver(driver);
		shared_ptr<IDibujable> aux = vTiles[posY + 2][posX + 2];
		aux->setVinculado(unidad.get());
		//vTiles[posY + 2][posX + 2]=unidad;
		m_vecUnidades.push_back(unidad);

	}

}
// ================== ~MapaCuatroUnidades ===================== //
// ================== ~MapaCuatroUnidades ===================== //


MapaCuatroEnemigos::MapaCuatroEnemigos(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaCuatroEnemigos::~MapaCuatroEnemigos(){

}

void MapaCuatroEnemigos::generarMapa(){
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

			}
			

		}
	}
	generarUnidades();
}

void MapaCuatroEnemigos::reset(const vector<SGenome>& poblacion){
	unidad_seleccionada = NULL;
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		shared_ptr<CUnidadesAprendizaje> unidad = m_vecUnidades[i];
		position2di posicion = unidad->getPosition();

		if(posicion.X != -1){
			nuevoSuelo(posicion.X,posicion.Y);			
		}


	}
	m_vecUnidades.clear();
	for(int i=0;i<m_vecEnemigos.size();i++){
		position2di p=m_vecEnemigos[i]->getPosition();
		if(p.X>=0){
			getTile(p)->setVinculado(NULL);
		}
	}
	m_vecEnemigos.clear();
	generarUnidades();
	for (int i=0; i<m_NumUnidades; ++i)
	{	
		m_vecUnidades[i]->PutWeights(poblacion[i].vecWeights);

	}
}

void MapaCuatroEnemigos::generarUnidades(){
	//creamos las unidades 
	int posX = 0;
	int posY = 0;
	int enemigoX=0;
	int enemigoY=0;
	int size = MAPSIZE / 12;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		posY = i / size * 12 +6;
		posX = i % size * 12 +6;

 		shared_ptr<EspadachinRedes>  unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(posX ,posY ));
		unidad->aplicarTextura(driver);
		unidad->setDriver(driver);
		shared_ptr<IDibujable> aux =  vTiles[posY ][posX ];
		aux->setVinculado(unidad.get());
		m_vecUnidades.push_back(unidad);

		int fila = RandInt(1,2);
		enemigoY=posY-fila;
		if (fila == 2)
		{
			enemigoX=RandInt(posX-2,posX+1);
		}else{
			enemigoX=RandInt(posX-1,posX);
		}
		
		
		shared_ptr<CUnidadesAprendizajeDummy> unidadDummy=shared_ptr<CUnidadesAprendizajeDummy>(new CUnidadesAprendizajeDummy(enemigoX,enemigoY));
		unidadDummy->aplicarTextura(driver);
		unidadDummy->setDriver(driver);
		 aux = vTiles[enemigoY][enemigoX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);


		fila = RandInt(1,2);
		enemigoX=posX+fila;
		if (fila == 2)
		{
			enemigoY=RandInt(posY-2,posY+1);
		}else{
			enemigoY=RandInt(posY-1,posY);
		}
		
		 unidadDummy=shared_ptr<CUnidadesAprendizajeDummy>(new CUnidadesAprendizajeDummy(enemigoX,enemigoY));
		unidadDummy->aplicarTextura(driver);
		unidadDummy->setDriver(driver);
		 aux = vTiles[enemigoY][enemigoX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		
		fila = RandInt(1,2);
		enemigoY=posY+fila;
		if (fila == 2)
		{
			enemigoX=RandInt(posX-1,posX+2);
		}else{
			enemigoX=RandInt(posX,posX+1);
		}
		
		 unidadDummy=shared_ptr<CUnidadesAprendizajeDummy>(new CUnidadesAprendizajeDummy(enemigoX,enemigoY));
		unidadDummy->aplicarTextura(driver);
		unidadDummy->setDriver(driver);
		 aux = vTiles[enemigoY][enemigoX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);

		fila = RandInt(1,2);
		enemigoX=posX-fila;
		if (fila == 2)
		{
			enemigoY=RandInt(posY-1,posY+2);
		}else{
			enemigoY=RandInt(posY,posY+1);
		}
		 unidadDummy=shared_ptr<CUnidadesAprendizajeDummy>(new CUnidadesAprendizajeDummy(enemigoX,enemigoY));
		unidadDummy->aplicarTextura(driver);
		unidadDummy->setDriver(driver);
		 aux = vTiles[enemigoY][enemigoX];
		aux->setVinculado(unidadDummy.get());
		//vTiles[posY][posX]=unidadDummy;
		m_vecEnemigos.push_back(unidadDummy);
		

		
	}

}
// ================== ~MapaCuatroUnidades ===================== //
// ================== ~MapaRandom ===================== //


MapaRandom::MapaRandom(IrrlichtDevice* dev,int num):MapaAprendizaje(dev,num){
	driver = dev->getVideoDriver();
	generarMapa();
}

MapaRandom::~MapaRandom(){

}

void MapaRandom::generarMapa(){
int j=0;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			nuevoSuelo(j,i);

		}
	}

	for(int i=0;i<3000;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);

		nuevoMuro(RandIntY,RandIntX);
	}
	generarUnidades();
}

void MapaRandom::reset(const vector<SGenome>& poblacion){
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

void MapaRandom::generarUnidades(){
	int x=0,y=0;
	bool noEstar=true;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		do{
			x= RandInt(0,MAPSIZE-1);
			y=RandInt(0,MAPSIZE-1);

			if(getTile(y,x)->getTipo()==0){
				shared_ptr<EspadachinRedes> unidad=shared_ptr<EspadachinRedes>(new EspadachinRedes(x,y));
				unidad->aplicarTextura(driver);
				shared_ptr<IDibujable> aux = vTiles[y][x];
				vTiles[y][x]=unidad;
				m_vecUnidades.push_back(unidad);
				noEstar=false;
			}
		}while(noEstar);
	noEstar=true;
	}
}
// ================== ~MapaRandom ===================== //