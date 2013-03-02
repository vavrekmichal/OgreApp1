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

	switch(type){
		case Line:	
			for(int i = 0; i< count; ++i){
				guards.push_back((std::shared_ptr<Guard>) new GuardLine( sceneManager, guardMesh, createName(groupName,i), positions));
				rotateDeque(positions);
			}
			break;
		case Follower:
			for(int i = 0; i< count; ++i){
				guards.push_back((std::shared_ptr<Guard>) new GuardFollower( sceneManager, guardMesh, createName(groupName,i), positions.at(0)));
				rotateDeque(positions);
			}
			break;
		case Cyclic:
			for(int i = 0; i< count; ++i){
				guards.push_back((std::shared_ptr<Guard>) new Guard( sceneManager, guardMesh, createName(groupName,i), positions));
				rotateDeque(positions);
			}
			break;
		case Random:
			for(int i = 0; i< count; ++i){
				guards.push_back((std::shared_ptr<Guard>) new GuardRandom(sceneManager,guardMesh, createName(groupName,i), positions.at(0), positions.at(1)));
				rotateDeque(positions);
			}
			break;
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
///Creates name from given group name and given order
std::string GuardGroup::createName(const std::string& s, int i){
	std::stringstream sstream;
	sstream<<s<<' '<<i;
	return sstream.str();
}
//-------------------------------------------------------------------------------------
///First makes last
void GuardGroup::rotateDeque(std::deque<Ogre::Vector3>& positions){
	Ogre::Vector3 temp = positions.front();  // this gets the front of the deque
	positions.pop_front();             // this removes the front of the deque
	positions.push_back(temp);
}
//-------------------------------------------------------------------------------------