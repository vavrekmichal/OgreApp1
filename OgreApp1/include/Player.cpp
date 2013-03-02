#include "Player.h"
#include "../res/resource.h"
#include <string>
#include "OgreApp1.h"

//-------------------------------------------------------------------------------------
///Creates player and set first animation Idle2
Player::Player(Ogre::SceneManager* sceneManager, const std::string& playerMesh, const std::string& playerName, const Ogre::Vector3& startPosition)
	:mWalkSpeed(200),
	deathTimeDiff(0.03),
	deathAnimeTime(0.015),
	farFarAway(50),
	deathTime(1)
{
	manager = sceneManager;
	name=playerName;
	mWalking=false; //bool to detect if object walking or stay
	death=false; //bool to detect if object is alive or death
	mesh=playerMesh; //mesh of players SceneNode (in this case is ninja.mesh)
	position=startPosition; //players start position 
	entity = manager->createEntity(name,mesh);
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", position);
	entity->setCastShadows(true);
	sceneNode->attachObject(entity);
	mAnimationState = entity->getAnimationState("Idle2");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	goingBack=false;
	goingForward=false;

}
//-------------------------------------------------------------------------------------
Player::~Player(void)
{
	manager->destroyEntity(entity);
	manager->destroySceneNode(sceneNode);
}
//-------------------------------------------------------------------------------------
///Checkes collision in going direction and translate SceneNode
void Player::update(float f){
	Ogre::Vector3 playerMove = Ogre::Vector3(0,0,0);
	mWalking = false;
	if(goingForward && !collision(true)){
		playerMove.z -= mWalkSpeed;
		mWalking=true;
	}
	if(goingBack && !collision(false)){
		playerMove.z += mWalkSpeed;
		mWalking=true;
	}
	sceneNode->translate(playerMove*f, Ogre::Node::TS_LOCAL); 

	walk(f);
}
//-------------------------------------------------------------------------------------
///control player status (walk,stay,death) and set right animation
void Player::walk(float f){
	
	if (!death) {
		mAnimationState->addTime(f*2);
		if (!mWalking) { //Player's staying
			mAnimationState = entity->getAnimationState("Idle3");
		} else {//Player's in motion          
			mAnimationState = entity->getAnimationState("Walk");
		}
	} else { //Player's death
		mAnimationState->addTime(deathAnimeTime); //just one animation
		mAnimationState = entity->getAnimationState("Death1");
		deathTime-=deathTimeDiff;
		if(deathTime<0){
			OgreApp1::endGame();
		}
	}
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);	
}
//-------------------------------------------------------------------------------------
///controls collision in given direction (true-front false-back)
bool Player::collision(bool goAhead){
	Ogre::Ray ray = Ogre::Ray(sceneNode->getPosition(), getDirection(sceneNode->getOrientation(),goAhead));
	Ogre::RaySceneQuery* mRaySceneQuery = manager->createRayQuery(ray);
	Ogre::RaySceneQueryResult result = mRaySceneQuery->execute();
	
	for(Ogre::RaySceneQueryResult::iterator it = result.begin(); it != result.end() ; ++it){
		if((it->distance < farFarAway)&& (it->distance > 0)){
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------
///transform quaternion in given direction
Ogre::Vector3 Player::getDirection(const Ogre::Quaternion& q, bool goAhead) {
	Ogre::Vector3 v = Ogre::Vector3(0, 0, 0);
	if(goAhead){
		v =  Ogre::Vector3(0, 0, -1);
	}else{
		v = Ogre::Vector3(0, 0, 1);
	}
	v = q * v;  //transform the vector by the objects rotation.
	return v;
}
//-------------------------------------------------------------------------------------
Ogre::SceneNode* Player::getSceneNode(void){
	return sceneNode;
}
//-------------------------------------------------------------------------------------
void Player::die(void){
	death=true;
}
//-------------------------------------------------------------------------------------
