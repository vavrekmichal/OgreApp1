#ifndef __GuardGroup_h_
#define __GuardGroup_h_

#include "Guard.h"
#include <vector>
#include <deque>

enum GuardType {Cyclic, Random, Line, Follower}; //enum with types of guards

class GuardGroup
{
public:
	GuardGroup(void);
	GuardGroup(Ogre::SceneManager* sceneManager, const std::string& guardMesh, const std::string& groupName, const int count, std::deque<Ogre::Vector3>& positions, const GuardType type);
	~GuardGroup(void);
	void update(float delay);

private:
	std::vector<std::shared_ptr<Guard>> guards;

	std::string createName(const std::string& s, int i);
	void rotateDeque(std::deque<Ogre::Vector3>& positions);
};
#endif // #ifndef __GuardGroup_h_