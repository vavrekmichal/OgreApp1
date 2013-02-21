#include "GuardRandom.h"

//-------------------------------------------------------------------------------------
GuardRandom::GuardRandom(void)
{
}

//-------------------------------------------------------------------------------------
GuardRandom::~GuardRandom(void)
{
}
//-------------------------------------------------------------------------------------
///Using base constructor a scale SceneNode (little smaller)
GuardRandom::GuardRandom(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& guardName, const Ogre::Vector3& down, const Ogre::Vector3& up)
	:minX(down.x),minY(down.z),maxX(up.x),maxY(up.z),Guard(sceneManager,guardMesh, guardName, down){	
		mDirection=Ogre::Vector3::ZERO;
		sceneNode->scale(.8,.8,.8);
}
//-------------------------------------------------------------------------------------
///This function is setting random destination in guards bounds
bool GuardRandom::nextLocation(void){
	mDestination = getRandomPosition();  // next random position in boundary
	mDirection = mDestination - sceneNode->getPosition();
    mDistance = mDirection.normalise();
	return true;
}
//-------------------------------------------------------------------------------------
///Calling base update
void GuardRandom::update(const float delay){
	Guard::update(delay);	
}
//-------------------------------------------------------------------------------------
///Returns random vector3 between points X and Y
Ogre::Vector3 GuardRandom::getRandomPosition(void){
	float a = minX+(rand() % ((int)abs(maxX-minX)));
	float b = minY+(rand() % ((int)abs(maxY-minY)));
	return Ogre::Vector3(a,0,b);
}
//-------------------------------------------------------------------------------------