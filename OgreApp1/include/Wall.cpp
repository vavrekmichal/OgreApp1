#include "Wall.h"

//-------------------------------------------------------------------------------------
///Inicializetion and set direction based on isHorizontal (use roll and pitch)
Wall::Wall(Ogre::SceneManager* sceneManager, const std::string& wallName, const Ogre::Vector3& startPosition, bool isHorizontal)
{
	manager = sceneManager;
	name=wallName;
	mesh = "WoodPallet4.mesh"; //Wall will be made from this mesh
	position=startPosition; //players start position 
	entity = manager->createEntity(name,mesh);
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", position);
	sceneNode->attachObject(entity);

	if (!isHorizontal) {
		sceneNode->roll( Ogre::Degree(90));
	}else{
		sceneNode->pitch( Ogre::Degree(90));
	}
}

//-------------------------------------------------------------------------------------
Wall::~Wall(void)
{
	manager->destroyEntity(entity);
	manager->destroySceneNode(sceneNode);
}
//-------------------------------------------------------------------------------------