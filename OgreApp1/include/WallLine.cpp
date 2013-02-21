#include "WallLine.h"
#include <sstream>

//-------------------------------------------------------------------------------------
///Create given number of wall in given direction
WallLine::WallLine(Ogre::SceneManager* manager, const int x, const int y, const Ogre::Vector2& v, const MyDirection& m)
{
	int a = 0;
	int b = 0;
	float c =160;
		
	bool isHorizontal = false;
	if(m ==Left || m == Right){
		isHorizontal= true;
	}

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			switch (m) {
				case Left:
					a += -300;
					break;
				case Right:
					a += 300;
					break;
				case Front:
					b += -300;
					break;
				case Back:
					b += 300;
					break;
				default:
					break;
			}
			Ogre::Real posX= v.x + a;
			Ogre::Real posZ= v.y + b;

			Ogre::Vector3 posVec = Ogre::Vector3(posX, c, posZ);
			std::stringstream ss;
			ss<<"name" << a << b << c << genRandom(5);
			std::shared_ptr<Wall> helpWall = (std::shared_ptr<Wall>) new Wall(
				manager, 
				ss.str(), 
				posVec,
				isHorizontal);
			wallVector.push_back(helpWall);
					
		}
		a = 0; b = 0;
		c += 300;
	}
}
//-------------------------------------------------------------------------------------
///using random string like prevention of collision in entity and sceneNode register
std::string WallLine::genRandom( const size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str;
    str.resize( length );
    std::generate_n( str.begin(), length, randchar );
    return str;
}
//-------------------------------------------------------------------------------------
WallLine::~WallLine(void)
{
}
//-------------------------------------------------------------------------------------