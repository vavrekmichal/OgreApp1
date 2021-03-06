#ifndef __WallLine_h_
#define __WallLine_h_

#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include "Wall.h"
#include <vector>

enum MyDirection {Left, Right, Front, Back};

class WallLine
{

public:
	WallLine(Ogre::SceneManager* manager, int x, int y, const Ogre::Vector2& v, const MyDirection& m);
	~WallLine(void);

protected:
	std::vector<std::shared_ptr<Wall>> wallVector;
	std::string genRandom( size_t length);
	const int blockLength;
};

#endif // #ifndef __WallLine_h_

