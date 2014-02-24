#ifndef STATEIA_H
#define STATEIA_H

using namespace std;

#include <iostream>
#include "IDibujable.h"
#include "battleIA.h"

class IDibujable;
class battleIA;

class CurrentIA
{
	class StateIA *current;
	public:
		CurrentIA();
		void setCurrent(StateIA *s)
		{
			current = s;
		}
		void buscando();
		void acercarse();
		void atacar();
		void huir();
		void recuperarse();
		bool inicial();
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};

class StateIA
{
	public:
		virtual void buscando(CurrentIA *c)
		{
			//cout << "buscando"<<endl;
		}	
		virtual void acercarse(CurrentIA *c)
		{
			//cout << "acercarse"<<endl;
		}
		virtual void atacar(CurrentIA *c)
		{
			cout << "atacar"<<endl;
		}
		virtual void huir(CurrentIA *c)
		{
			cout << "huir"<<endl;
		}
		virtual void recuperarse(CurrentIA *c)
		{
			cout << "recuperarse"<<endl;
		}
		virtual bool inicial() = 0;

		virtual void doSomething(battleIA* bIA, vector<IDibujable*>* user) = 0;
};

class BUSCANDO: public StateIA
{
	public:
		BUSCANDO();
		virtual ~BUSCANDO()
		{
			//cout << "dtor-BUSCANDO" << endl;
		};
		void acercarse(CurrentIA *c);
		bool inicial(){return true;}
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};

class ACERCARSE: public StateIA
{
	public:
		ACERCARSE();
		virtual ~ACERCARSE()
		{
			//cout << "dtor-ACERCARSE" << endl;
		};
		void buscando(CurrentIA *c);
		void atacar(CurrentIA *c);
		bool inicial(){return false;}
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};

class ATACAR: public StateIA
{
	public:
		ATACAR();
		virtual ~ATACAR()
		{
			cout << "dtor-ATACAR" << endl;
		};
		void buscando(CurrentIA *c);
		void acercarse(CurrentIA *c);
		void huir(CurrentIA *c);
		bool inicial(){return false;}
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};

class HUIR: public StateIA
{
	public:
		HUIR();
		virtual ~HUIR()
		{
			cout << "dtor-HUIR" << endl;
		};
		void recuperarse(CurrentIA *c);
		bool inicial(){return false;}
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};


class RECUPERARSE: public StateIA
{
	public:
		RECUPERARSE();
		virtual ~RECUPERARSE()
		{
			cout << "dtor-RECUPERARSE" << endl;
		};
		void buscando(CurrentIA *c);
		void huir(CurrentIA *c);
		bool inicial(){return false;}
		void doSomething(battleIA* bIA, vector<IDibujable*>* user);
};


#endif
