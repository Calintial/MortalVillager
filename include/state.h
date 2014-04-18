#ifndef STATE_H
#define STATE_H

using namespace std;

#include <iostream>
#include "gameEngine.h"
#include "graphicEngine.h"
#include "intelEngine.h"

class gameEngine;
class graphicEngine;
class intelEngine;

class Current
{
	class State *current;
	public:
		Current();
		void setCurrent(State *s)
		{
			current = s;
		}
		void main();
		void ingame();
		void pause();
		void finish();
		bool inicial();
		bool sfinal();
		bool is_ingame();
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa);
};

class State
{
	public:
		virtual void main(Current *c)
		{
			cout << "main"<<endl;
		}	
		virtual void ingame(Current *c)
		{
			cout << "ingame"<<endl;
		}
		virtual void pause(Current *c)
		{
			cout << "pause"<<endl;
		}
		virtual void finish(Current *c)
		{
			cout << "finish"<<endl;
		}

		virtual bool is_ingame() = 0;

		virtual bool inicial() = 0;

		virtual bool sfinal() = 0;

		virtual void doSomething(gameEngine* ge,graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa)
		{
		}
};

class MAINS: public State
{
	public:
		MAINS();
		virtual ~MAINS()
		{
			cout << "dtor-MAINS" << endl;
		};
		void ingame(Current *c);
		void finish(Current *c);
		bool inicial(){return true;}
		bool sfinal(){return false;}
		bool is_ingame(){return false;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa);
};

class INGAME: public State
{
	public:
		INGAME();
		virtual ~INGAME()
		{
			cout << "dtor-INGAME" << endl;
		};
		void pause(Current *c);
		bool inicial(){return false;}
		bool sfinal(){return false;}
		void finish(Current *c);
		bool is_ingame(){return true;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa);
};

class PAUSE: public State
{
	public:
		PAUSE();
		virtual ~PAUSE()
		{
			cout << "dtor-PAUSE" << endl;
		};
		void ingame(Current *c);
		void finish(Current *c);
		bool inicial(){return false;}
		bool sfinal(){return false;}
		bool is_ingame(){return false;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia, std::shared_ptr<mapa2D> mapa);
};

class FINISH: public State
{
	public:
		FINISH()
		{
			cout << "FINISH-ctor " << endl;
		};
		virtual ~FINISH()
		{
			cout << "dtor-FINISH" << endl;
		};
		bool inicial(){return false;}
		bool sfinal(){return true;}
		bool is_ingame(){return false;}
};

#endif
