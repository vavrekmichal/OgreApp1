#include "Guard.h"
#include "DieException.h"

const float	Guard::mWalkSpeed=35;  // The speed at which the object is moving
const std::string Guard::playerName = "Ninja";  // The name of hunting player
//-------------------------------------------------------------------------------------
Guard::Guard(void){
}
//-------------------------------------------------------------------------------------
///This constructor create guard with one setted position vector3
Guard::Guard(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName,const Ogre::Vector3& startPosition)
{
	manager = sceneManager;
	name=guardName;
	mesh=guardMesh; //mesh of players SceneNode (in this case is ninja.mesh)
	entity = manager->createEntity(name,mesh);
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", startPosition);
	entity->setCastShadows(true);
	sceneNode->attachObject(entity);
	mAnimationState = entity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	mDirection= Ogre::Vector3(0,0,0);
}
//-------------------------------------------------------------------------------------
///This constructor create guard with setted deque of vector3 which will be mWalkList
Guard::Guard(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName, std::deque<Ogre::Vector3>& positions){
	manager = sceneManager;
	name=guardName;
	mesh=guardMesh; //mesh of players SceneNode (in this case is ninja.mesh)
	entity = manager->createEntity(name,mesh);
	mWalkList= positions;
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", mWalkList.front());
	entity->setCastShadows(true);
	sceneNode->attachObject(entity);
	mAnimationState = entity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	mDirection= Ogre::Vector3(0,0,0);
}
//-------------------------------------------------------------------------------------
Guard::~Guard(void)
{
	manager->destroyEntity(entity);
	manager->destroySceneNode(sceneNode);
}
//-------------------------------------------------------------------------------------
///Here is control mWalkList and also there are setted vectors for next location
bool Guard::nextLocation(void){
	if (mWalkList.empty()){
		return false;
	}
	mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque
	mWalkList.push_back(mDestination);
    mDirection = mDestination - sceneNode->getPosition();
    mDistance = mDirection.normalise();
	return true;
}
//-------------------------------------------------------------------------------------
///This is main function of guards walking. Here is control if guard has some destination
///to go and setted animation Walk/Idle.
void Guard::update(const float delay){

	mAnimationState->addTime(delay);
	if (mDirection == Ogre::Vector3::ZERO){
        if (nextLocation()){
                // Set walking animation
			Ogre::Vector3 src = sceneNode->getOrientation() * Ogre::Vector3(1,0,0);
			Ogre::Quaternion quat = src.getRotationTo(mDirection);
			sceneNode->rotate(quat);
            mAnimationState = entity->getAnimationState("Walk");         
        }else{
			//Stay on position
			mAnimationState = entity->getAnimationState("Idle");
		}
	}else{//Guard is in motion
		if(!collision()){
			Ogre::Real move = mWalkSpeed * delay;
			mDistance -= move;
			if (mDistance <= 0.0f){                 
				sceneNode->setPosition(mDestination);
				mDirection = Ogre::Vector3(0,0,0);				
				// Set animation based on if the robot has another point to walk to. 
				goToNextLocation();
			}else{
				sceneNode->translate(mDirection * move);
			}
		}else{
			mDestination= sceneNode->getPosition();
			mDistance= .0f;
			goToNextLocation();
		}
	}
	mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
}
//-------------------------------------------------------------------------------------
///This function controls collision with other objects and mainly with player
bool Guard::collision(void){
	Ogre::Ray ray(sceneNode->getPosition(), getDirection(sceneNode->getOrientation()));
	Ogre::RaySceneQuery* mRaySceneQuery = manager->createRayQuery(ray);
	Ogre::RaySceneQueryResult result = mRaySceneQuery->execute();
	const float farfarAway = 15;

	for(Ogre::RaySceneQueryResult::iterator it= result.begin();
		it!=result.end();
		++it){
		
		if ((it->movable->getName() == playerName) && (it->distance < farfarAway * 5)) { //catch Ninja
			throw DieException("Hlidac "+name + "\nte polapil.");
		}
		if ((it->distance < farfarAway) && (it->distance > 0)) { //meet something else (Wall,Protector,...)
			return true;
		}
	}

	return false;
}
//-------------------------------------------------------------------------------------
///Translate quaternion into direction vector
 Ogre::Vector3 Guard::getDirection(const Ogre::Quaternion q) const{
	Ogre::Vector3 v(1, 0, 0); //facing in +z
	v = q * v;  //transform the vector by the objects rotation.
	return v;
}
//-------------------------------------------------------------------------------------
///Here is rotation of guard's sceneNode 
void Guard::goToNextLocation(void){
	if (!nextLocation()){
		// Set Idle animation                     
		mAnimationState = entity->getAnimationState("Idle");
	}else{
		// Rotation Code will go here later
		Ogre::Vector3 src = sceneNode->getOrientation() * Ogre::Vector3(1,0,0);
		if ((1.0f + src.dotProduct(mDirection)) < .0001f) {
			sceneNode->yaw(Ogre::Degree(180));						
		}else{
			Ogre::Quaternion quat = src.getRotationTo(mDirection);
			sceneNode->rotate(quat);
		}
	}
}
//-------------------------------------------------------------------------------------
