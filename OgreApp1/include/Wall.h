#ifndef __Wall_h_
#define __Wall_h_

#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <string>


class Wall
{
public:
	Wall(Ogre::SceneManager* sceneManager, const std::string& wallName, const Ogre::Vector3& startPosition, bool isHorizontal);
	~Wall(void);

protected:
	Ogre::SceneNode* sceneNode; //SceneNode of this Wall
	Ogre::Entity* entity; //Entity of this Wall
	std::string name; //name of this Wall
	std:: string mesh; //Wall will be made from this mesh
	Ogre::Vector3 position; //position of the Wall 
	Ogre::SceneManager* manager; //SceneManager from main class -> to inicialized Entity and SceneNode
};

#endif // #ifndef __Wall_h_
