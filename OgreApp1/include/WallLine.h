#ifndef __WallLine_h_
#define __WallLine_h_

#include <string>
#include <vector>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include "Wall.h"


enum MyDirection {Left, Right, Front, Back};

class WallLine
{

public:
	WallLine(Ogre::SceneManager* manager, const int x, const int y, const Ogre::Vector2& v, const MyDirection& m);
	~WallLine(void);

protected:
	std::vector<std::shared_ptr<Wall>> wallVector;
	std::string genRandom( const size_t length);
};

#endif // #ifndef __WallLine_h_

