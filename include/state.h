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
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia);
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
		virtual bool inicial() = 0;

		virtual bool sfinal() = 0;

		virtual void doSomething(gameEngine* ge,graphicEngine* graphics, intelEngine* ia)
		{
		}
};

class MAINS: public State
{
	public:
		MAINS();
		~MAINS()
		{
			cout << "dtor-MAINS" << endl;
		};
		void ingame(Current *c);
		void finish(Current *c);
		bool inicial(){return true;}
		bool sfinal(){return false;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia);
};

class INGAME: public State
{
	public:
		INGAME();
		~INGAME()
		{
			cout << "dtor-INGAME" << endl;
		};
		void pause(Current *c);
		bool inicial(){return false;}
		bool sfinal(){return false;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia);
};

class PAUSE: public State
{
	public:
		PAUSE();
		~PAUSE()
		{
			cout << "dtor-PAUSE" << endl;
		};
		void ingame(Current *c);
		void finish(Current *c);
		bool inicial(){return false;}
		bool sfinal(){return false;}
		void doSomething(gameEngine* ge, graphicEngine* graphics, intelEngine* ia);
};

class FINISH: public State
{
	public:
		FINISH()
		{
			cout << "FINISH-ctor " << endl;
		};
		~FINISH()
		{
			cout << "dtor-FINISH" << endl;
		};
		bool inicial(){return false;}
		bool sfinal(){return true;}
};

#endif
