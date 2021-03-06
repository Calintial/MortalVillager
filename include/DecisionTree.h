#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "IDibujable.h"
#include "gameEngine.h"

#include <vector>
#include <iostream>

using namespace std;

const int ALDEANO_COSTE = 100;
const int GRANJA_COSTE = 400;
const int CUARTEL_COSTE = 600;
const int ARQUERIA_COSTE = 600;
const int LANCERIA_COSTE = 600;
const int CONVERTIR_COSTE = 300;

class Node;

class DecisionTree
{	
	public:
		DecisionTree(video::IVideoDriver*);
		void doDecision(int vidaCC, int recursos, vector<shared_ptr<IDibujable>>* IAunits, vector<shared_ptr<IDibujable>>* Userunits, vector<shared_ptr<IDibujable>>* buildings);
		//48x29 desde x=0, y=0 para user, y x=351, y=370 para ia
		bool ExisteEnemigoCercaCC(vector<shared_ptr<IDibujable>>* Userunits);
		
		Node* getRaiz(){ return raiz;};
		
		bool isEnemigoCercaCC(){ return enemigoCercaCC;};
		void setEnemigoCercaCC(bool CercaCC){this->enemigoCercaCC = CercaCC;};
		int getVidaCC(){ return vidaCC;};
		void setVidaCC(int vidaCC){ this->vidaCC = vidaCC;};
		int getnumAldeanos(){ return numAldeanos;};
		void setIncNumAldeanos(){ this->numAldeanos++;};
		
		int getnumLanceros(){ return numLanceros;};
		void setIncNumLanceros(){ this->numLanceros++;};
		int getnumEspadachines(){ return numEspadachines;};
		void setIncNumEspadachines(){ this->numEspadachines++;};
		int getnumArqueros(){ return numArqueros;};
		void setIncNumArqueros(){ this->numArqueros++;};
		int getnumSoldados(){ return numLanceros+numEspadachines+numArqueros;};
		
		int getnumLancerosEnemigos(){ return numLancerosEnemigos;};
		void setIncNumLancerosEnemigos(){ this->numLancerosEnemigos++;};
		int getnumEspadachinesEnemigos(){ return numEspadachinesEnemigos;};
		void setIncNumEspadachinesEnemigos(){ this->numEspadachinesEnemigos++;};
		int getnumArquerosEnemigos(){ return numArquerosEnemigos;};
		void setIncNumArquerosEnemigos(){ this->numArquerosEnemigos++;};
		int getnumSoldadosEnemigos(){ return numLancerosEnemigos+numEspadachinesEnemigos+numArquerosEnemigos;};
		
		bool isCuartel(){ return cuartel;};
		void setCuartel(bool cuartel){this->cuartel = cuartel;};
		bool isArqueria(){ return arqueria;};
		void setArqueria(bool arqueria){this->arqueria = arqueria;};
		bool isLanceria(){ return lanceria;};
		void setLanceria(bool lanceria){this->lanceria = lanceria;};
		int isGranja(){ return granja;};
		void setGranja(bool granja){ this->granja = granja;};
		
		int getRecursos(){ return recursos;};
		void setRecursos(int recursos){this->recursos = recursos;};

		video::IVideoDriver* driver;
		vector<shared_ptr<IDibujable>>* IAunits;
		vector<shared_ptr<IDibujable>>* Userunits;
		vector<shared_ptr<IDibujable>>* buildings;
		
		vector<int> caminoNodos;
		
	private:
		Node* raiz;
		
		bool enemigoCercaCC;
		int vidaCC;
		int numLanceros;
		int numEspadachines;
		int numArqueros;
		int numAldeanos;
		int numLancerosEnemigos;
		int numEspadachinesEnemigos;
		int numArquerosEnemigos;
		bool cuartel;
		bool arqueria;
		bool lanceria;
		bool granja;
		int recursos;
};

class Node
{	
	public:
		Node(DecisionTree* dt);
		virtual void Decision(){};
		virtual DecisionTree* getDT(){return dt;};
		virtual void setYes(Node* y){yes = y;};
		virtual Node* getYes(){return yes;};
		virtual void setNo(Node* n){no = n;};
		virtual Node* getNo(){return no;};
		
	private:
		Node* yes;
		Node* no;
		//Puntero a decision Tree
		DecisionTree* dt;
};


//¿Enemigo cerca de mi CC?
class NodoEnemigoCercaCC: public Node
{
	public:
		NodoEnemigoCercaCC(DecisionTree* dt);
		void Decision();
};

//¿Vida CC < X
class NodoVidaCC: public Node
{
	public:
		NodoVidaCC(DecisionTree* dt);
		void Decision();
};

//¿Tengo mas de X soldados?
class NodoTengoSoldados: public Node
{
	public:
		NodoTengoSoldados(DecisionTree* dt);
		void Decision();
};

//¿Usuario tiene superioridad?
//Simple --> mi_ejercito > su_ejercito*1.5 || mi_ejercito es enorme
class NodoUsuarioSuperioridad: public Node
{
	public:
		NodoUsuarioSuperioridad(DecisionTree* dt);
		void Decision();
};

//¿Lanzas enemigas > Mis Espadas?
class NodoLanzasMayorEspadas: public Node
{
	public:
		NodoLanzasMayorEspadas(DecisionTree* dt);
		void Decision();
};

//¿Cuartel?
class NodoCuartel: public Node
{
	public:
		NodoCuartel(DecisionTree* dt);
		void Decision();
};

//¿Granja?
class NodoGranja: public Node
{
	public:
		NodoGranja(DecisionTree* dt);
		void Decision();
};

//¿Aldeano --> Que podria ser espadachin?
class NodoAldeanoEspadachin: public Node
{
	public:
		NodoAldeanoEspadachin(DecisionTree* dt);
		void Decision();
};

//¿Aldeano --> Que podria ser lancero?
class NodoAldeanoLancero: public Node
{
	public:
		NodoAldeanoLancero(DecisionTree* dt);
		void Decision();
};

//¿Aldeano --> Que podria ser arquero?
class NodoAldeanoArquero: public Node
{
	public:
		NodoAldeanoArquero(DecisionTree* dt);
		void Decision();
};

//¿Recursos para aldeano?
class NodoRecAldeano: public Node
{
	public:
		NodoRecAldeano(DecisionTree* dt);
		void Decision();
};

//¿Recursos para convertir aldeano en espadachin?
class NodoRecEspadachin: public Node
{
	public:
		NodoRecEspadachin(DecisionTree* dt);
		void Decision();
};

//¿Recursos para construir cuartel?
class NodoRecCuartel: public Node
{
	public:
		NodoRecCuartel(DecisionTree* dt);
		void Decision();
};

//¿Recursos para granja?
class NodoRecGranja: public Node
{
	public:
		NodoRecGranja(DecisionTree* dt);
		void Decision();
};

//¿Arqueros enemigos > Mis Lanceros?
class NodoArquerosMayorLanzas: public Node
{
	public:
		NodoArquerosMayorLanzas(DecisionTree* dt);
		void Decision();
};

//¿Lanceria?
class NodoLanceria: public Node
{
	public:
		NodoLanceria(DecisionTree* dt);
		void Decision();
};

//¿Recursos para construir lanceria?
class NodoRecLanceria: public Node
{
	public:
		NodoRecLanceria(DecisionTree* dt);
		void Decision();
};

//¿Recursos para convertir aldeano en lancero?
class NodoRecLancero: public Node
{
	public:
		NodoRecLancero(DecisionTree* dt);
		void Decision();
};

//¿Espadachines enemigos > Mis Arqueros?
class NodoEspadachinesMayorArcos: public Node
{
	public:
		NodoEspadachinesMayorArcos(DecisionTree* dt);
		void Decision();
};

//¿Arqueria?
class NodoArqueria: public Node
{
	public:
		NodoArqueria(DecisionTree* dt);
		void Decision();
};

//¿Recursos para construir arqueria?
class NodoRecArqueria: public Node
{
	public:
		NodoRecArqueria(DecisionTree* dt);
		void Decision();
};

//¿Recursos para convertir aldeano en arquero?
class NodoRecArquero: public Node
{
	public:
		NodoRecArquero(DecisionTree* dt);
		void Decision();
};

#endif
