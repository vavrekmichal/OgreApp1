#ifndef __GuardFollower_h_
#define __GuardFollower_h_


#include "Guard.h"

class GuardFollower :public Guard
{
public:
	GuardFollower(void);
	GuardFollower(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName,const Ogre::Vector3& startPosition);
	virtual ~GuardFollower(void);
	virtual bool nextLocation(void);
	virtual void update(float delay);
private:
	Ogre::SceneNode* toFollow; //in this case it is playes (his SceneNode)
};
#endif // #ifndef __GuardFollower_h_
