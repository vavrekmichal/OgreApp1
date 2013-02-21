#ifndef __Target_h_
#define __Target_h_

#include <string>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

class Target
{
public:
	Target(Ogre::SceneManager* mSceneManager, const std::string& newName, const Ogre::Vector3& setPosition, Ogre::SceneNode* setCollector);
	~Target(void);
	void update(void);
	bool checkDistanceFromCollector(void);

protected:
	Ogre::SceneNode* sceneNode; //SceneNode of this Target
	Ogre::Entity* entity; //Entity of this Target
	std::string name; //name of this Taget
	std::string mesh; //mesh for the Target, can be rewrite in constructor
	Ogre::Vector3 position; //position of the Target 
	Ogre::SceneManager* manager; //SceneManager from main class -> to inicialized Entity and SceneNode
	Ogre::SceneNode* collector; // Players SceneNode. In this case is Ninja (can pick up target)
	static const int pickUpDistance;
};
#endif // #ifndef __Target_h_
