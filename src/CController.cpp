#include "CController.h"


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
	

	//get the total number of weights used in the sweepers
	//NN so we can initialise the GA
	m_NumWeightsInNN = m_vecUnidades[0]->GetNumberOfWeights();

	//initialize the Genetic Algorithm class
	m_pGA = new CGenAlg(m_NumUnidades,
		CParams::dMutationRate,
		CParams::dCrossoverRate,
		m_NumWeightsInNN);

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

bool CController::tickRedNeuronal(){
	outfile.open("GeneticMovimientos.txt", ios::app);
	if (outfile.is_open())
	{
		outfile<<"##########################################################CController::Update:76"<<" mUnidades "<<m_NumUnidades<<" Ticks "<<m_iTicks<<"#####################################################"<<endl;


	}

	outfile.close();

	for (int i=0; i<m_NumUnidades; ++i)

	{
		if (m_vecUnidades[i]->getLife() > 0)
		{
			m_vecUnidades[i]->calcular8Objetos(Matriz);
			//Pintar();
				//update the NN and position
			outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad ANTES : "<<i<<" tiene de Fitness :"<<m_vecUnidades[i]->Fitness()<<" y esta en la posición: ("<<m_vecUnidades[i]->getPosicion().X <<","<<m_vecUnidades[i]->getPosicion().Y<<")"<<endl;

			}

			outfile.close();
			if (!m_vecUnidades[i]->Update(Matriz))
			{

					//error in processing the neural net
				cout<<"Wrong amount of NN inputs!"<<endl;
				return false;
			}


			outfile.open("GeneticMovimientos.txt", ios::app);
			if (outfile.is_open())
			{
				outfile << "La unidad : "<<i<<" tiene de Fitness :"<<m_vecUnidades[i]->Fitness()<<" y esta en la posición: ("<<m_vecUnidades[i]->getPosicion().X <<","<<m_vecUnidades[i]->getPosicion().Y<<")"<<endl;

			}

			outfile.close();

			if(m_vecUnidades[i]->getAtaque()==1){
				position2di atacando=m_vecUnidades[i]->getAtaqueMovimiento();

				if(Matriz[atacando.Y][atacando.X]!=NULL && Matriz[atacando.Y][atacando.X]->getTipo()==3){

					int dano = m_vecUnidades[i]->Attack((Unidades*)Matriz[atacando.Y][atacando.X]);
					m_vecUnidades[i]->IncrementFitness(dano);
					
					outfile.open("GeneticMovimientos.txt", ios::app);
					if (outfile.is_open())
					{

						outfile << "Y esta atacando a: ("<<atacando.X<<","<<atacando.Y<<")"<<endl;
					}

					outfile.close();
					
				}

				
			}
			else{

				if(m_vecUnidades[i]->getMover()==1){
					video::IVideoDriver* driver = device->getVideoDriver();
					Matriz[m_vecUnidades[i]->getPosicion().Y][m_vecUnidades[i]->getPosicion().X]= new Suelo(m_vecUnidades[i]->getPosicion().X,m_vecUnidades[i]->getPosicion().Y);
					((Suelo*) Matriz[m_vecUnidades[i]->getPosicion().Y][m_vecUnidades[i]->getPosicion().X])->setIsometric(false);
					Matriz[m_vecUnidades[i]->getPosicion().Y][m_vecUnidades[i]->getPosicion().X]->aplicarTextura(driver);
					position2di moverse=m_vecUnidades[i]->getMovimiento();
					if(Matriz[moverse.Y][moverse.X]->getTipo()==0){
						//cout<<"Estoy en ("<<m_vecUnidades[i]->getPosition().X<<","<<m_vecUnidades[i]->getPosition().Y<<") Y me muevo a ("<<moverse.X<<","<<moverse.Y<<")"<<"y hay en el vector: "<<m_vecUnidades.size()<<endl;
						m_vecUnidades[i]->setPosition(m_vecUnidades[i]->getMovimiento());

					}
					
					Matriz[m_vecUnidades[i]->getPosicion().Y][m_vecUnidades[i]->getPosicion().X]=m_vecUnidades[i];
				}
			}
				//update the chromos fitness score
			m_vecThePopulation[i].dFitness = m_vecUnidades[i]->Fitness();

		}else{
			position2di pos = m_vecUnidades[i]->getPosicion();
			if (pos.X >=0)
			{
				cout<<"##### HE MUERTO! POS: <"<<pos.X<<","<<pos.Y<<">"<<endl;
				Matriz[pos.Y][pos.X] = new Suelo(pos.X,pos.Y);
				((Suelo*) Matriz[pos.Y][pos.X])->setIsometric(false);
				Matriz[pos.Y][pos.X]->aplicarTextura(driver);
				m_vecUnidades[i]->setPosition(-1,-1);
			}
			
			
		}

	}


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
	for (int i=0; i<m_NumUnidades; ++i)
	{
		m_vecUnidades[i]->PutWeights(m_vecThePopulation[i].vecWeights);
		modificarUnidad(m_vecUnidades[i]);

	}
	for (int i=0; i<m_NumUnidades; ++i)
	{
		m_vecUnidades[i]->calcular8Objetos(Matriz);

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
	
	return (CUnidadesAprendizaje*) Matriz[pos.Y][pos.X];

};	

void CController::Pintar()
{
	video::IVideoDriver* driver = device->getVideoDriver();
	if (device->run())
	{        
		if(driver)
		{
			position2di GridPosition, DrawPosition;
			

			for(int i = 0; i < MAPSIZE; i++)
			{
				for(int j = 0; j < MAPSIZE; j++)
				{
					// Obtenermos coordenadas actuales cuadricula
					DrawPosition = position2di(j*TILE_H, i * TILE_W);
					//DrawPosition = getIsoFromTile(i - CameraScroll.X, j - CameraScroll.Y);
					// position2di((i*TILE_WIDTH) - CameraScroll.X, (j*TILE_HEIGHT) - CameraScroll.Y);
					// Validar coordenada
					IDibujable *Tile = Matriz[i][j];
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

			device->getGUIEnvironment()->drawAll();

		}
	}
	else
	{
		gameEngine::stado.finish();
	}
}


void CController::generarMapa(){
	int j=0;
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			Matriz[i][j]= new Suelo(i,j);
			((Suelo*) Matriz[i][j])->setIsometric(false);
			Matriz[i][j]->aplicarTextura(driver);

		}
	}

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		Matriz[RandIntY][RandIntX]=new Muro(RandIntX,RandIntY);
		((Muro*) Matriz[RandIntY][RandIntX])->setIsometric(false);
		Matriz[RandIntY][RandIntX]->aplicarTextura(driver);
	}

	//creamos las unidades 
	
	for (int i=0; i<m_NumUnidades; ++i)
	{
		if(i%20==0){
			j++;	
		}
		EspadachinRedes* unidad=new EspadachinRedes(j,i);
		unidad->aplicarTextura(driver);
		Matriz[i][j]=unidad;
		m_vecUnidades.push_back(unidad);
	}

	for (int i=0; i<m_NumUnidades; ++i)
	{
		m_vecUnidades[i]->calcular8Objetos(Matriz);
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
	Matriz[y][x]= new Suelo(x,y);
	((Suelo*) Matriz[y][x])->setIsometric(false);
	Matriz[y][x]->aplicarTextura(driver);
	unidad->Reset();
	bool noEstar=true;
	x=0;
	y=0;

	do{
		x= RandInt(0,MAPSIZE-1);
		y=RandInt(0,MAPSIZE-1);

		if(Matriz[y][x]->getTipo()==0){
				outfile.open("GeneticMovimientos.txt", ios::app);
		if (outfile.is_open())
		{
			outfile << "CConstroller::modificarUnidad:279 La unidad va a ser modificada y ESTA en ("<<x<<","<<y<<")"<<endl;;
		}

	outfile.close();
			unidad->setPosition(position2di(x,y));
			Matriz[y][x]=unidad;
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
				

				IDibujable* tile =  Matriz[pos_grid.Y][pos_grid.X];
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