#ifndef __GuardLine_h_
#define __GuardLine_h_

#include "Guard.h"

class GuardLine :public Guard
{
public:
	GuardLine(void);
	GuardLine(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& guardName, std::deque<Ogre::Vector3>& positions);
	virtual ~GuardLine(void);
	virtual bool nextLocation(void);
	virtual void update(float delay);

};
#endif // #ifndef __GuardLine_h_
