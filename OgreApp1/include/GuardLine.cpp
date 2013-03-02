#include "GuardLine.h"

//-------------------------------------------------------------------------------------
GuardLine::GuardLine(void)
{
}
//-------------------------------------------------------------------------------------
GuardLine::~GuardLine(void)
{
}
//-------------------------------------------------------------------------------------
///The constructor create new guard with his own mWalkList and scale his SceneNode (little bigger)
GuardLine::GuardLine(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& guardName, std::deque<Ogre::Vector3>& positions)
	:Guard(sceneManager, guardMesh, guardName, positions)
{
	sceneNode->scale(1.1,1.1,1.1); //bigger .1
}
//-------------------------------------------------------------------------------------
///Calling base update
void GuardLine::update(float delay){
	Guard::update(delay);	
}
//-------------------------------------------------------------------------------------
///The function checking mWalkList and just remove from front
bool GuardLine::nextLocation(void){
	if (mWalkList.empty()){
		return false;
	}
	mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque
    mDirection = mDestination - sceneNode->getPosition();
    mDistance = mDirection.normalise();
	return true;
}
//-------------------------------------------------------------------------------------