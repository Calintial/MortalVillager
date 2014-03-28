#include "CController.h"


//---------------------------------------constructor---------------------
//
//	initilaize the sweepers, their brains and the GA factory
//
//-----------------------------------------------------------------------
CController::CController(): m_NumUnidades(CParams::iNumUnidades), 
										                     m_pGA(NULL),
										                     m_iTicks(0),
										                     m_iGenerations(0)
{
	for (int i=0;i<MAPSIZE;i++){
		for(int j=0;j<MAPSIZE;j++){
			//0 transitable 1 no transitable
			Matriz[i][j]=NULL;
		}
	}

	for(int i=0;i<30;i++){
		int RandIntX=RandInt(1,MAPSIZE-1);
		int RandIntY=RandInt(1,MAPSIZE-1);
		Matriz[RandIntX][RandIntY]=new Muro(1,RandIntX,RandIntY);
	}

	//creamos las unidades 
	cout<<m_NumUnidades<<endl;
	for (int i=0; i<m_NumUnidades; ++i)
	{
		cout<<i<<endl;
		CUnidadesAprendizaje* unidad=new CUnidadesAprendizaje(Matriz);
		Matriz[unidad->Position().x][unidad->Position().x]=unidad;
		m_vecUnidades.push_back(new CUnidadesAprendizaje(Matriz));
	}

	for (int i=0; i<m_NumUnidades; ++i)
	{
		m_vecUnidades[i]->calcular8Objetos(Matriz);
	}

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


//-------------------------------------Update-----------------------------
//
//	This is the main workhorse. The entire simulation is controlled from here.
//
//	The comments should explain what is going on adequately.
//-------------------------------------------------------------------------
bool CController::Update(IrrlichtDevice* device)
{
	cout<<"Update"<<endl;
	//run the sweepers through CParams::iNumTicks amount of cycles. During
  //this loop each sweepers NN is constantly updated with the appropriate
  //information from its surroundings. The output from the NN is obtained
  //and the sweeper is moved. If it encounters a mine its fitness is
  //updated appropriately,
	if (m_iTicks++ < CParams::iNumTicks)
	{
		for (int i=0; i<m_NumUnidades; ++i)
		{
			//update the NN and position
			if (!m_vecUnidades[i]->Update())
			{
				//error in processing the neural net
				cout<<"Wrong amount of NN inputs!"<<endl;
				return false;
			}
				
				
			if(m_vecUnidades[i]->getAtaque()==1){
		        //we have discovered a mine so increase fitness
		        m_vecUnidades[i]->IncrementFitness();
			}


      

			//update the chromos fitness score
			m_vecThePopulation[i].dFitness = m_vecUnidades[i]->Fitness();

		}
	}

	//Another generation has been completed.
  
	//Time to run the GA and update the sweepers with their new NNs
	else
	{
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
		
			m_vecUnidades[i]->Reset();
		}
	}

	Pintar(device);

	return true;
}
//Devuelve la unidad que hay en esa posición 
CUnidadesAprendizaje* CController::getUnidadPosicion(SVector2D pos){
	
	return (CUnidadesAprendizaje*) Matriz[pos.x][pos.y];

};	

void CController::Pintar(IrrlichtDevice* device)
{
	cout<<"pintar"<<endl;
	video::IVideoDriver* driver = device->getVideoDriver();
	if (device->run())
    {        
        if(driver)
        {
			/*position2di GridPosition, DrawPosition;
			
						
		    for(int i = 0; i < MAPSIZE; i++)
		    {
				for(int j = 0; j < MAPSIZE; j++)
				{
					// Obtenermos coordenadas actuales cuadricula
		            DrawPosition = position2di(i*TILE_W, j * TILE_H);
					//DrawPosition = getIsoFromTile(i - CameraScroll.X, j - CameraScroll.Y);
					// position2di((i*TILE_WIDTH) - CameraScroll.X, (j*TILE_HEIGHT) - CameraScroll.Y);
					// Validar coordenada
						IDibujable *Tile = Matriz[i][j];
						//Pinta
						if(Tile->getTextura())
							Tile->Pintar(driver, DrawPosition.X, DrawPosition.Y);
				}
			}*/

			device->getGUIEnvironment()->drawAll();
			    	
        }
    }
    else
    {
    	gameEngine::stado.finish();
    }
}