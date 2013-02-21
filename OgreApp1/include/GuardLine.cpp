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
GuardLine::GuardLine(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& guardName, std::deque<Ogre::Vector3>& positions){
	manager = sceneManager;
	name=guardName;
	mesh=guardMesh; //mesh of guards SceneNode (in this case is robot1.mesh)
	entity = manager->createEntity(name,mesh);
	mWalkList= positions;
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", mWalkList.front());
	entity->setCastShadows(true);
	sceneNode->attachObject(entity);
	mAnimationState = entity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
	sceneNode->scale(1.1,1.1,1.1); //bigger .1
	mDirection= Ogre::Vector3(0,0,0);
}
//-------------------------------------------------------------------------------------
///Calling base update
void GuardLine::update(const float delay){
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