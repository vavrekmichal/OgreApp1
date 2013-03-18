#ifndef __Player_h_
#define __Player_h_

#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>

class Player
{
public:
	Player(Ogre::SceneManager* sceneManager, const std::string& playerMesh, const std::string& playerName, const Ogre::Vector3& startPosition);
	~Player(void);
	void update(float f);
	Ogre::SceneNode* getSceneNode(void);

	bool goingForward;
    bool goingBack;
	void die(void);

protected:

	void walk(float f);
	bool collision(bool goAhead);
	Ogre::Vector3 getDirection(const Ogre::Quaternion& q, bool goAhead);

	Ogre::SceneNode* sceneNode;
	Ogre::Entity* entity;
	std::string name; //name of the Player
	Ogre::AnimationState* mAnimationState; //The AnimationState the moving object
	bool mWalking; //bool to detect if object walking or stay
	bool death; //bool to detect if object is alive or death
	std::string mesh; //mesh of players SceneNode (in this case is ninja.mesh)
	Ogre::Vector3 position; //players start position 
	Ogre::SceneManager* manager;

	const float mWalkSpeed;  // The speed at which the object is moving
	float deathTime;   //duration of death animation;
	const float deathTimeDiff;   //duration of death animation;
	const float deathAnimeTime;
	const int farFarAway;
};

#endif // #ifndef __Player_h_

