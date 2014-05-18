#include "DecisionTree.h"

DecisionTree::DecisionTree()
{
	raiz = new NodoEnemigoCercaCC();
}

void DecisionTree::PasarDatos(int vidaCC, int recursos, vector<IDibujable*>* IAunits, vector<IDibujable*>* Userunits, vector<IDibujable*>* buildings)
{
	setVidaCC(vidaCC);
	setRecursos(recursos);
	
	for(IDibujable* ia: IAUnits)
	{
		
	}
	
	for(IDibujable* user: Userunits)
	{
		
	}
	
	//0 --> CC
	for(IDibujable* b: buildings)
	{
		
	}
		/*
		void setnumLanceros(int numLanceros){ this.numLanceros = numLanceros;};
		void setnumEspadachines(int numEspadachines){ this.numEspadachines = numEspadachines;};
		void setnumArqueros(int numArqueros){ this.numArqueros = numArqueros;};
		void setnumAldeanos(int numAldeanos){ this.numAldeanos = numAldeanos;};

		void setnumLancerosEnemigos(int numLancerosEnemigos){ this.numLancerosEnemigos = numLancerosEnemigos;};
		void setnumEspadachinesEnemigos(int numEspadachinesEnemigos){ this.numEspadachinesEnemigos = numEspadachinesEnemigos;};
		void setnumArquerosEnemigos(int numArquerosEnemigos){ this.numArquerosEnemigos = numArquerosEnemigos;};

		void setCuartel(boolean cuartel){this.cuartel = cuartel;};
		void setArqueria(boolean arqueria){this.arqueria = arqueria;};
		void setLanceria(boolean lanceria){this.lanceria = lanceria;};
		
		void setEnemigoCercaCC(boolean enemigoCercaCC){this.enemigoCercaCC = enemigoCercaCC;};*/
}

boolean DecisionTree::ExisteEnemigoCercaCC(IDibujable* building, vector<IDibujable*>* IAUnits)
{
	
	
}


//-----------------------------------//

NodoEnemigoCercaCC::NodoEnemigoCercaCC()
{
		yes = new NodoVidaCC();
		no = new NodoLanzasMayorEspadas();
}

void NodoEnemigoCercaCC::Decision()
{
	
}

//-----------------------------------//

NodoVidaCC::NodoVidaCC()
{
		yes = new NodoTengoSoldados();
		no = new NodoUsuarioSuperioridad();
}

void NodoVidaCC::Decision()
{
	
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
	
}

//-----------------------------------//

NodoUsuarioSuperioridad::NodoUsuarioSuperioridad()
{
		yes = new NodoLanzasMayorEspadas();
		no = null; //PASAR A ATACAR
}

void NodoUsuarioSuperioridad::Decision()
{
	
}

//-----------------------------------//

NodoLanzasMayorEspadas::NodoLanzasMayorEspadas()
{
		yes = new NodoCuartel(); 
		no = new NodoArquerosMayorLanzas();
}

void NodoLanzasMayorEspadas::Decision()
{
	
}

//-----------------------------------//

NodoCuartel::NodoCuartel()
{
		yes = new NodoAldeano(); 
		no = new NodoRecCuartel();
}

void NodoCuartel::Decision()
{
	
}

//-----------------------------------//

NodoAldeano::NodoAldeano()
{
		yes = new NodoRecEspadachin(); 
		no = new NodoRecAldeano();
}

void NodoAldeano::Decision()
{
	
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
	
}

//-----------------------------------//

NodoRecGranja::NodoRecGranja()
{
		yes = null; // CREAR GRANJA 
		no = null; // NADA
}

void NodoRecGranja::Decision()
{
	
}

//-----------------------------------//

NodoArquerosMayorLanzas::NodoArquerosMayorLanzas()
{
		yes = new NodoLanceria();
		no = new NodoEspadachinesMayorArcos();
}

void NodoArquerosMayorLanzas::Decision()
{
	
}

//-----------------------------------//

NodoLanceria::NodoLanceria()
{
		yes = new NodoAldeano(); 
		no = new NodoRecLanceria();
}

void NodoLanceria::Decision()
{
	
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
	
}

//-----------------------------------//

NodoEspadachinesMayorArcos::NodoEspadachinesMayorArcos()
{
		yes = new NodoArqueria(); 
		no = null; //PASAR A MODO ATACAR
}

void NodoEspadachinesMayorArcos::Decision()
{
	
}

//-----------------------------------//

NodoArqueria::NodoArqueria()
{
		yes = new NodoAldeano(); 
		no = new NodoRecArqueria();
}

void NodoArqueria::Decision()
{
	
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
	
}

//-----------------------------------//
