#include "GuardGroup.h"
#include <sstream>
#include "GuardFollower.h"
#include "GuardRandom.h"
#include "GuardLine.h"
//-------------------------------------------------------------------------------------
GuardGroup::GuardGroup(void)
{
}
//-------------------------------------------------------------------------------------
///Main constuctor of this class. Here is creating specific (GuardType) type and count of guards
GuardGroup::GuardGroup(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& groupName, const int count, std::deque<Ogre::Vector3>& positions, const GuardType type){

	for(int i = 0; i< count; ++i){
		std::stringstream sstream;
		sstream<<groupName<<' '<<i;
		std::string s = sstream.str();
		switch(type){
		case Line:
			guards.push_back((std::shared_ptr<Guard>) new GuardLine( sceneManager, guardMesh, s, positions));
			break;
		case Follower:
			guards.push_back((std::shared_ptr<Guard>) new GuardFollower( sceneManager, guardMesh, s, positions.at(1)));
			break;
		case Cyclic:
			guards.push_back((std::shared_ptr<Guard>) new Guard( sceneManager, guardMesh, s, positions));
			break;
		case Random:
			guards.push_back((std::shared_ptr<Guard>) new GuardRandom(sceneManager,guardMesh, s, positions.at(0), positions.at(1)));
			break;
		}
			Ogre::Vector3 mDestination = positions.front();  // this gets the front of the deque
			positions.pop_front();             // this removes the front of the deque
			positions.push_back(mDestination);
	}
}
//-------------------------------------------------------------------------------------
GuardGroup::~GuardGroup(void)
{

}
//-------------------------------------------------------------------------------------
///update all guards in group
void GuardGroup::update(float delay){
	for(std::vector<std::shared_ptr<Guard>>::iterator it = guards.begin();
		it!=guards.end();
		++it){
			(*it)->update(delay);
	}
}
//-------------------------------------------------------------------------------------


