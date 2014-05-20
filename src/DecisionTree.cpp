#include "DecisionTree.h"
#include "battleIA.h"
#include "edificio.h"
#include "Unidades.h"

DecisionTree::DecisionTree(video::IVideoDriver* driver)
{
	raiz = new NodoEnemigoCercaCC(this);
	
	enemigoCercaCC =false;
	vidaCC = 0;
	numLanceros = 0;
	numEspadachines = 0;
	numArqueros = 0;
	numAldeanos = 0;
	numLancerosEnemigos = 0;
	numEspadachinesEnemigos = 0;
	numArquerosEnemigos = 0;
	cuartel = false;
	arqueria = false;
	lanceria = false;
	granja = false;
	recursos = 0;
	this->driver = driver;	
}

void DecisionTree::doDecision(int vidaCC, int recursos, vector<shared_ptr<IDibujable>>* IAunits, vector<shared_ptr<IDibujable>>* Userunits, vector<shared_ptr<IDibujable>>* buildings)
{
	this->IAunits = IAunits;
	this->Userunits = Userunits;
	this->buildings = buildings;

	setVidaCC(vidaCC);
	setRecursos(recursos);
	
	//0 --> Aldeano
	//1 --> Arquero
	//2 --> Espadachin
	//3 --> Lancero
	for(int i=0; i<Userunits->size(); i++)
	{
		if(std::dynamic_pointer_cast<Unidades>(Userunits->at(i))->getType() == 1)
			setIncNumArquerosEnemigos();
		else if(std::dynamic_pointer_cast<Unidades>(Userunits->at(i))->getType() == 2)
			setIncNumEspadachinesEnemigos();
		else if(std::dynamic_pointer_cast<Unidades>(Userunits->at(i))->getType() == 3)
			setIncNumLancerosEnemigos();
	}
	
	for(int i=0; i<IAunits->size(); i++)
	{
		if(std::dynamic_pointer_cast<battleIA>(IAunits->at(i))->getType() == 0)
			setIncNumAldeanos();
		else if(std::dynamic_pointer_cast<battleIA>(IAunits->at(i))->getType() == 1)
			setIncNumArqueros();
		else if(std::dynamic_pointer_cast<battleIA>(IAunits->at(i))->getType() == 2)
			setIncNumEspadachines();
		else if(std::dynamic_pointer_cast<battleIA>(IAunits->at(i))->getType() == 3)
			setIncNumLanceros();
	}
	
	//0 --> CC
	//1 --> Granja
	//2 --> Cuartel
	//3 --> Arqueria
	//4 --> Lanceria
	for(int i=0; i<buildings->size(); i++)
	{
		if(std::dynamic_pointer_cast<edificio>(buildings->at(i))->getClase()==0)
			setEnemigoCercaCC(ExisteEnemigoCercaCC(Userunits));
		else if(std::dynamic_pointer_cast<edificio>(buildings->at(i))->getClase()==1)
			setGranja(true);
		else if(std::dynamic_pointer_cast<edificio>(buildings->at(i))->getClase()==2)
			setCuartel(true);
		else if(std::dynamic_pointer_cast<edificio>(buildings->at(i))->getClase()==3)
			setArqueria(true);
		else if(std::dynamic_pointer_cast<edificio>(buildings->at(i))->getClase()==4)
			setLanceria(true);
	}
	
	cout << "Datos recibidos, empieza decision" << endl;
	cout << "RECURSOS IA: "<< recursos << endl;
	
	raiz->Decision();
}


//48x29 x=351, y=370 para ia
bool DecisionTree::ExisteEnemigoCercaCC(vector<shared_ptr<IDibujable>>* Userunits)
{
	for(int i=0; i<Userunits->size(); i++)
	{
		if(Userunits->at(i)->getPosition().X > 350 && Userunits->at(i)->getPosition().Y > 369)
		{
			cout<<"Devuelve true"<<endl;
			return true;
		}
			
	}
	cout<<"Devuelve false"<<endl;
	return false;
}


Node::Node(DecisionTree* dt)
{
	this->dt = dt;
	yes = NULL;
	no = NULL;
}


//-----------------------------------//

NodoEnemigoCercaCC::NodoEnemigoCercaCC(DecisionTree* dt):Node(dt)
{
	setYes(new NodoVidaCC(getDT()));
	setNo(new NodoLanzasMayorEspadas(getDT()));
}

void NodoEnemigoCercaCC::Decision()
{
	if(getDT()->isEnemigoCercaCC())
	{
		cout << "SI --> NodoVidaCC" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NodoLanzasMayorEspadas" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoVidaCC::NodoVidaCC(DecisionTree* dt):Node(dt)
{
	setYes(new NodoTengoSoldados(getDT()));
	setNo(new NodoUsuarioSuperioridad(getDT()));
}

void NodoVidaCC::Decision()
{
	if(getDT()->getVidaCC()<30)
	{
		cout << "SI --> NodoTengoSoldados" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NodoUsuarioSuperioridad" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoTengoSoldados::NodoTengoSoldados(DecisionTree* dt):Node(dt)
{
		//PASAR A ESTADO DEFENDER EN LOS DOS CASOS
		//yes es NULL
		setNo(new NodoLanzasMayorEspadas(getDT()));
}

void NodoTengoSoldados::Decision()
{
	//Hay que poner estados en algun lao y cambiarlo aqui a DEFENDER
	if(gameEngine::state_war_ia != 2)
	{
		gameEngine::state_war_ia = 2;
	}
	if(getDT()->getnumSoldados() < getDT()->getnumSoldadosEnemigos())
	{
		cout << "NO --> NodoLanzasMayorEspadas + STATE=DEFENDER" << endl;
		getNo()->Decision();
	}
	else
	{
		cout << "SI --> HOJA + STATE=DEFENDER" << endl;
	}
}

//-----------------------------------//

//Simple --> mi_ejercito > su_ejercito*1.5 || mi_ejercito es enorme
//COMPLEJA --> hay que hacer algo con el triangulo de armas
NodoUsuarioSuperioridad::NodoUsuarioSuperioridad(DecisionTree* dt):Node(dt)
{
		//yes es null //PASAR A ATACAR
		setNo(new NodoLanzasMayorEspadas(getDT()));
}

void NodoUsuarioSuperioridad::Decision()
{
	if(gameEngine::state_war_ia != 1 && (getDT()->getnumSoldados() > getDT()->getnumSoldadosEnemigos()*1.5 || getDT()->getnumSoldados()>15))
	{
		cout << "SI --> HOJA + STATE=ATACAR" << endl;
		gameEngine::state_war_ia = 1;
	}
	else
	{
		cout << "NO --> NODOLANZASMAYORESPADAS" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoLanzasMayorEspadas::NodoLanzasMayorEspadas(DecisionTree* dt):Node(dt)
{
	setYes(new NodoCuartel(getDT()));
	setNo(new NodoArquerosMayorLanzas(getDT()));
}

//¿Lanzas enemigas > Mis Espadas?
void NodoLanzasMayorEspadas::Decision()
{
	if(getDT()->getnumLancerosEnemigos() > getDT()->getnumEspadachines())
	{
		cout << "SI --> NODOCUARTEL" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODOARQUEROSMAYORLANZAS" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoCuartel::NodoCuartel(DecisionTree* dt):Node(dt)
{
	setYes(new NodoAldeanoEspadachin(getDT()));
	setNo(new NodoRecCuartel(getDT()));
}

void NodoCuartel::Decision()
{
	if(getDT()->isCuartel())
	{
		cout << "YES --> NODOALDEANOESPADACHIN" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECCUARTEL" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoGranja::NodoGranja(DecisionTree* dt):Node(dt)
{
	//yes es null, NADA
	setNo(new NodoRecGranja(getDT()));
}

void NodoGranja::Decision()
{
	if(getDT()->isGranja())
	{
		cout << "YES --> HOJA, NADA" << endl;
	}
	else
	{
		cout << "NO --> NODORECGRANJA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//


NodoAldeanoEspadachin::NodoAldeanoEspadachin(DecisionTree* dt):Node(dt)
{
	setYes(new NodoRecEspadachin(getDT()));
	setNo(new NodoRecAldeano(getDT()));
}

void NodoAldeanoEspadachin::Decision()
{
	if(getDT()->getnumAldeanos()>=1)
	{
		cout << "SI --> NODORECESPADACHIN" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECALDEANO" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoAldeanoLancero::NodoAldeanoLancero(DecisionTree* dt):Node(dt)
{
	setYes(new NodoRecLancero(getDT()));
	setNo(new NodoRecAldeano(getDT()));
}

void NodoAldeanoLancero::Decision()
{
	if(getDT()->getnumAldeanos()>=1)
	{
		cout << "SI --> NODORECLANCERO" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECALDEANO" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoAldeanoArquero::NodoAldeanoArquero(DecisionTree* dt):Node(dt)
{
	setYes(new NodoRecArquero(getDT()));
	setNo(new NodoRecAldeano(getDT()));
}

void NodoAldeanoArquero::Decision()
{
	if(getDT()->getnumAldeanos()>=1)
	{
		cout << "SI --> NODORECARQUERO" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECALDEANO" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecAldeano::NodoRecAldeano(DecisionTree* dt):Node(dt)
{
		//yes es null CREAR ALDEANO 
		//no es null
		//no = new NodoRecGranja();
}

void NodoRecAldeano::Decision()
{
	if(getDT()->getRecursos() >= ALDEANO_COSTE)
	{
		cout << "SI --> HOJA, CREA ALDEANO" << endl; 
		//CREAR ALDEANO
		shared_ptr<AldeanoIA> aldeano = std::dynamic_pointer_cast<AldeanoIA>(gameEngine::addIAUnit(191,194,0));
		aldeano->aplicarTextura(getDT()->driver);
		aldeano->Move(188,191);
		gameEngine::recursos_ia -= ALDEANO_COSTE;
	}
	else
	{
		cout << "NO --> HOJA, NADA" << endl;
	}
}

//-----------------------------------//


NodoRecEspadachin::NodoRecEspadachin(DecisionTree* dt):Node(dt)
{
		//yes es nullCREAR ESPADACHIN 
		
	//-----
		 // null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		 // intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el espadachin. //Probar poniendo la granja a 150
	//----- 
		//no es null NADA
		//no = new NodoRecGranja();
}

void NodoRecEspadachin::Decision()
{
	if(getDT()->getRecursos() >= CONVERTIR_COSTE)
	{
		cout << "SI --> HOJA, CREA ESPADACHIN" << endl;
		//CREAR ESPADACHIN
		vector<shared_ptr<IDibujable>>* unidades = getDT()->IAunits;

		for(int i = 0; i < unidades->size(); i++)
		{
			shared_ptr<battleIA> unit = std::dynamic_pointer_cast<battleIA>(unidades->at(i));
			
			if(unit->getType() == 0)
			{
				gameEngine::recursos_ia -= CONVERTIR_COSTE;
				gameEngine::addIAUnit(unit->getPosicion().X,unit->getPosicion().Y,1)->aplicarTextura(getDT()->driver);
				unidades->erase(unidades->begin() + i);
				break;
			}
		}


	}
	else
	{
		cout << "NO --> HOJA, NADA" << endl;
	}
}

//-----------------------------------//

NodoRecCuartel::NodoRecCuartel(DecisionTree* dt):Node(dt)
{
		//yes es null CREAR CUARTEL
	//---
		//Podria pasar que construya granjas como un colgao, porque vale menos.
		 
		//Poner limite de 5, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
	//--- 
		setNo(new NodoGranja(getDT()));
}

void NodoRecCuartel::Decision()
{
	if(getDT()->getRecursos() >= CUARTEL_COSTE)
	{
		cout << "SI --> HOJA, CREAR CUARTEL" << endl;
		
		//Crear cuartel
		gameEngine::addBuildings(190,187,2,false)->aplicarTextura(getDT()->driver);
		gameEngine::recursos_ia -= CUARTEL_COSTE;
	}
	else
	{
		cout << "NO --> NODOGRANJA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecGranja::NodoRecGranja(DecisionTree* dt):Node(dt)
{
		//yes es null CREAR GRANJA 
		//no es null NADA
}

void NodoRecGranja::Decision()
{
	if(getDT()->getRecursos() >= GRANJA_COSTE)
	{
		cout << "SI --> HOJA, CREAR GRANJA" << endl;
		//CREAR GRANJA
		gameEngine::addBuildings(190,180,1,false)->aplicarTextura(getDT()->driver);
		gameEngine::recursos_ia -= GRANJA_COSTE;
	}
	else
	{
		cout << "NO --> HOJA, NADA" << endl;
	}
}

//-----------------------------------//

//¿Arqueros enemigos > Mis Lanceros?
NodoArquerosMayorLanzas::NodoArquerosMayorLanzas(DecisionTree* dt):Node(dt)
{
	setYes(new NodoLanceria(getDT()));
	setNo(new NodoEspadachinesMayorArcos(getDT()));
}

void NodoArquerosMayorLanzas::Decision()
{
	if(getDT()->getnumArquerosEnemigos() > getDT()->getnumLanceros())
	{
		cout << "SI --> NODOLANCERIA" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODOESPADACHINESMAYORARCOS" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoLanceria::NodoLanceria(DecisionTree* dt):Node(dt)
{
	setYes(new NodoAldeanoLancero(getDT())); 
	setNo(new NodoRecLanceria(getDT()));
}

void NodoLanceria::Decision()
{
	if(getDT()->isLanceria())
	{
		cout << "SI --> NODOALDEANOLANCERO" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECLANCERIA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecLanceria::NodoRecLanceria(DecisionTree* dt):Node(dt)
{
		//yes es null CREAR LANCERIA
	//---
		//Podria pasar que construya granjas como un colgao, porque vale menos.
		 
		//Poner limite de 1, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
	//--- 
		setNo(new NodoGranja(getDT()));
}

void NodoRecLanceria::Decision()
{
	if(getDT()->getRecursos() >= LANCERIA_COSTE)
	{
		cout << "SI --> HOJA, CREAR LANCERIA" << endl;
		//CREAR LANCERIA
		gameEngine::addBuildings(184,193,4,false)->aplicarTextura(getDT()->driver);
		gameEngine::recursos_ia -= LANCERIA_COSTE;

	}
	else
	{
		cout << "NO --> NODOGRANJA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecLancero::NodoRecLancero(DecisionTree* dt):Node(dt)
{
		//yes es null, CREAR LANCERO
	//---
		//null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		//intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el lancero. //Probar poniendo la granja a 150
		  
	//---
		//no es null, NADA
		//no = new NodoRecGranja();
}

void NodoRecLancero::Decision()
{
	if(getDT()->getRecursos() >= CONVERTIR_COSTE)
	{
		cout << "SI --> HOJA, CREAR LANCERO" << endl;
		//CREAR LANCERO
		vector<shared_ptr<IDibujable>>* unidades = getDT()->IAunits;

		for(int i = 0; i < unidades->size(); i++)
		{
			shared_ptr<battleIA> unit =  std::dynamic_pointer_cast<battleIA>(unidades->at(i));
			
			if(unit->getType() == 0)
			{
				gameEngine::recursos_ia -= CONVERTIR_COSTE;
				gameEngine::addIAUnit(unit->getPosicion().X,unit->getPosicion().Y,2)->aplicarTextura(getDT()->driver);
				unidades->erase(unidades->begin() + i);
				break;
			}
		}
	}
	else
	{
		cout << "NO --> HOJA, NADA" << endl;
	}
}

//-----------------------------------//

NodoEspadachinesMayorArcos::NodoEspadachinesMayorArcos(DecisionTree* dt):Node(dt)
{
		setYes(new NodoArqueria(getDT()));
		setNo(new NodoGranja(getDT()));
		//no es null PASAR A MODO ATACAR
}

//¿Espadachines enemigos > Mis Arqueros?
void NodoEspadachinesMayorArcos::Decision()
{
	if(getDT()->getnumEspadachinesEnemigos() > getDT()->getnumArqueros())
	{
		cout << "SI --> NODOARQUERIA" << endl;
		getYes()->Decision();
	}
	else
	{
		if(gameEngine::state_war_ia != 1 && (getDT()->getnumSoldados() > getDT()->getnumSoldadosEnemigos()*1.5 || getDT()->getnumSoldados()>15))
		{
			cout << "NO --> NODOGRANJA, STATE=ATACAR" << endl;
			gameEngine::state_war_ia=1;
			getNo()->Decision();
		}
		else
		{
			cout << "NO --> NODOGRANJA" << endl;
			getNo()->Decision();
		}
	}
}

//-----------------------------------//

NodoArqueria::NodoArqueria(DecisionTree* dt):Node(dt)
{
		setYes(new NodoAldeanoArquero(getDT()));
		setNo(new NodoRecArqueria(getDT()));
}

void NodoArqueria::Decision()
{
	if(getDT()->isArqueria())
	{
		cout << "SI --> NODOALDEANOARQUERO" << endl;
		getYes()->Decision();
	}
	else
	{
		cout << "NO --> NODORECARQUERIA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecArqueria::NodoRecArqueria(DecisionTree* dt):Node(dt)
{
		//yes es null CREAR ARQUERIA 
	//---
		 //Podria pasar que construya granjas como un colgao, porque vale menos.
		 
		 //Poner limite de 5, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
	//--- 
	
		setNo(new NodoGranja(getDT()));
}

void NodoRecArqueria::Decision()
{
	if(getDT()->getRecursos() >= ARQUERIA_COSTE)
	{
		cout << "SI --> HOJA, CREAR ARQUERIA" << endl;
		//CREAR ARQUERIA
		gameEngine::addBuildings(178,193,3,false)->aplicarTextura(getDT()->driver);
		gameEngine::recursos_ia -= ARQUERIA_COSTE;
	}
	else
	{
		cout << "NO --> NODOGRANJA" << endl;
		getNo()->Decision();
	}
}

//-----------------------------------//

NodoRecArquero::NodoRecArquero(DecisionTree* dt) : Node(dt)
{
		//yes es null CREARARQUERO 
	//---
		 //null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		 //intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el arquero. //Probar poniendo la granja a 150
		  
	//---
		//no es null //NADA
		//no = new NodoRecGranja();
}

void NodoRecArquero::Decision()
{
	if(getDT()->getRecursos() >= CONVERTIR_COSTE)
	{
		cout << "SI --> HOJA, CREAR ARQUERO" << endl;
		//CREAR ARQUERO
		vector<shared_ptr<IDibujable>>* unidades = getDT()->IAunits;

		for(int i = 0; i < unidades->size(); i++)
		{
			shared_ptr<battleIA> unit =  std::dynamic_pointer_cast<battleIA>(unidades->at(i));
			
			if(unit->getType() == 0)
			{
				gameEngine::recursos_ia -= CONVERTIR_COSTE;
				gameEngine::addIAUnit(unit->getPosicion().X,unit->getPosicion().Y,3)->aplicarTextura(getDT()->driver);
				unidades->erase(unidades->begin() + i);
				break;
			}
		}
	}
	else
	{
		cout << "NO --> HOJA, NADA" << endl;
	}
}

//-----------------------------------//
