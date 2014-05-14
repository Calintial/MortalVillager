#include "CController.h"
std::string cogerCommit(){
	FILE* pipe = popen("git rev-parse HEAD", "r");
	 if (!pipe)
	   return "ERROR";
	 char buffer[128];
	 std::string result = "";
	 while(!feof(pipe)) {
	   if(fgets(buffer, 128, pipe) != NULL){
	     result += buffer;
	     std::cout << buffer;
	 	}
	 }
	 pclose(pipe);
	 result.erase(std::remove(result.begin(),result.end(),'\n'),result.end());
	 return result;
}

//---------------------------------------constructor---------------------
//
//	initilaize the sweepers, their brains and the GA factory
//
//-----------------------------------------------------------------------
CController::CController(IrrlichtDevice* dev): m_NumUnidades(CParams::iNumUnidades), 
m_pGA(NULL),
m_iTicks(0),
m_iGenerations(0)
{
	device = dev;
	driver = device->getVideoDriver();
	generarMapa();
	t=time(0);
	struct tm * now=localtime(&t);
	std::string tiempoo=std::string("")+std::to_string(now->tm_mon+1)+"_"+std::to_string(now->tm_mday)+"_"+std::to_string(now->tm_hour)+"_"+std::to_string(now->tm_min)+"_"+std::to_string(now->tm_sec);
	versionGit=cogerCommit();
	nombreCarpeta=std::string("../logs/")+tiempoo+"_"+versionGit;
	std::string carpeta=std::string("mkdir \"")+nombreCarpeta+std::string("\"");

	system(carpeta.c_str());

	//get the total number of weights used in the sweepers
	//NN so we can initialise the GA
	m_NumWeightsInNN = m_vecUnidades[0]->GetNumberOfWeights();

	//initialize the Genetic Algorithm class
	m_pGA = new CGenAlg(m_NumUnidades,
		CParams::dMutationRate,
		CParams::dCrossoverRate,
		m_NumWeightsInNN,nombreCarpeta);

	//Get the weights from the GA and insert into the sweepers brains
	m_vecThePopulation = m_pGA->GetChromos();

	for (int i=0; i<m_NumUnidades; i++)

		m_vecUnidades[i]->PutWeights(m_vecThePopulation[i].vecWeights);

	//initialize mines in random positions within the application window

	unidad_seleccionada = NULL;
	
	font = device->getGUIEnvironment()->getFont("../media/fonthaettenschweiler.bmp");
}

//--------------------------------------destructor-------------------------------------
//
//--------------------------------------------------------------------------------------
CController::~CController()
{
	if(m_pGA)
	{
		delete		m_pGA;
	}


}

bool CController::tickRedNeuronalUnidad(CUnidadesAprendizaje* unidad, const int i){
	if (unidad->getLife() > 0)
		{
			unidad->calcular8Objetos(matriz);
			//Pintar();
				//update the NN and position
			outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad ANTES : "<<i<<" tiene de Fitness :"<<unidad->Fitness()<<" y esta en la posición: ("<<unidad->getPosicion().X <<","<<unidad->getPosicion().Y<<")"<<endl;

			}

			outfile.close();
			if (!unidad->Update(matriz))
			{

					//error in processing the neural net
				cout<<"Wrong amount of NN inputs!"<<endl;
				return false;
			}


			outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad : "<<i<<" tiene de Fitness :"<<unidad->Fitness()<<" y esta en la posición: ("<<unidad->getPosicion().X <<","<<unidad->getPosicion().Y<<")"<<endl;

			}

			outfile.close();

			if(unidad->getAtaque()==1){
				position2di atacando=unidad->getAtaqueMovimiento();

				if(matriz->getTile(atacando.Y,atacando.X)!=NULL && matriz->getTile(atacando.Y,atacando.X)->getTipo()==3){

					int dano = unidad->Attack((Unidades*)matriz->getTile(atacando.Y,atacando.X));
					unidad->IncrementFitness((CUnidadesAprendizaje*) matriz->getTile(atacando.Y,atacando.X),((Unidades*)unidad)->TrianguloArmas((Unidades*) matriz->getTile(atacando.Y,atacando.X)),m_pGA->BestFitness());
					
					outfile.open("GeneticMovimientos.txt", ios::app);
					if (outfile.is_open())
					{

						outfile << "Y esta atacando a: ("<<atacando.X<<","<<atacando.Y<<")"<<endl;
					}

					outfile.close();
					
				}

				
			}
			else{

				if(unidad->getMover()==1){
					video::IVideoDriver* driver = device->getVideoDriver();
					matriz->setTile(unidad->getPosicion(), new Suelo(unidad->getPosicion().X,unidad->getPosicion().Y));
					((Suelo*) matriz->getTile(unidad->getPosicion().Y,unidad->getPosicion().X))->setIsometric(false);
					matriz->getTile(unidad->getPosicion())->aplicarTextura(driver);
					position2di moverse=unidad->getMovimiento();
					if(matriz->getTile(moverse.Y,moverse.X)->getTipo()==0){
						//cout<<"Estoy en ("<<unidad->getPosition().X<<","<<unidad->getPosition().Y<<") Y me muevo a ("<<moverse.X<<","<<moverse.Y<<")"<<"y hay en el vector: "<<m_vecUnidades.size()<<endl;
						unidad->setPosition(unidad->getMovimiento());

					}
					
					matriz->setTile(unidad->getPosicion(),unidad);
				}
			}
		}else{
			position2di pos = unidad->getPosicion();
			if (pos.X >=0)
			{
				cout<<"##### HE MUERTO! POS: <"<<pos.X<<","<<pos.Y<<">"<<endl;
				matriz->setTile(pos.Y,pos.X, new Suelo(pos.X,pos.Y));
				((Suelo*) matriz->getTile(pos.Y,pos.X))->setIsometric(false);
				matriz->getTile(pos.Y,pos.X)->aplicarTextura(driver);
				unidad->setPosition(-1,-1);
			}
			
			
		}
		return true;
}

bool CController::tickRedNeuronal(){
	outfile.open("GeneticMovimientos.txt", ios::app);
	if (outfile.is_open())
	{
		outfile<<"##########################################################CController::Update:76"<<" mUnidades "<<m_NumUnidades<<" Ticks "<<m_iTicks<<"#####################################################"<<endl;


	}

	outfile.close();

	for (int i=0; i<m_NumUnidades; ++i)

	{
		tickRedNeuronalUnidad(m_vecUnidades[i],i);

	}
	for (int i=0; i<m_NumUnidades; ++i){
		m_vecUnidades[i]->setFitness(m_vecUnidades[i]->Fitness()*m_vecUnidades[i]->getLife()/100);
		//update the chromos fitness score
		m_vecThePopulation[i].dFitness = m_vecUnidades[i]->Fitness();
	}
	for (int i = m_NumUnidades; i < m_vecUnidades.size(); ++i)
	{
		tickRedNeuronalUnidad(m_vecUnidades[i],i);
	}
return true;

}

bool CController::redNeuronal(){
	bool ticks = m_iTicks++ < CParams::iNumTicks;
	if (ticks)
	{
		tickRedNeuronal();
	}
	return ticks;
}

bool CController::genetico(){
	//update the stats to be used in our stat window
	m_vecAvFitness.push_back(m_pGA->AverageFitness());
	m_vecBestFitness.push_back(m_pGA->BestFitness());

		//increment the generation counter
	++m_iGenerations;

		//reset cycles
	m_iTicks = 0;

		//run the GA to create a new population
	m_vecThePopulation = m_pGA->Epoch(m_vecThePopulation, m_iGenerations);

		//insert the new (hopefully)improved brains back into the sweepers
    //and reset their positions etc
    
	guardarPesos();
	matriz->reset(m_vecThePopulation);
	m_vecUnidades = matriz->getUnidadesAprendizaje();
	

	//}

	for (int i=0; i<m_NumUnidades; ++i)
	{
		m_vecUnidades[i]->calcular8Objetos(matriz);

	}
	return true;
}

void CController::guardarPesos(){
	ofstream pesosActualesFile;
	std::string redAux=nombreCarpeta+"/"+"RedAux_"+std::to_string(m_iGenerations)+".txt";
    std::string red=nombreCarpeta+"/"+"Red_"+std::to_string(m_iGenerations)+".txt";
	pesosActualesFile.open(redAux,ios::out);
	if (pesosActualesFile.is_open())
	{
		for (int i=0; i<m_NumUnidades; ++i)
		{	
			pesosActualesFile<<m_vecThePopulation[i].vecWeights[0];
			for (int j = 1; j < m_vecThePopulation[i].vecWeights.size(); ++j)
			{
				pesosActualesFile<<","<<m_vecThePopulation[i].vecWeights[j];
			}
			pesosActualesFile<<endl;
		}
		pesosActualesFile.close();
		rename (redAux.c_str(),red.c_str());
	}else{
		cerr<<"NO SE HA PODIDO ABRIR EL ARCHIVO DE RED NEURONAL"<<endl;
	}
}

//-------------------------------------Update-----------------------------
//
//	This is the main workhorse. The entire simulation is controlled from here.
//
//	The comments should explain what is going on adequately.
//-------------------------------------------------------------------------
/*bool CController::Update()
{
	//run the sweepers through CParams::iNumTicks amount of cycles. During
  //this loop each sweepers NN is constantly updated with the appropriate
  //information from its surroundings. The output from the NN is obtained
  //and the sweeper is moved. If it encounters a mine its fitness is
  //updated appropriately,
	

	//Another generation has been completed.

	//Time to run the GA and update the sweepers with their new NNs
	else
	{
		
		Pintar();
	}

	

	return true;
}*/
//Devuelve la unidad que hay en esa posición 
CUnidadesAprendizaje* CController::getUnidadPosicion(position2di pos){
	
	return (CUnidadesAprendizaje*) matriz->getTile(pos.Y,pos.X);

}


void CController::Pintar(){
	matriz->Pintar();
}

// mapa random
void CController::mapa0(){
	int j=0;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			matriz->setTile(i,j, new Suelo(j,i));
			((Suelo*) matriz->getTile(i,j))->setIsometric(false);
			matriz->getTile(i,j)->aplicarTextura(driver);

		}
	}

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		matriz->setTile(RandIntY,RandIntX,new Muro(RandIntX,RandIntY));
		((Muro*) matriz->getTile(RandIntY,RandIntX))->setIsometric(false);
		matriz->getTile(RandIntY,RandIntX)->aplicarTextura(driver);
	}

	//creamos las unidades 
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
		matriz->setTile(k,j,unidad);
		m_vecUnidades.push_back(unidad);
	}
}

// mapa con cada unidad rodeada de muros y con una unidad dummy a la que atacar
void CController::mapa1(){
	m_vecUnidades.clear();
	/*

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		matriz->setTile(RandIntY,RandIntX,new Muro(RandIntX,RandIntY));
		((Muro*) matriz->getTile(RandIntY,RandIntX))->setIsometric(false);
		matriz->getTile(RandIntY,RandIntX)->aplicarTextura(driver);
	}
*/
	
}

// mapa con cada unidad rodeada de muros y con una unidad dummy a la que atacar
void CController::mapa2(){
	m_vecUnidades.clear();
	/*

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		matriz->setTile(RandIntY,RandIntX,new Muro(RandIntX,RandIntY));
		((Muro*) matriz->getTile(RandIntY,RandIntX))->setIsometric(false);
		matriz->getTile(RandIntY,RandIntX)->aplicarTextura(driver);
	}
*/
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			matriz->setTile(i,j,new Suelo(j,i));
			((Suelo*) matriz->getTile(i,j))->setIsometric(false);
			matriz->getTile(i,j)->aplicarTextura(driver);

		}
	}
	for (int i=0;i<MAPSIZE;i+=6){
		for(int j=0;j<MAPSIZE;j+=6){
			if (i + 6 < MAPSIZE && j+6 < MAPSIZE)
			{	
				for (int iteradorEsquina = 0; iteradorEsquina < 6; ++iteradorEsquina)
				{
					matriz->setTile(i + iteradorEsquina,j, new Muro(j,i + iteradorEsquina));
					((Muro*) matriz->getTile(i + iteradorEsquina,j))->setIsometric(false);
					matriz->getTile(i + iteradorEsquina,j)->aplicarTextura(driver);
					matriz->setTile(i,j + iteradorEsquina, new Muro(j + iteradorEsquina,i));
					((Muro*) matriz->getTile(i,j + iteradorEsquina))->setIsometric(false);
					matriz->getTile(i,j + iteradorEsquina)->aplicarTextura(driver);
				}
				
			}
			

		}
	}
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
		matriz->setTile(posY,posX,unidadDummy);
		

		EspadachinRedes* unidad=new EspadachinRedes(posX + 2,posY + 2);
		unidad->aplicarTextura(driver);
		matriz->setTile(posY + 2,posX + 2,unidad);
		m_vecUnidades.push_back(unidad);
	}
}


void CController::generarMapa(){
	matriz = new MapaBasicoMuroYUnidad(device,m_NumUnidades);
	//mapa2();

	m_vecUnidades = matriz->getUnidadesAprendizaje();
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		//m_vecUnidades.push_back(aux[i]);
		m_vecUnidades[i]->calcular8Objetos(matriz);
	}

}
void CController::modificarUnidad(CUnidadesAprendizaje* unidad){
	int x=0,y=0;
	x=unidad->getPosicion().X;
	y=unidad->getPosicion().Y;
	outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
			outfile << "CConstroller::modificarUnidad:279 La unidad va a ser modificada y estaba en ("<<x<<","<<y<<")"<<endl;;
		}

	outfile.close();
	matriz->setTile(y,x, new Suelo(x,y));
	((Suelo*) matriz->getTile(y,x))->setIsometric(false);
	matriz->getTile(y,x)->aplicarTextura(driver);
	unidad->Reset();
	bool noEstar=true;
	x=0;
	y=0;

	do{
		x= RandInt(0,MAPSIZE-1);
		y=RandInt(0,MAPSIZE-1);

		if(matriz->getTile(y,x)->getTipo()==0){
				outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
			outfile << "CConstroller::modificarUnidad:279 La unidad va a ser modificada y ESTA en ("<<x<<","<<y<<")"<<endl;;
		}

	outfile.close();
			unidad->setPosition(position2di(x,y));
			matriz->setTile(y,x,unidad);
			noEstar=false;
		}
	}while(noEstar);

}
bool CController::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		position2di pos_grid;
		pos_grid.X = event.MouseInput.X/TILE_W;
		pos_grid.Y = event.MouseInput.Y/TILE_H;

		if (pos_grid.X < MAPSIZE && pos_grid.Y < MAPSIZE && pos_grid.X >= 0 && pos_grid.Y >= 0)
		{
			if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
			{
				if(unidad_seleccionada != NULL && unidad_seleccionada->getTipo() == 3)
				{
					unidad_seleccionada->TexturaSeleccionada(device->getVideoDriver(),false);
					unidad_seleccionada = NULL;
				}
				

				IDibujable* tile =  matriz->getTile(pos_grid.Y,pos_grid.X);
				cerr<<"Has clicado en ["<<pos_grid.X<<","<<pos_grid.Y<<"]";
				if (tile->getTipo() == 3)
				{
					CUnidadesAprendizaje* unit = (CUnidadesAprendizaje*) tile;
					unit->TexturaSeleccionada(device->getVideoDriver(),true);
					unidad_seleccionada = unit;
					cerr<<" - Unidad seleccionada.pos = ["<<unit->getPosicion().X<<","<<unit->getPosicion().Y<<"]";
				}
				cerr<<endl;
			}
		}
	}
	return false;

}

void CController::PintarInformacionUnidad()
{
	vector<ObjetosCercanos> objCercanos = ((CUnidadesAprendizaje*) unidad_seleccionada)->getVectorObjetos();
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
		position2di drawPos = position2di(objeto.posicion.X*TILE_W, objeto.posicion.Y * TILE_H);
		//Pinta
		if (objeto.tipo == 1) // muro
		{
			driver->draw2DRectangle(video::SColor(255,0,255,0),core::rect<s32>(drawPos,drawPos + position2di(TILE_W,TILE_H)));
		}else if (objeto.tipo == 3) // unidad?
		{
			driver->draw2DRectangle(video::SColor(255,0,255,255),core::rect<s32>(drawPos,drawPos + position2di(TILE_W,TILE_H)));
		}else{// lo que sea...
			driver->draw2DRectangle(video::SColor(255,0,0,255),core::rect<s32>(drawPos,drawPos + position2di(TILE_W,TILE_H)));
		}
	}
}
