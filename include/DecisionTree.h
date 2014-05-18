#ifndef DECISIONTREE_H
#define DECISIONTREE_H

using namespace std;

#include <iostream>

class DecisionTree
{
	#define ALDEANO_COSTE 100;
	#define GRANJA_COSTE 400;
	#define CUARTEL_COSTE 600;
	#define ARQUERIA_COSTE 600;
	#define LANCERIA_COSTE 600;
	#define CONVERTIR_COSTE 300;
	
	public:
		DecisionTree();
		void PasarDatos(int vidaCC, int recursos, vector<IDibujable*>* IAunits, vector<IDibujable*>* Userunits, vector<IDibujable*>* buildings);
		//48x29 desde x=0, y=0 para user, y x=351, y=370 para ia
		boolean ExisteEnemigoCercaCC(IDibujable* building, vector<IDibujable*>* IAUnits);
		
		Node getRaiz(){ return raiz;};
		boolean isEnemigoCercaCC(){ return enemigoCercaCC;};
		void setEnemigoCercaCC(boolean enemigoCercaCC){this.enemigoCercaCC = enemigoCercaCC;};
		int getVidaCC(){ return vidaCC;};
		void setVidaCC(int vidaCC){ this.vidaCC = vidaCC;};
		int getnumLanceros(){ return numLanceros;};
		void setnumLanceros(int numLanceros){ this.numLanceros = numLanceros;};
		int getnumEspadachines(){ return numEspadachines;};
		void setnumEspadachines(int numEspadachines){ this.numEspadachines = numEspadachines;};
		int getnumArqueros(){ return numArqueros;};
		void setnumArqueros(int numArqueros){ this.numArqueros = numArqueros;};
		int getnumAldeanos(){ return numAldeanos;};
		void setnumAldeanos(int numAldeanos){ this.numAldeanos = numAldeanos;};
		int getnumLancerosEnemigos(){ return numLancerosEnemigos;};
		void setnumLancerosEnemigos(int numLancerosEnemigos){ this.numLancerosEnemigos = numLancerosEnemigos;};
		int getnumEspadachinesEnemigos(){ return numEspadachinesEnemigos;};
		void setnumEspadachinesEnemigos(int numEspadachinesEnemigos){ this.numEspadachinesEnemigos = numEspadachinesEnemigos;};
		int getnumArquerosEnemigos(){ return numArquerosEnemigos;};
		void setnumArquerosEnemigos(int numArquerosEnemigos){ this.numArquerosEnemigos = numArquerosEnemigos;};
		boolean isCuartel(){ return Cuartel;};
		void setCuartel(boolean cuartel){this.cuartel = cuartel;};
		boolean isArqueria(){ return Arqueria;};
		void setArqueria(boolean arqueria){this.arqueria = arqueria;};
		boolean isLanceria(){ return Lanceria;};
		void setLanceria(boolean lanceria){this.lanceria = lanceria;};
		int getRecursos(){ return recursos;};
		void setRecursos(int recursos){this.recursos = recursos;};
		
	private:
		Node raiz;
		
		boolean enemigoCercaCC;
		int vidaCC;
		int numLanceros;
		int numEspadachines;
		int numArqueros;
		int numAldeanos;
		int numLancerosEnemigos;
		int numEspadachinesEnemigos;
		int numArquerosEnemigos;
		boolean Cuartel;
		boolean Arqueria;
		boolean Lanceria;
		int recursos;
}

class Node
{
	public:
		Node();
		virtual void Decision() = 0;
		
	private:
		Node yes;
		Node no;
		//Puntero a decision Tree
		
}

//¿Enemigo cerca de mi CC?
class NodoEnemigoCercaCC: public Node
{
	public:
		NodoEnemigoCercaCC();
		void Decision();
}

//¿Vida CC < X
class NodoVidaCC: public Node
{
	public:
		NodoVidaCC();
		void Decision();
}

//¿Tengo mas de X soldados?
class NodoTengoSoldados: public Node
{
	public:
		NodoTengoSoldados();
		void Decision();
}

//¿Usuario tiene superioridad?
//Simple --> mi_ejercito > su_ejercito*1.5 || mi_ejercito es enorme
class NodoUsuarioSuperioridad: public Node
{
	public:
		NodoEnemigoSuperioridad();
		void Decision();
}

//¿Lanzas enemigas > Mis Espadas?
class NodoLanzasMayorEspadas: public Node
{
	public:
		NodoLanzasMayorEspadas();
		void Decision();
}

//¿Cuartel?
class NodoCuartel: public Node
{
	public:
		NodoCuartel();
		void Decision();
}

//¿Aldeano?
class NodoAldeano: public Node
{
	public:
		NodoAldeano();
		void Decision();
}

//¿Recursos para aldeano?
class NodoRecAldeano: public Node
{
	public:
		NodoRecAldeano();
		void Decision();
}

//¿Recursos para convertir aldeano en espadachin?
class NodoRecEspadachin: public Node
{
	public:
		NodoRecSoldados();
		void Decision();
}

//¿Recursos para construir cuartel?
class NodoRecCuartel: public Node
{
	public:
		NodoRecCuartel();
		void Decision();
}

//¿Recursos para granja?
class NodoRecGranja: public Node
{
	public:
		NodoRecGranja();
		void Decision();
}

//¿Arqueros enemigos > Mis Lanceros?
class NodoArquerosMayorLanzas: public Node
{
	public:
		NodoLanzasMayorEspadas();
		void Decision();
}

//¿Lanceria?
class NodoLanceria: public Node
{
	public:
		NodoLanceria();
		void Decision();
}

//¿Recursos para construir lanceria?
class NodoRecLanceria: public Node
{
	public:
		NodoRecLanceria();
		void Decision();
}

//¿Recursos para convertir aldeano en lancero?
class NodoRecLancero: public Node
{
	public:
		NodoRecLancero();
		void Decision();
}

//¿Espadachines enemigos > Mis Arqueros?
class NodoEspadachinesMayorArcos: public Node
{
	public:
		NodoEspadasMayorArcos();
		void Decision();
}

//¿Arqueria?
class NodoArqueria: public Node
{
	public:
		NodoArqueria();
		void Decision();
}

//¿Recursos para construir arqueria?
class NodoRecArqueria: public Node
{
	public:
		NodoRecArqueria();
		void Decision();
}

//¿Recursos para convertir aldeano en arquero?
class NodoRecArquero: public Node
{
	public:
		NodoRecArquero();
		void Decision();
}
