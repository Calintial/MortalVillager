#include "DecisionTree.h"

DecisionTree::DecisionTree()
{
	raiz = new NodoEnemigoCercaCC();
	
	enemigoCercaCC =false;
	vidaCC = 0;
	numLanceros = 0;
	numEspadachines = 0;
	numArqueros = 0;
	numAldeanos = 0;
	numLancerosEnemigos = 0;
	numEspadachinesEnemigos = 0;
	numArquerosEnemigos = 0;
	Cuartel = false;
	Arqueria = false;
	Lanceria = false;
	granjas = 0;
	recursos = 0;
}

void DecisionTree::PasarDatos(int vidaCC, int recursos, vector<IDibujable*>* IAunits, vector<IDibujable*>* Userunits, vector<IDibujable*>* buildings)
{
	setVidaCC(vidaCC);
	setRecursos(recursos);
	
	//0 --> Aldeano
	//1 --> Arquero
	//2 --> Espadachin
	//3 --> Lancero
	
	for(IDibujable* ia: IAUnits)
	{
		if(ia->getType() == 1)
			setIncNumArquerosEnemigos();
		if(ia->getType() == 2)
			setIncNumEspadachinesEnemigos();
		if(ia->getType() == 3)
			setIncNumLancerosEnemigos();
	}
	
	for(IDibujable* user: Userunits)
	{
		if(user->getType() == 0)
			setIncNumAldeanos();
		if(user->getType() == 1)
			setIncNumArqueros();
		if(user->getType() == 2)
			setIncNumEspadachines();
		if(uesr->getType() == 3)
			setIncNumLanceros();
	}
	
	//0 --> CC
	//1 --> Granja
	//2 --> Cuartel
	//3 --> Arqueria
	//4 --> Lanceria
	for(IDibujable* b: buildings)
	{
		if(b->getClase()==0)
			setEnemigoCercaCC(ExisteEnemigoCercaCC(Userunits));
		if(b->getClase()==1)
			setIncGranjas();
		if(b->getClase()==2)
			setCuartel(true);
		if(b->getClase()==3)
			setArqueria(true);
		if(b->getClase()==4)
			setLanceria(true);
	}
}

//48x29 x=351, y=370 para ia
boolean DecisionTree::ExisteEnemigoCercaCC(vector<IDibujable*>* Userunits)
{
	for(IDibujable* user: Userunits)
	{
		if(user->getPosition().X > 350 && user->getPosition() > 369)
			return true;
	}
	
	return false;
}


//-----------------------------------//

NodoEnemigoCercaCC::NodoEnemigoCercaCC()
{
		yes = new NodoVidaCC();
		no = new NodoLanzasMayorEspadas();
}

void NodoEnemigoCercaCC::Decision()
{
	if(isEnemigoCercaCC())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoVidaCC::NodoVidaCC()
{
		yes = new NodoTengoSoldados();
		no = new NodoUsuarioSuperioridad();
}

void NodoVidaCC::Decision()
{
	if(getVidaCC()<30)
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoTengoSoldados::NodoTengoSoldados()
{
		//PASAR A ESTADO DEFENDER EN LOS DOS CASOS
		yes = null; 
		no = new NodoLanzasMayorEspadas(); 
}

void NodoTengoSoldados::Decision()
{
	//Hay que poner estados en algun lao y cambiarlo aqui a DEFENDER
	if(getnumSoldados()<getnumSoldadosEnemigos())
		no.Decision();
}

//-----------------------------------//

//Simple --> mi_ejercito > su_ejercito*1.5 || mi_ejercito es enorme
//COMPLEJA --> hay que hacer algo con el triangulo de armas
NodoUsuarioSuperioridad::NodoUsuarioSuperioridad()
{
		yes = null; //PASAR A ATACAR
		no = new NodoLanzasMayorEspadas();
}

void NodoUsuarioSuperioridad::Decision()
{
	if(getnumSoldados() > getnumSoldadosEnemigos()*1.5 || getnumSoldados()>10)
		//Hay que poner estados en algun lao y cambiarlo aqui a ATACAR
	else
		no.Decision();
}

//-----------------------------------//

NodoLanzasMayorEspadas::NodoLanzasMayorEspadas()
{
		yes = new NodoCuartel(); 
		no = new NodoArquerosMayorLanzas();
}

//¿Lanzas enemigas > Mis Espadas?
void NodoLanzasMayorEspadas::Decision()
{
	if(getnumLancerosEnemigos()>getnumEspadachines())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoCuartel::NodoCuartel()
{
		yes = new NodoAldeano(); 
		no = new NodoRecCuartel();
}

void NodoCuartel::Decision()
{
	if(isCuartel())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoAldeano::NodoAldeano()
{
		yes = new NodoRecEspadachin(); 
		no = new NodoRecAldeano();
}

void NodoAldeano::Decision()
{
	if(getnumAldeanos()>=1)
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoRecAldeano::NodoRecAldeano()
{
		yes = null; // CREAR ALDEANO 
		no = null;
		//no = new NodoRecGranja();
}

void NodoRecAldeano::Decision()
{
	if(getRecursos() >= ALDEANO_COSTE)
		//CREAR ALDEANO
}

//-----------------------------------//

NodoRecEspadachin:NodoRecEspadachin()
{
		yes = null; //CREAR ESPADACHIN 
		
		/*
		 * null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		 * intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el espadachin. //Probar poniendo la granja a 150
		 *  
		*/
		no = null; //NADA
		//no = new NodoRecGranja();
}

void NodoRecEspadachin::Decision()
{
	if(getRecursos() >= CONVERTIR_COSTE)
		//CREAR ESPADACHIN
}

//-----------------------------------//

NodoRecCuartel::NodoRecCuartel()
{
		yes = null; //CREAR CUARTEL
		/*
		 * Podria pasar que construya granjas como un colgao, porque vale menos.
		 * 
		 * Poner limite de 5, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
		*/ 
		no = new NodoRecGranja();
}

void NodoRecCuartel::Decision()
{
	if(getRecursos() >= CUARTEL_COSTE)
		//CREAR CUARTEL
	else
		no.Decision();
}

//-----------------------------------//

NodoRecGranja::NodoRecGranja()
{
		yes = null; // CREAR GRANJA 
		no = null; // NADA
}

void NodoRecGranja::Decision()
{
	if(getRecursos() >= GRANJA_COSTE)
		//CREAR GRANJA
}

//-----------------------------------//

//¿Arqueros enemigos > Mis Lanceros?
NodoArquerosMayorLanzas::NodoArquerosMayorLanzas()
{
		yes = new NodoLanceria();
		no = new NodoEspadachinesMayorArcos();
}

void NodoArquerosMayorLanzas::Decision()
{
	if(getnumArquerosEnemigos()>getnumLanceros())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoLanceria::NodoLanceria()
{
		yes = new NodoAldeano(); 
		no = new NodoRecLanceria();
}

void NodoLanceria::Decision()
{
	if(isLanceria())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoRecLanceria::NodoRecLanceria()
{
		yes = null; //CREAR LANCERIA 
		/*
		 * Podria pasar que construya granjas como un colgao, porque vale menos.
		 * 
		 * Poner limite de 5, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
		*/ 
		no = new NodoRecGranja();
}

void NodoRecLanceria::Decision()
{
	if(getRecursos() >= LANCERIA_COSTE)
		//CREAR LANCERIA
	else
		no.Decision();
}

//-----------------------------------//

NodoRecLancero::NodoRecLancero()
{
		yes = null; //CREAR LANCERO
		
		/*
		 * null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		 * intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el lancero. //Probar poniendo la granja a 150
		 *  
		*/
		no = null; //NADA
		//no = new NodoRecGranja();
}

void NodoRecLancero::Decision()
{
	if(getRecursos() >= CONVERTIR_COSTE)
		//CREAR LANCERO
}

//-----------------------------------//

NodoEspadachinesMayorArcos::NodoEspadachinesMayorArcos()
{
		yes = new NodoArqueria(); 
		no = null; //PASAR A MODO ATACAR
}

//¿Espadachines enemigos > Mis Arqueros?
void NodoEspadachinesMayorArcos::Decision()
{
	if(getnumEspadachinesEnemigos()>getnumArqueros())
		yes.Decision();
	else
		//PASAR A MODO ATACAR
}

//-----------------------------------//

NodoArqueria::NodoArqueria()
{
		yes = new NodoAldeano(); 
		no = new NodoRecArqueria();
}

void NodoArqueria::Decision()
{
	if(isArqueria())
		yes.Decision();
	else
		no.Decision();
}

//-----------------------------------//

NodoRecArqueria::NodoRecArqueria()
{
		yes = null; //CREAR ARQUERIA 
		/*
		 * Podria pasar que construya granjas como un colgao, porque vale menos.
		 * 
		 * Poner limite de 5, aun así, podria construir las 5 granjas y luego ya el resto de cosas 
		*/ 
		no = new NodoRecGranja();
}

void NodoRecArqueria::Decision()
{
	if(getRecursos() >= ARQUERIA_COSTE)
		//CREAR ARQUERIA
	else
		no.Decision();
}

//-----------------------------------//

NodoRecArquero::NodoRecArquero()
{
		yes = null;//CREARARQUERO 
		/*
		 * null --> Podria pasar que el usuario siempre tenga mas de algo, y no se construya nunca granja
		 * intento construir granja --> Nunca pasara, porque la granja vale mas cara,que el arquero. //Probar poniendo la granja a 150
		 *  
		*/
		no = null; //NADA
		//no = new NodoRecGranja();
}

void NodoRecArquero::Decision()
{
	if(getRecursos() >= CONVERTIR_COSTE)
		//CREAR ARQUERO
}

//-----------------------------------//
