#ifndef __GuardRandom_h_
#define __GuardRandom_h_


#include "Guard.h"

class GuardRandom :public Guard
{
public:
	GuardRandom(void);
	GuardRandom(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& guardName, const Ogre::Vector3& down, const Ogre::Vector3& up);
	virtual ~GuardRandom(void);
	virtual bool nextLocation(void);
	virtual void update(float delay);
private:
	float minX;
	float maxX;
	float minY;
	float maxY;
	Ogre::Vector3 getRandomPosition(void);
};
#endif // #ifndef __GuardRandom_h_
