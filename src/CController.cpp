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
	red="";
	generarMapa(1);
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



bool CController::tickRedNeuronal(){
	outfile.open("GeneticMovimientos.txt", ios::app);
	if (outfile.is_open())
	{
		outfile<<"##########################################################CController::Update:76"<<" mUnidades "<<m_NumUnidades<<" Ticks "<<m_iTicks<<"#####################################################"<<endl;


	}

	outfile.close();

	for (int i=0; i<m_NumUnidades; ++i)

	{
		m_vecUnidades[i]->updateIA(matriz);

	}
	
	for (int i = m_NumUnidades; i < m_vecUnidades.size(); ++i)
	{
		m_vecUnidades[i]->updateIA(matriz);
	}
return true;

}

bool CController::redNeuronal(){
	bool ticks = m_iTicks++ < CParams::iNumTicks;
	if (ticks)
	{
		tickRedNeuronal();
	}else{
		for (int i=0; i<m_NumUnidades; ++i){
			m_vecUnidades[i]->setFitness(m_vecUnidades[i]->Fitness()*m_vecUnidades[i]->getLife()/100);
			//update the chromos fitness score
			m_vecThePopulation[i].dFitness = m_vecUnidades[i]->Fitness();
		}
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
    vector<double> pesoPrincipio=m_vecThePopulation[0].vecWeights;
    guardarPesos();
	matriz->reset(m_vecThePopulation);
	m_vecUnidades = matriz->getUnidadesAprendizaje();
	prueba=m_vecUnidades[0]->getCNeuralWeight();

	for (int i = 0; i < pesoPrincipio.size(); ++i)
	{
		if(pesoPrincipio[i]!=prueba[i]){
			cout<<"No son iguales"<<endl;
		}
	}
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
    red=nombreCarpeta+"/"+"Red_"+std::to_string(m_iGenerations)+".txt";
	pesosActualesFile.open(redAux,ios::out);
	if (pesosActualesFile.is_open())
	{
		for (int i=0; i<m_NumUnidades; ++i)
		{	
			pesosActualesFile<<m_vecThePopulation[i].vecWeights[0];
			for (int j = 1; j < m_vecThePopulation[i].vecWeights.size(); ++j)
			{
				pesosActualesFile<<","<<m_vecThePopulation[i].vecWeights[j]<<std::setprecision(20);
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
shared_ptr<CUnidadesAprendizaje> CController::getUnidadPosicion(position2di pos){
	
	return std::dynamic_pointer_cast<CUnidadesAprendizaje>( matriz->getTile(pos.Y,pos.X));

}


void CController::Pintar(){
	matriz->Pintar();
}





void CController::generarMapa(int tipoMapa){
	if(tipoMapa==1){
		matriz = shared_ptr<MapaAprendizaje>(new MapaBasicoDummy(device,m_NumUnidades));
	}
	else if(tipoMapa==2){
		matriz = shared_ptr<MapaAprendizaje>(new MapaBasicoMuroYUnidad(device,m_NumUnidades));
			
	}
	else if(tipoMapa==3){
		matriz= shared_ptr<MapaAprendizaje>(new MapaCuatroUnidades(device,m_NumUnidades));
		
	}
	else if(tipoMapa==4){
		matriz= shared_ptr<MapaAprendizaje>(new MapaCuadrado(device,m_NumUnidades));
	}
	else{
		cerr<<"NO HAY MAPA: "<<tipoMapa<<endl;
	}


	m_vecUnidades = matriz->getUnidadesAprendizaje();
	for (int i = 0; i < m_NumUnidades; ++i)
	{
		//m_vecUnidades.push_back(aux[i]);
		m_vecUnidades[i]->calcular8Objetos(matriz);
	}
	if(red!=""){
		ponerWeightFichero(red);
		vector<double> vecW=m_vecUnidades[0]->getCNeuralWeight();
		for (int i = 0; i < vecW.size(); ++i)
		{
			if(vecW[i]!=prueba[i]){
				cout<<"ERROR DE CAMBIO DE MAPA CON LOS PESOS"<<endl;
			}
		}
	}

}
void CController::ponerWeightFichero(std::string fichero){
	vector<double> weights;
	std::string cadena,buf;
	vector<std::string> parser;
	ifstream myReadFile;
	int numFilas=0;

	myReadFile.open(fichero,ios::in);
 	if (myReadFile.is_open()) {

 		while (!myReadFile.eof()) {
 				
   			getline(myReadFile,cadena);
    		stringstream ss(cadena);

    		ss>>buf;
    		boost::split(parser, buf, boost::is_any_of(","));
    		for(std::string & weight : parser){
    			weights.push_back(atof(weight.c_str()));
    		}
    		m_vecUnidades[numFilas]->PutWeights(weights);
    		numFilas++;
	 		if(numFilas==m_NumUnidades){
	 			break;
	 		}
 		}
	}
myReadFile.close();
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
				

				shared_ptr<IDibujable> tile =  matriz->getTile(pos_grid.Y,pos_grid.X);
				cerr<<"Has clicado en ["<<pos_grid.X<<","<<pos_grid.Y<<"]";
				if (tile->getTipo() == 3)
				{
					shared_ptr<CUnidadesAprendizaje> unit = std::dynamic_pointer_cast<CUnidadesAprendizaje>( tile);
					unit->TexturaSeleccionada(device->getVideoDriver(),true);
					unidad_seleccionada = unit;
					cerr<<" - Unidad seleccionada.pos = ["<<unit->getPosicion().X<<","<<unit->getPosicion().Y<<"]";
				}
				cerr<<endl;
				matriz->setUnidadSeleccionada(unidad_seleccionada);
			}
		}
	}
	return false;

}

void CController::PintarInformacionUnidad()
{
	matriz->PintarInformacionUnidad();
}
