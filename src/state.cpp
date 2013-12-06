void Current::main()
{
  current->main(this);
}

void Current::ingame()
{
  current->ingame(this);
}

void Current::pause()
{
  current->pause(this);
}

void Current::finish()
{
  current->finish(this);
}

//---MAINS--/
void MAINS::ingame(Current *c)
{
  cout << "cambio de MAINS a INGAME";
  c->setCurrent(new INGAME());
  delete this;
}

void MAINS::finish(Current *c)
{
  cout << "cambio de MAINS a FINISH";
  c->setCurrent(new FINISH());
  delete this;
}

//---INGAME--/
void INGAME::pause(Current *c)
{
  cout << "cambio de INGAME a PAUSE";
  c->setCurrent(new PAUSE());
  delete this;
}

//--PAUSE--//
void MAINS::ingame(Current *c)
{
  cout << "cambio de PAUSE a INGAME";
  c->setCurrent(new INGAME());
  delete this;
}

void PAUSE::finish(Current *c)
{
  cout << "cambio de PAUSE a FINISH";
  c->setCurrent(new FINISH());
  delete this;
}

//--FINISH--//


