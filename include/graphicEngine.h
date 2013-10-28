// Facade pattern to separate graphic engine from the rest of the game
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

class graphicEngine {
public:
	graphicEngine();
	~graphicEngine() {};
	graphicEngine(const graphicEngine&) {};
	graphicEngine& operator=(const graphicEngine&) {};
	bool updateOnce();

private:
	IrrlichtDevice * device;
	ISceneManager * smgr;
	IVideoDriver * driver;
	ISceneNode * node;
};