#include "Target.h"
#include <stdio.h>
#include <stdlib.h>

const int Target::pickUpDistance= 700;
//-------------------------------------------------------------------------------------
///Inicialization of sceneNode and entity
Target::Target(Ogre::SceneManager* mSceneManager, const std::string& newName, const Ogre::Vector3& setPosition, Ogre::SceneNode* setCollector)
{
	mesh = "ogrehead.mesh";
	manager = mSceneManager;
	name = newName;
	collector = setCollector;
	position = setPosition;
	entity = manager->createEntity(name, mesh);
	sceneNode = manager->getRootSceneNode()->createChildSceneNode(name + "Node", position);
	sceneNode->attachObject(entity);
	entity->setCastShadows(true);	
}
//-------------------------------------------------------------------------------------
Target::~Target(void)
{
	manager->destroyEntity(entity);
	manager->destroySceneNode(sceneNode);
}
//-------------------------------------------------------------------------------------
///Just rotote on a place
void Target::update(void){
	sceneNode->yaw(Ogre::Degree( .5f));
}
//-------------------------------------------------------------------------------------
///This function is checking distance from player node. If target is near, so target is 
///picked up.
bool Target::checkDistanceFromCollector(void){
	Ogre::Vector3 i = collector->getPosition();
	Ogre::Vector3 j = sceneNode->getPosition();
	double axisX = abs(i.x -j.x);
	double axisY = abs(i.z -j.z);
	double distanceSquered = axisX*axisX+axisY*axisY; //distance is squered -> no reason to make square root (difficul)

	if (distanceSquered < pickUpDistance) {
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------
