#ifndef __Guard_h_
#define __Guard_h_

#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>

class Guard
{
public:
	Guard(void);
	Guard(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName,const Ogre::Vector3& startPosition);
	Guard(Ogre::SceneManager* sceneManager,const std::string& guardMesh,const std::string& guardName, std::deque<Ogre::Vector3>& positions);
	~Guard(void);
	virtual void update(float delay);
	virtual bool nextLocation(void);

protected:
	virtual bool collision(void);
	virtual void goToNextLocation(void);
	Ogre::Vector3 getDirection(const Ogre::Quaternion& q) const;
	
	Ogre::SceneManager* manager;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity* entity;
	std::string name; //Guard's name 
	Ogre::AnimationState* mAnimationState; //The AnimationState the moving object
	
	std::string mesh; //Guard's mesh (in this case is robot1.mesh)
	
	Ogre::Real mDistance;                  // The distance the object has left to travel
    Ogre::Vector3 mDirection;              // The direction the object is moving
    Ogre::Vector3 mDestination;			   // The destination to go
	
	static const float inDestination;
	static const int farFarAway;
	const Ogre::Vector3 directionVector;
	const float mWalkSpeed;  // The speed at which the object is moving
	const std::string playerName;  // The name of hunting player
	std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to
};

#endif // #ifndef __Guard_h_

