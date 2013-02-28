#include "GuardFollower.h"

//-------------------------------------------------------------------------------------
GuardFollower::GuardFollower(void)
{

}
//-------------------------------------------------------------------------------------
GuardFollower::~GuardFollower(void)
{
}
//-------------------------------------------------------------------------------------
///Create new guard and scale his sceneNode (little bigger), after that is setted following node (NinjaNode)
GuardFollower::GuardFollower(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName,const Ogre::Vector3& startPosition)
:Guard(sceneManager, guardMesh, guardName, startPosition){
	sceneNode->scale(1.3,1.3,1.3);
	toFollow = sceneManager->getSceneNode("NinjaNode");
}
//-------------------------------------------------------------------------------------
void GuardFollower::update(float delay){
	Guard::update(delay);	
}
//-------------------------------------------------------------------------------------
///This function is setting destination like players actual position
bool GuardFollower::nextLocation(void){
	mDestination = toFollow->getPosition();
    mDirection = mDestination - sceneNode->getPosition();
    mDistance = mDirection.normalise();
	return true;
}
//-------------------------------------------------------------------------------------