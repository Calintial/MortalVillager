#ifndef STATE_H
#define STATE_H

using namespace std;

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
};

class MAINS: public State
{
  public:
    MAINS()
    {
        cout << "MAINS-ctor " << endl;
    };
    ~MAINS()
    {
        cout << "dtor-MAINS" << endl;
    };
    void ingame(Current *c);
    void finish(Current *c);
};

class INGAME: public State
{
  public:
    INGAME()
    {
        cout << "INGAME-ctor " << endl;
    };
    ~INGAME()
    {
        cout << "dtor-INGAME" << endl;
    };
    void pause(Current *c);
};

class PAUSE: public State
{
  public:
    PAUSE()
    {
        cout << "PAUSE-ctor " << endl;
    };
    ~PAUSE()
    {
        cout << "dtor-PAUSE" << endl;
    };
    void ingame(Current *c);
    void finish(Current *c);
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
};

#endif
